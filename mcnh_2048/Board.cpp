//
// Created by Mariusz on 24.09.2016.
//

#include "Board.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <utility>
#include <vector>
#include <windows.h>
#include <string>


Board::Board() : points(0) {

}

Board::~Board() {

}

void Board::show_table(void) {
	for (short y = 0; y<4; y++) {
		for (short x = 0; x<4; x++) {
			std::cout << std::setw(5);
			std::cout << this->table[x][y].get_value();
		}
		std::cout << std::endl;
	}
}

void Board::add_new(void) {
	std::vector<std::pair<short, short>> free_locations;
	for (short x = 0; x<4; x++) {
		for (short y = 0; y<4; y++) {
			if (this->table[x][y].get_value() == 0) {
				free_locations.push_back({ x,y });
			}
		}
	}
	std::pair<short, short> new_loc = free_locations[rand() % free_locations.size()];
	this->table[new_loc.first][new_loc.second] = Block(2);
	return;
}
void Board::push_table(dir direction) {
	std::array<std::array<Block, 4>, 4> transposed;
	bool happened = false;
	for (short x = 0; x<4; x++) {
		for (short y = 0; y<4; y++) {
			switch (direction) {
			case dir::up:
				transposed[x][y] = this->table[x][y];
				break;
			case dir::down:
				transposed[x][y] = this->table[x][3 - y];
				break;
			case dir::left:
				transposed[x][y] = this->table[y][x];
				break;
			case dir::right:
				transposed[x][y] = this->table[3 - y][3 - x];
				break;
			}
		}
	}
	for (auto& col : transposed) {
		for (short y1 = 0; y1<3; y1++) {
			if (col[y1].get_value() != 0) {
				for (auto y2 = y1 + 1; y2<4 && (col[y2] == col[y1] || col[y2].get_value() == 0); y2++) {
					if (col[y2] == col[y1]) {
						col[y1] + col[y2];
						points += col[y1].get_value();
						//OutputDebugString((std::to_string(points)+"\n").c_str());
						happened = true;
						break;
					}
				}
			}
		}
		bool done;
		while (true) {
			done = true;
			for (short y1 = 0;y1<3;y1++) {
				if (col[y1].get_value() == 0) {
					for (short y2 = y1 + 1;y2<4; y2++) {
						if (col[y2].get_value() != 0) {
							col[y1] = col[y2];
							col[y2] = Block(0);
							happened = true;
							done = false;
							break;
						}
					}
				}
			}
			if (done) {
				break;
			}
		}
	}
	for (short x = 0; x<4; x++) {
		for (short y = 0; y<4; y++) {
			switch (direction) {
			case dir::up:
				this->table[x][y] = transposed[x][y];
				break;
			case dir::down:
				this->table[x][3 - y] = transposed[x][y];
				break;
			case dir::left:
				this->table[y][x] = transposed[x][y];
				break;
			case dir::right:
				this->table[3 - y][3 - x] = transposed[x][y];
				break;
			}
		}
	}
	if (happened) {
		this->add_new();
	}
	return;
}

std::vector<showBlock> Board::get_blocks(void)
{
	std::vector<showBlock> blocks;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (table[x][y].get_value()) {
				blocks.push_back(showBlock(table[x][y].get_value(), x, y));
			}
		}
	}
	return blocks;
}

void Board::better_move(dir direction)
{
	struct TraceBlock{
		int old_x;
		int old_y;
		Block block;
	};
	std::array<std::array<TraceBlock, 4>, 4> transposed;
	bool happened = false;
	for (short x = 0; x<4; x++) {
		for (short y = 0; y<4; y++) {
			switch (direction) {
			case dir::up:
				transposed[x][y] = { x,y,table[x][y] };
				break;
			case dir::down:
				transposed[x][y] = { x,3- y ,table[x][3 - y] };
				break;
			case dir::left:
				transposed[x][y] = { y, x, table[y][x] };
				break;
			case dir::right:
				transposed[x][y] = { 3-y, 3-x, table[3 - y][3 - x] };
				break;
			}
		}
	}
	for (auto& col : transposed) {
		for (short y1 = 0; y1<3; y1++) {
			if (col[y1].block.get_value() != 0) {
				for (auto y2 = y1 + 1; y2<4 && (col[y2].block == col[y1].block || col[y2].block.get_value() == 0); y2++) {
					if (col[y2].block == col[y1].block) {
						col[y1].block + col[y2].block;
						col[y1].old_x = col[y2].old_x;
						col[y1].old_y = col[y2].old_y;
						points += col[y1].block.get_value();
						happened = true;
						break;
					}
				}
			}
		}
		bool done;
		while (true) {
			done = true;
			for (short y1 = 0;y1<3;y1++) {
				if (col[y1].block.get_value() == 0) {
					for (short y2 = y1 + 1;y2<4; y2++) {
						if (col[y2].block.get_value() != 0) {
							col[y1] = col[y2];
							col[y2].block = Block(0);
							happened = true;
							done = false;
							break;
						}
					}
				}
			}
			if (done) {
				break;
			}
		}
	}
	if (happened) {
		std::array<std::array<TraceBlock, 4>, 4> detransposed;
		for (short x = 0; x<4; x++) {
			for (short y = 0; y<4; y++) {
				switch (direction) {
				case dir::up:
					detransposed[x][y] = transposed[x][y];
					break;
				case dir::down:
					detransposed[x][3 - y] = transposed[x][y];
					break;
				case dir::left:
					detransposed[y][x] = transposed[x][y];
					break;
				case dir::right:
					detransposed[3 - y][3 - x] = transposed[x][y];
					break;
				}
			}
		}
		ticks_left = 20;
		movement.clear();
		for (short x = 0; x < 4; x++) {
			for (short y = 0; y < 4; y++) {
				table[x][y] = detransposed[x][y].block;
				if (table[x][y].get_value()) {
					movement.push_back({ x,y,x - detransposed[x][y].old_x,y - detransposed[x][y].old_y});
				}
			}
		}
		add_new();
	}
	return;


}


