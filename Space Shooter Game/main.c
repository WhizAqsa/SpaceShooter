#include<raylib.h>
#include<stdio.h>

#include "TypeDefs.h"
#include "Alien.h"
#include "Laser.h"
#include "Spaceship.h"
#include "Obstacle.h"


// Global vars
Alien aliens[ALIEN_SIZE];
Obstacle obstacles[OBSTACLES_SIZE];
Spaceship s;

int main() {
	

	//creating an object of window 
   //specifying its width, height and title

	const int WIDTH = 800;
	const int HEIGHT = 600;

	Color grey = { 29,29,27,255 };
	
	InitWindow(WIDTH, HEIGHT, "Space Shooter Game");
	SetTargetFPS(60);

	/*SPACESHIP*/
	//load image here
	Image spaceshipImage = LoadImage("images/spaceship.png");
	s.image = LoadTextureFromImage(spaceshipImage);
	s.position.x = (GetScreenWidth() - spaceshipImage.width)/2;
	s.position.y = GetScreenHeight()-spaceshipImage.height;
	s.lastFireTime = 0.0;

	// Initialize the spaceship's lasers
	for (int i = 0; i < MAX_LASERS; i++) {
		s.lasers[i].active = false;
	}

	CreateObstacles(obstacles);
	InitializeAliens(aliens);


	//game loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(grey);

		// Draw all the sprites
		DrawTextureV(s.image, s.position, WHITE);
		for (int i = 0; i < OBSTACLES_SIZE; i++)
		{
			DrawObstacle(&obstacles[i]);
		}
		DrawAliens(aliens);

		// Input Handlings
		if (IsKeyDown(KEY_LEFT)) {
			MoveLeft(&s);  //function call
			if (s.position.x < 0) {
				s.position.x = 0;
			}
		}
		if (IsKeyDown(KEY_RIGHT)) {
			MoveRight(&s);
			if (s.position.x > GetScreenWidth() - spaceshipImage.width) {
				s.position.x = GetScreenWidth() - spaceshipImage.width;
			}
		}
		if (IsKeyDown(KEY_SPACE)) {
			FireLaser(&s);
		}

		// Collision detection
		for (int i = 0; i < MAX_LASERS; i++) {
			Laser* laser = &s.lasers[i];
			if (!laser->active) continue;

			HandleObstalesCollisionsWithLaser(laser, obstacles);
			HandleAlienCollisionsWithLaser(laser, aliens);
		}


		// Updating States
		UpdateLasers(&s);
		UpdateAliens(aliens);

		EndDrawing();
	}
	//unload spaceship texture and image
	UnloadImage(spaceshipImage);
	UnloadTexture(s.image);

	

	CloseWindow();
	

	return 0;
}