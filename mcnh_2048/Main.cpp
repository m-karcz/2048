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
	//Board board;
	GameMain game;
	game.run_loop();
	/*board.show_table();
	board.add_new();
	char in = 'a';
	while (in != 'q') {
		switch (in) {
		case 'w':
			board.push_table(dir::up);
			break;
		case 'a':
			board.push_table(dir::left);
			break;
		case 's':
			board.push_table(dir::down);
			break;
		case 'd':
			board.push_table(dir::right);
			break;
		}
		board.show_table();
		cin >> in;
	}*/
	return 0;
}