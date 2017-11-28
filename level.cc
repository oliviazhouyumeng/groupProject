#include "level.h"
#include "Block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"

#include "StarBlock.h"
#include "HintBlock.h"

using namespace std;

Level::Level(unsigned seed, bool isRandom, int levelNum): 
  seed{seed}, isRandom{isRandom}, levelNum{levelNum} {}

int Level::getLevel() const {
	return levelNum;
}
bool Level::getRandom() const{
	return isRandom;
}

void Level::setRandom(bool isR) {
	isRandom = isR;
}

unsigned Level::getSeed() const {
	return seed;
}

void Level::setSeed(unsigned seedNum) {
	seed = seedNum;
}

Level::~Level() {};