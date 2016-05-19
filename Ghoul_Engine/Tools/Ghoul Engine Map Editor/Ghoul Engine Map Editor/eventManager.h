#pragma once

#include "event.h"
#include "eventListener.h"

#include <map>
#include <queue>

class eventManager
{
public:
	void queueEvent(Event E);
	void sendNow(Event E);
	void update();
	static eventManager* getInst();
	void addListener(eventListener*, int, Event E);
	void printListeners();
private:
	queue <Event> EventQueue;
	multimap <int, Event> dictionary;
	eventListener* listeners[];
	static eventManager *inst;
protected:
	eventManager();
};
