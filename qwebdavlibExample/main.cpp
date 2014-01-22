#include <QtCore/QCoreApplication>

#include "../qwebdavlib/qwebdavobject.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Input DAV URL: ";
    std::string s;
    std::cin >> s;

    QWebdavObject obj(QUrl(QString::fromStdString(s)));
    foreach(QWebdavObject obj, obj.list())
    {
        qDebug() << obj.name();
    }

}
