/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -N -c MprisPlayerProxy -p mprisplayerproxy.h:mprisplayerproxy.cpp -i mprisstatus.h introspection/vlc_player.xml org.freedesktop.MediaPlayer
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "mprisplayerproxy.h"

/*
 * Implementation of interface class MprisPlayerProxy
 */

MprisPlayerProxy::MprisPlayerProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

MprisPlayerProxy::~MprisPlayerProxy()
{
}
