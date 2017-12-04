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

Level::Level(int levelNum, bool isRandom, long seed, bool isSeed): 
  levelNum{levelNum}, isRandom{isRandom}, seed{seed}, isSeed{isSeed} {}

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

void Level::setSeed(long seedNum) {
	seed = seedNum;
}

void Level::setIsSeed(bool isseed) {
	isSeed = isseed;
}

Level::~Level() {}
