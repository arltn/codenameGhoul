#pragma once

#include "Component.h"

class PositionComponent : public Component
{
public:
	PositionComponent(int, int);
private:
	int xPos;
	int yPos;
};
