#ifndef QWEBDAVOBJECT_H
#define QWEBDAVOBJECT_H

#include <QUrl>
#include <QSharedPointer>
#include "qwebdav.h"
#include <QObject>
#include <QEventLoop>
#include <qwebdavdirparser.h>
class WebDavProvider: public QObject
{
    Q_OBJECT

public:
    explicit WebDavProvider(QUrl url);
    QList<QWebdavItem> list(QString path="/");
    QByteArray download(QString path);
    bool upload(QString path, QByteArray data);
    bool mkdir(QString path);
    bool remove(QString path);

private:
    QWebdav _webdav;
    QEventLoop loop;
private slots:
    void exitLoop();

};

class QWEBDAVSHARED_EXPORT QWebdavObject
{
    friend class WebDavProvider;
    QWebdavObject(QSharedPointer<WebDavProvider> provider, QString path, QWebdavItem item = QWebdavItem());
public:

    enum Type
    {
        AbstractPath, File, Directory
    };

    QWebdavObject(QUrl url);

    QByteArray content();
    bool setContent(QByteArray content);

    QString name();
    Type type();
    bool isFile();
    bool isDir();
    QList<QWebdavObject> list();
    QWebdavObject child(QString path);


private:
    QString _path;
    QWebdavItem _item;
    QSharedPointer<WebDavProvider> _provider;
    Type _type;
};

#endif // QWEBDAVDIR_H
