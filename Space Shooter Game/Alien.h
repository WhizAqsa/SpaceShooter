#include<raylib.h>
#include "TypeDefs.h"

#ifndef _ALIEN_
#define _ALIEN_


#define MAX_ALIENS 10 
#define ALIEN_SIZE 40

void InitializeAliens(Alien[]);
void UpdateAliens(Alien[]);
void DrawAliens(Alien[]);
void HandleAlienCollisionsWithLaser(Laser*, Alien[]);

#endif // !_ALIEN_


