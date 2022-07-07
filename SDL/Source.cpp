#include<SDL.h>
#include <iostream>

SDL_Window* win;
SDL_Renderer* ren;

void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}
void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Couldn't init SDL! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	win = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1000, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (win == NULL)
	{
		printf("Couldn't create window! Error: %s", SDL_GetError());
		system("pause");
		DeInit(2);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren = NULL)
	{
		printf("Couldn't create renderer! Error: %s", SDL_GetError());
		system("pause");
		DeInit(3);
	}
}

int main(int argc, char* argv[])
{
	Init();

	SDL_Init(0);

	SDL_Quit();
	return 0;
}