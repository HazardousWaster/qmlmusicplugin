/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -N -c Mpris2TrackListProxy -p mpris2tracklistproxy.h:mpris2tracklistproxy.cpp introspection/clementine_all.xml org.mpris.MediaPlayer2.TrackList
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MPRIS2TRACKLISTPROXY_H_1324197705
#define MPRIS2TRACKLISTPROXY_H_1324197705

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.mpris.MediaPlayer2.TrackList
 */
class Mpris2TrackListProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.mpris.MediaPlayer2.TrackList"; }

public:
    Mpris2TrackListProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~Mpris2TrackListProxy();

    Q_PROPERTY(bool CanEditTracks READ canEditTracks)
    inline bool canEditTracks() const
    { return qvariant_cast< bool >(property("CanEditTracks")); }

    Q_PROPERTY(QList<QDBusObjectPath> Tracks READ tracks)
    inline QList<QDBusObjectPath> tracks() const
    { return qvariant_cast< QList<QDBusObjectPath> >(property("Tracks")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> AddTrack(const QString &Uri, const QDBusObjectPath &AfterTrack, bool SetAsCurrent)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(Uri) << qVariantFromValue(AfterTrack) << qVariantFromValue(SetAsCurrent);
        return asyncCallWithArgumentList(QLatin1String("AddTrack"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> GetTracksMetadata(const QList<QDBusObjectPath> &TrackIds)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(TrackIds);
        return asyncCallWithArgumentList(QLatin1String("GetTracksMetadata"), argumentList);
    }

    inline QDBusPendingReply<> GoTo(const QDBusObjectPath &TrackId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(TrackId);
        return asyncCallWithArgumentList(QLatin1String("GoTo"), argumentList);
    }

    inline QDBusPendingReply<> RemoveTrack(const QDBusObjectPath &TrackId)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(TrackId);
        return asyncCallWithArgumentList(QLatin1String("RemoveTrack"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void TrackAdded(const QVariantMap &Metadata, const QDBusObjectPath &AfterTrack);
    void TrackListReplaced(const QList<QDBusObjectPath> &Tracks, const QDBusObjectPath &CurrentTrack);
    void TrackMetadataChanged(const QDBusObjectPath &TrackId, const QVariantMap &Metadata);
    void TrackRemoved(const QDBusObjectPath &TrackId);
};

#endif
