#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>

class ArrayInt {
	int m_length;
	int* m_data;
public:
	ArrayInt() : m_length(0), m_data(nullptr) { }
	ArrayInt(int length) : m_length(length) {
		assert(length >= 0);
		if (length > 0)
			m_data = new int[length]{0};
		else
			m_data = nullptr;
	}
	~ArrayInt() { delete[] m_data; }
	int* begin() {
		return& m_data[0];
	}
	int* end() {
		return m_data + m_length - 1;
	}
	void fill(int val) {
		for (size_t i = 0; i < m_length; i++)
		{
			m_data[i] = val;
		}
	}
	int size() {
		return m_length;
	}
	void erase() {
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
			m_length = 0;
		}
	}
	int& operator[](int index) {
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}
	void resize(int newSize) {
		if (newSize == m_length)
			return;
		if (newSize <= 0)
		{
			erase();
			return;
		}
		int* newData = new int[newSize] {0};
		int N_copy = (newSize >= m_length) ? m_length : newSize;
		for (size_t i = 0; i < N_copy; i++)
			newData[i] = m_data[i];
		delete[] m_data;
		m_data = newData;
		m_length = newSize;
	}
	void insert(int val, int index) {
		int* newData = new int[m_length + 1]{ 0 };
		newData[index] = val;
		for (size_t i = 0; i < index; i++)
			newData[i] = m_data[i];
		for (size_t i = index; i < m_length; i++)
			newData[i+1] = m_data[i];
		delete[] m_data;
		m_data = newData;
		m_length++;
	}
	void delEnd() {
		int* newData = new int[--m_length];
		for (size_t i = 0; i < m_length; i++)
			newData[i] = m_data[i];
		delete[] m_data;
		m_data = newData;
	}
	void delBegin() {
		int* newData = new int[--m_length];
		for (size_t i = 0; i < m_length; i++)
			newData[i] = m_data[i+1];
		delete[] m_data;
		m_data = newData;
	}
	void swap(int i1, int i2){
		int a = m_data[i1];
		m_data[i1] = m_data[i2];
		m_data[i2] = a;
	}
	void sort(size_t first, size_t last){
		size_t min = first;
		size_t max = last;
		size_t c = (first + last) / 2;
		int med = m_data[c];
		do
		{
			while (m_data[min] < med)
				min++;
			while (m_data[max] > med)
				max--;
			if (min <= max)
			{
				swap(min, max);
				min++;
				max--;
			}
		} while (min <= max);
		if (min < last)
			sort(min, last);
		if (max > first)
			sort(first, max);
	}
	void print() {
		for (size_t i = 0; i < m_length; i++)
			std::cout << m_data[i] << ' ';
		std::cout << std::endl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	Card(Suits _suit, Value _val, bool _open): suit(_suit), val(_val), open(_open) {};
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

int main()
{
	//task 1
	ArrayInt Arr(5);
	Arr.insert(1, 0);
	Arr.insert(2, 0);
	Arr.insert(3, 0);
	Arr.insert(4, 0);
	Arr.insert(5, 0);
	Arr.print();
	Arr.delBegin();
	Arr.delEnd();
	Arr.print();
	Arr.sort(0, Arr.size()-1);
	Arr.print();
	std::cout << std::endl;

	//task 2
	std::vector<int> vec1(0);
	for (size_t i = 0; i < 10; i++)
		vec1.push_back(rand() % 10);
	for (auto elem : vec1)
		std::cout << elem << ' ';
	std::cout << std::endl;
	std::vector<int> vec2;
	bool key = true;
	for (auto elem1 : vec1)
	{
		for (auto elem2 : vec2)
			if (elem1 == elem2)
			{
				key = false;
				break;
			}
		if (key)
			vec2.push_back(elem1);
		key = true;
	}
	std::cout << "Different numbers: "<< vec2.size() << std::endl;
	std::cout << std::endl;

	//task 3
	Card card1(CROSSES, A, 0);
	std::cout << "A = " << card1.getValue() << " value" << std::endl;
	Hand hand1;
	hand1.add( (&card1));
	std::cout << "Value hand: " << hand1.getValue() << std::endl;
	std::cout << std::endl;
}