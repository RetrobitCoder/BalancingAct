#ifndef levels_h
#define levels_h

#include <Arduboy2.h>

#include "Object.h"

const byte MAX_NUM_LVLS = 4;
const byte MAX_NUM_OBJS = 6;

const byte WIDTH_OFFSET = 48; // also used in main file
const byte START_X = (WIDTH - WIDTH_OFFSET) / 2;
const byte START_Y = 1;
const float FALL_SPEED = 0.01;

Object levels[MAX_NUM_LVLS][MAX_NUM_OBJS] =
{
    {Object(FALL_SPEED, START_X, START_Y, ObjectType::BOX), Object(FALL_SPEED, START_X, START_Y, ObjectType::LUGGAGE), Object(FALL_SPEED, START_X, START_Y, ObjectType::WEIGHT), Object(FALL_SPEED, START_X, START_Y, ObjectType::ELEPHANT), Object(FALL_SPEED, START_X, START_Y, ObjectType::BOX), Object(FALL_SPEED, START_X, START_Y, ObjectType::LUGGAGE)},
    {Object(FALL_SPEED * 2, START_X, START_Y, ObjectType::LUGGAGE), Object(FALL_SPEED * 3, START_X, START_Y, ObjectType::BOX), Object(FALL_SPEED * 3, START_X, START_Y, ObjectType::LUGGAGE), Object(FALL_SPEED * 3, START_X, START_Y, ObjectType::BOX), Object(FALL_SPEED * 3, START_X, START_Y, ObjectType::ELEPHANT), Object(FALL_SPEED * 3, START_X, START_Y, ObjectType::WEIGHT),},
    {Object(FALL_SPEED * 3, START_X, START_Y, ObjectType::ELEPHANT), Object(FALL_SPEED * 4, START_X, START_Y, ObjectType::ELEPHANT), Object(FALL_SPEED * 4, START_X, START_Y, ObjectType::LUGGAGE), Object(FALL_SPEED * 4, START_X, START_Y, ObjectType::WEIGHT), Object(FALL_SPEED * 4, START_X, START_Y, ObjectType::WEIGHT), Object(FALL_SPEED * 4, START_X, START_Y, ObjectType::LUGGAGE)},
    {Object(FALL_SPEED * 5, START_X, START_Y, ObjectType::ELEPHANT), Object(FALL_SPEED * 5, START_X, START_Y, ObjectType::BOX), Object(FALL_SPEED * 5, START_X, START_Y, ObjectType::LUGGAGE), Object(FALL_SPEED * 5, START_X, START_Y, ObjectType::WEIGHT), Object(FALL_SPEED * 5, START_X, START_Y, ObjectType::LUGGAGE), Object(FALL_SPEED * 5, START_X, START_Y, ObjectType::ELEPHANT)}
};

#endif //levels_h
