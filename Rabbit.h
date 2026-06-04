#pragma once
#include "Animal.h"
#include"Plant.h"
#include"World.h"
class Rabbit : public Animal
{
public:
	Rabbit(int, int);
	void move(World&);
	void eat(World&);
	void reproduce(World&);
};