#ifndef __DATE_H
#define __DATE_H

#include <iostream>
#include <fstream>

const int FIRST_DAY = 1;
const int LAST_DAY = 31;
const int FIRST_MONTH = 1;
const int LAST_MONTH = 12;
const int CURR_YEAR = 2023;

class DateException : public std::exception
{
public:
	virtual const char* what() const override { return "Failed inserting the date!"; }
};

class DayException : public DateException
{
public:
	virtual const char* what() const override { return "Failed inserting the day!"; }
};

class MonthException : public DateException
{
public:
	virtual const char* what() const override { return "Failed inserting the month!"; }
};

class YearException : public DateException
{
public:
	virtual const char* what() const override { return "Failed inserting the year!"; }
};

class Date
{
private:
	int day, month, year;

public:
	Date(int currDay = FIRST_DAY, int currMonth = FIRST_MONTH, int currYear = CURR_YEAR)noexcept(false);
	Date(std::ifstream& inFile) { inFile >> *this; }

	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }

	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend std::istream& operator>>(std::istream& is, Date& date);
};
#endif
