// 2048Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "2048 - Bartlomiej Nosek",sf::Style::Close|sf::Style::Titlebar);
    sf::RectangleShape square(sf::Vector2f(100,100));
    square.setFillColor(sf::Color::Red);
    //square.setSize(sf::Vector2f(50, 50));

    while (window.isOpen())
    {
        sf::Event evet;
        while (window.pollEvent(evet))
        {
            switch (evet.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                if(evet.text.unicode<128)
                printf("%c",evet.text.unicode);
            }


        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            square.move(sf::Vector2f(0.3, 0.0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            square.move(sf::Vector2f(-0.3, 0.0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            square.move(sf::Vector2f(0.0, 0.3));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            square.move(sf::Vector2f(0.0, -0.3));
        }
        window.clear(sf::Color::White);
        window.draw(square);
        window.display();
    }

    return 0;
}

