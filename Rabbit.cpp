#include"Rabbit.h"
#include"Plant.h"


Rabbit::Rabbit(int x, int y) : Animal(x, y, 50, "Rabbit") {}

void Rabbit::move(World& world) {
    const int dx[4] = { 1, -1, 0, 0 };
    const int dy[4] = { 0, 0, 1, -1 };

    //săn mồi trong phạm vi xung quanh.
    for (int i = 0;i < 4;i++) {
        Plant* prey = world.getPlantAt(getX() + dx[i], getY() + dy[i]);
        if (prey != nullptr) {
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

void Rabbit::eat(World& world) {
    Plant* prey = world.getPlantAt(getX(), getY());
    if (prey != nullptr) {
        world.removePlant(prey);
        energy += 20;
    }
}

void Rabbit::reproduce(World& world) {
    const int reproduceThreshold = 80;
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
            world.addAnimalsQueue(new Rabbit(nx, ny));
            if (world.getAnimalAt(nx, ny, *this) != nullptr)
            energy -= reproduceCost;
            return;
        }
    }
}
