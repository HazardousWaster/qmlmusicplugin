#include "source.h"
#include "mprisstatus.h"
#include "mpris2playerproxy.h"

#ifndef MPRIS2SOURCE_H
#define MPRIS2SOURCE_H

class Mpris2Source : public Source
{
	Q_OBJECT
	
public:
	Mpris2Source(char *serviceName);

	void disconnect() { m_playerProxy->Stop(); }
	void playpause();
	void next() { m_playerProxy->Next(); }
	void previous() { m_playerProxy->Previous(); }
	void toggleShuffle();
	void toggleRepeat();
	
	QString getTitle();
	QString getArtist();
	QString getAlbum();
	QTime getLength();
	QTime position();
	PlayStatus getPlayStatus();
	RepeatStatus getRepeatStatus();
	bool getShuffleStatus();
	
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

	Mpris2PlayerProxy *m_playerProxy;
	QDBusInterface	*m_dbusInterface;
	
	QString title;
	QString artist;
	QString album;
	QTime length;
	PlayStatus playStatus;
	RepeatStatus repeatStatus;
	bool shuffleStatus;

};

#endif // MPRIS2SOURCE_H