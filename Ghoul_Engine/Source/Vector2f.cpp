#include "Vector2f.h"

Vector2f::Vector2f(int newX = 0, int newY = 0)
{
	x = newX; 
	y = newY;
};
Vector2f Vector2f::add(Vector2f b)
{
	return Vector2f(x + b.x, y + b.y);
};
Vector2f Vector2f::subtract(Vector2f b)
{
	return Vector2f(x + (b.x * -1), y + (b.y * -1));;
};
Vector2f Vector2f::multiply(int scale)
{
	return Vector2f(x * scale, y * scale);
};
float Vector2f::dotProduct(Vector2f b)
{
	return ((x * b.x) + (y * b.y));
};