#include "mpris2source.h"
#include "mpris2playerproxy.h"

Mpris2Source::Mpris2Source()
{
	m_playerProxy = new Mpris2PlayerProxy(serviceName(),
										"/org/mpris/MediaPlayer2",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	QDBusObjectPath opath;
	QDBusPendingReply<QList<QDBusObjectPath> > reply = m_playerProxy->Play();
	reply.waitForFinished();
	if (reply.isError()) {
		qDebug() << reply.error();
	} else {
		opath = reply.value().first();
		qDebug() << opath.path();
	}

	m_dbusInterface = new QDBusInterface(serviceName(), "/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", QDBusConnection::sessionBus(), static_cast<QObject*>(this));
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

QString Mpris2Source::getTitle()
{
	return title;
}

QString Mpris2Source::getArtist()
{
	return artist;
}

QString Mpris2Source::getAlbum()
{
	return album;
}

QTime Mpris2Source::getLength()
{
	return length;
}

QTime Mpris2Source::position()
{
	/*QDBusPendingReply<int> reply = m_playerProxy->PositionGet();
	reply.waitForFinished();	
	return QTime(0, 0, 0).addSecs(reply.value() / 1000);*/
	return QTime(0, 0, 0);
}

Source::PlayStatus Mpris2Source::getPlayStatus()
{
	return playStatus;
}

Source::RepeatStatus Mpris2Source::getRepeatStatus()
{
	return repeatStatus;
}

bool Mpris2Source::getShuffleStatus()
{
	return shuffleStatus;
}
/*
void Mpris2Source::capsChange(int in0)
{
	qDebug() << "Caps changed: " << "\t" << in0;
}

void Mpris2Source::statusChange(MprisStatus in0)
{
	qDebug() << "Status changed: " << "\t" << in0.i1 << "\t" << in0.i2 << "\t" << in0.i3 << "\t" << in0.i4;
	
	playStatus = (in0.i1 == 0) ? PLAY_PLAYING : PLAY_PAUSED;
	repeatStatus = (in0.i4 == 1) ? REPEAT_ALL : ((in0.i3 == 1) ? REPEAT_SINGLE : REPEAT_NONE);
	shuffleStatus = (in0.i2 == 1);
	
	emit statusChanged();
}

void Mpris2Source::trackChange(const QVariantMap &in0)
{
	const QVariantMap qMap = in0;
	QVariantMap *qMap2 = new QVariantMap(qMap);
	QVariantMap::Iterator it;
	qDebug("Track changed:");
	//qDebug("signal:");
	for (it = qMap2->begin(); it != qMap2->end(); it++)
	{
		qDebug() << it.key() << "\t\t" << it.value().typeName() << "\t\t" << it.value().toString();
	}
	
	title = qMap2->value("title").toString();
	artist = qMap2->value("artist").toString();
	album = qMap2->value("album").toString();
	/*qDebug("metadata:");
	QDBusPendingReply<QVariantMap> reply3 = m_playerProxy->Metadata();
	reply3.waitForFinished();*	QVariantMap::Iterator it2;
	QVariantMap qMap3 = reply3.value();
	for (it2 = qMap3.begin(); it2 != qMap3.end(); it2++)
	{
		qDebug() << it2.key() << "\t\t" << it2.value().typeName() << "\t\t" << it2.value().toString();
	}
	length = QTime(0, 0, 0).addSecs(reply3.value().value("time").toInt());
	emit trackChanged();
}
*/
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
	}
}

void Mpris2Source::parseMetadata(QVariantMap metadata)
{
	title = metadata.value("xesam:title").toString();
	artist = metadata.value("xesam:artist").toString();
	album = metadata.value("xesam:album").toString();
	length = QTime(0, 0, 0).addSecs(metadata.value("mpris:length").toInt()/1000000);
}