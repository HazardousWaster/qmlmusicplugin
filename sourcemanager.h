#include<map>

#ifndef SOURCEMANAGER_H
#define SOURCEMANAGER_H

#define MUSIC_REGISTER_SOURCE(name, classname)	namespace{papa::registra<Source,classname> theRegistra(std::string(name));SourceRegistration sourceReg(&classname::getSourceOptions);}

typedef QList<SourceOption*> (*fptr)();

class SourceManager 
{
public:
	static SourceManager& instance();

	std::vector<fptr> optionsListFunctions;

	QList<SourceOption*> getSourceOptions();

private:
	SourceManager() {};
};

class SourceRegistration
{
public:
	SourceRegistration(fptr funcPtr)
	{
		SourceManager::instance().optionsListFunctions.push_back(funcPtr);
	}
};

#endif // SOURCEMANAGER_H