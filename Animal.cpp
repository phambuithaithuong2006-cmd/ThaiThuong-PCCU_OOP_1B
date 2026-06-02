
#include "Animal.h"
Animal::Animal(int x, int y, int energy,std::string species)
    : Entity(x, y){
    this->energy = energy;
    this->species = species;
}

void Animal::beEaten(bool dead) {
    this->dead = dead;
}

bool Animal::isAlive() const {
    if (!dead) {
        return energy > 0;
    }else return 0;
    
}

string Animal::getSpecies() const {
    return species;
}
int Animal::getEnergy()const {
    return energy;
}
