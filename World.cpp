#include "World.h"
#include"Animal.h"
#include"Plant.h"
#include"Rabbit.h"
#include"Wolf.h"


World::World(int wolfs, int rabbits, int grass) {
	for (int x = 0;x < rows;x++) {
		for (int y = 0;y < cols;y++) {
			grid[x][y] = '.';
		}
	}
	for (int i = 0;i < rabbits;i++) {
		int x = rand() % rows;
		int y = rand() % cols;
		while (!isAvailable(x, y)) {
			x = rand() % rows;
			y = rand() % cols;
		}
		animals.push_back(new Rabbit(x, y));
	}

	for (int i = 0;i < wolfs;i++) {
		int x = rand() % rows;
		int y = rand() % cols;
		while (!isAvailable(x, y)) {
			x = rand() % rows;
			y = rand() % cols;
		}
		animals.push_back(new Wolf(x, y));
	}
	for (int i = 0;i < grass;i++) {
		int x = rand() % rows;
		int y = rand() % cols;
		while (!isAvailable(x, y)) {
			x = rand() % rows;
			y = rand() % cols;
		}
		plants.push_back(new Plant(x, y));
	}

}
void World::update() {
	vector<Animal*> toRemove;
	//update wolfs
	for (auto it: animals) {
		if(it->isAlive() && it->getSpecies() == "Wolf")
		{
			it->move(*this);
			it->eat(*this);
			it->reproduce(*this);
		}
	}
	//cleanup deed
	for (auto it : animals) if (!it->isAlive()) toRemove.push_back(it);
	for (auto a : toRemove) removeAnimal(a);
	toRemove.clear();
	//update rabbits
	for (auto it : animals) {
		if (it->isAlive() && it->getSpecies() == "Rabbit")
		{
			it->move(*this);
			it->eat(*this);
			it->reproduce(*this);
		}
	}
	//cleanup deed
	for(auto it:animals) if (!it->isAlive()) toRemove.push_back(it);
	for (auto a : toRemove) removeAnimal(a);
	toRemove.clear();

	addAnimal();
	//update plant
	for (auto it : plants) {
		it->grow();
		it->spread(*this);
	}
	addPlant();
	
}
void World::display(){

	static int turnCounts = 0;
	int wolf = 0;
	int rabbit = 0;
	int plant = 0;

	for (int x = 0;x < rows;x++) 
		for (int y = 0;y < cols;y++) 
			grid[x][y] = '.';

	for (int x = 0;x < rows;x++)
		for (int y = 0;y < cols;y++)
		for (auto a : animals)
				if (a->getX() == x && a->getY() == y) {
					if (a->getSpecies() == "Wolf") {
						grid[x][y] = 'W'; wolf++;
					}
					if (a->getSpecies() == "Rabbit") {
						grid[x][y] = 'R'; rabbit++;
					}
				}

	for (int x = 0;x < rows;x++) 
	for (int y = 0;y < cols;y++)
		for (auto a : plants) 
			if (a->getX() == x && a->getY() == y) {
				grid[x][y] = 'G'; plant++;
			}
	//draw
	cout << endl;
	cout << endl << "--------------------------" << endl;
	cout << "Turn: " <<turnCounts++ << endl;
	for (int x = 0;x < rows;x++) {
		for (int y = 0;y < cols;y++) {
			cout << left <<setw(3)<< grid[x][y];
		}
		cout << endl;
	}
	cout << endl;
	cout << left << setw(5) << "Current wolf population:" << wolf << endl;
	cout << left << setw(5) << "Current rabbit population:" << rabbit << endl;
	cout << left << setw(5) << "Current grass population:" << plant	 << endl;
	cout << endl << "--------------------------" << endl;
}
void World::addAnimalsQueue(Animal* a) {
	animalsAddQueue.push_back(a);
}
void World::addPlantsQueue(Plant* a) {
	plantsAddQueue.push_back(a);
}

void World::addAnimal(){
	animals.insert(animals.end(), animalsAddQueue.begin(), animalsAddQueue.end());
	animalsAddQueue.clear();
}
void World::addPlant(){
	plants.insert(plants.end(), plantsAddQueue.begin(), plantsAddQueue.end());
	plantsAddQueue.clear();
}
void World::removeAnimal(Animal* a){
	for (auto it=animals.begin();it!=animals.end();++it) {
		if (*it == a) {
			animals.erase(it);
			delete a;
			return;
		}
	}
}
void World::removePlant(Plant* p){
	for (auto it = plants.begin();it !=plants.end();++it) {
		if (*it == p) {
			plants.erase(it);
			delete p;
			return ;
		}
	}
	
}
Animal* World::getAnimalAt(int x, int y,Animal &hunter){
	for (auto& it : animals) {
		if(it->isAlive()&&it!=&hunter&&it->getX()==x&&it->getY()==y) return it;
	}
	return 0;
}
Plant* World::getPlantAt(int x, int y){
	for (auto& it : plants) {
		if (it->getX() == x && it->getY() == y) return it;
	}
	return 0;
}
bool World::isAvailable(int x, int y){
	//kiểm tra biên.
	if (x<0 || y<0 || x>=rows || y>=cols) return false;

	//kiểm tra list chính.
	for (auto  a : animals) {
		if (x == a->getX()&& y==a->getY()) return false;
	}
	for (auto p : plants) {
		if(x==p->getX() && y == p->getY()) return false;
	}

	//Kiểm tra hàng đợi.
	for (auto a : animalsAddQueue) {
		if (x == a->getX() && y == a->getY()) return false;
	}
	for (auto p : plantsAddQueue) {
		if (x == p->getX() && y == p->getY()) return false;
	}
	return true;
}