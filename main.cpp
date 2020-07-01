#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <windows.h>
using namespace std;

class Carta {
private:
	unsigned int rang;
	unsigned int mast;
	unsigned int weight;
public:
	Carta(unsigned rang, unsigned mast, unsigned weight) {
		this->rang = rang;
		this->mast = mast;
		this->weight = weight;
	}

	unsigned int getRang() {
		return rang;
	}
	unsigned int getMast() {
		return mast;
	}
	unsigned int getWeight() {
		return weight;
	}

};

class KolodaCart {
private:
	static KolodaCart *m_instanceSingleton;
	vector <Carta *> koloda;
	KolodaCart() {
		//vector <Carta *> koloda;
		for (int i = 1; i < 5; i++) {
			for (int j = 2; j < 11; j++) {
				Carta *carta = new Carta(j, i, j);
				koloda.push_back(carta);
			}
			for (int k = 11; k < 14; k++) {
				Carta *carta2 = new Carta(k, i, 10);
				koloda.push_back(carta2);
			}
			Carta *carta3 = new Carta(14, i, 11);
			koloda.push_back(carta3);
		}
		std::shuffle(koloda.begin(), koloda.end(), std::random_device());

		//cout << koloda.size() << endl;
	}
	KolodaCart(const KolodaCart& root) = delete;
	KolodaCart& operator=(const KolodaCart&) = delete;
public:
	static KolodaCart* getInstance() {

		return (!m_instanceSingleton) ?
			m_instanceSingleton = new KolodaCart :
			m_instanceSingleton;
	}


	vector <Carta *> giveKoloda() { //отдать колоду
		return koloda;
	}

};

class Human {
private:
	vector <Carta *> koloda;
public:
	virtual string getName() = 0;

	void setCarta(Carta * carta) {
		koloda.push_back(carta);
	}

	Carta * showlastCard() {
		return koloda[koloda.size() - 1];
	}



};

class Dealer : public Human{
public:
	string getName() override {
		return "Dealer";
	}
};

class Player :public Human {
public:
	string getName() override {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}
private:
	string name;
};

class CardListener {
public:
	static vector<unsigned int> show(Carta * carta) {
		vector<unsigned int> data;
		data.push_back(carta->getRang());
		data.push_back(carta->getMast());
		data.push_back(carta->getWeight());
		return data;
	}

	static void printCard(vector<unsigned int> carta)
	{
		switch (carta[0])
		{
		case 2:
			cout << "Двойка";
			break;
		case 3:
			cout << "Тройка";
			break;
		case 4:
			cout << "Четвёрка";
			break;
		case 5:
			cout << "Пятёрка";
			break;
		case 6:
			cout << "Шестёрка";
			break;
		case 7:
			cout << "Семерка";
			break;
		case 8:
			cout << "Восьмёрка";
			break;
		case 9:
			cout << "Девятка";
			break;
		case 10:
			cout << "Десятка";
			break;
		case 11:
			cout << "Валет";
			break;
		case 12:
			cout << "Дама";
			break;
		case 13:
			cout << "Король";
			break;
		case 14:
			cout << "Туз";
			break;
		}


		switch (carta[1])
		{
		case 1:
			cout << " Пики";
			break;
		case 2:
			cout << " Крести";
			break;
		case 3:
			cout << " Буби";
			break;
		case 4:
			cout << " Черви";
			break;
		}
	}
};

class PlayerList {

private:
	int kol;
	vector <Player *> players;
public:
	PlayerList() {
		while (true)
		{
			cout << "Введите количество игроков: ";
			cin >> kol;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Введено некорректное значение...\n";
			}
			else
				break;

		}

		for (int i = 0; i < kol; i++)
		{
			string name;
			Player *gamer = new Player;
			cout << "Введите имя игрока №" << i + 1 << ": ";
			cin >> name;
			gamer->setName(name);
			cout << endl;
			players.push_back(gamer);
		}
	}
	vector <Player *> getPlayers() {
		return players;
	}
	int getKol() {
		return kol;
	}
};

class CartaGiver {
private:
	vector <Carta *> koloda;
public:
	void giveCarta(Human * player) { //выдать карту игроку
		player->setCarta(koloda[koloda.size() - 1]);
		koloda.pop_back();
	}

