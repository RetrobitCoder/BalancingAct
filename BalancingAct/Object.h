#ifndef object_h
#define object_h

#include <Arduboy2.h>

enum class ObjectType : unsigned char
{
    BOX, ELEPHANT, LUGGAGE, WEIGHT
};

class Object
{
    public:
        Object(const float& fallSpeed, const float& x, const float& y, const ObjectType& objectType);
        ~Object() {};

        /**
         * Get the ObjectType of this Object
         * @return ObjectType
         */
        ObjectType getType() const;

        /**
         * Get the weight of this object
         * @return weight
         */
        byte getWeight() const;

        /**
         * Get x position of this object
         * @return x position
         */
        float getX() const;

        /**
         * Get y position of this object
         * @return y position
         */
        float getY() const;

        /**
         * Update this object's y position
         */
         void updateObject();

         /**
          * Update this objects x position
          */
          void updateObject(const float& posStep);
         
    private:
        byte m_weight = 0;

        float m_speed = 0;
        float m_x = 0;
        float m_y = 0;

        ObjectType m_type;
};

#endif //object_h
