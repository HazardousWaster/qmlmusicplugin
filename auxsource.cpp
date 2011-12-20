#include "auxsource.h"

QList<SourceOption*> AuxSource::getSourceOptions()
{
	QList<SourceOption*> options;

	QVariantMap params;
	SourceOption *auxOption = new SourceOption("Aux In", "auxsource", params);
	options.append(auxOption);

	return options;
}

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

MUSIC_REGISTER_SOURCE("auxsource", AuxSource)