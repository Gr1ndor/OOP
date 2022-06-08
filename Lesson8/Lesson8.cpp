#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

class DivisionByZero : public std::exception
{
	std::string error;
public:
	DivisionByZero(const std::string& err = "It cannot be divided by 0!") : error(err) {};
	const char* what() const noexcept { return error.c_str(); }
};

template<class T>
double div(T x, T y) {
	if (y == 0) 
		throw DivisionByZero();
	return x / y;
}

/////////////////////////////////////////////////////////////////////////////////////////////

class Ex
{
	double x;
public:
	Ex(double _x) : x(_x) {}
	double get() { return x; }
};

class Bar
{
	double y;
public:
	Bar() : y(0) {}
	void set(double a) {
		if (y + a > 100) throw Ex(a * y);
		y = a;
	}
};

//////////////////////////////////////////////////////////////////////////////////////

class OffTheField
{
	int x, y, move;
public:
	OffTheField(int _x, int _y, int _move) : x(_x), y(_y), move(_move) {	}
	const char* what() { return "U cant move in this place! U are going beyond the boundaries of the field!"; }
	int getX() { return x; }
	int getY() { return y; }
	int getMove() { return move; }
};

class IllegalCommand
{
	int x, y, move;
public:
	IllegalCommand(int _x, int _y, int _move) : x(_x), y(_y), move(_move) {	}
	const char* what() { return "U cant move in this place! Illegal command!"; }
	int getX() { return x; }
	int getY() { return y; }
	int getMove() { return move; }
};

class Robot
{
	int x;
	int y;
public:
	Robot() : x(0), y(0) {}
	int getX() { return x; }
	int getY() { return y; }
	void goTo(int a) {
		if (a < 0 or a > 4) throw IllegalCommand(x, y, a);
		switch (a)
		{
		case 1:
			if (y - 1 < 0) throw OffTheField(x, y, a);
			y--;
			break;
		case 2:
			if (x + 1 > 9) throw OffTheField(x, y, a);
			x++;
			break;
		case 3:
			if (y + 1 > 9) throw OffTheField(x, y, a);
			y++;
			break;
		case 4:
			if (x - 1 < 0) throw OffTheField(x, y, a);
			x--;
			break;
		}
	}
};



int main()
{
	//task 1
	
	int a = 10, b = 3;
	double a1 = 5, b2 = 0;
	try
	{
		std::cout << a << " / " << b << " = " <<  div<double>(a, b) << std::endl;
		std::cout << a1 << " / " << b2 << " = " << div<double>(a1, b2) << std::endl;
	}
	catch (std::exception& exception)
	{
		std::cerr << "Error!" << exception.what() << std::endl;
	}
	std::cout << std::endl;

	//task 2
	Bar bar;
	int n;
	std::cout << "Enter n: " << std::endl;
	std::cin >> n;
	try
	{
		while (n != 0)
		{
			bar.set(n);
			std::cout << "Enter n: " << std::endl;
			std::cin >> n;
		}
	}
	catch (Ex _ex)
	{
		std::cout << "The last 2 numbers add up to more than 100. their multiplication is equal to" << _ex.get() << std::endl;
	}
	
	//task 3
	Robot robot;
	int move = -1;
	std::cout << "Ur position: " << robot.getX() << '.' << robot.getY() << std::endl;
	std::cout << "Enter the direction of movement: 1 - up, 2 - right, 3 - down, 4 - left, 0 - end movement" << std::endl;
	std::cin >> move;
	try
	{
		while (move != 0)
		{
			robot.goTo(move);
			std::cout << "Ur position: " << robot.getX() << '.' << robot.getY() << std::endl;
			std::cout << "Enter the direction of movement: 1 - up, 2 - right, 3 - down, 4 - left, 0 - end movement" << std::endl;
			std::cin >> move;			
		}
	}
	catch (OffTheField f)
	{
		std::cout << "Ur position: " << f.getX() << '.' << f.getY() << std::endl;
		std::cout << "U tried direction of movement: " << f.getMove() << std::endl;
		std::cout << f.what() << std::endl;
	}
	catch (IllegalCommand i)
	{
		std::cout << "Ur position: " << i.getX() << '.' << i.getY() << std::endl;
		std::cout << "U tried direction of movement: " << i.getMove() << std::endl;
		std::cout << i.what() << std::endl;
	}
	
}