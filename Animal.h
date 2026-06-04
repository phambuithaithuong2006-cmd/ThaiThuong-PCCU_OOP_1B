#ifndef ANIMAL_H
#define ANIMAL_H
#include<string>
#include<iostream>
#include"Entity.h"
using namespace std;
class World;
class Animal: public Entity
{
protected:
	string species;
	int energy;
	bool dead = false;
public:
	Animal(int x, int y, int energy, std::string species);
	virtual ~Animal()= default;
	void setSpecies(string);
	void setEnergy(int);
	string getSpecies() const;
	int getEnergy()const;

	virtual void move(World&)=0;
	virtual void eat(World&)=0;
	virtual void reproduce(World&)=0;

	void beEaten(bool);
	bool isAlive() const;


};
#endif
