#include <raylib.h>

#ifndef _TYPEDEFS_
#define _TYPEDEFS_

#define SPACESHIP_WIDTH 64
#define SPACESHIP_HEIGHT 52
#define MAX_LASERS 10
#define LASER_HEIGHT 15
#define LASER_WIDTH 4

#define MAX_BULLETS 5

#define PIXEL_SIZE 3
#define OBSTACLES_SIZE 4

#define GRID_ROWS 13 
#define GRID_COL 23

#define LEVEL_WIDTH 8

#define ALIEN_SPEED 3

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
	int lives;
} Spaceship;

typedef struct Bullet {
	int x;
	int y;
	int speed;
	bool active;
}Bullet;

/**
* Here is the explanation for Alien
* 1. Lives is int because it shows how many bullets are required to kill this alien
* 2. type int:
*   - 0 -> Simple type, just fires after some delay and with the given probability, has 1 life
*   - 1 -> Fires and can randomly goes to player current position at that time and comes back if not killed, has 2 lives
*   - 2 -> Fires in the direction of player, and has 3 lives.
*/
typedef struct Alien {
	Vector2 position;
	int lives;
	int type;
	Texture2D image;
	Bullet bullets[MAX_BULLETS];
	float fireRate;
	float fireTimer;
} Alien;


#endif // !_TYPEDEFS_
