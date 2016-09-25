//
// Created by Mariusz on 24.09.2016.
//

#include "Block.h"
#include <iostream>

using namespace std;

Block::Block() {
	value = 0;
}

Block::~Block() {

}

int Block::get_value() {
	return this->value;
}

Block::Block(int _val) : value(_val) {
}

Block Block::operator+(Block &rhs) {
	if (this->get_value() != rhs.get_value()) {
		return Block(0);
	}
	this->value *= 2;
	rhs.value = 0;
	return *this;
}

bool Block::operator==(Block &rhs) {
	return this->get_value() == rhs.get_value();
}


