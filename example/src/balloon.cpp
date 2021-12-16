#include <balloon.hpp>
#include <iostream>


namespace mt
{
    Balloon::Balloon(int type, int x, int y)//, int type
    {
        m_x = x;
        m_y = y;
        m_type = type;
        if (m_type == 1) // обычные
        {
            m_speed = (rand() % 4) + 1;
            m_r = 35;
            m_circle = new sf::CircleShape(m_r);
            m_circle->setFillColor(sf::Color((rand() % 230), (rand() % 230), rand() % 230));
        }
        else if (m_type == 2) // Большие и медленные
        {
            m_speed = (rand() % 2) + 1;
            m_r = 45;
            m_circle = new sf::CircleShape(m_r);
            m_circle->setFillColor(sf::Color((rand() % 230), 0, 0));
        }
        else if (m_type == 3) // Маленькие и быстрые
        {
            m_speed = 6;
            m_r = 25;
            m_circle = new sf::CircleShape(m_r);
            m_circle->setFillColor(sf::Color(0, (rand() % 230), 0));
        }
        else if (m_type == 10) // Технические
        {
            m_speed = 0;
            m_r = 80;
            m_circle = new sf::CircleShape(m_r);
            m_circle->setFillColor(sf::Color((rand() % 200), (rand() % 230), rand() % 200));
        }




        m_circle->setOrigin(0 + m_r, 0 + m_r);
        m_circle->setPosition(m_x, m_y);

        m_circle->setOutlineThickness(2.f);
        m_circle->setOutlineColor(sf::Color(0, 0, 0));
    }
    Balloon::~Balloon()
    {
        if (m_circle != nullptr)
            delete m_circle;

    }
    void Balloon::BMoveY()
    {
        m_y -= m_speed;
        m_circle->setPosition(m_x, m_y);
    }
    sf::CircleShape* Balloon::Get()
    {
        return m_circle;
    }
    void Balloon::SetSpeed(int speed)
    {
        m_speed = speed;
    }
    int Balloon::GetY()
    {
        return m_y;
    }
    int Balloon::GetX()
    {
        return m_x;
    }
    int Balloon::GetR()
    {
        return m_r;
    }
    void Balloon::SetX(int x)
    {
        m_x = x;
    }
    void Balloon::SetY(int y)
    {
        m_y = y;
    }
    void Balloon::SetColorRed()
    {
        m_circle->setFillColor(sf::Color::Red);
    }
}
