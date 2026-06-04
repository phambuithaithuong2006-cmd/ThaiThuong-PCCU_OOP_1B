#pragma once
#include<iostream>
using namespace std;

class Entity
{
private:
	int x;
	int y;
public:
	Entity();
	Entity(int, int);
	void setPosition(int, int);
	int getX();
	int getY();
};
