#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>

#include "bfhttpecho.h"
#include "http_echo.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("bfhttpecho");
    QCoreApplication::setApplicationVersion(BFHTTPECHO_VERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription("bfhttpecho is a testing tool for HTTP clients.");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOptions({
        {{"v", "verbose"},
            QCoreApplication::translate("main", "Be verbose.")},
        {{"p", "port"},
            QCoreApplication::translate("main", "The port to listen on (default 8080)."),
            QCoreApplication::translate("main", "port")},
    });

    parser.process(app);

    unsigned int port = 8080;

    if (parser.isSet("port")) {
        port = parser.value("port").toUInt();
    }

    HttpEcho httpEcho(port);

    httpEcho.listen();

    return app.exec();
}
