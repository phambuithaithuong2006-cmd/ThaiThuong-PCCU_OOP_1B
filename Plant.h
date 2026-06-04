#pragma once
#include<iostream>
#include<string>
#include"Entity.h"
using namespace std;

class World;
class Plant:public Entity
{
private:
	int growCounter;
public:
	Plant(int x, int y) : Entity(x, y), growCounter(0) {};
	void grow();
	void spread(World&);

};
