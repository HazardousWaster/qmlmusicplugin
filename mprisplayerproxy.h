/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -N -c MprisPlayerProxy -p mprisplayerproxy.h:mprisplayerproxy.cpp -i mprisstatus.h introspection/vlc_player.xml org.freedesktop.MediaPlayer
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MPRISPLAYERPROXY_H_1323804090
#define MPRISPLAYERPROXY_H_1323804090

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "mprisstatus.h"

/*
 * Proxy class for interface org.freedesktop.MediaPlayer
 */
class MprisPlayerProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.MediaPlayer"; }

public:
    MprisPlayerProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~MprisPlayerProxy();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<int> GetCaps()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetCaps"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> GetMetadata()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetMetadata"), argumentList);
    }

    inline QDBusPendingReply<MprisStatus> GetStatus()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("GetStatus"), argumentList);
    }

    inline QDBusPendingReply<> Next()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Next"), argumentList);
    }

    inline QDBusPendingReply<> Pause()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Pause"), argumentList);
    }

    inline QDBusPendingReply<> Play()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Play"), argumentList);
    }

    inline QDBusPendingReply<int> PositionGet()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("PositionGet"), argumentList);
    }

    inline QDBusPendingReply<> PositionSet(int in0)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("PositionSet"), argumentList);
    }

    inline QDBusPendingReply<> Prev()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Prev"), argumentList);
    }

    inline QDBusPendingReply<> Repeat(bool in0)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("Repeat"), argumentList);
    }

    inline QDBusPendingReply<> Stop()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Stop"), argumentList);
    }

    inline QDBusPendingReply<int> VolumeGet()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("VolumeGet"), argumentList);
    }

    inline QDBusPendingReply<> VolumeSet(int in0)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(in0);
        return asyncCallWithArgumentList(QLatin1String("VolumeSet"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void CapsChange(int in0);
    void StatusChange(MprisStatus in0);
    void TrackChange(const QVariantMap &in0);
};

#endif