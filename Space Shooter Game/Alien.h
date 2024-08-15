#include <raylib.h>
#include <stdio.h>
#include "TypeDefs.h"

#ifndef _ALIEN_
#define _ALIEN_


#define MAX_ALIENS 10 
#define ALIEN_SIZE 40

void InitializeAliens(Alien aliens[][LEVEL_WIDTH], int levelDesign[][LEVEL_WIDTH], int);
void UpdateAliens(Alien aliens[][LEVEL_WIDTH], int height);
void DrawAliens(Alien aliens[][LEVEL_WIDTH], int height);
void HandleAlienCollisionsWithLaser(Laser* laser, Alien aliens[][LEVEL_WIDTH], int height);
void FireBullet(Alien* );

#endif // !_ALIEN_


