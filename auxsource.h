#include "source.h"

class AuxSource : public Source
{
	Q_OBJECT

public:
	static QList<SourceOption*> getSourceOptions();

	AuxSource(QVariantMap params) {}
	AuxSource();
	
	void enable();
	void disable();

	QString getName() { return "Aux"; };

	QString getInfoLine1() { return "AUX"; };
	QString getInfoLine2() { return "IN"; };
};