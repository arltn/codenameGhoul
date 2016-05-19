#include "eventListener.h"
#include "eventManager.h"

int eventListener::internalID = 0;

eventListener::eventListener()
{};

void eventListener::init()
{
	eventCount = 0;
	ID = internalID;
	internalID++;
}

void eventListener::registerEvent(Event E)
{
	cout << "Event listener, registerEvent()" << endl;
	eventManager* eventMan;
	eventMan = eventManager::getInst();
	events[eventCount] = E;
	eventMan->addListener(this, ID, E);
	eventCount++;
};


void eventListener::recieveEvent(Event E)
{
	//cout << "This listener has recieved an event we care about!" << endl;
	listenerEvents.push(E);
};

Event eventListener::removeEvent() 
{ 
	Event retVal = listenerEvents.front();
	listenerEvents.pop();
	return retVal;
};


bool operator < (const eventListener _L1, const eventListener _L2)
{
	return (_L1.eventCount > _L2.eventCount);
};

