#include <iostream>

#include <QCoreApplication>

#include "bfhttpecho.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    std::cout << "bfhttpecho " << BFHTTPECHO_VERSION << std::endl;

    return app.exec();
}
