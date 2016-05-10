#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdio>

using namespace std;

class DebuggingSystem
{
public:
	static DebuggingSystem* getInstance();
	void writeMessage(string message);
	void closeDebugging();
private:
	fstream debuggingFile;
	DebuggingSystem();
	static DebuggingSystem* inst;
};
