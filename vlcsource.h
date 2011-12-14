#include "mprissource.h"

class VlcSource : public MprisSource
{
	Q_OBJECT

public:
    VlcSource() : MprisSource("org.mpris.vlc")
	{
		setObjectName("VLC");
		setProperty("name", "VLC");
	}

	QString getName() { return "VLC"; };
};