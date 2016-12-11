#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

std::vector<Entity> entities;
std::vector<sf::Texture*> textures;


class Entity : public sf::CircleShape
{
public:
	Entity(std::string _name, std::string _textureName)
		: name(_name), alive(true)
	{
	/*	for (std::vector<sf::Texture>::iterator it = textures.begin(); it != textures.end(); it++)
		{
			if (_textureName == textures)
		}*/

	};
	~Entity();

protected:
	std::string name;
	bool alive;

	sf::Sprite sprite;
private:

};

class Player : public Entity
{
public:
	Player(std::string _name)
	: Entity(_name)
	{};
	~Player();
private:
	int hp = 100;
};

// to be done
class Animation
{
public:

protected:

private:

};

bool AABB(Entity* a, Entity* b)
{
	//return (b->x - a->x) * (b->x - a->x)
	//	 + (b->y - a->y) * (b->y - a->y)
	//	 < (a->R + b->R) * (a->R + b->R);
}

void CheckCollision()
{
	for (auto a : entities)
	{
		for (auto b : entities)
		{
			//if (a.)
		}
	}
}

struct Texture
{
	sf::Texture texture;
	std::string name;
};

void Initialize()
{
	// to be done

	/*t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");*/


}

int main()
{
	//sf::CircleShape player(100, 6);

	srand(time(0));
	
	for (int i = 0; i < 7; i++)
	{
		std::unique_ptr<sf::Texture> texture(new sf::Texture);
		textures.push_back(texture);
	}

	sf::Sprite background(t2);

	Initialize();
	
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


