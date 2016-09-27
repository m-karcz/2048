#pragma once

#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "SDL_ttf.h"
#include "Board.h"
#include "Block.h"
#include <map>
#include <memory>
#include "BlockDrawer.h"

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
	std::shared_ptr<SDL_Event> mainEvent;
	Board board;
	SDL_Texture* background_image;
	static void setRect(SDL_Rect* rect, int x, int y, int w, int h);
	const int blockSize = 70;
	const int spaceBetweenBlocks = 10;
	const int topOffset = 145;
	const int leftOffset = 25;
	const int windowWidth = 360;
	const int windowHeight = 480;
	//std::map<int, SDL_Texture*> block_images;
	vector<SDL_Rect> block_rects;
	SDL_Rect test_rect;
	SDL_Surface* test_surf;
	SDL_Texture* test_text;
	std::unique_ptr<BlockDrawer> block_drawer;
	SDL_Color white = { 255,255,255,255 };
	TTF_Font* OpenSans;
};

