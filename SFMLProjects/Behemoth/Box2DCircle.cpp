#include "Box2DCircle.h"

#include "SFML\OpenGL.hpp"
b2Circle::b2Circle(b2World* world, float radius)
{
	//body = NULL;
	//radius = radius;

	////set up dynamic body, store in class variable
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0, 20);
	//body = world->CreateBody(&bodyDef);

	////add circle fixture
	//b2CircleShape circleShape;
	//circleShape.m_p.Set(0, 0);
	//circleShape.radius = radius; //use class variable
	//b2FixtureDef myFixtureDef;
	//myFixtureDef.shape = &circleShape;
	//myFixtureDef.density = 1;
	//m_body->CreateFixture(&myFixtureDef);
}

void b2Circle::render()
{
	//circle outline
	//glBegin(GL_LINE_LOOP);
	//for (float a = 0; a < 360 * DEGTORAD; a += 30 * DEGTORAD)
	//	glVertex2f(sinf(a), cosf(a));
	//glEnd();
}