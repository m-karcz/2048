#include "GameMain.h"
#include <iostream>
#include <string>


GameMain::GameMain(void)
{
	window = SDL_CreateWindow("2048 by MCNH", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
	background_rect = new SDL_Rect();
	background_image = IMG_LoadTexture(renderer, "bg.bmp");
	setRect(background_rect, 0, 0, windowWidth, windowHeight);
	for (int num : {2, 4, 8, 16}) {
		string file_to_open = "blocks/" + std::to_string(num) + ".bmp";
		block_images[num] = IMG_LoadTexture(renderer, file_to_open.c_str());
	}
	board.add_new();
}


GameMain::~GameMain(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(background_image);
	for (auto& texture : block_images) {
		SDL_DestroyTexture(texture.second);
	}
	delete mainEvent;
	delete background_rect;
}

void GameMain::run_loop(void)
{
	while (mainEvent->type != SDL_QUIT) {
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_image, nullptr, background_rect);
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
		for (auto block : board.get_blocks()) {
			//SDL_Rect newBlock;
			block_rects.push_back(SDL_Rect());
			setRect(&block_rects.back(),leftOffset + (blockSize+spaceBetweenBlocks)*block.x ,topOffset + (blockSize + spaceBetweenBlocks)*block.y,blockSize,blockSize);
			SDL_RenderCopy(renderer, block_images[block.value], nullptr, &block_rects.back());
		//	SDL_RenderCopy(renderer, )
		}
		SDL_RenderPresent(renderer);
	}
	return;
}

void GameMain::make_move(dir here)
{
	board.push_table(here);
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
