#include "Gra.h"

//dziala
Gra::Gra(int szerokosc, int wysokosc,int rozmiar)				
{
	rozmiarKafelka = (szerokosc - MARGINES_PLANSZY * 2 - MARGINES_KAFELKA * (rozmiar - 1)) / rozmiar;		//definuje wielkosc kafelka w porownaniu do danych rozmiarowych
	animaStatus = false;			
	if (!czcionka.loadFromFile("Oswald-VariableFont_wght.ttf"))
		printf("czciona sie nie wczytala - gra\n");
	SetSzerokosc(szerokosc);				//paremtry wpisywane s¹ do zmiennych wewnetrznych( co pozwala na ustawianie wielkoœci planszy
	SetWysokossc(wysokosc);
	SetPlansza(rozmiar);
	Restart();
}
//dziala
void Gra::OnEvent(sf::Event evet) {
	if (evet.type == sf::Event::KeyPressed) {
		if (animaStatus)
			return;

		sf::Keyboard::Key klaw = evet.key.code;
		if (koniecGry == true) { 
			Restart();
			koniecGry = false;
		}
		else {
			if (klaw == sf::Keyboard::Left || klaw == sf::Keyboard::A)
				ruch(-1, 0);												//po klikniêciu uruchamia siê funkcja ruch z parametrami
			else if (klaw == sf::Keyboard::Right || klaw == sf::Keyboard::D)
				ruch(1, 0);
			else if (klaw == sf::Keyboard::Up || klaw == sf::Keyboard::W)
				ruch(0, -1);
			else if (klaw == sf::Keyboard::Down || klaw == sf::Keyboard::S)
				ruch(0, 1);
		}

	}
}	 

//dziala
void Gra::Update()
{
	if (animaStatus) {										//czy zaacza siê animacja
		if (animaCzas.getElapsedTime().asSeconds() >= DLUGOSC_ANIMACJI) {	//if do wy³¹czenia animacji
			animaStatus = false;

			for (size_t i = 0; i < ruchy.size(); i++)			//dla ka¿dego kafelka wygenerowanego
			{
				sf::Vector2i pierwszy = ruchy[i].first.first;		//pocz¹tkowy vector2i
				sf::Vector2i drugi = ruchy[i].first.second;			//koncowy vektor2i

				char pocztVal = ruchy[i].second;					//id kafla poczatkowe
				char koncVal = plansza[drugi.x][drugi.y];			//tam gdzie po ruchu znajdzie sie kafel

				plansza[pierwszy.x][pierwszy.y] = 0;				//zerujemy miejsce pocz¹tkowe

				if (pocztVal == koncVal && pierwszy != drugi) {		//jesli id kafla na miejscu koncowym ruchu tego kafla bedzie takie samo
					plansza[drugi.x][drugi.y] = pocztVal + 1;		//zwiekszamy wartosc kafla koncowego
				}
				else {
					plansza[drugi.x][drugi.y] = pocztVal;			
				}
			}
			ruchy.clear();						//czyscimy caly wektor ruchów
			licznikRuchow++;
			TworKafelka();							//tworzenie kafelka
			return;
		}
	}
}


