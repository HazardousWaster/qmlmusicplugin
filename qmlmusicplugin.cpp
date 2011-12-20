#include "qmlmusicplugin.h" 

void QmlMusicPlugin::registerTypes(const char *uri)
{
	Q_ASSERT(uri == QLatin1String("music"));
	qmlRegisterType<Player>(uri, 1, 0, "Player");
	qmlRegisterType<Source>(uri, 1, 0, "Source");
	qmlRegisterType<SourceOption>(uri, 1, 0, "SourceOption");
	qDBusRegisterMetaType<MprisStatus>();
}

Q_EXPORT_PLUGIN2(qmlmusicplugin, QmlMusicPlugin);