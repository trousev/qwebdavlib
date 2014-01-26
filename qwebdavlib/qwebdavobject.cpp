#include "qwebdavobject.h"
#include "qwebdav.h"
#include "qwebdavdirparser.h"

WebDavProvider::WebDavProvider(QUrl url)
    :_url(url)
{
    QWebdav::QWebdavConnectionType conntype = QWebdav::HTTP;
    int port = 80;
    if(url.scheme().toLower() == "https")
    {
        conntype = QWebdav::HTTPS;
        port = 443;
    }
    if(url.port() > 0) port = url.port();
    QString login = url.userName();
    QString password = url.password();
    QString host = url.host();
    QString path = url.path();

    _webdav.setConnectionSettings(conntype, host, path, login, password, port);
}

void WebDavProvider::exitLoop()
{
    loop.exit();
}

QUrl WebDavProvider::url(QString path)
{
    QUrl u = _url;
    u.setPath(u.path()+path);
    return u;
}

QList<QWebdavItem>  WebDavProvider::list(QString path)
{
    if(!path.endsWith("/"))
        path += "/";
    QWebdavDirParser * parser = new QWebdavDirParser;
    connect(parser, SIGNAL(finished()), this, SLOT(exitLoop()));
    if(!parser->listDirectory(&_webdav, path))
        return QList<QWebdavItem> ();
    loop.exec();
    QList<QWebdavItem> ans;
    foreach(QWebdavItem item, parser->getList())
    {
        ans << item;
    }
    delete parser;
    return ans;
}

QByteArray WebDavProvider::download(QString path)
{
    QNetworkReply * reply =  _webdav.get(path);
    connect(reply, SIGNAL(finished()), this, SLOT(exitLoop()));
    loop.exec();
    QByteArray ans = reply->readAll();
    reply->deleteLater();
    return ans;
}

bool WebDavProvider::upload(QString path, QByteArray data)
{
    QNetworkReply * reply = _webdav.put(path, data);
    connect(reply, SIGNAL(finished()), this, SLOT(exitLoop()));
    loop.exec();
    if(reply->readAll().contains("error")) return false;
    reply->deleteLater();
    return true;
}


bool WebDavProvider::mkdir(QString path)
{
    QNetworkReply * reply = _webdav.mkdir(path);
    connect(reply, SIGNAL(finished()), this, SLOT(exitLoop()));
    loop.exec();
    if(reply->readAll().contains("error")) return false;
    reply->deleteLater();
    return true;
}
bool WebDavProvider::remove(QString path)
{
    QNetworkReply * reply = _webdav.remove(path);
    connect(reply, SIGNAL(finished()), this, SLOT(exitLoop()));
    loop.exec();
    if(reply->readAll().contains("error")) return false;
    reply->deleteLater();
    return true;
}

/////////////////////////////////////////////////////////////

QWebdavObject::QWebdavObject(QSharedPointer<WebDavProvider> provider, QString path, QWebdavItem item )
{
    _provider = provider;
    _path = path;
    _item = item;
    if(item.name().isEmpty())
        _type = AbstractPath;
    else
        _type=((item.isDir())?Directory:File);
}

QWebdavObject::QWebdavObject(QUrl url)
{
    _provider = QSharedPointer<WebDavProvider>(new WebDavProvider(url));
    _path = "/";
    _item = QWebdavItem();
    _type = AbstractPath;
}

QByteArray QWebdavObject::content()
{
    return _provider->download(_path);
}

bool QWebdavObject::setContent(QByteArray content)
{
    return _provider->upload(_path, content);
}

QString QWebdavObject::name()
{
    if(_item.name().isEmpty())
        return _path;
    return _item.name();
}

QWebdavObject::Type QWebdavObject::type()
{
    return _type;
}

bool QWebdavObject::isFile()
{
    return _type == File;
}

bool QWebdavObject::isDir()
{
    return _type == Directory;
}

QList<QWebdavObject> QWebdavObject::list()
{
    QList<QWebdavObject> ans;
    foreach(QWebdavItem item, _provider->list(_path))
    {
        ans << QWebdavObject(_provider, _path+"/"+item.name(), item);
    }
    return ans;
}


QWebdavObject QWebdavObject::child(QString path)
{
    return QWebdavObject(_provider, _path+"/"+path);
}
bool QWebdavObject::mkdir(QString path)
{
    _provider->mkdir(_path+"/"+path);
}

bool QWebdavObject::remove()
{
    _provider->remove(_path);
}

QUrl QWebdavObject::url()
{
    return _provider->url(_path);
}
