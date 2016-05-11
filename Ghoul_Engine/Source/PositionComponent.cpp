#include "PositionComponent.h"

PositionComponent::PositionComponent(int x, int y) : Component() 
{
	cout << "In Position Constructor!\nX: " << x << "\nY:" << y << endl;
	xPos = x;
	yPos = y;
};