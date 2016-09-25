#pragma once

#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Board.h"
#include "Block.h"
#include <map>

class GameMain
{
public:
	GameMain(void);
	~GameMain(void);
	void run_loop(void);
	void make_move(dir);
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event* mainEvent;
	Board board;
	SDL_Texture* background_image;
	SDL_Rect* background_rect;
	static void setRect(SDL_Rect* rect, int x, int y, int w, int h);
	const int blockSize = 70;
	const int spaceBetweenBlocks = 10;
	const int topOffset = 145;
	const int leftOffset = 25;
	const int windowWidth = 360;
	const int windowHeight = 480;
	std::map<int, SDL_Texture*> block_images;
	vector<SDL_Rect> block_rects;
	const int xd = 0;
};

