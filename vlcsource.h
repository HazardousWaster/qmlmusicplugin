#include "mprissource.h"

class VlcSource : public MprisSource
{
	Q_OBJECT

public:
    virtual inline const char *serviceName() { return "org.mpris.vlc"; }
};