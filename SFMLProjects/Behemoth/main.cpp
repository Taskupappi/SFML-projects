#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>


int main()
{
	//b2Vec2 gravity(0.0f, -10.0f);
	//b2World world(gravity);

	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -10.0f);

	//b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(50.0f, 10.0f);

	//groundBody->CreateFixture(&groundBox, 0.0f);




	sf::CircleShape player(100, 3);









	sf::RenderWindow window(sf::VideoMode(400, 400), "Box2D");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}
