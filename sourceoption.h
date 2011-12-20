#include <QObject>
#include <QVariant>

#ifndef SOURCEOPTION_H
#define SOURCEOPTION_H

class SourceOption : public QObject
{
	Q_OBJECT

public:
	Q_PROPERTY(QString name READ getName);

	SourceOption(QString _name, QString _classname, QVariantMap _params)
	{
		name = _name;
		classname = _classname;
		params = _params;
	}
	SourceOption() {};

	QString name;
	QString classname;
	QVariantMap params;

	QString getName() { return name; };
};

#endif // SOURCEOPTION_H