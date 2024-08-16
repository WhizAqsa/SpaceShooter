#include<raylib.h>
#include<stdio.h>


#include "TypeDefs.h"
#include "Alien.h"
#include "Laser.h"
#include "Spaceship.h"
#include "Obstacle.h"
#include "Bullet.h"

enum Screens
{
	startscreen,
	level1,
	level2,
	level3,
	nextlevelscreen,
	gameover,
	winscreen
};

// Global vars
Alien aliens[5][LEVEL_WIDTH];
Obstacle obstacles[OBSTACLES_SIZE];
Spaceship s;
int currentLevelHeight = 3;
int currentLevel = 1;

int levels[3][5][LEVEL_WIDTH] = {
	
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
	},
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
	},
	{
		{ 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
	}
};

/*
* Game won?
* Game over?
* Level completed?
*/


int main() {
	const int WIDTH = 800;
	const int HEIGHT = 600;

	Color grey = { 29,29,27,255 };
	
	InitWindow(WIDTH, HEIGHT, "Space Shooter Game");
	SetTargetFPS(60);

	int currentScreen = startscreen;

	ToggleFullscreen();

	Texture2D startBackgroundTexture = LoadTexture("images/start-background.png");

	// init spaceship
	Image spaceshipImage = LoadImage("images/spaceship.png");
	s.image = LoadTextureFromImage(spaceshipImage);
	s.position.x = ((float)GetScreenWidth() - spaceshipImage.width) / 2;
	s.position.y = GetScreenHeight() - spaceshipImage.height - BOTTOMBAR_HEIGHT;
	s.lastFireTime = 0.0;
	s.lives = 3;

	Image resizedSpaceshipImage = LoadImage("images/spaceship.png");
	ImageResize(&resizedSpaceshipImage, (int)resizedSpaceshipImage.width * 0.5, (int)resizedSpaceshipImage.height * 0.5);
	Texture2D resizedSpaceship = LoadTextureFromImage(resizedSpaceshipImage);

	// Initialize the spaceship's lasers
	for (int i = 0; i < MAX_LASERS; i++) {
		s.lasers[i].active = false;
	}

	// Initialize the alien's bullets
	for (int i = 0; i < currentLevelHeight; i++) {
		for (int j = 0; j < LEVEL_WIDTH; j++) {
			for (int k = 0; k < MAX_BULLETS; k++) {
				aliens[i][j].bullets[k].active = false; // Initialize bullets
			}
		}
	}

	InitializeObstacles(obstacles);
	InitializeAliens(aliens, levels[currentLevel - 1], currentLevelHeight);

	// text measure
	int levelTextWidth = MeasureText("LEVEL 00", 20);
	int highScoreTextWidth = MeasureText("HIGH SCORE", 20);
	int scoreTextHeight = 20;

	int score = 0;
	int highScore = 0;
	int prevScreen = startscreen;

	//game loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(grey);

		DrawTexture(startBackgroundTexture, 0, 0, WHITE);
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color) { 0, 0, 0, 190 });

		if (currentScreen == startscreen)
		{
			DrawText(
				"Space Shooter", 
				(GetScreenWidth() - MeasureText("Space Shooter", 32)) / 2, 
				GetScreenHeight() / 2 - 32 - 40, 
				32, 
				WHITE
			);

			// Button to start the game
			DrawRectangle(
				(GetScreenWidth() - 140) / 2,
				GetScreenHeight() / 2 + 10,
				140,
				40,
				ORANGE
			);
			DrawText(
				"Start",
				(GetScreenWidth() - MeasureText("Start", 20)) / 2,
				GetScreenHeight() / 2 + 20,
				20,
				WHITE
			);

			// handle this button click
			if (
				CheckCollisionPointRec(GetMousePosition(), (Rectangle) { (GetScreenWidth() - 140) / 2, GetScreenHeight() / 2 + 10, 140, 40 })
				&& IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				)
			{
				// reinitilize everything
				s.position.x = ((float)GetScreenWidth() - spaceshipImage.width) / 2;
				s.position.y = GetScreenHeight() - spaceshipImage.height - BOTTOMBAR_HEIGHT;
				s.lastFireTime = 0.0;
				s.lives = 3;

				currentLevel = 1;
				currentLevelHeight = 3;

				InitializeObstacles(obstacles);
				InitializeAliens(aliens, levels[currentLevel - 1], currentLevelHeight);

				currentScreen = level1;

				// Initialize the spaceship's lasers
				for (int i = 0; i < MAX_LASERS; i++) {
					s.lasers[i].active = false;
				}

				// Initialize the alien's bullets
				for (int i = 0; i < currentLevelHeight; i++) {
					for (int j = 0; j < LEVEL_WIDTH; j++) {
						for (int k = 0; k < MAX_BULLETS; k++) {
							aliens[i][j].bullets[k].active = false; // Initialize bullets
						}
					}
				}

				if (score > highScore) 
					highScore = score;
			}
		}
		else if (currentScreen == nextlevelscreen)
		{
			if (prevScreen == level3)
			{
				currentScreen = winscreen;
				continue;
			}

			DrawText(
				"You have passed the level",
				(GetScreenWidth() - MeasureText("You have passed the level", 32)) / 2,
				GetScreenHeight() / 2 - 32 - 40,
				32,
				WHITE
			);

			DrawRectangle(
				(GetScreenWidth() - 140) / 2,
				GetScreenHeight() / 2 + 10,
				140,
				40,
				ORANGE
			);
			DrawText(
				"Next",
				(GetScreenWidth() - MeasureText("Next", 20)) / 2,
				GetScreenHeight() / 2 + 20,
				20,
				WHITE
			);

			// handle this button click
			if (
				CheckCollisionPointRec(GetMousePosition(), (Rectangle) { (GetScreenWidth() - 140) / 2, GetScreenHeight() / 2 + 10, 140, 40 })
				&& IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				)
			{
				switch (prevScreen)
				{
				case level1:
					currentScreen = level2;
					currentLevel++;
					if (currentLevelHeight < 4) currentLevelHeight++;
					InitializeAliens(aliens, levels[currentLevel - 1], currentLevelHeight);
					break;

				case level2:
					currentScreen = level3;
					currentLevel++;
					if (currentLevelHeight < 4) currentLevelHeight++;
					InitializeAliens(aliens, levels[currentLevel - 1], currentLevelHeight);
					break;

				case level3:
					currentScreen = winscreen;
					break;
				}
			}

			
		}
		else if (currentScreen == level1 || currentScreen == level2 || currentScreen == level3)
		{
			// checking for win or lose states
			bool alienRemaining = 0;
			for (int j = 0; j < LEVEL_WIDTH; j++)
			{
				for (int i = 0; i < currentLevelHeight; i++)
				{
					if (aliens[i][j].lives > 0)
					{
						alienRemaining = 1;
						break;
					}
				}
				if (alienRemaining) break;
			}

			if (s.lives <= 0)
			{
				currentScreen = gameover;
			}
			else if (!alienRemaining)
			{
				prevScreen = currentScreen;
				currentScreen = nextlevelscreen;
			}

			char* currentLevelText = TextFormat("LEVEL %02d", currentLevel);

			// Draw all the sprites
			DrawTextureV(s.image, s.position, WHITE);

			for (int i = 0; i < OBSTACLES_SIZE; i++)
			{
				DrawObstacle(&obstacles[i]);
			}
			DrawAliens(aliens, currentLevelHeight);

			DrawLine(20, GetScreenHeight() - BOTTOMBAR_HEIGHT + 6, GetScreenWidth() - 20, GetScreenHeight() - BOTTOMBAR_HEIGHT + 6, ORANGE);

			// Display spaceships as lives
			for (int i = 0; i < s.lives; i++)
			{
				DrawTexture(
					resizedSpaceship,
					20 + i * resizedSpaceship.width + (i + 1) * 20,
					GetScreenHeight() - BOTTOMBAR_HEIGHT + 18,
					WHITE
				);
			}

			// Drawing text for current Level
			DrawText(currentLevelText, GetScreenWidth() - levelTextWidth - 20, GetScreenHeight() - BOTTOMBAR_HEIGHT + 18, 20, ORANGE);

			// Draw Score Stuff
			DrawText("SCORE", 40, 4, 20, ORANGE);
			DrawText("HIGH SCORE", GetScreenWidth() - 40 - highScoreTextWidth, 4, 20, ORANGE);
			DrawText(TextFormat("%05d", score), 40, 26, 20, ORANGE);
			DrawText(TextFormat("%05d", highScore), GetScreenWidth() - 40 - highScoreTextWidth, 26, 20, ORANGE);

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

			//Aliens bullet fire 
			for (int i = 0; i < currentLevelHeight; i++) {
				for (int j = 0; j < LEVEL_WIDTH; j++) {
					Alien* alien = &aliens[i][j];
					if (alien->lives > 0) {
						FireBullet(alien);
					}
				}
			}

			// Collision detection
			for (int i = 0; i < MAX_LASERS; i++) {
				Laser* laser = &s.lasers[i];
				if (!laser->active) continue;

				HandleObstalesCollisionsWithLaser(laser, obstacles);
				HandleAlienCollisionsWithLaser(laser, aliens, currentLevelHeight, &score);
			}

			for (int i = 0; i < currentLevelHeight; i++)
			{
				for (int j = 0; j < LEVEL_WIDTH; j++)
				{
					Alien* cur = &aliens[i][j];

					HandleBulletCollisionWithObstacles(obstacles, cur);
					HandleBulletCollisionWithSpaceship(&s, cur);
				}
			}

			// Updating States
			UpdateLasers(&s);
			UpdateAliens(aliens, currentLevelHeight);
		}
		else if (currentScreen == gameover)
		{
			DrawText(
				"Game Over",
				(GetScreenWidth() - MeasureText("Game Over", 32)) / 2,
				GetScreenHeight() / 2 - 32 - 40,
				32,
				WHITE
			);

			// Button to start the game
			DrawRectangle(
				(GetScreenWidth() - 230) / 2,
				GetScreenHeight() / 2 + 10,
				230,
				40,
				ORANGE
			);
			DrawText(
				"Go to start screen",
				(GetScreenWidth() - MeasureText("Go to start screen", 20)) / 2,
				GetScreenHeight() / 2 + 20,
				20,
				WHITE
			);

			// handle this button click
			if (
				CheckCollisionPointRec(GetMousePosition(), (Rectangle) { (GetScreenWidth() - 230) / 2, GetScreenHeight() / 2 + 10, 230, 40 })
				&& IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				)
			{
				currentScreen = startscreen;
			}
		}
		else if (currentScreen == winscreen)
		{
			DrawText(
				"Yeay! You Won the Game",
				(GetScreenWidth() - MeasureText("Yeay! You Won the Game", 32)) / 2,
				GetScreenHeight() / 2 - 32 - 40,
				32,
				WHITE
			);

			// Button to start the game
			DrawRectangle(
				(GetScreenWidth() - 200) / 2,
				GetScreenHeight() / 2 + 10,
				200,
				40,
				ORANGE
			);
			DrawText(
				"Want to replay?",
				(GetScreenWidth() - MeasureText("Want to replay?", 20)) / 2,
				GetScreenHeight() / 2 + 20,
				20,
				WHITE
			);

			// handle this button click
			if (
				CheckCollisionPointRec(GetMousePosition(), (Rectangle) { (GetScreenWidth() - 200) / 2, GetScreenHeight() / 2 + 10, 200, 40 })
				&& IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				)
			{
				currentScreen = startscreen;
			}
		}
		else {
			DrawText("Invalid screen provided. Please start with a valid screen.", 20, 20, 20, ORANGE);
		}

		


		EndDrawing();
	}
	//unload spaceship texture and image
	UnloadImage(spaceshipImage);
	UnloadTexture(s.image);

	

	CloseWindow();
	

	return 0;
}