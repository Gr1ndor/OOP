#include <iostream>
#include <string>
#include <cassert>
#include <vector>

template <typename T>
class Pair1 {
	T x;
	T y;
public:
	Pair1(T _x, T _y) : x(_x), y(_y) {}
	T first() const { return x; }
	T second() const { return y; }
};
//////////////////////////////////////////////////////////////////////

template <typename T1, typename T2>
class Pair {
	T1 x;
	T2 y;
public:
	Pair(T1 _x, T2 _y) : x(_x), y(_y) {}
	T1 first() const { return x; }
	T2 second() const { return y; }
};
////////////////////////////////////////////////////////////////////////////////

template<typename T4>
class StringValuePair : public Pair<std::string, T4>
{
public:
	StringValuePair(std::string _x, T4 _y) : Pair<std::string, T4>(_x, _y) {}
};
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
};

class Hand {
	std::vector <Card*> hand;
public:
	Hand() {};
	void add(Card* new_card) {
		hand.push_back(new_card);
	}
	void clear() {
		hand.clear();
	}
	int getValue() {
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
	std::string name;
public:
	GenericPlayer(std::string _name) : name(_name) {}
	virtual bool IsHitting() {}
	bool IsBoosted() { return getValue() > 21; }
	void Bust() { std::cout << name << " have bust"; }
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//task 1
	{
		Pair1<int> p1(6, 9);
		std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
		const Pair1<double> p2(3.4, 7.8);
		std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	}
	std::cout << std::endl;

	//task 2
	{
		Pair<int, double> p1(6, 7.8);
		std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
		const Pair<double, int> p2(3.4, 5);
		std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	}
	std::cout << std::endl;

	//task 3
	{
		StringValuePair<int> svp("Amazing", 7);
		std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
	}
}