void Gra::Renderowanie(sf::RenderTarget& rt)
{	

		sf::Text text;
		text.setFont(czcionka);
		text.setStyle(sf::Text::Style::Bold);

		sf::RectangleShape kafel;
		kafel.setSize(sf::Vector2f(rozmiarKafelka, rozmiarKafelka));
		//rysujemy szkielet planszy i kafle
		for (int x = 0; x < wilekoscPlansza; x++) {
			for (int y = 0; y < wilekoscPlansza; y++) {
				kafel.setPosition(MARGINES_PLANSZY + x * (rozmiarKafelka + MARGINES_KAFELKA), MARGINES_PLANSZY + y * (rozmiarKafelka + MARGINES_KAFELKA));
				kafel.setFillColor(KolorKafla(plansza[x][y])); //bierzemy kolor kalfa

				rt.draw(kafel);

				if (plansza[x][y] != 0) {
					text.setCharacterSize(wielkoscTekstu(plansza[x][y]));
					text.setString(TekstKafla(plansza[x][y]));

					sf::FloatRect fr = text.getLocalBounds();
					text.setPosition(MARGINES_PLANSZY + x * (rozmiarKafelka + MARGINES_KAFELKA) + (rozmiarKafelka - fr.width) / 2 - fr.left, MARGINES_PLANSZY + y * (rozmiarKafelka + MARGINES_KAFELKA) + (rozmiarKafelka - fr.height) / 2 - fr.top);
					text.setFillColor(KolorLiczbyKafla(plansza[x][y]));

					rt.draw(text);
				}
			}
		}

		sf::Vector2i fMargines(MARGINES_PLANSZY, MARGINES_PLANSZY);
		//rysujemy animacje
		for (int i = 0; i < ruchy.size(); i++) { //dla kazdego kafla w ruchu
			sf::Vector2i orig = ruchy[i].first.first;		//orginalna pozycja
			sf::Vector2i f = fMargines + orig * (rozmiarKafelka + MARGINES_KAFELKA);
			sf::Vector2i t = fMargines + ruchy[i].first.second * (rozmiarKafelka + MARGINES_KAFELKA);

			float ruchWProcentach = (animaCzas.getElapsedTime().asSeconds() / DLUGOSC_ANIMACJI);		//jak szybko powinien sie kwadrat poruszaæ
			sf::Vector2f curPos = sf::Vector2f(f) + sf::Vector2f(t - f) * ruchWProcentach;			//terazniejsza pozycja

			text.setCharacterSize(wielkoscTekstu(ruchy[i].second)); // ustawiamy wielkosc napisu kafla
			text.setString(TekstKafla(ruchy[i].second));			//ustawiamy napis kafla

			sf::FloatRect fr = text.getLocalBounds();		//klasa do poruszania szescianami, ¿eby napis nie wyje¿dza³ spoza rogów kafla

			text.setPosition(curPos.x + (rozmiarKafelka - fr.width) / 2 - fr.left, curPos.y + (rozmiarKafelka - fr.height) / 2 - fr.top); //zmieniamy pozycje kafla
			text.setFillColor(KolorLiczbyKafla(ruchy[i].second));

			kafel.setPosition(curPos);
			kafel.setFillColor(KolorKafla(ruchy[i].second));
			// zmiana pozycji jest pomniejszana procentowo
			rt.draw(kafel);
			rt.draw(text);
		}
		//tekst do licznika ruchów
		licznikRuchowWys.setFont(czcionka);
		licznikRuchowWys.setFillColor(sf::Color(103, 78, 124));
		licznikRuchowWys.setString("Ilosc ruchów: " + std::to_string(licznikRuchow));
		licznikRuchowWys.setPosition(MARGINES_PLANSZY + szerokosc / 2, ((wysokosc - szerokosc) / 2) + szerokosc - MARGINES_PLANSZY);
		licznikRuchowWys.setCharacterSize(40);
		//wynik tekst
		wynikWys.setFont(czcionka);
		wynikWys.setFillColor(sf::Color(103, 78, 124));
		wynikWys.setString("Twoj wynik: " + std::to_string(wynik));
		wynikWys.setPosition(MARGINES_PLANSZY, ((wysokosc - szerokosc) / 2) + szerokosc - MARGINES_PLANSZY);
		wynikWys.setCharacterSize(40);
		rt.draw(licznikRuchowWys);
		rt.draw(wynikWys);
		rt.draw(koniec);
	
}


void Gra::TworKafelka()
{
	int ileoscKafli = 0; //wolnych kafli
	sf::Vector2i* mozliweRuchy = new sf::Vector2i[wilekoscPlansza * wilekoscPlansza];		//ilosc miejsc na miapie
	for (size_t x = 0; x < wilekoscPlansza; x++)
	{
		for (size_t y = 0; y < wilekoscPlansza; y++)
		{
			if (plansza[x][y] == 0) {								//jesli miejsce jest wolne
				mozliweRuchy[ileoscKafli] = sf::Vector2i(x, y);
				ileoscKafli++;
			}
		}
	}
	if (ileoscKafli == 0) {
		Restart();
		return;
	}
	sf::Vector2i newPozycja = mozliweRuchy[rand() % ileoscKafli]; // pseudolosowo wybieramy pozycjê
	char nowyKafelId = (rand() % 10);			//generujemy nowy kafel				
	if (nowyKafelId == 9)
	{
		nowyKafelId = 2;
	}
	else { nowyKafelId = 1; }
	plansza[newPozycja.x][newPozycja.y] = nowyKafelId; //przypisujemy nowy kafel na miesce

}

