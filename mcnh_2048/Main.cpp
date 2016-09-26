#include <iostream>
#include "Block.h"
#include "Board.h"
#include "GameMain.h"
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_image.h"

int main(int argc, char *argv[]) {
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	GameMain game;
	game.run_loop();
	return 0;
}