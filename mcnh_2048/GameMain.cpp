#include "GameMain.h"
#include <iostream>
#include <string>


GameMain::GameMain(void)
{
	window = SDL_CreateWindow("2048 by MCNH", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = std::make_shared<SDL_Event>();
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	OpenSans = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 12);
	_ASSERTE(OpenSans!=NULL);
	test_surf = SDL_CreateRGBSurface(0, 100, 100, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

	test_surf = TTF_RenderText_Solid(OpenSans, "test", white);
	test_text = SDL_CreateTextureFromSurface(renderer, test_surf);
	
	_ASSERTE(test_text != NULL, "dupa");
	background_image = IMG_LoadTexture(renderer, "bg.bmp");
	for (int num : {2, 4, 8, 16}) {
		string file_to_open = "blocks/" + std::to_string(num) + ".bmp";
		block_images[num] = IMG_LoadTexture(renderer, file_to_open.c_str());
	}
	board.add_new();
	block_drawer = std::make_unique<BlockDrawer>(board, renderer);
}


GameMain::~GameMain(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(background_image);
	for (auto& texture : block_images) {
		SDL_DestroyTexture(texture.second);
	}
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
		for (auto block : board.get_blocks()) {
			//SDL_Rect newBlock;
			block_rects.push_back(SDL_Rect());
			setRect(&block_rects.back(),leftOffset + (blockSize+spaceBetweenBlocks)*block.x ,topOffset + (blockSize + spaceBetweenBlocks)*block.y,blockSize,blockSize);
			SDL_RenderCopy(renderer, block_images[block.value], nullptr, &block_rects.back());
		//	SDL_RenderCopy(renderer, )
		}
		//SDL_RenderFillRect(renderer, &test_rect);
		setRect(&test_rect, 0, 0, test_surf->w, test_surf->h);
		SDL_RenderCopy(renderer, test_text, nullptr, &test_rect);
		setRect(&test_rect, 100, 100, test_surf->w, test_surf->h);
		SDL_RenderCopy(renderer, test_text, nullptr, &test_rect);
		block_drawer->test_draw_nums();
		//SDL_RenderDrawRect(renderer, &test_rect);
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
