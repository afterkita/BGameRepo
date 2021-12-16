// Подключение графической библиотеки
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <balloon.hpp>
#include <iostream>

#include <vector>
#include <thread>

#include <string>
#include <fstream>
#include <cmath>
#include <ctime>


#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
using namespace std;
using namespace sf;



int main()
{
    srand(time(0));
    int N = 6; // Количество шаров в начале игры
    sf::Time u = sf::seconds(0.002f); // Задержка между циклами(ФПС)

    int gover = 0; // Постоянные значения
    const int width = 1000;
    const int height = 650;
    const int R = 30;
    int xx, yy, tsize = 60;
    int kof;

    sf::Text text;
    sf::Text score;
    sf::Font font;

    font.loadFromFile("fonts/arial.ttf"); // Настройки текстов
    text.setFont(font);
    text.setString("");
    text.setOrigin(tsize / 2, tsize / 2);
    text.setCharacterSize(tsize);
    text.setFillColor(Color(0, 0, 0));
    text.setStyle(sf::Text::Bold);

    score.setFont(font);
    score.setString("");
    score.setCharacterSize(tsize / 3);
    score.setFillColor(Color(10, 0, 0));
    score.setStyle(sf::Text::Bold);

    sf::RenderWindow window(sf::VideoMode(width, height), "BGame", sf::Style::Close);
    window.setFramerateLimit(120);

    sf::Texture texture1;
    sf::Texture texture2;
    if (!texture1.loadFromFile("img/Btown.png")) //Подгрузка заднего фона
    {
        return -1;
    }
    if (!texture2.loadFromFile("img/Btown2.jpg")) //Подгрузка 2 заднего фона
    {
        return -1;
    }
    texture1.setRepeated(true);
    texture2.setRepeated(true);
    sf::Sprite sprite(texture1);
    if (rand() % 2 == 0)
    {
        sf::Sprite sprite(texture2);
    }


    std::vector<mt::Balloon*> ballons; // Инициализация вектора с шарами для игры и создание первых фигур
    for (int i = 0;i < N;i++)
    {
        ballons.push_back(new mt::Balloon(1, R + (rand() % (width + R)), height - 100));
    }
    std::vector<mt::Balloon*> modes; // Инициализация вектора с шарами выбора режима
    for (int i = 0;i < 3;i++)
    {
        modes.push_back(new mt::Balloon(10, (width / 4) * (i + 1), height - 200));
    }

    int key = 0; // Переменная отвечающая за начало и конец игры
    int mod = 0;
    unsigned int start_time = clock();
    while (window.isOpen()) // Общее тело игры
    {
        sf::Event event;
        while (key == 0) // Пока key = 0, грузится начало игры
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left) // Выбор режима и начало игры
                    {
                        xx = event.mouseButton.x;
                        yy = event.mouseButton.y;
                        for (int i = 0;i < 3;i++)
                        {
                            if (sqrt((pow(xx - modes[i]->GetX(), 2)) + (pow(yy - modes[i]->GetY(), 2))) <= modes[i]->GetR())
                            {
                                mod = i;
                                key = 1;
                                gover = 0;
                                for (int f = 0;f < 3;f++)
                                {
                                    ballons.push_back(new mt::Balloon(1, R + rand() % (width - R - R), height - 100));
                                }
                            }
                        }
                    }
                }
            }

            window.clear(Color(200, 200, 200, 0));
            text.setString(L"Выберите режим игры:");
            text.setPosition(200, 100);
            window.draw(text);
            for (int i = 0;i < 3;i++)
            {
                text.setString(std::to_string(i + 1));
                text.setPosition(modes[i]->GetX() + 10, modes[i]->GetY() - 10);

                window.draw(*modes[i]->Get());
                window.draw(text);
            }
            window.display();
        }
        N = ballons.size(); // Подсчёт оставшихся шаров на экране

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    xx = event.mouseButton.x;
                    yy = event.mouseButton.y;
                    for (int i = 0;i < N;i++)
                    {
                        if (sqrt((pow(xx - ballons[i]->GetX(), 2)) + (pow(yy - ballons[i]->GetY(), 2))) <= ballons[i]->GetR())
                        {
                            if (N > 0)
                            {
                                ballons.erase(ballons.begin() + i);
                                N = ballons.size();
                                i = 0;
                            }
                        }
                    }
                }

            }

        }
        window.clear(Color(100, 100, 100, 0)); // Задний фон
        window.draw(sprite);

        score.setString(L" пропущенно " + std::to_string(gover) + L" из " + std::to_string(6 - mod));
        window.draw(score);

        for (const auto& circle : ballons)
        {
            circle->BMoveY();
            window.draw(*circle->Get());
        }

        /*
        for (int i = 0;i < N;i++) // Движение и отрисовка шаров
        {
            ballons[i].BMoveY();
            window.draw(ballons[i].Get());
        }
        */



        for (int i = 0;i < N;i++)
        {
            if (ballons[i]->GetY() + R <= 0) // Проверка на прохождение верхней границы
            {
                if (N > 0)
                {
                    ballons.erase(ballons.begin() + i);
                    N = ballons.size();
                    i = 0;
                    gover++;
                }
            }
        }
        if (gover >= 6 - mod) // Проверка на окончание игры
        {
            while (key == 1)
            {
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left) // Выход из игры
                        {
                            return 0;
                        }
                        if (event.mouseButton.button == sf::Mouse::Right) // Новое начало игры
                        {
                            N = ballons.size();
                            for (int i = 0;i < N;i++)
                            {
                                if (N > 0)
                                {
                                    ballons.erase(ballons.begin());
                                }
                            }

                            key = 0;
                        }
                    }
                }
                // Текст после поражения
                window.clear(Color(200, 100, 100, 0));
                text.setString(L"Поражение");
                text.setPosition(350, 200);
                window.draw(text);
                text.setString(L"ПКМ играть ещё, ЛКМ выход");
                text.setPosition(100, 400);
                window.draw(text);
                window.display();
            }
        }

        window.display();
        N = ballons.size();
        std::cout << N << std::endl;
        unsigned int end_time = clock();
        if (end_time - start_time >= 700) // Проверка по окончанию промежутка времени
        {
            if (ballons.size() == 0) // Проверка на окончание игры
            {
                while (key == 1)
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();
                        if (event.type == sf::Event::MouseButtonPressed)
                        {
                            if (event.mouseButton.button == sf::Mouse::Left) // Выход из игры
                            {
                                return 0;
                            }
                            if (event.mouseButton.button == sf::Mouse::Right) // Новое начало игры
                            {
                                key = 0;
                            }
                        }
                    }
                    // Текст после победы
                    window.clear(Color(100, 200, 100, 0));
                    text.setString(L"Победа!");
                    text.setPosition(400, 200);
                    window.draw(text);
                    text.setString(L"ПКМ играть ещё, ЛКМ выход");
                    text.setPosition(100, 400);
                    window.draw(text);
                    window.display();
                }
            }
            int ra = rand() % (mod * 3 - 1); // Создание новых сфер в зависимости от уровня сложности
            start_time = clock();
            for (int j = 0;j < ra;j++)
            {
                kof = rand() % 50;
                if (kof % 3 == 0)
                {
                    kof = 2;
                }
                else if (kof % 5 == 0)
                {
                    kof = 3;
                }
                else
                {
                    kof = 1;
                }
                ballons.push_back(new mt::Balloon(kof, 40 + (rand() % (width - 80)), height - (rand() % 50)));
            }

        }
        //sleep(u);
    }

    return 0;
}