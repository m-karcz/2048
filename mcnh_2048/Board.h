#pragma once
//
// Created by Mariusz on 24.09.2016.
//

#ifndef _2048_BOARD_H
#define _2048_BOARD_H

#include <array>
#include <vector>
#include <utility>
#include "Block.h"

using namespace std;

enum dir {
	up,
	down,
	left,
	right
};


class Board {
public:
	Board();
	~Board();
	void show_table(void);
	void add_new(void);
	void push_table(dir);
	vector<showBlock> get_blocks(void);
private:
	array<array<Block, 4>, 4> table;
};


#endif //_2048_BOARD_H


