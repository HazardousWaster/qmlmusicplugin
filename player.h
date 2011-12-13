#include <QObject>
#include <QDeclarativeItem>

#include "source.h"


class Player : public QDeclarativeItem
{
	Q_OBJECT

public:
	Player(QDeclarativeItem *parent);
	Player();

	void connectSignals();

	Q_PROPERTY(QString source READ source NOTIFY sourceChanged);
	Q_PROPERTY(QString title READ title NOTIFY titleChanged);
	Q_PROPERTY(QString artist READ artist NOTIFY artistChanged);
	Q_PROPERTY(QString album READ album NOTIFY albumChanged);
	Q_PROPERTY(QTime length READ length NOTIFY lengthChanged);
	Q_PROPERTY(QTime position READ position NOTIFY positionChanged);
	Q_PROPERTY(Source::PlayStatus playStatus READ playStatus NOTIFY playStatusChanged);
	Q_PROPERTY(Source::RepeatStatus repeatStatus READ repeatStatus NOTIFY repeatStatusChanged);
	Q_PROPERTY(bool shuffleStatus READ shuffleStatus NOTIFY shuffleStatusChanged);
		
	//Q_PROPERTY(QString repeat READ repeat);
	//Q_PROPERTY(bool shuffle READ isShuffling WRITE setShuffle);
	
	Q_INVOKABLE void changeSource();
	Q_INVOKABLE void playpause();
	Q_INVOKABLE void next();
	Q_INVOKABLE void previous();
	Q_INVOKABLE void toggleShuffle();
	Q_INVOKABLE void toggleRepeat();
	
	QString source();
	QString title();
	QString artist();
	QString album();
	QTime length();
	QTime position();
	Source::PlayStatus playStatus();
	Source::RepeatStatus repeatStatus();
	bool shuffleStatus();

public slots:
	void playbackStatusChanged();
	void repeatStatusChanged();
	void shuffleStatusChanged();
	void trackChanged();
	
signals:
	void sourceChanged(QString newSource);
	void titleChanged(QString newTitle);
	void artistChanged(QString newArtist);
	void albumChanged(QString newAlbum);
	void lengthChanged(QTime newLength);
	void positionChanged(QTime newPosition);
	void playStatusChanged(Source::PlayStatus newPlayStatus);
	void repeatStatusChanged(Source::RepeatStatus newRepeatStatus);
	void shuffleStatusChanged(bool newShuffleStatus);
	
//		QString repeat();
//	bool isShuffling();
//	void setShuffle(bool bShuffle);


private:
	Source *m_source;

	bool isBanshee;
};