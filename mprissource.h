#include "source.h"
#include "mprisstatus.h"
#include "mprisplayerproxy.h"

class MprisSource : public Source
{
	Q_OBJECT
	
public:
    MprisSource(char *serviceName);

	void disconnect() { m_playerProxy->Stop(); }
	void playpause();
	void next() { m_playerProxy->Next(); }
	void previous() { m_playerProxy->Prev(); }
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
    void capsChange(int in0);
    void statusChange(MprisStatus in0);
    void trackChange(const QVariantMap &in0);		

private:
	MprisPlayerProxy *m_playerProxy;
	
	QString title;
	QString artist;
	QString album;
	QTime length;
	PlayStatus playStatus;
	RepeatStatus repeatStatus;
	bool shuffleStatus;
};