#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<iomanip>
using namespace std;

class Animal;
class Plant;
class World
{
private:
	static const int rows = 20;
	static const int cols = 10;
	char grid[rows][cols];

	vector<Animal*> animals;
	vector<Animal*> animalsAddQueue;

	vector<Plant*> plants;
	vector<Plant*> plantsAddQueue;
public:
	World(int,int,int);
	void update();
	void display();
	void addAnimalsQueue(Animal*);
	void addPlantsQueue(Plant*);
	void addAnimal();
	void addPlant();
	void removeAnimal(Animal*);
	void removePlant(Plant*);
	Animal* getAnimalAt(int,int,Animal&);
	Plant* getPlantAt(int,int);
	bool isAvailable(int, int);
};
#endif