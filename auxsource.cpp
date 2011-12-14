#include "auxsource.h"

AuxSource::AuxSource()
{
	setObjectName(getName());
}

void AuxSource::enable()
{
	qDebug("enabling Aux");
	system("amixer -c 0 sset Line unmute");
}

void AuxSource::disable()
{
	qDebug("disablign Aux");
	system("amixer -c 0 sset Line mute");
}