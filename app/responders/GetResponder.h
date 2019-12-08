//
// Created by Robert Jakob on 08.12.19.
//

#ifndef BFHTTPECHO_GETRESPONDER_H
#define BFHTTPECHO_GETRESPONDER_H

#include "Responder.h"

class GetResponder : public Responder {
public:

    bool matches(const QString& verb, const QString& route, const Headers& headers) const override;
    Response run(const QString& verb, const QString& route, const Headers& headers) const override;

};


#endif //BFHTTPECHO_GETRESPONDER_H
