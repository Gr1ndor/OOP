#include <iostream>

class Figure {
public:
	Figure() {};
	virtual float area() = 0;
};

class Parallelogram : public Figure {
protected:
	float side;
	float h;
public:
	Parallelogram(float _h, float _side): side(_side), h(_h) {};
	virtual float area() override { return h * side; };
};

class Circle : public Figure {
	float r;
public:
	Circle(float _r): r(_r) {};
	virtual float area() override { return 3.14 * r * r; };
};

class Rectangle : public Parallelogram {
public:
	Rectangle(float _h, float _side): Parallelogram(_h, _side) {};
};

class Square : public Parallelogram {
public:
	Square(float _side) : Parallelogram(_side, _side) {};
};

class Rhombus : public Parallelogram {
public:
	Rhombus(float _d1, float _d2) : Parallelogram(_d1, _d2) {};
	virtual float area() override { return h * side / 2; };
};
///////////////////////////////////////////////////////////////////////////////

class Car {
protected:
	std::string company;
	std::string model;
public:
	Car(std::string _company, std::string _model): company(_company), model(_model) { std::cout << "Car: " << company << ' ' << model << std::endl; };
};

class PassengerCar: virtual public Car {
public:
	PassengerCar(std::string _company, std::string _model) : Car(_company, _model) { std::cout << "Passenger car: " << company << ' ' << model << std::endl; };
};

class Bus : virtual public Car {
public:
	Bus(std::string _company, std::string _model) : Car(_company, _model) { std::cout << "Bus: " << company << ' ' << model << std::endl; };
};

class Minivan : public PassengerCar, public Bus {
public:
	Minivan(std::string _company, std::string _model) : PassengerCar(_company, _model), Bus(_company, _model), Car(_company, _model) { std::cout << "Car: " << company << ' ' << model << std::endl; };
};
////////////////////////////////////////////////////////////////////////////////////////////////

class Faction {
	int ch;
	int z;
public:
	Faction() {};
	Faction(int _ch, int _z): ch(_ch), z(_z) {
		while (z == 0)
		{
			std::cout << "Denominator shuold be != 0! Enter new denominator ";
			std::cin >> z;
		}
	};
	Faction operator+(int right)						{ return Faction(ch + right * z, z); }
	friend Faction operator+(int left, Faction& right)	{ return Faction(right.ch + left * right.z, right.z); }
	Faction operator+(Faction& right)					{ return Faction(right.ch * z + ch  * right.z,z * right.z); }

	Faction operator-(int right)						{ return Faction(ch - right * z, z); }
	friend Faction operator-(int left, Faction& right)	{ return Faction( left * right.z - right.ch, right.z); }
	Faction operator-(Faction& right)					{ return Faction(ch * right.z - right.ch * z, z * right.z); }

	Faction operator*(int right)						{ return Faction(ch * right, z); }
	friend Faction operator*(int left, Faction& right)	{ return Faction(right.ch * left, right.z); }
	Faction operator*(Faction& right)					{ return Faction(right.ch * ch, z * right.z); }

	Faction operator/(int right)						{
		while (right == 0)
		{
			std::cout << "Denominator shuold be != 0! Enter new right number ";
			std::cin >> right;
		}
		return Faction(ch, z * right); 
	}
	friend Faction operator/(int left, Faction& right)	{
		if (right.ch == 0)
		{
			std::cout << "Denominator shuold be != 0! division is not possible ";
			return Faction(0,0);
		}
		return Faction(left * right.z, right.ch); 
	}
	Faction operator/(Faction& right)					{
		if (right.ch == 0)
		{
			std::cout << "Denominator shuold be != 0! division is not possible ";
			return Faction(0, 0);
		}
		return Faction(ch * right.z, z * right.ch);
	}

	Faction operator--()								{ return Faction(ch - z, z); }
	Faction operator--(int)								{ return Faction(ch - z, z); }

	bool operator==(double right)						{ if (ch == (right * z)) return true; return false; }
	bool operator==(Faction& right)						{ if ((ch * right.z) == (right.ch * z)) return true; return false; }
	friend bool operator==(double left, Faction& right)	{ if (right.ch == (left * right.z)) return true; return false; }

	bool operator!=(double right)						{ return !(Faction(ch, z) == right); }
	bool operator!=(Faction& right)						{ return !(Faction(ch, z) == right); }
	friend bool operator!=(double left, Faction& right) { return !(left == right); }

	bool operator<(double right)						{ if (ch < (right * z)) return true; return false; }
	bool operator<(Faction& right)						{ if ((ch / z) < (right.ch / right.z)) return true; return false; }
	friend bool operator<(double left, Faction& right)	{ if (right.ch > (left * right.z)) return true; return false; }

	bool operator>=(double right)						{ return !(Faction(ch, z) < right); }
	bool operator>=(Faction& right)						{ return !(Faction(ch, z) < right); }
	friend bool operator>=(double left, Faction& right) { return !(left < right); }

	bool operator>(double right)						{ if (ch > (right * z)) return true; return false; }
	bool operator>(Faction& right)						{ if ((ch / z) > (right.ch / right.z)) return true; return false; }
	friend bool operator>(double left, Faction& right)	{ if (right.ch < (left * right.z)) return true; return false; }

	bool operator<=(double right)						{ return !(Faction(ch, z) > right); }
	bool operator<=(Faction& right)						{ return !(Faction(ch, z) > right); }
	friend bool operator<=(double left, Faction& right) { return !(left > right); }

	friend std::ostream& operator<<(std::ostream& c_out, Faction& right) {
		c_out << right.ch << '/' << right.z;
		return c_out;
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

int main()
{
	//task 1
	Parallelogram par(5, 5);
	Circle cir(9);
	Rectangle rec(2, 11);
	Square sq(3);
	Rhombus rho(12, 15);
	std::cout << "Area of Parallelogram = " << par.area() << std::endl;
	std::cout << "Area of Circle = " << cir.area() << std::endl;
	std::cout << "Area of Rectangle = " << rec.area() << std::endl;
	std::cout << "Area of Square = " << sq.area() << std::endl;
	std::cout << "Area of Rhombus = " << rho.area() << std::endl;
	std::cout << std::endl;

	//task 2
	Car c("car", "111");
	std::cout << std::endl;
	PassengerCar p("pas", "222");
	std::cout << std::endl;
	Bus b("bus", "333");
	std::cout << std::endl;
	Minivan m("mini", "444"); // не срабатывает конструктор минивэна, на выводе видно что второй раз срабатывает конструктор кар
	std::cout << std::endl;

	//task 3
	Faction f1(2, 3), f2(1, 4), f3;
	f3 = f1 + 1;
	std::cout << f1 << " + 1 = " << f3 << std::endl;
	f3 = 1 - f1;
	std::cout << "1 - " << f1 << " = " << f3 << std::endl;
	f3 = f1 * f2;
	std::cout << f1 << " * " << f2 << " = " << f3 << std::endl;
	if (f1 == f2)
		std::cout << f1 << '=' << f2 << std::endl;
	else
		std::cout << f1 << " != " << f2 << std::endl;
	if (f2 != 0.25)
		std::cout << f2 << " != " << f2 << std::endl;
	else
		std::cout << f2 << " = " << f2 << std::endl;
	std::cout << std::endl;

	//task 4
	Card card1(CROSSES, A, 0);
	std::cout << "A = " << card1.getValue() << " value" << std::endl;
}