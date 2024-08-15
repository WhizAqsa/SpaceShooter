#include "Alien.h"
#include<stdlib.h>

void InitializeAliens(Alien aliens[][LEVEL_WIDTH], int levelDesign[][LEVEL_WIDTH], int height) 
{


    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
        {
            aliens[i][j].fireRate = 1.0f + (float)rand() / RAND_MAX * 0.5f; // Random fire rate between 1.0 and 1.5 seconds
            Alien* cur = &aliens[i][j];

            switch (levelDesign[i][j])
            {
            case 0:
                cur->image = LoadTexture("images/alien_1.png");
                cur->lives = 1;
                cur->type = 0;
                break;

            case 1:
                cur->image = LoadTexture("images/alien_2.png");
                cur->lives = 2;
                cur->type = 1;
                break;

            case 2:
                cur->image = LoadTexture("images/alien_3.png");
                cur->lives = 3;
                cur->type = 2;
                break;

            default:
                printf("Invalid Enemy Type\n");

            }

            // margin top: 30px
            // gap: 20px 40px
            
            cur->position.y = 30 + i * (20 + cur->image.height);
            cur->position.x = j * (40 + cur->image.width);
        }
    }
}

//[    ^
//    [0, 1, 1]
//    [0, 1, 0]
//    [0, 1, 1]
//]

void UpdateAliens(Alien aliens[][LEVEL_WIDTH], int height) {
    static int currentDirection = 1;

    Alien leftFirst;
    for (int j = 0; j < LEVEL_WIDTH; j++)
    {
        int hasFound = 0;
        for (int i = 0; i < height; i++)
        {
            if (aliens[i][j].lives > 0) 
            {
                hasFound = 1;
                leftFirst = aliens[i][j];
                break;
            }
        }
        if (hasFound) break;
    }

    Alien rightFirst;
    for (int j = LEVEL_WIDTH - 1; j >= 0; j--)
    {
        int hasFound = 0;
        for (int i = 0; i < height; i++)
        {
            if (aliens[i][j].lives > 0)
            {
                hasFound = 1;
                rightFirst = aliens[i][j];
                break;
            }
        }
        if (hasFound) break;
    }

    if (leftFirst.position.x - ALIEN_SPEED <= 0) currentDirection = 1;
    else if (rightFirst.position.x + rightFirst.image.width + ALIEN_SPEED >= GetScreenWidth()) currentDirection = -1;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
        {
            aliens[i][j].position.x += currentDirection * ALIEN_SPEED;
        }
    }
}

void DrawAliens(Alien aliens[][LEVEL_WIDTH], int height) {
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
        {
            Alien* cur = &aliens[i][j];
            if (cur->lives == 0) continue;
            
            DrawTextureV(cur->image, cur->position, RED);
        }
    }
}


void HandleAlienCollisionsWithLaser(Laser* laser, Alien aliens[][LEVEL_WIDTH], int height) {
    Rectangle laserRect = { laser->x, laser->y, LASER_WIDTH, LASER_HEIGHT };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < LEVEL_WIDTH; j++)
        {
            Alien* cur = &aliens[i][j];

            if (cur->lives == 0) continue;
            if (CheckCollisionRecs((Rectangle) { cur->position.x, cur->position.y, cur->image.width, cur->image.height }, laserRect)) {
                if (cur->lives > 0) cur->lives--;
                laser->active = false;
                break;
            }
        }
    }
}

void FireBullet(Alien* alien)
{
    alien->fireTimer += GetFrameTime();
    if (alien->fireTimer >= alien->fireRate) {
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!alien->bullets[i].active) {
                alien->bullets[i].x = alien->position.x + alien->image.width / 2 - 2;
                alien->bullets[i].y = alien->position.y;
                alien->bullets[i].speed = -6;
                alien->bullets[i].active = true;
                alien->fireTimer = 0.0f;
                break;
            }
        }
    }
}