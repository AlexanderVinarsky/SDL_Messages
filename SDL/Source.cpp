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

	double x1, y1, x2, y2;
	int sx1, sy1, sx2, sy2;
	double scale = 1.0;

	bool rising = true;
	int point_count = 3;

	while (true)
	{
	#pragma region Draw Lines 
		SDL_SetRenderDrawColor(ren, 230, 230, 230, 255);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 100, 100, 230, 255);

		x1 = -200, y1 = 0, x2 = 200, y2 = 0;

		mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
		mathCoordsToScreen(x2, y2, scale, win_width / 2, win_height / 2, sx2, sy2);

		SDL_RenderDrawLine(ren, sx1, sy1, sx2, sy2);
		
		x1 = 0, y1 = -200, x2 = 0, y2 = 200;

		mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
		mathCoordsToScreen(x2, y2, scale, win_width / 2, win_height / 2, sx2, sy2);

		SDL_RenderDrawLine(ren, sx1, sy1, sx2, sy2);

	#pragma endregion

		SDL_Point* points = (SDL_Point*)malloc(sizeof(SDL_Point) * (point_count + 1));

		float alpha = 0;
		for (int i = 0; i < point_count; i++)
		{
			alpha += 2 * M_PI / point_count;
			mathCoordsToScreen(200 * cos(alpha), 200 * sin(alpha), scale, win_width / 2, win_height / 2, points[i].x, points[i].y);
		}
		points[point_count] = points[0];

		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawLines(ren, points, point_count + 1);

		SDL_RenderPresent(ren);

		SDL_Delay(250);

		if (rising)
			point_count++;
		else
			point_count--;

		if (rising && point_count > 10 || !rising && point_count <= 3)
			rising = !rising;
		free(points);
	}

	DeInit(0);
	return 0;
}