#include "mpris2source.h"

class SpotifySource : public Mpris2Source
{
	Q_OBJECT
	
public:
    SpotifySource() : Mpris2Source("org.mpris.MediaPlayer2.spotify")
	{
		setObjectName(getName());
	}

	QString getName() { return "Spotify"; };

	void disable()
	{
		qDebug("disabling spotify");
		m_playerProxy->Pause();
		m_playerProxy->Seek(0);
	}
};