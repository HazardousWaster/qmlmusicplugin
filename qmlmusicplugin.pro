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
SOURCES += mpris2playerproxy.cpp mprisplayerproxy.cpp mprissource.cpp mprisstatus.cpp player.cpp qmlmusicplugin.cpp source.cpp mpris2source.cpp auxsource.cpp
HEADERS += mpris2playerproxy.h mpris2source.h mprisplayerproxy.h mprissource.h mprisstatus.h player.h qmlmusicplugin.h source.h vlcsource.h spotifysource.h bansheesource.h auxsource.h
#RESOURCES += contacts.qrc
sources.files = $$SOURCES $$HEADERS $$RESOURCES qmlmusicplugin.pro
sources.path = .
target.path += music

INSTALLS += sources target
