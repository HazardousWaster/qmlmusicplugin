#include <QObject>
#include <QDeclarativeItem>
#include <QTime>

#include<vector>
#include<papafactory/factory.h>

#include "sourceoption.h"
#include "sourcemanager.h"

#ifndef SOURCE_H
#define SOURCE_H

class Source : public QDeclarativeItem
{
	Q_OBJECT
	Q_ENUMS(PlayStatus);
	Q_ENUMS(RepeatStatus);
	
public:
	enum PlayStatus
	{
		PLAY_PLAYING = 0,
		PLAY_PAUSED,
		PLAY_STOPPED
	};

	enum RepeatStatus
	{
		REPEAT_NONE = 0,
		REPEAT_ALL,
		REPEAT_SINGLE
	};

	typedef boost::mpl::list<QVariantMap> factory_constructor_typeList;

	Source(QDeclarativeItem *parent);
	Source();

	Q_PROPERTY(QString name READ getName);

	virtual void enable() {};
	virtual void disable() {};
	virtual QString getName() { return name; };
	virtual bool checkValid() { return true; };

	virtual void playpause() {};
	virtual void next() {};
	virtual void previous() {};
	virtual void toggleShuffle() {};
	virtual void toggleRepeat() {};

	virtual QString getInfoLine1() { return ""; };
	virtual QString getInfoLine2() { return ""; };

	virtual QString getTitle() { return ""; };
	virtual QString getArtist() {return ""; };
	virtual QString getAlbum() {return ""; };
	virtual QTime getLength() {return QTime(0,0,0);};
	virtual QTime position() {return QTime(0,0,0);};
	virtual PlayStatus getPlayStatus() { return PLAY_PLAYING; }
	virtual RepeatStatus getRepeatStatus() { return REPEAT_NONE; }
	virtual bool getShuffleStatus() { return false; }

protected:
	QString name;
	
signals:
	void infoLine1Changed();
	void infoLine2Changed();

	void playbackStatusChanged();
	void repeatStatusChanged();
	void shuffleStatusChanged();
	void trackChanged();
	

};

#endif // SOURCE_H