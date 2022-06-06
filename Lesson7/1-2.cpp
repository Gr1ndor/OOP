#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>

class Date
{
	int day, month, year;
public:
	Date(int _d, int _m, int _y) : day(_d), month(_m), year(_y) {}
	friend std::ostream& operator<<(std::ostream& _out, const Date& _date) {
		_out << _date.day << '.' << _date.month << '.' << _date.year << std::endl;
		return _out;
	}
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }
};

///////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<Date>& lateDate(std::unique_ptr<Date>& _date1, std::unique_ptr<Date>& _date2) {
	if (_date1->getYear() > _date2->getYear())
		return _date1;
	if (_date1->getMonth() > _date2->getMonth())
		return _date1;
	if (_date1->getDay() > _date2->getDay())
		return _date1;
	return _date2;
}

void changeDate(std::unique_ptr<Date>& _date1, std::unique_ptr<Date>& _date2) {
	std::unique_ptr<Date> _date3 = move(_date1);
	_date1 = move(_date2);
	_date2 = move(_date3);
}

////////////////////////////////////////////////////////////////////////////////
int main()
{
	//task 1
	std::cout << "task 1" << std::endl;
	std::unique_ptr<Date> today(new Date(6, 6, 2022));
	std::unique_ptr<Date> date;
	std::cout << today->getDay() << '.' << today->getMonth() << '.' << today->getYear() << std::endl;
	std::cout << *today << std::endl;
	date = move(today);
	std::cout << *date << std::endl;
	std::cout << today.get() << std::endl;
	std::cout << date.get() << std::endl;
	std::cout << std::endl;
	//task 2
	std::cout << "task 2" << std::endl;
	std::unique_ptr<Date> date1(new Date(5, 6, 2022));
	std::unique_ptr<Date> date2(new Date(6, 6, 2022));
	std::cout << date1.get() << std::endl;
	std::cout << date2.get() << std::endl;
	std::cout << *lateDate(date1, date2) << std::endl;
	std::cout << "1 - " << date1.get() << std::endl;
	std::cout << "2 - " << date2.get() << std::endl;
	changeDate(date1, date2);
	std::cout << "1 - " << date1.get() << std::endl;
	std::cout << "2 - " << date2.get() << std::endl;
	std::cout << std::endl;
	return 0;
}