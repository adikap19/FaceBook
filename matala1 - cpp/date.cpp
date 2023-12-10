#include "date.h"
#include <fstream>

using namespace std;

Date::Date(int currDay, int currMonth, int currYear)noexcept(false)
//constructor
{
	if (currDay < FIRST_DAY || currDay > LAST_DAY)
		throw DayException();
	if (currMonth < FIRST_MONTH || currMonth > LAST_MONTH)
		throw MonthException();
	if (currYear > CURR_YEAR || currYear <= 0)
		throw YearException();

	day = currDay;
	month = currMonth;
	year = currYear;
}

ostream& operator<<(ostream& os, const Date& date)
//operator << 
{
	if (typeid(os) == typeid(ofstream))
		os << date.getDay() << " " << date.getMonth() << " " << date.getYear() << endl;
	else
	{
		os << (date.getDay() < 10 ? "0" : "") << date.getDay() << "/"
			<< (date.getMonth() < 10 ? "0" : "") << date.getMonth() << "/"
			<< date.getYear() << endl;
	}
	return os;
}

istream& operator>>(istream& is, Date& date)
//operator >>
{
	is >> date.day >> date.month >> date.year;
	is.get();
	return is;
}
