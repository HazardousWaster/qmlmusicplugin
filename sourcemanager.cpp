#include <vector>
#include <QList>

#include "sourceoption.h"
#include "sourcemanager.h"

SourceManager& SourceManager::instance()
{
	static SourceManager singleton;
	return singleton;
}

QList<SourceOption*> SourceManager::getSourceOptions()
{
	QList<SourceOption*> allOptions;
	std::vector<fptr>::iterator sourceIt;

	for(sourceIt = optionsListFunctions.begin(); sourceIt != optionsListFunctions.end(); sourceIt++)
	{
		fptr funcPtr = *sourceIt;
		QList<SourceOption*> newOptions = (*funcPtr)();
		allOptions.append(newOptions);
	}
	return allOptions;
}