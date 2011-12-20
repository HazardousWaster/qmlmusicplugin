#include "source.h"

#ifndef TRACKSOURCE_H
#define TRACKSOURCE_H

class TrackSource : public Source
{
	Q_OBJECT

public:
	TrackSource() {};

	virtual void enable() = 0;
	virtual void disable() = 0;

	virtual void playpause() = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual void toggleShuffle() = 0;
	virtual void toggleRepeat() = 0;

	virtual QString getInfoLine1();
	virtual QString getInfoLine2();
	
	virtual QString getTitle();
	virtual QString getArtist();
	virtual QString getAlbum();
	virtual QTime getLength();
	virtual QTime position() = 0;
	virtual PlayStatus getPlayStatus();
	virtual RepeatStatus getRepeatStatus();
	virtual bool getShuffleStatus();

protected:
	QString title;
	QString artist;
	QString album;
	QTime length;
	PlayStatus playStatus;
	RepeatStatus repeatStatus;
	bool shuffleStatus;
};

#endif // TRACKSOURCE_H