	CartaGiver(KolodaCart* koloda) { //задать колоду для раздатчика
		this->koloda = koloda->giveKoloda();
	}

	int getKolodaSize() {
		return koloda.size();
	}
};

class ScoreBoard {
	int d_score = 0, g_score = 0, b_score = 0;
public:
	void set_d(int score) {
		d_score += score;
	}

	void set_g(int score) {
		g_score += score;
	}

	void set_b(int score) {
		b_score += score;
	}

	int get_d() {
		return d_score;
	}

	int get_b() {
		return b_score;
	}

	int get_g() {
		return g_score;
	}

	void swap() {
		b_score = g_score;
	}
	void zero_g() {
		g_score = 0;
	}

	void final_score() { //проверка таблицы
		if (d_score < b_score)
		{

			cout << "Игроки выиграли \n";
		}
		else if (d_score == b_score)
		{

			cout << "Ничья \n";
		}
		else
		{

			cout << "Диллер выиграл \n";
		}
		cout << "\n\n\n";
		cout << "Счёт Дилера " << d_score << " / Лучший счёт " << b_score << endl;
	}

};

class Painter {
public:
	static void setR() {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, FOREGROUND_RED);
	}

	static void setG() {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, FOREGROUND_GREEN);
	}

	static void setB() {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, FOREGROUND_BLUE);
	}

	static void setY() {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}

};  //статическая раскраска


class Game{
public:
	int play() {
		//Painter painter;

		Painter::setY();
		cout << "Добро пожаловать в игру Blackjack\n\n"; //эта работает
		cout << "1. Для начала игры напишите 'start'\n";
		cout << "2. Для выхода из игры напишите 'exit'\n";

		string game;
		do { //начало игры
			cin >> game;
		} while (game != "start" && game != "exit"); //пишем здесь начать игру
		// Выход из игры
		if (game == "exit")
		{
			return 0;
		}

		Dealer *dealer = new Dealer; //добавляем диллера в список игроков!
		KolodaCart *koloda;
		koloda = koloda->getInstance();
		CartaGiver giver(koloda);
		PlayerList playerlist;
		ScoreBoard score;
		vector<Player *> players = playerlist.getPlayers(); //вектор плееров

			//ход диллера
			Painter::setR();
			char vibor;
			cout << "Диллер берёт карту.....\n" << endl;

			giver.giveCarta(dealer);
			Carta* carta = dealer->showlastCard();
			vector<unsigned int> tempCarta = CardListener::show(carta);
			CardListener::printCard(tempCarta);

			 score.set_d( tempCarta[2]);
			 cout << endl << "Очки дилера: " << score.get_d() << endl;

		    cout << "\n\n\n";

			// Ход игроков
			Painter::setG();
			for (int x = 0; x < playerlist.getKol(); x++)
			{

				cout << "Ход игрока " << players[x]->getName() << "\n" << "Игрок берёт карту....." << endl;

				do
				{
					Human * player = players[x];
					giver.giveCarta(players[x]);
					Carta* carta = player->showlastCard();
					vector<unsigned int> tempCarta = CardListener::show(carta);
					CardListener::printCard(tempCarta);
					score.set_g(tempCarta[2]);
					cout << endl << "Очки игрока "<< player->getName() << ": "<<score.get_g() << endl;
					cout << "\n Взять ещё карту(y-да, n-нет) ";
					cin >> vibor;
				} while ((vibor != 'n') and (score.get_g() <= 21));

				if (score.get_g() <= 21 && score.get_g() > score.get_b())
				{
					score.swap();
				}

				score.zero_g();
				cout << "\n\n\n";
			}
			// Второй ход дилера
			Painter::setR();
			cout << "Дилер берёт вторую карту....." << endl;

			giver.giveCarta(dealer);
			carta = dealer->showlastCard();
			tempCarta = CardListener::show(carta);
			CardListener::printCard(tempCarta);

			score.set_d(tempCarta[2]);
			cout << endl << "Очки дилера: " << score.get_d() << endl;
			cout << "\n\n\n";

			//проверка результатов
			Painter::setY();
			score.final_score();
			cout << "\n\n\n";
			system("pause");
			return 0;
	}
};

KolodaCart* KolodaCart::m_instanceSingleton = nullptr;

int main()
{
	setlocale(LC_ALL, "Russian");
	Game game;
	game.play();
}


