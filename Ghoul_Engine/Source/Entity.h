#pragma once
#include "Component.h"
#include "ComponentManager.h"
#include <vector>

using namespace std;

class Entity
{
public:
	Entity(Component*);
	Entity(vector<Component*> components);
private:
	int ID;
};
