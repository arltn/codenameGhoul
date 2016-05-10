#include "DebuggingSystem.h"

DebuggingSystem* DebuggingSystem::inst = 0;

DebuggingSystem::DebuggingSystem() 
{ 
	debuggingFile.open("..\\Debug\\debugFile.txt", ios::out); 
	if (debuggingFile)
	{
		time_t t = time(0);   // get time now
		struct tm now;
		localtime_s(&now, &t);
		debuggingFile << "*********************************************************" 
			<< endl << (now.tm_year + 1900) << '-' << (now.tm_mon + 1) << '-' << now.tm_mday << ' ' << now.tm_hour << ':' << now.tm_min << ':' << now.tm_sec << endl
			<< "Debugging System Started" << endl << endl;
	}
};

DebuggingSystem* DebuggingSystem::getInstance() 
{
	if (inst == NULL)
		inst = new DebuggingSystem();
	return inst;
};

void DebuggingSystem::closeDebugging()
{
	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t);
	debuggingFile << (now.tm_year + 1900) << '-' << (now.tm_mon + 1) << '-' << now.tm_mday << ' ' << now.tm_hour << ':' << now.tm_min << ':' << now.tm_sec << endl
		<< "Debugging System Destroyed, Program ending." << endl << "*********************************************************" << endl << endl;
	debuggingFile.close();
};

void DebuggingSystem::writeMessage(string message)
{
	//printf(message.c_str() + '\n');
	cout << message << endl;
	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t);
	debuggingFile << (now.tm_year + 1900) << '-' << (now.tm_mon + 1) << '-' << now.tm_mday << ' ' << now.tm_hour << ':' << now.tm_min << ':' << now.tm_sec << endl
	<< message << endl << endl;
};