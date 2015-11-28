
class Vector2f
{
public:
	Vector2f(int x, int y);
	Vector2f add(Vector2f b);
	Vector2f subtract(Vector2f b);
	float dotProduct(Vector2f b);
	Vector2f multiply(int scale);
private:
	int x;
	int y;
protected:
};