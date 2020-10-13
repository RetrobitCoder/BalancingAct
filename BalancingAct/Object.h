#ifndef object_h
#define object_h

#include <Arduboy2.h>

enum class ObjectType : unsigned char
{
    BOX, ELEPHANT, LUGGAGE, WEIGHT,
};

class Object
{
    public:
        Object(const float& fallSpeed, const float& x, const float& y, const ObjectType& objectType);
        ~Object() {};

        /**
         * Handles getting type as string
         */
        String getName() const;

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
         * Hanldes printing object info to the screen
         * @param arduboy reference for print function
         */
        void printTo(const Arduboy2& arduboy) const;

        /**
         * Update this object's y position
         */
         void updateObject();

         /**
          * Update this objects x/y position
          * @param fastDrop, when true, increase fall speed (y pos)
          */
          void updateObject(const float& posStep, const bool& fastDrop);
         
    private:
        byte m_index = 0;

        float m_speed = 0;
        float m_x = 0;
        float m_y = 0;
};

#endif //object_h
