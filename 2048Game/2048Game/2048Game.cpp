// 2048Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include"Menu.h";
#include"Gra.h"

using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Menu - 2048", sf::Style::Close | sf::Style::Titlebar); //Stworzenie okna menu
    int jaka = 2;       //Id rozmiar planszy
    string opcjeOpcji[7] = { "2x2","3x3","4x4","5x5","6x6","7x7","8x8"};        //Zbiór opcji menu planszy
    string opcjeMenu[3] =  { "URUCHOM",opcjeOpcji[jaka],"ZAMKNIJ"};             //Zbiór opcji menu
    Menu menu(window.getSize().x,opcjeMenu);            //Wywo³anie obiektu menu
    window.setKeyRepeatEnabled(false);          //Wyl¹czenie przytrzymania klawisza, przytrzymanie klawisza = 1 nacisk
    char* wileko; //Zmiena przetrzymuj¹ca wybran¹ opcje menu planszy

    while (window.isOpen())
    {
        sf::Event evet;
        while (window.pollEvent(evet))
        {
            switch (evet.type) {            //Switch sprawdzaj¹cy typ eventu
            case sf::Event::KeyReleased:        //Klawisz puszczony
                switch (evet.key.code)          //Switch sprawdzaj¹cy jaki kalwisz wcisnieto
                {
                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    menu.DoDolu();              //menu ruch do do³u
                    break;
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    menu.DoGory();              //do góry
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    if (jaka > 0) {             //sprawdzanie czy s¹ jescze w dan¹ strinê dostêpne opcje*
                        jaka--;                     //min array
                        menu.OptionRefresh(opcjeOpcji[jaka]); // Odœwie¿enie renderowania menu*
                    }
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    if (jaka < (sizeof(opcjeOpcji) / sizeof(opcjeOpcji[0]) - 1)) {
                        jaka++;                                     //max array
                        menu.OptionRefresh(opcjeOpcji[jaka]);       //to samo co w * tylko w drug¹ stronê
                    }
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Space:
                case sf::Keyboard::Enter:       //Uruchomienie gry
                    switch (menu.KliknietaOpcja())
                    {
                    case 0:
                    {
                        cout << "Uruchom kliknieto\n";
                        wileko = &opcjeOpcji[jaka][0];      //pod zmienna zapisujemy 1 znak z stringa
                        srand(time(NULL));                  //do psedo losowoœci
                        sf::RenderWindow game(sf::VideoMode(800, 900), "2048", sf::Style::Close | sf::Style::Titlebar); //generujemy okienko gry
                        game.setKeyRepeatEnabled(false);
                        Gra gra(game.getSize().x, game.getSize().y, atoi(wileko));          //towrrzymy obiekt gra z parametrami(szer,wys i liczba(wilekosc planszy))
                        sf::Event evet2;
                        while (game.isOpen()) {
                            while (game.pollEvent(evet2)) {
                                if (evet2.type == sf::Event::Closed)
                                    game.close();
                                switch (evet2.type) {
                                case sf::Event::KeyReleased:
                                    if (evet2.key.code == sf::Keyboard::Escape)
                                        game.close();
                                    if (evet2.key.code == sf::Keyboard::R) {
                                        gra.Restart();                          //R restartuje grê
                                    }
                                    break;
                                }
                                gra.OnEvent(evet2);
                            }

                            gra.Update();

                            game.clear(sf::Color(222, 230, 233));       //ustawiamy tlo gry
                            gra.Renderowanie(game);                     //renderujemy okno gry
                            game.display();                             //wyswietlamy
                        }
                        break;
                    }
                    //case 1:
                    //    cout << "Opcje " << opcjeOpcji[jaka] << "\n";
                    //    break;
                    case 2:
                        window.close();
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear(sf::Color(222, 230, 233));     //tlo menu ustawiamy
        menu.Draw(window);
        window.display();
    }
       return 0;
}

