#pragma once

#include "TypeDefs.h"

void DrawObstacle(Obstacle* obstacle); 
void HandleObstalesCollisionsWithLaser(Laser* laser, Obstacle obstacles[]);
void CreateObstacles(Obstacle obstacles[]);