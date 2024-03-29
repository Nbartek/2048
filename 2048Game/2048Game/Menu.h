#pragma once

#include<SFML/Graphics.hpp>
#include<string>
#define OPCJE 3			//ilosc mozliwych opcji
class Menu
{
public:
	Menu(int wymiary,std::string a[OPCJE]);		//kreator z parametrami
	~Menu();
	void DoGory();								// ruch do g�ry
	void DoDolu();								// ruch do do�u
	void OptionRefresh(std::string a);			//odswierzenie opcji
	void Draw(sf::RenderWindow& window);		// renderowanie
	int KliknietaOpcja() { return wybranaOpcja; }


private:
	int opcje;
	sf::Font czcionka;
	int wybranaOpcja;
	sf::Text menu[OPCJE];
	sf::Text tytul;


};

