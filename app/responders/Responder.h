//
// Created by Robert Jakob on 08.12.19.
//

#ifndef BFHTTPECHO_RESPONDER_H
#define BFHTTPECHO_RESPONDER_H

#include <QString>
#include <QList>
#include <QPair>

class Responder {
public:
    using Headers = QList<QPair<QString, QString>>;

    struct Response
    {
        Headers headers;
        QByteArray body;
    };

    virtual ~Responder() {}

    virtual bool matches(const QString& verb, const QString& route, const Headers& headers) const = 0;
    virtual Response run(const QString& verb, const QString& route, const Headers& headers) const = 0;
};


#endif //BFHTTPECHO_RESPONDER_H
