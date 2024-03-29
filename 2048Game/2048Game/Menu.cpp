#include "Menu.h"
#include<SFML/Graphics.hpp>
#include<iostream>
Menu::Menu(int wymiary, std::string a[OPCJE])
{
    if (!czcionka.loadFromFile("Oswald-VariableFont_wght.ttf")) {
        std::cout << "Nie udalo sie wczytac pliku z czcionka\n";    //wczytywanie czcionki i test czy sie uda³o
    }
    else { std::cout<<"Czcionka jest!!\n"; }
    /*
        kreator ustawia dla ka¿dej opcji w menu parametry takie jak czcionka,kolor,napis,wielkosc i pozycje zale¿n¹ od ilosci opcji
    */
    tytul.setFont(czcionka);
    tytul.setFillColor(sf::Color(103, 78, 124));
    tytul.setString("2048 - Bartek Nosek");
    tytul.setPosition(sf::Vector2f(20, wymiary / (OPCJE + 2) * 1));
    tytul.setCharacterSize(40);

    menu[0].setFont(czcionka);
    menu[0].setFillColor(sf::Color(246, 124, 95));
    menu[0].setString(a[0]);
    menu[0].setPosition(sf::Vector2f(20, wymiary / (OPCJE + 2) * 2));

    menu[1].setFont(czcionka);
    menu[1].setFillColor(sf::Color(246, 124, 95));
    menu[1].setString(a[1]);
    menu[1].setPosition(sf::Vector2f(wymiary/2, wymiary / (OPCJE + 2)  *2));

    menu[2].setFont(czcionka);
    menu[2].setFillColor(sf::Color(97, 118, 123));
    menu[2].setString(a[2]);
    menu[2].setPosition(sf::Vector2f(20, wymiary / (OPCJE + 2) * 3));

    wybranaOpcja = 0; //ustawia która opcja jest wybrana jako podstawowa

}

Menu::~Menu()
{
}

void Menu::DoGory()
{
    //if (wybranaOpcja - 1 >= 0) {
    //    menu[wybranaOpcja].setFillColor(sf::Color::Black);
    //    wybranaOpcja--;
    //    menu[wybranaOpcja].setFillColor(sf::Color::Green);
    //}
    if (wybranaOpcja == 2) { wybranaOpcja = 0; }
    menu[2].setFillColor(sf::Color(97, 118, 123));      //Podswietla która opcja jest na razie wybrana
    menu[0].setFillColor(sf::Color(246, 124, 95));
    menu[1].setFillColor(sf::Color(246, 124, 95));
}

void Menu::DoDolu()
{
    //if (wybranaOpcja + 1 < OPCJE) {
    //    menu[wybranaOpcja].setFillColor(sf::Color::Black);
    //    wybranaOpcja++;
    //    menu[wybranaOpcja].setFillColor(sf::Color::Green);
    //}
    if (wybranaOpcja == 0) { wybranaOpcja = 2; }
    menu[0].setFillColor(sf::Color(97, 118, 123));      //zmienia kolor wybranej opcji
    menu[1].setFillColor(sf::Color(97, 118, 123));
    menu[2].setFillColor(sf::Color(246, 124, 95));
}

void Menu::OptionRefresh(std::string a)
{
    menu[1].setString(a);                   //Odwieza opcje rozmiaru planszy
}

void Menu::Draw(sf::RenderWindow& window)
{
    window.draw(tytul);                 //po kolei renderuje menu
    for (int i = 0; i < OPCJE;i++) {
        window.draw(menu[i]);
    }
}
