#pragma once

#include <string>
#include <iostream>

using namespace std;

class Event {

public:
	Event();
	Event(string str);
	Event(string str, double v);
	Event(string str, double v, double v1);
	void setName(string n) { eventName = n; };
	void setValue1(double v);
	void setValue2(double v);
	void setValues(double v, double v1) { value1 = v; value2 = v1; };
	double getValue1() { return value1; };
	double getValue2() { return value2; };
	string getName() { return eventName; };
	friend bool operator == (Event E, Event E1);
	friend ostream& operator << (ostream& out, Event E);
private:
	string eventName;
	double value1, value2;
};