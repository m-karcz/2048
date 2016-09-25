#pragma once

#ifndef _2048_BLOCK_H
#define _2048_BLOCK_H


class Block {
public:
	Block();
	~Block();
	Block(int);
	int get_value();
	Block operator +(Block&);
	bool operator==(Block&);
private:
	int value;
};

struct showBlock {
	showBlock(int _value, int _x, int _y) : value(_value), x(_x), y(_y) {}
	int value;
	int x;
	int y;
};
#endif //_2048_BLOCK_H