void Gra::Restart()
{
	wynik = 0;
	licznikRuchow = 0;
	koniec.setString("");
	for (size_t i = 0; i < wilekoscPlansza; i++)
	{
		for (size_t j = 0; j < wilekoscPlansza; j++)
		{
			plansza[i][j] = 0; //zerowanie mapy
		}
	}
	TworKafelka(); //generowanie pierwszego kafla
}

void Gra::Final(bool moment)
{
	//licznikRuchow--;
	if (moment) {		//jesli bool == true
		koniec.setFont(czcionka);
		koniec.setFillColor(sf::Color::Yellow);
		koniec.setString("WYGRANA\nR - restart");
		koniec.setPosition((szerokosc / 5 - MARGINES_PLANSZY)*2, (szerokosc / 5)*2);
		koniec.setCharacterSize(80);
	}
	else {
		koniec.setFont(czcionka);
		koniec.setFillColor(sf::Color::Red);
		koniec.setString("PRZEGRANA\nR - restart");
		koniec.setPosition((szerokosc / 5 - MARGINES_PLANSZY) * 2, (szerokosc / 5) * 2);
		koniec.setCharacterSize(80);
	}
	//rt.draw(koniec);
}
//na pewno dziala
sf::Color Gra::KolorKafla(char kafel)
{
	static const sf::Color kolory[] = {
	sf::Color(191, 209, 219, 97),		// pusty
	sf::Color(200, 203, 191),			//  2
	sf::Color(159, 177, 142),			//  4
	sf::Color(71, 154, 142),			//  8
	sf::Color(101, 129, 109),			//  16
	sf::Color(86, 104, 113),			//  32
	sf::Color(156, 179, 195),			//  64
	sf::Color(196, 131, 136),			//  128
	sf::Color(176, 78, 59),				//  256
	sf::Color(233, 54, 103),			//  512
	sf::Color(243, 131, 7),				//  1024
	sf::Color(249, 226, 26),			//  2048
	sf::Color(97, 12, 159)				//	4096
	};
	return kolory[kafel];
}

sf::Color Gra::KolorLiczbyKafla(char kafel)
{
	if (kafel >= 3) {
		return sf::Color(249, 246, 242);
	}
	return sf::Color(119,110,101);
}

std::string Gra::TekstKafla(char kafel)
{
	static const std::string text[] = { "","2","4","8","16","32","64","128","256","512","1024","2048","4096"};
	return text[kafel];
}

int Gra::wielkoscTekstu(char kafel)
{
	if (kafel >= 10) {
		return 35;
	}
	else if (kafel >= 7) {
		return 45;
	}
	else
		return 55;
}

