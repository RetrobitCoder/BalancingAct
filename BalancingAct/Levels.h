#ifndef levels_h
#define levels_h

#include <Arduboy2.h>

#include "Object.h"

const byte MAX_NUM_LVLS = 2;
const byte MAX_NUM_OBJS = 2;

Object levels[MAX_NUM_LVLS][MAX_NUM_OBJS] = {{Object(0.01, 1, 1, ObjectType::ELEPHANT), Object(0.02, 2, 2, ObjectType::ELEPHANT)},{Object(3, 3, 3, ObjectType::BOX), Object(4, 4, 4, ObjectType::BOX)}}; // TODO add more levels

#endif //levels_h
