#include <SDL.h>
#include <stdio.h>
#include <string>
#include "LiveOperate.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

LiveOperate MyGame;

//Loads individual image  
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL; 

//The window renderer    È«¾ÖäÖÈ¾Æ÷
SDL_Renderer* gRenderer = NULL;


//Current displayed image
SDL_Surface* gCurrentSurface = NULL; 

void DrawRect();


bool init()
{

	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Life Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				MyGame.randomInit(15, 15);
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 225);
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	return success;
}

void close()
{

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}


int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_RenderClear(gRenderer);
				DrawRect();
				SDL_RenderPresent(gRenderer);
				SDL_Delay(500);
				MyGame.updateLive();



				//SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();

	return 0;
}

void DrawRect() {

	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 225);
	for (int i = 0; i < MyGame._cols; i++)
	{
		for (int j = 0; j < MyGame._rows; j++)
		{
			if (MyGame._world[i][j])
			{

				SDL_Rect rect = { i * 50,j * 50,50,50 };
				SDL_RenderFillRect(gRenderer, &rect);
			}
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 225);
}