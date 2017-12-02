#include "level.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"

#include "starblock.h"

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