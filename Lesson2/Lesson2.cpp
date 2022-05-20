#include <iostream>

class Person {
protected:
	std::string name;
	std::string gender;
	int age;
	int weight;
public:
	Person(std::string _name, std::string _gender, int _age, int _weight) : name(_name), gender(_gender), age(_age), weight(_weight) {}
	void changeName(std::string _name) { name = _name; }
	void changeAge(int _age) { age = _age; }
	void changeWeigth(int _weight) { weight = _weight; }
};

class Student :public Person {
	size_t year;
	static size_t count;
public:
	Student(std::string _name, std::string _gender, int _age, int _weight, int _year) :Person(_name, _gender, _age, _weight), year(_year) { count++; }
	void setYear(int _year) { year = _year; }
	void nextYear() { year++; }
	void printCount() { std::cout << "Students: " << count << std::endl; std::cout << std::endl; }
	void print() {
		std::cout << "Name: " << name << std::endl;
		std::cout << "Gender: " << gender << std::endl;
		std::cout << "Age: " << age << std::endl;
		std::cout << "Weight: " << weight << std::endl;
		std::cout << "Year of study: " << year << std::endl;
		std::cout << std::endl;
	}
};
size_t Student::count = 0;

class Fruit {
public:
	Fruit(std::string _color) : color(_color){};
	std::string getName() { return name; };
	std::string getColor() { return color; };
protected:
	std::string name;
	std::string color;
};

class Apple: public Fruit  {
public:
	Apple(std::string _color) : Fruit(_color) { name = "Apple"; };
};

class Banana: public Fruit  {
public:
	Banana() : Fruit("yellow") { name = "Banana"; };
};

class GrannySmith: public Apple  {
public:
	GrannySmith() : Apple("green") { name = "Granny Smith apple"; };
};

int main()
{
	//task 1
	Student A("Ivan", "male", 21, 80, 3);
	Student B("Masha", "female", 18, 60, 1);
	Student C("Anna", "female", 23, 72, 5);
	A.printCount();
	A.print();
	B.print();
	C.print();

	//task 2
	Apple a("red");
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

	//task 3
	/*
	class Game {
	int hand[13];                                       рука игрока. 13 разных карт, массив с указанием количества каждого эземпляра
	int dilHand[13];									рука диллера
	int plPoints = 0;                                   очки игрока
	int dilPoints = 0;									очки диллера
	bool check = true;									флаг на то продолжает ли игрок игру, в случае добровольного отказа или перебора false
	bool dillerWin = false;								флаг победы диллера
	bool playerWin = false;								флаг победы игрока
	bool tie = false;									флаг ничьей
public:
	Game() {};											обнуление рук игрока и диллера, выдача 2 карт игроку и диллеру
	bool checkBJ(int* _nahd);							проверка на 21
	bool checkWin();									проверка на победу
	bool checkOver(int* _hand);							проверка на перебор
	int points(int* _hand);								подсчет очков в руке
	void more(int* _hand);								добавление карты в руку
	void printPlayerHand();								вывести карты игрока на экран
	void printDillerHand();								пока игрок продолжает играть выводим только 1 карту, иначе все
	void printGame();									очистить экран и вывести все данные об игре
	void resetHands(int* _hand);						обнулить все карты в руке игрока или диллера
	int randomCard() { return rand() % 13; };			взятие случайной карты для диллера или игрока
	};

	void main()
	{
		1 создаем игру, в конструкторе игрок и диллер получат карты
		2 проверяем на блек джек диллера и игрока, если находим у одного из них, тот победил если у обоих - ничья
		3 выводим на экран игру
		4 цикл while(!dillerWin & !playerWin & !tie)
			цикл. пока игрок может играть
				предлагаем взять еще, в случае отказа check = false
				добавляем карту в руку
				проверяем на 21, check = false если 21
				проверяем на перебор, check = false если перебор, диллер выиграл
				выводим игру на экран
			проверка на победу диллера, break если диллер выиграл
			цикл. пока у диллера меньше 17
				берем еще 1 карту в руку
				добавляем карту в руку
				выводим игру на экран
				проверяем на перебор, если перебор, игрок выиграл
			проверка на победу игрока/диллера или ничью
		5 игра окончена, выводим игру на экран
	}
		это версия без возможности разбиения пары одинаковых карт на 2 руки игроком
	*/
}