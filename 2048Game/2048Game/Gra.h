#pragma once
#include<vector>
//#include<SFML/Graphics/RenderTarget.hpp>
//#include<SFML/Graphics/Text.hpp>
//#include<SFML/Graphics/Font.hpp>
#include<SFML/System/Clock.hpp>
#include<SFML/Window/Event.hpp>
#include<SFML/Graphics.hpp>
#include<string>

//Podstawowe wielkosci
#define MARGINES_PLANSZY 40				
#define MARGINES_KAFELKA 20
#define DLUGOSC_ANIMACJI 0.1F 
class Gra
{
public:
	Gra(int szerokosc, int wysokosc, int rozmiar);		//kreator obiektu
	void OnEvent(sf::Event evet);						//Reakcja na przyciski, uruchamia ruch
	void Update();										//render polaczonego kafla/ konczenie animacji
	void Renderowanie(sf::RenderTarget& rt);			//Renderuje plansze
	void TworKafelka();									//Zrzuca kafelek na planszê
	void Restart();										//Restartuje grê
	void Final(bool moment);							//Sprawdza jak gra siê skonczy³a
private:
	void SetPlansza(int wilekoscPlansza) {				//Ustawia zmienna prywatn¹ z parametra$
		this->wilekoscPlansza = wilekoscPlansza;
	}	
	void SetSzerokosc(int szerokosc) {					//$
		this->szerokosc = szerokosc;
	}	
	void SetWysokossc(int wysokosc) {					//$
		this->wysokosc = wysokosc;
	}
	//~Gra();


	int szerokosc;
	int wysokosc;
	int licznikRuchow =0;
	int wynik=0;
	bool koniecGry;
	sf::Text koniec;
	sf::Text wynikWys;
	sf::Text licznikRuchowWys;
	int rozmiarKafelka;
	int wilekoscPlansza;
	char plansza[8][8] = {0};				//MAKSYMALNA WIELKOSC PLANSZY
	char planszaTemp[8][8] = {0};
	sf::Clock animaCzas;
	bool animaStatus;
	sf::Font czcionka;
	sf::Color KolorKafla(char kafel);
	sf::Color KolorLiczbyKafla(char kafel);
	std::string TekstKafla(char kafel);
	int wielkoscTekstu(char kafel);
	void ruch(char x, char y);											//Odpowiada za ruch kafelków, 
	//parametry pokazuj¹ w jak¹ stronê
	void polaczenie(sf::Vector2i z, sf::Vector2i dokad, int x, int y);	//scalanie kafelków
	std::vector<std::pair<std::pair<sf::Vector2i,sf::Vector2i>,char>> ruchy; // ³¹czy polo¿enie z kafelkiem
	// [ ({x poczatek,y pocz¹tek},{x koniec, y koniec} ),kafelek ]


};

