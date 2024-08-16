#pragma once

#include "TypeDefs.h"

void DrawObstacle(Obstacle* obstacle); 
void HandleObstalesCollisionsWithLaser(Laser* laser, Obstacle obstacles[]);
void InitializeObstacles(Obstacle obstacles[]); 
void HandleObstacleCollisionWithCircle(Obstacle* ob, Vector2 center, int radius);