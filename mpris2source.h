#include "tracksource.h"
#include "mprisstatus.h"
#include "mpris2playerproxy.h"
#include "mpris2rootproxy.h"
#include "mpris2tracklistproxy.h"

#ifndef MPRIS2SOURCE_H
#define MPRIS2SOURCE_H

class Mpris2Source : public TrackSource
{
	Q_OBJECT
	
public:
	static QList<SourceOption*> getSourceOptions();

	Mpris2Source(QVariantMap params);
	Mpris2Source(QString serviceName);

	void enable();
	void disable();
	bool checkValid();

	void playpause();
	void next() { m_playerProxy->Next(); }
	void previous() { m_playerProxy->Previous(); }
	void toggleShuffle();
	void toggleRepeat();
		
	QTime position();
	
public slots:
	void propertiesChanged(const QString &interface, const QVariantMap &changed_properties, const QStringList &string_list);

private:
	static Source::PlayStatus parsePlaybackStatus(QString playbackStatus)
	{
		if (playbackStatus ==  "Playing")
			return PLAY_PLAYING;
		else if (playbackStatus == "Paused")
			return PLAY_PAUSED;
		else
			return PLAY_STOPPED;
	}

	static Source::RepeatStatus parseLoopStatus(QString loopStatus)
	{
		if (loopStatus == "None")
			return REPEAT_NONE;
		else if (loopStatus == "Track")
			return REPEAT_SINGLE;
		else
			return REPEAT_ALL;
	}

	void parseMetadata(QVariantMap metadata);

protected:
	Mpris2RootProxy *m_rootProxy;
	Mpris2PlayerProxy *m_playerProxy;
	Mpris2TrackListProxy *m_trackListProxy;

private:
	QDBusInterface	*m_dbusInterface;
};

#endif // MPRIS2SOURCE_H