void Gra::ruch(char dirX, char dirY)
{
	
for (int x = 0; x < wilekoscPlansza; x++)
	for (int y = 0; y < wilekoscPlansza; y++)
		planszaTemp[x][y] = plansza[x][y];		//ustawiamy macierz pomocnicz¹

if (dirX == -1) {
	for (int x = 1; x < wilekoscPlansza; x++) {
		for (int y = 0; y < wilekoscPlansza; y++) {
			if (planszaTemp[x][y] == 0)			//macierz pusta, pomijamy
				continue;

			sf::Vector2i finalPos = sf::Vector2i(x, y); //uznajemy ¿e siê kafelek nie poruszy

			for (int mx = x - 1; mx >= 0; mx--) {	//poruszamy sie w danej osi, sprawdzaj¹c czy kafle s¹ wolne
				finalPos = sf::Vector2i(mx, y);

				if (planszaTemp[mx][y] != 0)  //z czymœ siê zderzamy
					break;
			}

			polaczenie(sf::Vector2i(x, y), finalPos, dirX, dirY); //uruchamiamy funkcje polaczenia
		}
	}
}
else if (dirX == 1) {
	for (int x = wilekoscPlansza - 2; x >= 0; x--) {
		for (int y = 0; y < wilekoscPlansza; y++) {
			if (planszaTemp[x][y] == 0)
				continue;

			sf::Vector2i finalPos = sf::Vector2i(x, y);

			for (int mx = x + 1; mx < wilekoscPlansza; mx++) {
				finalPos = sf::Vector2i(mx, y);

				if (planszaTemp[mx][y] != 0)
					break;
			}

			polaczenie(sf::Vector2i(x, y), finalPos, dirX, dirY);
		}
	}
}
else if (dirY == -1) {
	for (int y = 1; y < wilekoscPlansza; y++) {
		for (int x = 0; x < wilekoscPlansza; x++) {
			if (planszaTemp[x][y] == 0)
				continue;

			sf::Vector2i finalPos = sf::Vector2i(x, y);

			for (int my = y - 1; my >= 0; my--) {
				finalPos = sf::Vector2i(x, my);

				if (planszaTemp[x][my] != 0)
					break;
			}

			polaczenie(sf::Vector2i(x, y), finalPos, dirX, dirY);
		}
	}
}
else if (dirY == 1) {
	for (int y = wilekoscPlansza - 2; y >= 0; y--) {
		for (int x = 0; x < wilekoscPlansza; x++) {
			if (planszaTemp[x][y] == 0)
				continue;

			sf::Vector2i finalPos = sf::Vector2i(x, y);

			for (int my = y + 1; my < wilekoscPlansza; my++) {
				finalPos = sf::Vector2i(x, my);

				if (planszaTemp[x][my] != 0)
					break;
			}

			polaczenie(sf::Vector2i(x, y), finalPos, dirX, dirY);
		}
	}
}

bool isFilled = true;
bool isGameOver = true;
for (int x = 0; x < wilekoscPlansza; x++) {
	for (int y = 0; y < wilekoscPlansza; y++) {
		if (planszaTemp[x][y] == 0) {
			isFilled = false;
			isGameOver = false;
			break;
		}

		char val = planszaTemp[x][y];

		if (x != 0 && planszaTemp[x - 1][y] == val)
			isGameOver = false;
		else if (y != 0 && planszaTemp[x][y - 1] == val)
			isGameOver = false;
		else if (x != wilekoscPlansza - 1 && planszaTemp[x + 1][y] == val)
			isGameOver = false;
		else if (y != wilekoscPlansza - 1 && planszaTemp[x][y + 1] == val)
			isGameOver = false;
	}

	if (!isFilled || !isGameOver)
		break;
}

if (isGameOver) {
	Final(false);
	koniecGry = false;
}

//Restart();
}

void Gra::polaczenie(sf::Vector2i f, sf::Vector2i t, int dx, int dy)
{
	char srcVal = planszaTemp[f.x][f.y];		//poczatkowe po³ozenie id
	char destVal = planszaTemp[t.x][t.y];		//koncowe po³o¿enie id

	planszaTemp[f.x][f.y] = 0; //zerujemy poczatkowe po³o¿enie kafla

	if (destVal == srcVal) {   //jesli id takie same, ³¹czymy
		planszaTemp[t.x][t.y] = srcVal + 1;		//zmiana wartosci kafla
		wynik += std::stoi(TekstKafla(srcVal + 1)); //dodajemy nowego kafla do wyniku
		if (srcVal + 1 == 11) { //sprawdzamy czy kafel jest 2048(fina³owy)
		//	Restart();
			koniecGry = true;
			Final(koniecGry);
		}
	}
	else
		planszaTemp[t.x - (dx * (destVal != 0))][t.y - (dy * (destVal != 0))] = srcVal; //zatrzymujemy kafla przed zderzeniem

	sf::Vector2i from = f, to;

	if (destVal == srcVal)
		to = t;
	else
		to = sf::Vector2i(t.x - (dx * (destVal != 0)), t.y - (dy * (destVal != 0)));

	if (from != to) {
		plansza[f.x][f.y] = 0;

		ruchy.push_back(std::make_pair(std::make_pair(from, to), srcVal)); //dodajemy nowy ruch do wyrenderowania

		animaStatus = true; //w³aczmy mozliwosc animacji
		animaCzas.restart(); //zerujemy czas
	}
}
