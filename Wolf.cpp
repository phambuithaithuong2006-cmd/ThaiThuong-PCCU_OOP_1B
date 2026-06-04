#include "Wolf.h"
#include"World.h"

Wolf::Wolf(int x, int y) : Animal(x, y, 40, "Wolf") {}

void Wolf::move(World& world) {
    const int dx[4] = { 1, -1, 0, 0 };
    const int dy[4] = { 0, 0, 1, -1 };

    //săn mồi trong phạm vi xung quanh.
    for (int i = 0;i < 4;i++) {
        Animal* prey = world.getAnimalAt(getX()+dx[i], getY()+dy[i],*this);

        if (prey != nullptr && prey->getSpecies() == "Rabbit") {
            setPosition(getX() + dx[i], getY() + dy[i]);
            energy -= 5;
            return;
        }
    }

    //không phát hiện mồi, di chuyển ngẫu nhiên.
        int xy = rand() % 4;
        int nextX = getX() + dx[xy];
        int nextY = getY() + dy[xy];
        if (world.isAvailable(nextX, nextY)) {
            setPosition(nextX, nextY);
        }
    energy -= 5;
}

void Wolf::eat(World& world) {
    Animal* prey = world.getAnimalAt(getX(), getY(),*this);
    if (prey != nullptr && prey->getSpecies() == "Rabbit") {
        prey->beEaten(true);
        energy += 15;
    }
}

void Wolf::reproduce(World& world) {
    const int reproduceThreshold = 60;
    const int reproduceCost = 40;

    if (energy < reproduceThreshold) {
        return;
    }

    const int x = getX();
    const int y = getY();
    const int dx[4] = { 1, -1, 0, 0 };
    const int dy[4] = { 0, 0, 1, -1 };

    for (int i = 0; i < 4; ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        
        if (world.isAvailable(nx, ny)) {
            world.addAnimalsQueue(new Wolf(nx, ny));
            energy -= reproduceCost;
            return;
        }
    }
}
