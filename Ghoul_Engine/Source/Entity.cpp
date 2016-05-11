#include "Entity.h"

Entity::Entity(Component* component)
{
	ComponentManager* compManager = ComponentManager::getInstance();
	ID = compManager->createEntity(component);
	delete compManager;
};

Entity::Entity(vector<Component*> components)
{
	ComponentManager* compManager = ComponentManager::getInstance();
	ID = compManager->createEntity(components);
	delete compManager;
}