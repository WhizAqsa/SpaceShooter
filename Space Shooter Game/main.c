#include<raylib.h>
#include<stdio.h>

#define MAX_SIZE 10 //for lasers
#define GRID_ROWS 13 
#define GRID_COL 23
#define PIXEL_SIZE 3
#define OBSTACLES_SIZE 4
#define SPACESHIP_SIZE 64
#define LASER_HEIGHT 15
#define LASER_WIDTH 4


typedef struct {
	int x;
	int y;
	int speed;
	bool active;

}Laser;

typedef struct{
	Texture2D image;
	Vector2 position;
	Laser lasers[MAX_SIZE];  //array to store the lasers fired by spaceship
	double lastFireTime;
}Spaceship;

typedef struct {
	int x;
	int y;
	Color color;
}Block;
typedef struct {
	int x;
	int y;
	int grid[GRID_ROWS][GRID_COL];
}Obstacle;

//update laser
void UpdateLaser(Laser* laser) {
	laser->y += laser->speed;
	if (laser->active) {
		if (laser->y > GetScreenHeight() || laser->y < 0) {
			laser->active = false;
			printf("Laser Inactive!");
		}
	}
}

//function
//to move the spaceship to the left
void Spaceship_MoveLeft(Spaceship* spaceship) {
	spaceship->position.x -= 7;
}
//function
//to move the spaceship to the right
void Spaceship_MoveRight(Spaceship* spaceship) {
	spaceship->position.x += 7;
}
// Function to fire the laser
void FireLaser(Spaceship* spaceship) {
	if (GetTime() - spaceship->lastFireTime >= 0.35) {
		for (int i = 0; i < MAX_SIZE; i++) {
			if (!spaceship->lasers[i].active) {
				spaceship->lasers[i].x = spaceship->position.x + spaceship->image.width / 2 - 2;
				spaceship->lasers[i].y = spaceship->position.y;
				spaceship->lasers[i].speed = -6;
				spaceship->lasers[i].active = true;
				spaceship->lastFireTime = GetTime();
				break;
			}
		}
	}
}
// Function to update the game
void UpdateGame(Spaceship* spaceship) {
	for (int i = 0; i < MAX_SIZE; i++) {
		if (spaceship->lasers[i].active) {
			UpdateLaser(&spaceship->lasers[i]);
			DrawRectangle(spaceship->lasers[i].x, spaceship->lasers[i].y, LASER_WIDTH, LASER_HEIGHT, RED);
		}
	}
}

//function to create a block
void DrawObstacle(Obstacle* obstacle) {
	
	for (unsigned int row = 0; row < GRID_ROWS; row++) {
		for (unsigned int col = 0; col < GRID_COL; col++) {
			if (obstacle->grid[row][col] == 1) {
				float pos_x = obstacle->x + col * PIXEL_SIZE;
				float pos_y = obstacle->y + row * PIXEL_SIZE;
				DrawRectangle(pos_x, pos_y, PIXEL_SIZE, PIXEL_SIZE, RED);
			}
		}
	}
}

//function to create an obstacle

void CreateObstacles(Obstacle obstacles[]) {
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
		obstacle.y = GetScreenHeight() - SPACESHIP_SIZE * 2 - obstacleHeight;
		memcpy(obstacle.grid, shieldPixelArt, sizeof(shieldPixelArt));

		obstacles[i] = obstacle;
	}
}

//get LaserRectangle
Rectangle getLaserRectangle(Laser* laser) {
	Rectangle rect;
	rect.x = laser->x;
	rect.y = laser->y;
	rect.width = LASER_WIDTH;
	rect.height = LASER_HEIGHT;
	return rect;
}

int main() {
	

	//creating an object of window 
   //specifying its width, height and title

	const int WIDTH = 800;
	const int HEIGHT = 600;

	Color grey = { 29,29,27,255 };
	
	InitWindow(WIDTH, HEIGHT, "Space Shooter Game");
	SetTargetFPS(60);

	/*SPACESHIP*/
	Spaceship s;
	//load image here
	Image spaceshipImage = LoadImage("images/spaceship-sprite.png");
	s.image = LoadTextureFromImage(spaceshipImage);
	s.position.x = (GetScreenWidth() - spaceshipImage.width)/2;
	s.position.y = GetScreenHeight()-spaceshipImage.height;
	s.lastFireTime = 0.0;

	// Initialize the spaceship's lasers
	for (int i = 0; i < MAX_SIZE; i++) {
		s.lasers[i].active = false;
	}

	Obstacle obstacles[OBSTACLES_SIZE];
	CreateObstacles(obstacles);

	//for checking collisions
	bool checkCollisions = false;


	//game loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(grey);

		UpdateGame(&s);
		//TEXT DRAWING FUNCTION
		//taking text, posX, posY, font size and color as arguments

		//for moving spaceship
		if (IsKeyDown(KEY_LEFT)) {
			Spaceship_MoveLeft(&s);  //function call
			if (s.position.x < 0) {
				s.position.x = 0;
			}
		}
		if (IsKeyDown(KEY_RIGHT)) {
			Spaceship_MoveRight(&s);
			if (s.position.x > GetScreenWidth() - spaceshipImage.width) {
				s.position.x = GetScreenWidth() - spaceshipImage.width;
			}
		}
		if (IsKeyDown(KEY_SPACE)) {
			FireLaser(&s);
		}

		//draw texture here
		DrawTextureV(s.image, s.position, WHITE);

		// Collision detection
		for (int i = 0; i < MAX_SIZE; i++) {
			Laser* laser = &s.lasers[i];

			if (!laser->active) continue;

			//In case defensive obstacle damages due to collision with lasers
			for (int j = 0; j < OBSTACLES_SIZE; j++) {
				Obstacle* ob = &obstacles[j];
				if (laser->y <= ob->y) continue;
				if (laser->x < ob->x) continue;
				if (laser->x > ob->x + GRID_COL * PIXEL_SIZE) continue;
				
				
				for (unsigned int row = 0; row < GRID_ROWS; row++) {
					for (unsigned int col = 0; col < GRID_COL; col++) {
						if (ob->grid[row][col] == 1) {
							float pos_x = ob->x + col * PIXEL_SIZE;
							float pos_y = ob->y + row * PIXEL_SIZE;
							Rectangle obstacleRect = { pos_x, pos_y, PIXEL_SIZE, PIXEL_SIZE };

							if (CheckCollisionRecs(getLaserRectangle(laser), obstacleRect)) {
								ob->grid[row][col] = 0;
								laser->active = false;
								break;
							}
						}

					}
				}
			}
		}

		for (int i = 0; i < OBSTACLES_SIZE; i++)
		{
			DrawObstacle(&obstacles[i]);
		}

		EndDrawing();
	}
	//unload spaceship texture and image
	UnloadImage(spaceshipImage);
	UnloadTexture(s.image);

	

	CloseWindow();
	

	return 0;
}