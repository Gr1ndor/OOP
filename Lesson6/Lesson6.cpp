#include <iostream>
#include <string>
#include <cassert>
#include <vector>

class NewEndl
{
public:
	friend std::ostream& operator<< (std::ostream& out, const NewEndl& _endl) {
		out << std::endl << std::endl;
		return out;
	}
};

////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////

enum Suits {
	SPADES,
	CROSSES,
	HEARTS,
	DIAMONDS
};
enum Value {
	A = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K
};

class Card {

	Suits suit;
	Value val;
	bool open;
public:
	Card(Suits _suit, Value _val, bool _open) : suit(_suit), val(_val), open(_open) {};
	void flip() { open = !open; }
	int getValue() { return val; };
	friend std::ostream& operator<<(std::ostream& _out, const Card& _card) {
		if (!_card.open)
			_out << "XX" << std::endl;
		else
			_out << _card.suit << ' ' << _card.val << std::endl;
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
		for (auto  elem : _gen.hand)
		{
			_out << elem << ",   ";
		}
		_out << std::endl << _gen.getValue() << std::endl;
		return _out;
	}
	virtual bool IsHitting() = 0;
	bool IsBoosted() { return getValue() > 21; }
	void Bust() { std::cout << name << " have bust"; }
};

class Player : public GenericPlayer
{
public:
	virtual bool IsHitting() const {
		char x;
		std::cout << "Do you need another card? y/n" << std::endl;
		std::cin >> x;
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
	virtual bool IsHitting() const {
		return (getValue() < 17);
	}
	void FlipFirstCard() {
		hand[0]->flip();
	}
};

////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//task 1
	int i;
	std::cout << "Enter int : "; 
	std::cin >> i;
	while (std::cin.fail() || std::cin.get() != '\n')
	{
		std::cin.clear();
		std::cin.ignore(9999, '\n');
		std::cin.sync();
		std::cout << "Error! Enter int : "; 
		std::cin >> i;
	}
	std::cout << std::endl;

	//task 2
	NewEndl endll;
	std::cout << 'A' << endll << 'B' << std::endl;

	//task 3

}