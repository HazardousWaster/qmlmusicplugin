TEMPLATE = lib
TARGET = qmlmusicplugin
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += qt plugin qdbus qtextras
QT += declarative
DESTDIR = music

QMAKE_GCC = colorgcc
QMAKE_GXX = colorgcc

# Input
SOURCES += sourcemanager.cpp mpris2tracklistproxy.cpp mprisrootproxy.cpp mpris2rootproxy.cpp mpris2playerproxy.cpp mprisplayerproxy.cpp mprissource.cpp mprisstatus.cpp player.cpp qmlmusicplugin.cpp source.cpp mpris2source.cpp auxsource.cpp tracksource.cpp
HEADERS += sourcemanager.h sourceoption.h mpris2tracklistproxy.h mprisrootproxy.h mpris2rootproxy.h mpris2playerproxy.h mpris2source.h mprisplayerproxy.h mprissource.h mprisstatus.h player.h qmlmusicplugin.h source.h auxsource.h tracksource.h papafactory/details.h papafactory/factory.h papafactory/papa_exception.h papafactory/phactory.h papafactory/singleton.h papafactory/staticfactory.h
#RESOURCES += contacts.qrc
sources.files = $$SOURCES $$HEADERS $$RESOURCES qmlmusicplugin.pro
sources.path = .
target.path += music

INSTALLS += sources target
