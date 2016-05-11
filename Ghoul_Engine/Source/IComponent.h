#pragma once

#include <iostream>
using namespace std;

class IComponent
{
public:
	virtual ~IComponent() {};
	virtual void update() = 0;

private:
};