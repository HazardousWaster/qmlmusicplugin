#include "mprissource.h"
#include "mprisplayerproxy.h"
#include "mprisstatus.h"


enum 
{
	CAN_GO_NEXT = 0x01,
	CAN_GO_PREV = 0x02,
	CAN_PAUSE = 0x04,
	CAN_PLAY = 0x08,
	CAN_SEEK = 0x10,
	CAN_PROVIDE_METADATA = 0x20,
	CAN_HAS_TRACKLIST = 0x40
};

QList<SourceOption*> MprisSource::getSourceOptions()
{
	QList<SourceOption*> options;

	QDBusReply<QStringList> reply = QDBusConnection::sessionBus().interface()->registeredServiceNames();
	if (!reply.isValid()) {
		qDebug() << "Error:" << reply.error().message();
	}
	
	foreach (QString serviceName, reply.value())
	{
		if (serviceName.startsWith("org.mpris") && !serviceName.startsWith("org.mpris.MediaPlayer2"))
		{
			QByteArray ba = serviceName.toLocal8Bit();

			MprisRootProxy *rootProxy = new MprisRootProxy(ba.data(),
										"/",
										QDBusConnection::sessionBus(),
										NULL);

			QString fullName = rootProxy->Identity()  + " (MPRIS)";
			
			QVariantMap params;
			params.insert("serviceName", serviceName);
			SourceOption *option = new SourceOption(fullName, "mprissource", params);
			options.append(option);
		}
	}
	
	return options;
}


MprisSource::MprisSource(QVariantMap params)
{
	QString serviceName = params.value("serviceName").toString();

	QByteArray ba = serviceName.toLocal8Bit();

	m_playerProxy = new MprisPlayerProxy(ba.data(),
										"/Player",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));
	
	m_rootProxy = new MprisRootProxy(ba.data(),
										"/",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	name = m_rootProxy->Identity() + " (MPRIS)";
}

MprisSource::MprisSource(QString serviceName)
{
	
	QByteArray ba = serviceName.toLocal8Bit();

	m_playerProxy = new MprisPlayerProxy(ba.data(),
										"/Player",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));
	
	m_rootProxy = new MprisRootProxy(ba.data(),
										"/",
										QDBusConnection::sessionBus(),
										static_cast<QObject*>(this));

	name = m_rootProxy->Identity() + " (MPRIS)";
}

void MprisSource::enable()
{
	QDBusObjectPath opath;
	QDBusPendingReply<> reply = m_playerProxy->Play();
	reply.waitForFinished();
	if (reply.isError()) {
		qDebug() << reply.error();
	}
	
	QObject::connect(m_playerProxy, SIGNAL(CapsChange(int)), this, SLOT(capsChange(int)));
	QObject::connect(m_playerProxy, SIGNAL(StatusChange(MprisStatus)), this, SLOT(statusChange(MprisStatus)));
	QObject::connect(m_playerProxy, SIGNAL(TrackChange(const QVariantMap)), this, SLOT(trackChange(const QVariantMap)));

/*	QDBusPendingReply<int> reply2 = m_playerProxy->GetCaps();
	reply2.waitForFinished();

	bool cangonext, cangoprev, canpause, canplay, canseek, canmeta, cantrack;


	if (reply2.isError()) {
		qDebug() << reply2.error();
	} else {
		int i = reply2.value();
		cangonext = i & CAN_GO_NEXT;
		cangoprev = i & CAN_GO_PREV;
		canpause = i & CAN_PAUSE;
		canplay = i & CAN_PLAY;
		canseek = i & CAN_SEEK;
		canmeta = i & CAN_PROVIDE_METADATA;
		cantrack = i & CAN_HAS_TRACKLIST;

		qDebug() << i << cangonext << cangoprev << canpause << canplay << canseek << canmeta << cantrack;
	}*/
	
	QDBusPendingReply<QVariantMap> reply3 = m_playerProxy->GetMetadata();
	reply3.waitForFinished();	
	if (!reply3.isError())
	{
		trackChange(reply3.value());
	}
	else
	{
		qDebug() << reply3.error();
	}
	
	QDBusPendingReply<MprisStatus> reply4 = m_playerProxy->GetStatus();
	reply4.waitForFinished();
	if (!reply4.isError())
	{
		statusChange(reply4.value());
	}
	else
	{
		qDebug() << reply4.error();
	}
}

void MprisSource::disable()
{
	m_playerProxy->Stop();
}

bool MprisSource::checkValid()
{
	QDBusPendingReply<QString> reply = m_rootProxy->Identity();
	return reply.isValid() && reply.value() == name;
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

QTime MprisSource::position()
{
	QDBusPendingReply<int> reply = m_playerProxy->PositionGet();
	reply.waitForFinished();	
	return QTime(0, 0, 0).addSecs(reply.value() / 1000);
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
	length = QTime(0, 0, 0).addSecs(qMap2->value("time").toInt());

	emit trackChanged();
	emit infoLine1Changed();
	emit infoLine2Changed();
}

MUSIC_REGISTER_SOURCE("mprissource", MprisSource);