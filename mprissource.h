#include "tracksource.h"
#include "mprisstatus.h"
#include "mprisplayerproxy.h"
#include "mprisrootproxy.h"

class MprisSource : public TrackSource
{
	Q_OBJECT
	
public:
	static QList<SourceOption*> getSourceOptions();

	MprisSource(QVariantMap params);
    MprisSource(QString serviceName);

	void enable();
	void disable();
	bool checkValid();

	void playpause();
	void next() { m_playerProxy->Next(); }
	void previous() { m_playerProxy->Prev(); }
	void toggleShuffle();
	void toggleRepeat();
	
	QTime position();

public slots:
    void capsChange(int in0);
    void statusChange(MprisStatus in0);
    void trackChange(const QVariantMap &in0);		

private:
	MprisPlayerProxy *m_playerProxy;
	MprisRootProxy *m_rootProxy;

};