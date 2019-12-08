//
// Created by Robert Jakob on 08.12.19.
//

#include "GetResponder.h"

bool GetResponder::matches(const QString& verb, const QString &route, const Responder::Headers &headers) const {
    return verb == "GET";
}

Responder::Response GetResponder::run(const QString& verb, const QString &route, const Responder::Headers &headers) const {
    Response response;
    response.body = "{}";
    response.headers.append(qMakePair(QString("Content-Type"), QString("application/json")));

    return response;
}
