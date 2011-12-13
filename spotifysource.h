#include "mpris2source.h"

class SpotifySource : public Mpris2Source
{
	Q_OBJECT
	
public:
    SpotifySource() : Mpris2Source("org.mpris.MediaPlayer2.spotify")
	{

	}
};