#include "mpris2source.h"

class BansheeSource : public Mpris2Source
{
	Q_OBJECT
	
public:
    BansheeSource() : Mpris2Source("org.mpris.MediaPlayer2.banshee")
	{

	}
};