#include "Bullet.h"

void UpdateBullet(Alien* alien) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet* bullet = &alien->bullets[i];
        if (bullet->active) {
            bullet->y += bullet->speed;

            if (bullet->y > GetScreenHeight() || bullet->y < 0) {
                bullet->active = false;
            }
        }
    }
}