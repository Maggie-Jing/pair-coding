#include <SDL.h>
#include <stdio.h>
#include <string>
#include "LiveOperate.h"

#include <gtest/gtest.h>
//#define _UNIT_TEST

//单元测试：
TEST(CheckLiveTest, PosAt00)
{
	bool live[5][5] = {
		{ 0, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0 }
	};

	vector<vector<bool> > world;
	for (int i = 0; i < 5; ++i)
	{
		vector<bool> temp;
		for (int j = 0; j < 5; ++j)
		{
			temp.push_back(live[i][j]);
		}
		world.push_back(temp);
	}

	LiveOperate lo;
	lo.init(world, 5, 5);

	EXPECT_EQ(true, lo.checkLive(Point(0, 0)));
}

TEST(CheckLiveTest, shouldBe1WhenSroundingLess3Atom)
{
	bool live[5][5] = {
		{ 0, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0 }
	};

	vector<vector<bool> > world;
	for (int i = 0; i < 5; ++i)
	{
		vector<bool> temp;
		for (int j = 0; j < 5; ++j)
		{
			temp.push_back(live[i][j]);
		}
		world.push_back(temp);
	}

	LiveOperate lo;
	lo.init(world, 5, 5);

	EXPECT_EQ(true, lo.checkLive(Point(1, 1)));
}

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int rows = 100;
const int cols = 100;

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

//The window renderer    全局渲染器
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
				MyGame.randomInit(rows, cols);
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
#ifdef _UNIT_TEST
	testing::InitGoogleTest(&argc, args);
	return RUN_ALL_TESTS();
#else

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
				SDL_Delay(30);
				MyGame.updateLive();



				//SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();


	return 0;
#endif
}


void DrawRect() {

	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 225);
	for (int i = 0; i < MyGame.getCols(); i++)
	{
		for (int j = 0; j < MyGame.getRows(); j++)
		{
			if (MyGame.getWorld()[i][j])
			{

				SDL_Rect rect = { i * 2,j * 2, 2, 2 };
				SDL_RenderFillRect(gRenderer, &rect);
			}
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 225);
}