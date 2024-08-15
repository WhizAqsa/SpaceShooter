#include "Alien.h"

void InitializeAliens(Alien aliens[]) {

    //int obstacleWidth = GRID_COL * PIXEL_SIZE;
    //int obstacleHeight = GRID_ROWS * PIXEL_SIZE;
    //float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    ////initilize grid of blocks as obstacle
    //int shieldPixelArt[GRID_ROWS][GRID_COL] = {
    //   {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    //   {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    //   {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    //   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    //   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    //   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
    //};

    //for (int i = 0; i < OBSTACLES_SIZE; i++) {
    //    Obstacle obstacle;
    //    obstacle.x = i * obstacleWidth + (i + 1) * gap;
    //    obstacle.y = GetScreenHeight() - SPACESHIP_SIZE * 2 - obstacleHeight;
    //    memcpy(obstacle.grid, shieldPixelArt, sizeof(shieldPixelArt));

    //    obstacles[i] = obstacle;
    //}

    for (int i = 0; i < MAX_ALIENS; i++) {
        aliens[i].position.x = GetRandomValue(0, GetScreenWidth() - ALIEN_SIZE);
        aliens[i].position.y = GetRandomValue(-GetScreenHeight(), -ALIEN_SIZE); // Start off-screen above
        aliens[i].active = true;
    }
}

void UpdateAliens(Alien aliens[]) {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i].active) {
            aliens[i].position.y += 2; // Move the alien down by 2 units per frame
            if (aliens[i].position.y > GetScreenHeight()) {
                aliens[i].active = false; // Deactivate if the alien goes off-screen
            }
        }
        else {
            aliens[i].position.x = GetRandomValue(0, GetScreenWidth() - ALIEN_SIZE);
            aliens[i].position.y = GetRandomValue(-GetScreenHeight(), -ALIEN_SIZE); // Start off-screen above
            aliens[i].active = true;
        }
    }
}

void DrawAliens(Alien aliens[]) {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i].active) {
            DrawRectangle(aliens[i].position.x, aliens[i].position.y, ALIEN_SIZE, ALIEN_SIZE, GREEN);
        }
    }
}


void HandleAlienCollisionsWithLaser(Laser* laser, Alien aliens[]) {
    Rectangle laserRect = { laser->x, laser->y, LASER_WIDTH, LASER_HEIGHT };

    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i].active) {
            if (CheckCollisionRecs((Rectangle) { aliens[i].position.x, aliens[i].position.y, ALIEN_SIZE, ALIEN_SIZE }, laserRect)) {
                aliens[i].active = false;
                laser->active = false;
                break;
            }
        }
    }
}