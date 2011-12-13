#include "mprissource.h"
#include "mprisplayerproxy.h"
#include "mprisstatus.h"

MprisSource::MprisSource()
{
	m_playerProxy = new MprisPlayerProxy(serviceName(),
										"/Player",
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
	
	QObject::connect(m_playerProxy, SIGNAL(CapsChange(int)), this, SLOT(capsChange(int)));
	QObject::connect(m_playerProxy, SIGNAL(StatusChange(MprisStatus)), this, SLOT(statusChange(MprisStatus)));
	QObject::connect(m_playerProxy, SIGNAL(TrackChange(const QVariantMap)), this, SLOT(trackChange(const QVariantMap)));
	
	QDBusPendingReply<QVariantMap> reply3 = m_playerProxy->GetMetadata();
	reply3.waitForFinished();	
		QVariantMap::Iterator it;
		QVariantMap qMap3 = reply3.value();
		for (it = qMap3.begin(); it != qMap3.end(); it++)
	{
		qDebug() << it.key() << "\t\t" << it.value().typeName() << "\t\t" << it.value().toString();
	}
	
	title = reply3.value().value("title").toString();
	artist = reply3.value().value("artist").toString();
	album = reply3.value().value("album").toString();
	length = QTime(0, 0, 0).addSecs(reply3.value().value("time").toInt());
	
	QDBusPendingReply<MprisStatus> reply4 = m_playerProxy->GetStatus();
	reply3.waitForFinished();
	MprisStatus in0 = reply4.value();

	playStatus = (in0.i1 == 0) ? PLAY_PLAYING : ((in0.i1 == 1) ? PLAY_PAUSED : PLAY_STOPPED);
	repeatStatus = (in0.i4 == 1) ? REPEAT_ALL : ((in0.i3 == 1) ? REPEAT_SINGLE : REPEAT_NONE);
	shuffleStatus = (in0.i2 == 1);
}

void MprisSource::playpause()
{	
	if (playStatus == PLAY_PLAYING)
	{
		m_playerProxy->Pause();
	}
	else if (playStatus == PLAY_PAUSED)
	{
		m_playerProxy->Pause();
	}
	else if (playStatus == PLAY_STOPPED)
	{
		m_playerProxy->Play();
	}
}

void MprisSource::toggleShuffle()
{
	
}

void MprisSource::toggleRepeat()
{
	if (repeatStatus == REPEAT_NONE)
		m_playerProxy->Repeat(true);
	else
		m_playerProxy->Repeat(false);
}

QString MprisSource::getTitle()
{
	return title;
}

QString MprisSource::getArtist()
{
	return artist;
}

QString MprisSource::getAlbum()
{
	return album;
}

QTime MprisSource::getLength()
{
	return length;
}

QTime MprisSource::position()
{
	QDBusPendingReply<int> reply = m_playerProxy->PositionGet();
	reply.waitForFinished();	
	return QTime(0, 0, 0).addSecs(reply.value() / 1000);
}

Source::PlayStatus MprisSource::getPlayStatus()
{
	return playStatus;
}

Source::RepeatStatus MprisSource::getRepeatStatus()
{
	return repeatStatus;
}

bool MprisSource::getShuffleStatus()
{
	return shuffleStatus;
}

void MprisSource::capsChange(int in0)
{
	qDebug() << "Caps changed: " << "\t" << in0;
}

void MprisSource::statusChange(MprisStatus in0)
{
	qDebug() << "Status changed: " << "\t" << in0.i1 << "\t" << in0.i2 << "\t" << in0.i3 << "\t" << in0.i4;
	
	playStatus = (in0.i1 == 0) ? PLAY_PLAYING : PLAY_PAUSED;
	repeatStatus = (in0.i4 == 1) ? REPEAT_ALL : ((in0.i3 == 1) ? REPEAT_SINGLE : REPEAT_NONE);
	shuffleStatus = (in0.i2 == 1);
	
	emit playbackStatusChanged();
	emit repeatStatusChanged();
	emit shuffleStatusChanged();
}

void MprisSource::trackChange(const QVariantMap &in0)
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
	QDBusPendingReply<QVariantMap> reply3 = m_playerProxy->GetMetadata();
	reply3.waitForFinished();*	QVariantMap::Iterator it2;
	QVariantMap qMap3 = reply3.value();
	for (it2 = qMap3.begin(); it2 != qMap3.end(); it2++)
	{
		qDebug() << it2.key() << "\t\t" << it2.value().typeName() << "\t\t" << it2.value().toString();
	}
	length = QTime(0, 0, 0).addSecs(reply3.value().value("time").toInt());*/
	emit trackChanged();
}