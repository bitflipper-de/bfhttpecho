#pragma once

#include <QObject>
#include <memory>

class HttpEcho : public QObject
{
    Q_OBJECT
public:
    explicit HttpEcho(unsigned int port, QObject *parent = 0);
    virtual ~HttpEcho();

    void listen();

private slots:
    void newConnection();

private:
    struct Impl;
    std::unique_ptr<Impl> _d;
};