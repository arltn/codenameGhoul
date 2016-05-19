#include "eventManager.h"

eventManager* eventManager::inst = 0;

eventManager::eventManager()
{
};

void eventManager::queueEvent(Event E)
{
	EventQueue.push(E);
};

void eventManager::sendNow(Event E)
{
	Event currentEvent;
	int holdEvent = 0;
	eventListener *currentListener;

	//cout << "Sending event: " << E.getName() << endl;

	for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
	{
		if (it->second == E)
		{
			currentEvent = E;
			holdEvent = it->first;
			currentListener = listeners[holdEvent];
			currentListener->recieveEvent(E);
		}

	}
};

void eventManager::update()
{
	if (!EventQueue.empty())
	{
		Event currentEvent = EventQueue.front();
		EventQueue.pop();
		sendNow(currentEvent);
	}
};

eventManager* eventManager::getInst()
{
	if (inst == NULL)
		inst = new eventManager();
	return inst;
};

void eventManager::addListener(eventListener *L, int I, Event E)
{
	//cout << "Adding listener!" << endl;
	dictionary.insert(pair <int, Event>(I, E));
	listeners[I] = L;
};

void eventManager::printListeners()
{
	for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
	{
		cout << "First: "<< it->first <<", Second: " << it->second << endl;
	}
};