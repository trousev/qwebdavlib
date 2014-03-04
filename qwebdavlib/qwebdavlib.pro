QT       += network xml

# for a qwebdavlib without support for GUI
QT       -= gui

TARGET = qwebdav
TEMPLATE = lib

DESTDIR=../lib
# Enable DEBUG output with qDebug()
DEFINES += DEBUG_WEBDAV

# Enable extended WebDAV properties (see QWebDavItem.h/cpp)
#DEFINES += QWEBDAVITEM_EXTENDED_PROPERTIES

# DO NOT REMOVE - REQUIRED BY qwebdav_global.h
DEFINES += QWEBDAV_LIBRARY

include(qwebdavlib.pri)

OTHER_FILES += \
    CHANGES \
    LICENSE \
    README
