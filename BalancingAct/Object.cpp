#include "Object.h"

/**** Public ****/

Object::Object(const float& fallSpeed, const float& x, const float& y, const ObjectType& objectType) : m_speed(fallSpeed), m_x(x), m_y(y), m_type(objectType)
{}

ObjectType Object::getType() const
{
  return m_type;
}

byte Object::getWeight() const
{
  return m_weight;
}

float Object::getX() const
{
  return m_x;
}

float Object::getY() const
{
  return m_y;
}

void Object::updateObject()
{
  m_y++;
}

void Object::updateObject(const float& posStep)
{
  m_x += posStep;
}
