#include "http_echo.h"
#include "responders/Responder.h"

#include "responders/GetResponder.h"

#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

struct HttpEcho::Impl
{
    unsigned int port;
    QTcpServer* server;
    QList<Responder*> responders;
};

HttpEcho::HttpEcho(unsigned int port, QObject *parent /* = 0 */) :
    _d(std::make_unique<Impl>()) {
    _d->port = port;
    _d->server = new QTcpServer(this);

    _d->responders.append(new GetResponder()); // Memory leak
}

HttpEcho::~HttpEcho() {

}

void HttpEcho::listen() {

    qDebug() << "Listening on" << _d->port;

    connect(_d->server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!_d->server->listen(QHostAddress::Any, _d->port)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started!";
    }
}

struct Request
{
    bool error = false;
    QString http_version;
    QString verb;
    QString route;
    QList<QPair<QString, QString>> headers;
    QByteArray body;
};

Request parseHttpRequest(QByteArray request)
{
    Request parsed_request;

    auto request_str = request.toStdString();

    auto header_length = request.indexOf("\r\n\r\n");

    auto header = request.left(header_length);
    auto body = request.mid(header_length+4);

    auto headers = QString::fromLatin1(header).split("\r\n");

    auto http_header = headers.first();
    QRegularExpression http_header_parser("^(\\S*) (.*) HTTP/(.*)");
    auto matches = http_header_parser.match(http_header);

    if (!matches.isValid()) {
        parsed_request.error = true;
        return parsed_request;
    }

    headers.removeAt(0);

    QRegularExpression header_parser("^([^:]*): (.*)$");

    for (const auto& header : headers) {
    auto h = header.toStdString();
        auto match = header_parser.match(header);

        if (!match.isValid()) {
            parsed_request.error = true;
            return parsed_request;
        }

        auto s1 = match.captured(1).toStdString();
        auto s2 = match.captured(2).toStdString();

        parsed_request.headers.append(qMakePair(match.captured(1), match.captured(2)));
    }

    parsed_request.verb = matches.captured(1);
    parsed_request.route = matches.captured(2);
    parsed_request.http_version = matches.captured(3);
    parsed_request.body = body;

    return parsed_request;
}

void HttpEcho::newConnection() {
    QTcpSocket *socket = _d->server->nextPendingConnection();

    socket->waitForConnected(1000);
    socket->waitForReadyRead(1000);

    QByteArray request = socket->readAll();

    auto parsed_request = parseHttpRequest(request);

    qDebug() << parsed_request.verb << parsed_request.http_version << parsed_request.route;

    QJsonObject headers;

    for (auto const& header : parsed_request.headers) {
        headers.insert(header.first, header.second);
    }

    QJsonObject answer;
    answer.insert("headers", headers);

    QByteArray data;
    data.append(QJsonDocument(answer).toJson(QJsonDocument::Indented));

    socket->write("HTTP/1.1 200 OK\r\n");
    socket->write("Server: bfhttpecho \r\n");
    socket->write(QString("Content-Length: %1\r\n").arg(data.size()).toLatin1());
    socket->write("Connection: close\r\n");
    socket->write("Content-Type: application/json\r\n");
    socket->write("\r\n");
    socket->write(data);
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();

    if (parsed_request.route.startsWith("/kill")) {
        qApp->exit(0);
    }
}
