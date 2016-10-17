#ifndef SQUAD_H
#define SQUAD_H

#include <vector>

class Squad
{
public:
	Squad();
	~Squad();
private:
	std::vector<Unit> units;
};

#endif