#ifndef UNIT_H
#define UNIT_H

#include "SFML\Graphics.hpp"

class Unit
{
public:
	Unit(const std::string spriteName);
	void SetNumber(int number);
	void SetDamage(int damage);
	void SetRange(int damage);
	void SetPhysicalDefence(int damage);
	void SetMagicalDefence(int damage);

	~Unit();
private:
	unsigned int number;
	unsigned int damage;
	unsigned int range;
	unsigned int physicalDefence;
	unsigned int magicalDefence;

	sf::Sprite sprite;

};

#endif