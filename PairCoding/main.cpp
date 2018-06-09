#include <SDL.h>
#include <stdio.h>
#include <string>
#include "LiveOperate.h"

#include <gtest/gtest.h>
//#define _UNIT_TEST

//单元测试：
TEST(CollectAroundNumber, shouldBe1WhenSroundingLessthan3Atom)
{
	int live[5][5] = {
		{ 0, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0 }
	};

	LiveOperate lo;
	lo.setWorld(live, 5, 5);

	EXPECT_EQ(1, lo.collectAliveNaber(0, 0));
	EXPECT_EQ(3, lo.collectAliveNaber(1, 1));
	EXPECT_EQ(2, lo.collectAliveNaber(4, 4));
	EXPECT_EQ(3, lo.collectAliveNaber(2, 4));
	EXPECT_EQ(1, lo.collectAliveNaber(0, 4));
}


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int a_w = 10;
const int a_h = 10;

const int rows = 80;
const int cols = 80;
const int colors[][4] = { { 255, 51, 204,225 },{ 255, 153,0,225 },{ 204, 153, 204,255 },{ 102, 255, 204,255 },{ 255, 99, 71,255 },{ 238, 238, 0,255 }
,{ 209, 238, 238,255 },{ 139, 99, 108,255 } };



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
				MyGame.init(rows, cols);
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
			bool flag_sigle_frame = true;
			bool shouldUpdateLive = true;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (e.key.keysym.sym == SDLK_RETURN&&e.type == SDL_KEYDOWN)
					{
							flag_sigle_frame = !flag_sigle_frame;
							shouldUpdateLive = true;
					}
				}
				
				
				if (shouldUpdateLive) {
					SDL_RenderClear(gRenderer);
					DrawRect();
					SDL_RenderPresent(gRenderer);
					MyGame.updateLive();
					if (flag_sigle_frame)
						shouldUpdateLive = false;
				}
				cout << shouldUpdateLive << " " << flag_sigle_frame << endl;
				SDL_Delay(500);



				//SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();


	return 0;
#endif
}


void DrawRect() {

	cout << MyGame.getCols() << " " << MyGame.getRows() << endl;
	for (int i = 0; i < MyGame.getRows(); i++)
	{
		for (int j = 0; j < MyGame.getCols(); j++)
		{
			if (MyGame.getWorld(i, j))
			{
				int color = rand() % 8;
				SDL_SetRenderDrawColor(gRenderer, colors[color][0], colors[color][1], colors[color][2], colors[color][3]);
				SDL_Rect rect = { i * a_w,j * a_h, a_w, a_h };
				SDL_RenderFillRect(gRenderer, &rect);
			}
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 225);
}