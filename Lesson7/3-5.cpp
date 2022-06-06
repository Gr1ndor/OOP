#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>

enum Suits {
	SPADES,
	CROSSES,
	HEARTS,
	DIAMONDS
};
enum Value {
	A, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K
};

char check(char key) {
	while (key != 'y' && key != 'n')
	{
		std::cout << "Error! only y/n" << std::endl;
		std::cin >> key;
	}
	return key;
}

class Card {
protected:
	Suits suit;
	Value val;
	bool open = true;
public:
	Card(Suits _suit, Value _val) : suit(_suit), val(_val) {};
	void flip() { open = !open; }
	int getValue() {
		if (!open)
			return 0;
		if (val > 9)
			return 10;
		return val + 1;
	};
	friend std::ostream& operator<<(std::ostream& _out, const Card* _card) {
		std::string suits[4]{ "SPADES", "CROSSES",	"HEARTS",	"DIAMONDS" };
		std::string value[13]{ "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
		if (!(* _card).open)
			_out << "XX";
		else
			_out << suits[(*_card).suit] << ' ' << value[(*_card).val];
		return _out;
	}
};

class Hand {
protected:
	std::vector <Card*> hand;
public:
	Hand() {};
	void add(Card* new_card) {
		hand.push_back(new_card);
	}
	void clear() {
		hand.clear();
	}
	int getValue() const {
		int key = 0;
		int value = 0;
		for (auto elem : hand)
		{
			value += (*elem).getValue();
			if ((*elem).getValue() == 1)
				key++;
		}
		if (value > 10 || key == 0)
			return value;
		value += key * 10;
		return (value < 22) ? value : value - key * 10;
	}
};

class GenericPlayer : public Hand
{
protected:
	std::string name;
public:
	GenericPlayer(std::string _name) : name(_name) {}
	friend std::ostream& operator<<(std::ostream& _out, const GenericPlayer& _gen) {
		_out << "Player: " << _gen.name << std::endl;
		_out << "Cards: ";
		for (auto elem : _gen.hand)
		{
			_out << elem << ",   ";
		}
		_out << std::endl << "Value: " << _gen.getValue() << std::endl;
		return _out;
	}
	virtual bool IsHitting() const = 0;
	bool IsBoosted() { return getValue() > 21; }
	void Bust() { std::cout << "Player " << name << " have bust!" << std::endl; }
};

class Player : public GenericPlayer
{
public:
	Player(std::string _name) : GenericPlayer(_name) {}
	virtual bool IsHitting() const {
		char x;
		std::cout << name << " need another card? y/n" << std::endl;
		std::cin >> x;
		x = check(x);
		if (x == 'y')
			return true;
		return false;
	}
	void Win() const {
		std::cout << "Player " << name << " won!" << std::endl;
	}
	void Lose() const {
		std::cout << "Player " << name << " lost!" << std::endl;
	}
	void Push() const {
		std::cout << "Player " << name << ", tie!" << std::endl;
	}
};

class House : public GenericPlayer
{
public:
	House() : GenericPlayer("Diller") {}
	virtual bool IsHitting() const {
		return (getValue() < 17);
	}
	void FlipFirstCard() {
		hand[0]->flip();
	}
};

class Deck : public Hand
{
protected:
	std::vector <Card> deck;
public:
	Deck() { Populate(); }
	void Populate() {
		for (int i = SPADES; i <= DIAMONDS; i++)
		{
			Suits suit = static_cast<Suits>(i);
			for (int j = A; j <= K; j++)
			{
				Value value = static_cast<Value>(j);
				Card card(suit, value);
				deck.push_back(card);
			}
		}
	}
	void Shuffle() {
		random_shuffle(deck.begin(), deck.end());
	}
	void Deal(Hand& aHand) {
		aHand.add(&deck.back());
		deck.pop_back();
	}
	void AddltionalCards(GenericPlayer& aGenerlcPlayer) {
		while (!aGenerlcPlayer.IsBoosted() && aGenerlcPlayer.IsHitting())
		{
			std::cout << "New card: " << (&deck.back()) << std::endl;
			Deal(aGenerlcPlayer);
			std::cout << "New value: " << aGenerlcPlayer.getValue() << std::endl;
		}
	}
};

class Game
{
	Deck mainDeck;
	House diller;
	std::vector <Player> players;
public:
	Game(std::vector<std::string> _players) {
		for (auto element : _players)
		{
			Player player(element);
			players.push_back(player);
			mainDeck.Shuffle();
		}
	}
	void play() {
		for (auto& element : players)
		{
			mainDeck.Deal(element);
			mainDeck.Deal(element);
		}
		mainDeck.Deal(diller);
		mainDeck.Deal(diller);
		diller.FlipFirstCard();
		print();
		for (auto& element : players)
		{
			mainDeck.AddltionalCards(element);
			system("cls");
			print();
		}
		diller.FlipFirstCard();
		system("cls");
		mainDeck.AddltionalCards(diller);
		print();
		for (auto& element : players)
		{
			if (element.IsBoosted())
			{
				element.Bust();
				element.Lose();
			}
			else
			{
				if (diller.getValue() > 21)
					element.Win();
				else
				{
					if (element.getValue() > diller.getValue())
						element.Win();
					if (element.getValue() == diller.getValue())
						element.Push();
					if (element.getValue() < diller.getValue())
						element.Lose();
				}
			}
			element.clear();
			std::cout << std::endl;
		}
	}
	void print() {
		std::cout << diller << std::endl;
		for (auto& element : players)
			std::cout << element << std::endl;
	}
};

int main()
{
	std::vector<std::string> players;
	bool wantToPlay = false;
	std::cout << "Do u want to play? y/n" << std::endl;
	char key;
	char key2 = 'y';
	std::cin >> key;
	key = check(key);
	while (key == 'y')
	{
		if (key2 == 'y')
			players.clear();
		while (key2 == 'y')
		{
			std::cout << "Enter name of player: ";
			std::string name; 
			std::cin >> name;
			players.push_back(name);
			std::cout << "Do u need add more player? y/n" << std::endl;
			std::cin >> key2;
			key2 = check(key2);
		}
		system("cls");
		Game* game1 = new Game (players);
		(* game1).play();
		delete game1;
		std::cout << "Do u want to play more? y/n" << std::endl;
		std::cin >> key;
		key = check(key);
		system("cls");
		std::cout << "Do u want to change players? y/n" << std::endl;
		std::cin >> key2;
		key2 = check(key2);
	}
}