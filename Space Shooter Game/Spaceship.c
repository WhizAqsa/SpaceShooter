#include "Spaceship.h"

void FireLaser(Spaceship* spaceship)
{
	if (GetTime() - spaceship->lastFireTime >= 0.35) {
		for (int i = 0; i < MAX_LASERS; i++) {
			if (!spaceship->lasers[i].active) {
				spaceship->lasers[i].x = spaceship->position.x + spaceship->image.width / 2 - 2;
				spaceship->lasers[i].y = spaceship->position.y;
				spaceship->lasers[i].speed = -12;
				spaceship->lasers[i].active = true;
				spaceship->lastFireTime = GetTime();
				break;
			}
		}
	}
}

//function
//to move the spaceship to the left
void MoveLeft(Spaceship* spaceship) {
	spaceship->position.x -= 7;
}
//function
//to move the spaceship to the right
void MoveRight(Spaceship* spaceship) {
	spaceship->position.x += 7;
}