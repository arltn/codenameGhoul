#include "event.h"
#include <iostream>

using namespace std;

Event::Event()
{
	eventName = "";
	value1 = 0;
	value2 = 0;
}

Event::Event(string str)
{
	eventName = str;
};

Event::Event(string str, double v)
{
	eventName = str;
	value1 = v;
	value2 = 0;
};

Event::Event(string str, double v, double v1)
{
	eventName = str;
	value1 = v;
	value2 = v1;
};

void Event::setValue1(double v)
{
	value1 = v;
}

void Event::setValue2(double v)
{
	value2 = v;
};

bool operator == (Event E, Event E1)
{
	//cout << "Event: " << E.eventName << ", Event 1: " << E1.eventName << endl;
	if (E.eventName == E1.eventName)
		return true;
	return false;
}

ostream& operator << (ostream& out, Event E)
{
	out << E.eventName << ", " << E.value1 << ", " << E.value2 << endl;
	return out;
};