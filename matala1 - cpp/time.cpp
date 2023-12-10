#include "time.h"

#include <fstream>

using namespace std;

Time::Time(int currHours, int currMinutes)noexcept(false)
//constructor
{
	if (currHours < FIRST_DAY_HOUR || currHours >= LAST_DAY_HOUR)
		throw HourException();
	if (currMinutes < FIRST_MINUTE || currMinutes >= LAST_MINUTE)
		throw MinutesException();

	hours = currHours;
	minutes = currMinutes;
}

ostream& operator<<(ostream& os, const Time& time)
//operator <<
{
	if (typeid(os) == typeid(ofstream))
		os << time.hours << " " << time.minutes << endl;
	else
	{
		os << (time.getHour() < 10 ? "0" : "") << time.getHour() << ":"
			<< (time.getMinutes() < 10 ? "0" : "") << time.getMinutes();
	}
	return os;
}

istream& operator>>(istream& is, Time& time)
//operator >>
{
	is >> time.hours >> time.minutes;
	is.get();
	return is;
}

bool Time::operator==(const Time& other) const
//operator ==
{
	return ((hours == other.hours) && (minutes == other.minutes));
}

bool Time::operator!=(const Time& other) const
//operator !=
{
	return !(*this == other);
}