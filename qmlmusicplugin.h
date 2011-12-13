#include <QtDeclarative/QDeclarativeExtensionPlugin>
#include <QtDeclarative/qdeclarative.h>
#include <qdebug.h>
#include <qdatetime.h>
#include <qbasictimer.h>
#include <qapplication.h>

#include "player.h"
#include "mprisstatus.h"

class QmlMusicPlugin : public QDeclarativeExtensionPlugin
{
	Q_OBJECT
public:
	void registerTypes(const char *uri)
	{
		Q_ASSERT(uri == QLatin1String("music"));
		qmlRegisterType<Player>(uri, 1, 0, "Player");
		qmlRegisterType<Source>(uri, 1, 0, "Source");
		qDBusRegisterMetaType<MprisStatus>();
	}
};

