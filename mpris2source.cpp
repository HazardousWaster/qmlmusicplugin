#include "mpris2source.h"
#include "mpris2playerproxy.h"

QList<SourceOption*> Mpris2Source::getSourceOptions()
{
	QList<SourceOption*> options;

	QDBusReply<QStringList> reply = QDBusConnection::sessionBus().interface()->registeredServiceNames();
	if (!reply.isValid()) {
		qDebug() << "Error:" << reply.error().message();
	}
	
	foreach (QString serviceName, reply.value())
	{
		if (serviceName.startsWith("org.mpris.MediaPlayer2"))
		{
			QByteArray ba = serviceName.toLocal8Bit();

			Mpris2RootProxy *rootProxy = new Mpris2RootProxy(ba.data(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										NULL);

			QString fullName = rootProxy->identity()  + " (MPRIS2)";
			
			QVariantMap params;
			params.insert("serviceName", serviceName);
			SourceOption *option = new SourceOption(fullName, "mpris2source", params);
			options.append(option);
		}
	}
	
	return options;
}

Mpris2Source::Mpris2Source(QVariantMap params)
{
	QString serviceName = params.value("serviceName").toString();

	QByteArray ba = serviceName.toLocal8Bit();

	m_playerProxy = new Mpris2PlayerProxy(ba.data(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	m_rootProxy = new Mpris2RootProxy(ba.data(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	m_trackListProxy = new Mpris2TrackListProxy(ba.data(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	name = m_rootProxy->identity()  + " (MPRIS2)";

	m_dbusInterface = new QDBusInterface(serviceName, "/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", QDBusConnection::sessionBus(), static_cast<QObject*>(this));
}

Mpris2Source::Mpris2Source(QString serviceName)
{
	QByteArray ba = serviceName.toLocal8Bit();

	m_playerProxy = new Mpris2PlayerProxy(ba.data(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	m_rootProxy = new Mpris2RootProxy(ba.data(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	m_trackListProxy = new Mpris2TrackListProxy(ba.data(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	name = m_rootProxy->identity()  + " (MPRIS2)";

	m_dbusInterface = new QDBusInterface(serviceName, "/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", QDBusConnection::sessionBus(), static_cast<QObject*>(this));
}

void Mpris2Source::enable()
{
	m_playerProxy->PlayPause();
	
	QStringList matchArgs;
    matchArgs << "org.mpris.MediaPlayer2.Player";
	QDBusConnection::sessionBus().connect(m_dbusInterface->service(),
										m_dbusInterface->path(),
										m_dbusInterface->interface(),
										"PropertiesChanged",
										matchArgs,
										QString(), // signature
										this,
										SLOT(propertiesChanged(QString,QVariantMap,QStringList)));

	QVariantMap qMap3 = m_playerProxy->metadata();
	QVariantMap::Iterator it;
	for (it = qMap3.begin(); it != qMap3.end(); it++)
	{
		qDebug() << it.key() << "\t\t" << it.value().typeName() << "\t\t" << it.value().toString();
	}

	parseMetadata(m_playerProxy->metadata());
	
	playStatus = parsePlaybackStatus(m_playerProxy->playbackStatus());
	repeatStatus = parseLoopStatus(m_playerProxy->loopStatus());
	shuffleStatus = m_playerProxy->shuffle();

	//QList<QDBusObjectPath> trackList = m_trackListProxy->tracks();
	//qDebug() << "yellow" << trackList.count();
	//QVariantMap tracksMetaData = m_trackListProxy->GetTracksMetadata(trackList);
	//qDebug() << tracksMetaData;
	//qDebug() << trackList;
}

void Mpris2Source::disable()
{
	m_playerProxy->Stop();
}

bool Mpris2Source::checkValid()
{
	qDebug() << "Checking: " << name;
	QString test = m_rootProxy->identity();
	qDebug() << "result: " << test;
	return name == test;
}

void Mpris2Source::playpause()
{	
	m_playerProxy->PlayPause();
}

void Mpris2Source::toggleShuffle()
{
	qDebug() << "Setting shuffle to: " << (shuffleStatus ? "false" : "true");
	m_playerProxy->setShuffle(!shuffleStatus);
}

void Mpris2Source::toggleRepeat()
{
	switch (repeatStatus)
	{
	case REPEAT_NONE:
		m_playerProxy->setLoopStatus("Playlist");
		break;
	case REPEAT_ALL:
		m_playerProxy->setLoopStatus("Track");
		break;
	case REPEAT_SINGLE:
		m_playerProxy->setLoopStatus("None");
		break;
	}
}

QTime Mpris2Source::position()
{
	/*QDBusPendingReply<int> reply = m_playerProxy->PositionGet();
	reply.waitForFinished();	
	return QTime(0, 0, 0).addSecs(reply.value() / 1000);*/
	return QTime(0, 0, 0);
}

void Mpris2Source::propertiesChanged(const QString &interface, const QVariantMap &changed_properties, const QStringList &string_list)
{
	qDebug() << "Properties changed on interface: " << interface;
	const QVariantMap qMap = changed_properties;
	QVariantMap *qMap2 = new QVariantMap(qMap);
	QVariantMap::Iterator it;
	for (it = qMap2->begin(); it != qMap2->end(); it++)
	{
		qDebug() << it.key() << "\t\t" << it.value().typeName() << "\t\t" << it.value().toString();
	}

	if (qMap2->contains("PlaybackStatus"))
	{
		playStatus = parsePlaybackStatus(qMap2->value("PlaybackStatus").toString());
		emit playbackStatusChanged();
	}

	if (qMap2->contains("LoopStatus"))
	{
		repeatStatus = parseLoopStatus(qMap2->value("LoopStatus").toString());
		emit repeatStatusChanged();
	}

	if (qMap2->contains("Shuffle"))
	{
		shuffleStatus = qMap2->value("Shuffle").toBool();
		emit shuffleStatusChanged();

		qDebug() << "Shuffle: " << (shuffleStatus ? "true" : "false");
	}

	if (qMap2->contains("Metadata"))
	{
		//shuffleStatus = qMap2->value("Shuffle").toBool();
		parseMetadata(m_playerProxy->metadata());
		emit trackChanged();
		emit infoLine1Changed();
		emit infoLine2Changed();
	}
}

void Mpris2Source::parseMetadata(QVariantMap metadata)
{
	title = metadata.value("xesam:title").toString();
	artist = metadata.value("xesam:artist").toString();
	album = metadata.value("xesam:album").toString();
	length = QTime(0, 0, 0).addSecs(metadata.value("mpris:length").toInt()/1000000);
}

MUSIC_REGISTER_SOURCE("mpris2source", Mpris2Source);
/*
namespace
{
	papa::registra<Source,Mpris2Source> theRegistra(std::string("mpris2source"));
}

*/