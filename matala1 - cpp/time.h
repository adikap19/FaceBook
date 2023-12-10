#ifndef __TIME_H
#define __TIME_H

#include <iostream>
#include <fstream>

const int FIRST_DAY_HOUR = 0;
const int FIRST_MINUTE = 0;
const int LAST_DAY_HOUR = 24;
const int LAST_MINUTE = 60;

class TimeException : public std::exception
{
public:
	virtual const char* what() const override { return "Failed inserting the time!"; }
};

class HourException : public TimeException
{
public:
	virtual const char* what() const override { return "Failed inserting the hour!"; }
};

class MinutesException : public TimeException
{
public:
	virtual const char* what() const override { return "Failed inserting the minutes!"; }
};

class Time
{
private:
	int hours, minutes;
public:
	Time(int currHours = FIRST_DAY_HOUR, int currMinutes = FIRST_MINUTE)noexcept(false);
	Time(std::ifstream& inFile) { inFile >> *this; }

	int getHour() const { return hours; }
	int getMinutes() const { return minutes; }

	friend std::ostream& operator<<(std::ostream& os, const Time& time);
	friend std::istream& operator>>(std::istream& is, Time& time);
	bool operator==(const Time& other) const;
	bool operator!=(const Time& other) const;
};
#endif
