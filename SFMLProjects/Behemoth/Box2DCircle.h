#ifndef BOX2DCIRCLE_H
#define BOX2DCIRCLE_H

#include "Box2D\Box2D.h"

class b2Circle
{
public:
	b2Circle(b2World* world, float radius);

	void render();
private:
	float radius;
	b2Body* body;
};

#endif