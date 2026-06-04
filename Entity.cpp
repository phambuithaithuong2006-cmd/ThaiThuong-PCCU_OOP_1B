#include "Entity.h"

Entity::Entity(){
}
Entity::Entity(int x, int y) {
	this->x = x;
	this->y = y;
}

void Entity::setPosition(int x, int y){
	this->x = x;
	this->y = y;
}
int Entity::getX() {
	return x;
}
int Entity::getY(){
	return y;
}