#pragma once
#include <SFML/Graphics.hpp>

namespace mt
{
    class Balloon
    {
    public:
        Balloon(int type, int x, int y);

        ~Balloon();

        void BMoveY();

        sf::CircleShape* Get();

        void SetSpeed(int speed);

        int GetY();

        int GetX();

        int GetR();

        void SetX(int x);

        void SetY(int y);

        void SetColorRed();


    private:
        int m_x, m_y, m_r, m_type, m_speed;

        sf::CircleShape* m_circle = nullptr;
    };
}