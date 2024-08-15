#include <raylib.h>

#ifndef _TYPEDEFS_
#define _TYPEDEFS_

#define SPACESHIP_WIDTH 64
#define SPACESHIP_HEIGHT 52
#define MAX_LASERS 10
#define LASER_HEIGHT 15
#define LASER_WIDTH 4

#define PIXEL_SIZE 3
#define OBSTACLES_SIZE 4

#define GRID_ROWS 13 
#define GRID_COL 23

typedef struct Obstacle {
	int x;
	int y;
	int grid[GRID_ROWS][GRID_COL];
} Obstacle;


typedef struct Laser {
	int x;
	int y;
	int speed;
	bool active;

} Laser;

typedef struct Spaceship {
	Texture2D image;
	Vector2 position;
	Laser lasers[MAX_LASERS];
	double lastFireTime;
} Spaceship;

typedef struct Alien {
	Vector2 position;
	bool active;
} Alien;


#endif // !_TYPEDEFS_
