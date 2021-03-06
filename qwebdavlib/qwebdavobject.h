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
    friend class QWebdavObject;
public:
    explicit WebDavProvider(QUrl url);
    QList<QWebdavItem> list(QString path="/");
    QByteArray download(QString path);
    bool upload(QString path, QByteArray data);
    bool mkdir(QString path);
    bool remove(QString path);
    bool rename(QString path, QString newPath);
    QUrl url(QString path);

private:
    QWebdav _webdav;
    QEventLoop loop;
    QUrl _url;
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
        Null, AbstractPath, File, Directory
    };

    QWebdavObject(QUrl url);
    QWebdavObject();

    QByteArray content();
    bool setContent(QByteArray content);

    QUrl url();
    QString name();
    Type type();
    bool isFile();
    bool isDir();
    bool isNull();
    QList<QWebdavObject> list();
    QWebdavObject child(QString path);
    bool mkdir(QString path);
    bool remove();
    bool renameTo(QString newPath);
    QDateTime lastModified();

    QWebdav * engine() { return &(_provider->_webdav); }

private:
    QString _path;
    QWebdavItem _item;
    QSharedPointer<WebDavProvider> _provider;
    Type _type;
};

#endif // QWEBDAVDIR_H
