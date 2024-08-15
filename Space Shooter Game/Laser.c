#include "Laser.h"

void UpdateLasers(Spaceship* spaceship) {
	for (int i = 0; i < MAX_LASERS; i++) {
		Laser* laser = &spaceship->lasers[i];
		if (laser->active) {
			laser->y += laser->speed;
			if (laser->active) {
				if (laser->y > GetScreenHeight() || laser->y < 0) {
					laser->active = false;
				}
			}
			DrawRectangle(spaceship->lasers[i].x, spaceship->lasers[i].y, LASER_WIDTH, LASER_HEIGHT, ORANGE);
		}
	}
}