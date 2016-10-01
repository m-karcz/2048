#include "GameMain.h"
#include <iostream>
#include <string>


GameMain::GameMain(void)
{
	window = SDL_CreateWindow("2048 by MCNH", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = std::make_shared<SDL_Event>();
	background_image = IMG_LoadTexture(renderer, "bg.bmp");
	board.add_new();
	block_drawer = std::make_unique<BlockDrawer>(board, renderer);
}


GameMain::~GameMain(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(background_image);
}

void GameMain::run_loop(void)
{
	while (mainEvent->type != SDL_QUIT) {
		SDL_PollEvent(mainEvent.get());
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_image, nullptr, nullptr);
		switch (mainEvent->type) {
		case SDL_KEYDOWN:
			switch (mainEvent->key.keysym.sym) {
			case SDLK_w:
				std::cout << "w" << std::endl;
				make_move(dir::up);
				break;
			case SDLK_a:
				std::cout << "a" << std::endl;
				make_move(dir::left);
				break;
			case SDLK_s:
				std::cout << "s" << std::endl;
				make_move(dir::down);
				break;
			case SDLK_d:
				std::cout << "d" << std::endl;
				make_move(dir::right);
				break;
			}
			break;
		}
		block_rects.clear();
		if (board.ticks_left) {
			block_drawer->better_draw();
		}
		else {
			for (auto block : board.get_blocks()) {
				block_drawer->draw_block(block.x, block.y);
			}
		}
		block_drawer->draw_points();
		SDL_RenderPresent(renderer);
	}
	return;
}

void GameMain::make_move(dir here)
{
	//board.push_table(here);
	board.better_move(here);
	return;
}

void GameMain::setRect(SDL_Rect * rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return;
}
