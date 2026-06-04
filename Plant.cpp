#include "Plant.h"
#include"World.h"
void Plant::grow() {
    growCounter += 10;
}
void Plant::spread(World& world){
	const int growCounterThreshold = 30;
	if (growCounter < growCounterThreshold) {
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
            world.addPlantsQueue(new Plant(nx, ny));
            growCounter = 0;
            return;
        }
    }
}