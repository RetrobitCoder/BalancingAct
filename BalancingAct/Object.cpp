#include "Object.h"

String objectNames[4] = {"Box", "Elephnt", "Luggage", "Weight"};
byte objectWeights[4] = {10, 130, 50, 100};

/**** Public ****/

Object::Object(const float& fallSpeed, const float& x, const float& y, const ObjectType& objectType) : m_speed(fallSpeed), m_x(x), m_y(y)
{
    //wanted to index objectWeights using the ObjectType enum but arduino is not liking that

    switch(objectType)
    {
        case ObjectType::BOX:
            m_index = 0;
            break;
        case ObjectType::ELEPHANT:
            m_index = 1;
            break;
        case ObjectType::LUGGAGE:
            m_index = 2;
            break;
        case ObjectType::WEIGHT:
            m_index = 3;
            break;
    }
}

String Object::getName() const
{
    return objectNames[m_index];
}

byte Object::getWeight() const
{
    return objectWeights[m_index];
}

float Object::getX() const
{
    return m_x;
}

float Object::getY() const
{
    return m_y;
}

void Object::printTo(const Arduboy2& arduboy) const
{
    size_t x = Arduboy2::getCursorX();
    size_t y = Arduboy2::getCursorY();

    arduboy.print(this->getName());

    y += 8;

    Arduboy2::setCursor(x, y);
    arduboy.print("Weight");

    y += 8;

    Arduboy2::setCursor(x, y);
    arduboy.print(this->getWeight());
}

void Object::updateObject()
{
    m_y += m_speed;
}

void Object::updateObject(const float& posStep, const bool& fastDrop)
{
    if(fastDrop) m_y += posStep;
    else m_x += posStep;
}
