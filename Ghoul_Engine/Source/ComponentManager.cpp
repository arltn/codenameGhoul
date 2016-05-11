#include "ComponentManager.h"

ComponentManager* ComponentManager::inst = 0;
int ComponentManager::entityID = 0;

ComponentManager* ComponentManager::getInstance()
{
	if (inst == 0)
	{
		inst = new ComponentManager();
	}
	return inst;
}

int ComponentManager::createEntity(vector<Component*> components)
{
	int retVal = entityID;
	entityList.insert(make_pair(entityID, components));
	if (entityID + 1 < INT_MAX)
		entityID = 0;
	else
		entityID++;
	return retVal;
};

int ComponentManager::createEntity(Component *comp)
{
	vector<Component*> components;
	components.push_back(comp);
	int retVal = entityID;
	entityList.insert(make_pair(entityID, components));
	if (entityID + 1 < INT_MAX)
		entityID = 0;
	else
		entityID++;
	return retVal;
};

void ComponentManager::update() 
{
};