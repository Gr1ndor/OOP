#include <iostream>
#include <cstdint>

class Power {
	double x;
	double y;
public:
	void set(double _x, double _y) { x = _x; y = _y; };
	double calculate() { return pow(x, y); };
};

class RGBA {
	uint8_t m_red = 0;
	uint8_t m_green = 0;
	uint8_t m_blue = 0;
	uint8_t m_alpha = 255;
public:
	RGBA(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha) { m_red = _red; m_green = _green; m_blue = _blue; m_alpha = _alpha; };
	void print();
};

void RGBA::print() {
	std::cout << "m_red = " << (int)m_red << std::endl;
	std::cout << "m_green = " << (int)m_green << std::endl;
	std::cout << "m_blue = " << (int)m_blue << std::endl;
	std::cout << "m_alpha = " << (int)m_alpha << std::endl;
}

class Stack {
	int arr[10];
	size_t length = 0;
public:
	void reset();
	bool push(int _data);
	int pop();
	void print();
};

void Stack::reset() {
	for (size_t i = 0; i < 10; i++)
		arr[i] = 0;
	length = 0;
}

bool Stack::push(int _data) {
	if (length == 10)
		return false;
	arr[length++] = _data;
	return true;
}

int Stack::pop() {
	if (length == 0)
		return 0;
	int a = arr[--length];
	arr[length] = 0;
	return a;
}

void Stack::print() {
	std::cout << "( ";
	for (size_t i = 0; i < length; i++)
		std::cout << arr[i] << ' ';
	std::cout << ')' << std::endl;
}

int main()
{
	//task 1
	Power num;
	num.set(1.23, 5.671);
	std::cout << "x^y = " << num.calculate() << std::endl;
	std::cout << std::endl;

	//task 2
	RGBA colors(10, 12, 50, 115);
	colors.print();
	std::cout << std::endl;

	//task 3
	Stack stack;
	stack.reset();
	stack.print();

	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();
	stack.print();
}