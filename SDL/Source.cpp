#include<SDL.h>
#include <iostream>
#include <cmath>

SDL_Window* win;
SDL_Renderer* ren;

int win_width = 600, win_height = 600;

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
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (win == NULL)
	{
		printf("Couldn't create window! Error: %s", SDL_GetError());
		system("pause");
		DeInit(2);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Couldn't create renderer! Error: %s", SDL_GetError());
		system("pause");
		DeInit(3);
	}
}
double circle(double x, double x0, double y0, double rad)
{
	return sqrt(rad * rad - (x - x0) * (x - x0)) + y0;
}
void mathCoordsToScreen(double x, double y, double scale, int centerx, int centery, int &sx, int &sy)
{
	sx = round(centerx + x * scale);
	sy = round(centery - y * scale);
}

int main(int argc, char* argv[])
{
	Init();

	SDL_SetRenderDrawColor(ren, 230, 230, 230, 255);
	SDL_RenderClear(ren);
	for (int i = 0; i < 300; i++)
	{
		SDL_SetRenderDrawColor(ren, 150+2*i, 75+2*i, 150+i, 255);
		SDL_RenderDrawLine(ren, 0, i, win_width, i);
		SDL_RenderDrawLine(ren, 0, win_height - 1 - i, win_width, win_height - 1 - i);
		SDL_RenderDrawLine(ren, i, 0, i, win_height);
		SDL_RenderDrawLine(ren, win_width - 1 - i, 0, win_width - 1 - i, win_height);
		SDL_Delay(20);
		SDL_RenderPresent(ren);
	}

	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	int sx1, sy1, sx2, sy2;
	double scale = 2.5;

	mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
	mathCoordsToScreen(x2, y2, scale, win_width / 2, win_height / 2, sx1, sy1);

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

	SDL_Rect r = { 0,0,6,6 };

	//Descartes Coordinates
	/*
	for (x1 = 0; x1 <= 360; x1 += 10.0)
	{
		y1 = circle(x1, 0, 0, 100);
		mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
		r.x = sx1 - 3;
		r.y = sy1 - 3;
		SDL_RenderDrawPoint(ren, sx1, sy1);
		SDL_RenderFillRect(ren, &r);

		y1 = -y1;
		mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
		r.x = sx1 - 3;
		r.y = sy1 - 3;
		SDL_RenderDrawPoint(ren, sx1, sy1);
		SDL_RenderFillRect(ren, &r);
		SDL_RenderPresent(ren);
	}
	*/

	double radius = 100;
	//Polar Coordinates
	for (double alpha = 0; alpha <= 360; alpha += 10.0)
	{
		x1 = radius * cos(alpha * M_PI / 180.0);
		y1 = radius * sin(alpha * M_PI / 180.0);

		mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
		r.x = sx1 - 3;
		r.y = sy1 - 3;
		SDL_RenderFillRect(ren, &r);

		SDL_Delay(100);
		SDL_RenderPresent(ren);
	}

	SDL_Delay(5000);
	DeInit(0);
	return 0;
}