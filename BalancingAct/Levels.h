#ifndef levels_h
#define levels_h

#include <Arduboy2.h>

#include "Object.h"

const byte MAX_NUM_LVLS = 2;
const byte MAX_NUM_OBJS = 4;

const byte WIDTH_OFFSET = 48; // also used in main file
const byte START_X = (WIDTH - WIDTH_OFFSET) / 2;
const byte START_Y = 1;

Object levels[MAX_NUM_LVLS][MAX_NUM_OBJS] =
{
    {Object(0.01, 1, 1, ObjectType::BOX), Object(0.02, 2, 2, ObjectType::ELEPHANT), Object(0.03, 3, 3, ObjectType::LUGGAGE), Object(0.04, 4, 4, ObjectType::WEIGHT)},
    {Object(3, 3, 3, ObjectType::BOX), Object(4, 4, 4, ObjectType::BOX), Object(0.02, 2, 2, ObjectType::BOX), Object(0.02, 2, 2, ObjectType::BOX)}
}; // TODO add more levels

#endif //levels_h
