#include "Obstacle.h"

//function to create a block
void DrawObstacle(Obstacle* obstacle) 
{
	for (unsigned int row = 0; row < GRID_ROWS; row++) {
		for (unsigned int col = 0; col < GRID_COL; col++) {
			if (obstacle->grid[row][col] == 1) {
				float pos_x = obstacle->x + col * PIXEL_SIZE;
				float pos_y = obstacle->y + row * PIXEL_SIZE;
				DrawRectangle(pos_x, pos_y, PIXEL_SIZE, PIXEL_SIZE, ORANGE);
			}
		}
	}
}

void HandleObstalesCollisionsWithLaser(Laser* laser, Obstacle obstacles[])
{
	Rectangle laserRect = { laser->x, laser->y, LASER_WIDTH, LASER_HEIGHT };
	for (int j = 0; j < OBSTACLES_SIZE; j++) {
		Obstacle* ob = &obstacles[j];
		Rectangle obRect = { ob->x, ob->y, GRID_COL * PIXEL_SIZE, GRID_ROWS * PIXEL_SIZE };

		if (!CheckCollisionRecs(obRect, laserRect)) continue;
		if (laser->y <= ob->y) continue;
		if (laser->x < ob->x) continue;
		if (laser->x > ob->x + GRID_COL * PIXEL_SIZE) continue;

		for (unsigned int row = 0; row < GRID_ROWS; row++) {
			for (unsigned int col = 0; col < GRID_COL; col++) {
				if (ob->grid[row][col] == 1) {
					float pos_x = ob->x + col * PIXEL_SIZE;
					float pos_y = ob->y + row * PIXEL_SIZE;
					Rectangle obstacleRect = { pos_x, pos_y, PIXEL_SIZE, PIXEL_SIZE };

					if (CheckCollisionRecs(laserRect, obstacleRect)) {
						ob->grid[row][col] = 0;
						laser->active = false;
						break;
					}
				}
			}
		}
	}
}

void HandleObstacleCollisionWithCircle(Obstacle* ob, Vector2 center, int radius)
{
	for (unsigned int row = 0; row < GRID_ROWS; row++) {
		for (unsigned int col = 0; col < GRID_COL; col++) {
			if (ob->grid[row][col] == 1) {
				float pos_x = ob->x + col * PIXEL_SIZE;
				float pos_y = ob->y + row * PIXEL_SIZE;
				Rectangle obstacleRect = { pos_x, pos_y, PIXEL_SIZE, PIXEL_SIZE };

				if (CheckCollisionCircleRec(center, radius, obstacleRect)) {
					ob->grid[row][col] = 0;
					break;
				}
			}
		}
	}
}

//function to create an obstacle

void InitializeObstacles(Obstacle obstacles[]) {
	int obstacleWidth = GRID_COL * PIXEL_SIZE;
	int obstacleHeight = GRID_ROWS * PIXEL_SIZE;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	//initilize grid of blocks as obstacle
	int shieldPixelArt[GRID_ROWS][GRID_COL] = {
	   {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
	   {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	   {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
	};

	for (int i = 0; i < OBSTACLES_SIZE; i++) {
		Obstacle obstacle;
		obstacle.x = i * obstacleWidth + (i + 1) * gap;
		obstacle.y = GetScreenHeight() - SPACESHIP_HEIGHT * 2 - obstacleHeight;
		memcpy(obstacle.grid, shieldPixelArt, sizeof(shieldPixelArt));

		obstacles[i] = obstacle;
	}
}