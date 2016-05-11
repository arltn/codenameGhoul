#pragma once
#include "Component.h"
#include "Entity.h"
#include <map>
#include <vector>

using namespace std;

typedef vector<Component*> entityComponents;

class ComponentManager
{
public:
	static ComponentManager* getInstance();
	int createEntity(vector<Component*>);
	int createEntity(Component*);
	void update();
private:
	static int entityID;
	map<int, entityComponents> entityList;
	static ComponentManager* inst;
	ComponentManager() {};
};
