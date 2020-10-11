#ifndef object_h
#define object_h

#include <Arduboy2.h>

enum class ObjectType : unsigned char
{
    BOX, ELEPHANT, LUGGAGE, WEIGHT,
};

class Object : public Printable
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
         * @implements print
         * Allows passing object to arduboy.print
         */
        size_t printTo(Print& p) const
        {
          size_t line = 0;
          size_t x = Arduboy2::getCursorX();
          size_t y = Arduboy2::getCursorY();
          
          line += p.print(this->getName());

          y += 8;

          Arduboy2::setCursor(x, y);
          line += p.print("Weight");

          y += 8;

          Arduboy2::setCursor(x, y);
          line += p.print(this->getWeight());

          return line;
        }

        /**
         * Update this object's y position
         */
         void updateObject();

         /**
          * Update this objects x position
          */
          void updateObject(const float& posStep);
         
    private:
        byte m_index = 0;

        float m_speed = 0;
        float m_x = 0;
        float m_y = 0;
};

#endif //object_h
