#pragma once

#include "event.h"
#include <queue>
#include <iostream>

using namespace std;

const int MAX_EVENTS = 256;

class eventListener
{
public:
	eventListener();
	void init();
	void registerEvent(Event E);
	void recieveEvent(Event E);
	inline Event getLastEvent() { return events[eventCount - 1]; };
	inline bool isEmpty() { return listenerEvents.empty(); };
	Event removeEvent();
	friend bool operator < (const eventListener _L1, const eventListener _L2);
private:
	Event events[MAX_EVENTS];
	queue<Event> listenerEvents;
	int eventCount;
	int ID;
	static int internalID;
protected:
};
