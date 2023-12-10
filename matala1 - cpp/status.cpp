#include "status.h"
#include "statusVideo.h"
#include "statusPicture.h"
#include <fstream>

using namespace std;

Status::Status(Time& time, Date& date, const string stat)noexcept(false) :publishDate(date), publishTime(time)
//constructor
{
	if (stat[0] == '\0')
		throw TextException();

	text = stat;
}

bool Status::operator==(const Status& other) const
//operator == that compares between 2 statuses by their text
{
	return (text == other.text);
}

bool Status::operator!=(const Status& other) const
//operator != that compares between 2 statuses by their text
{
	return !(text == other.text);
}

void Status::toOs(ostream& os) const
//belongs to the operator << function
{ 
	if (typeid(os) != typeid(ofstream))
		os << endl;
}

ostream& operator<<(ostream& os, const Status& status)
//operator <<
{
	if (typeid(os) == typeid(ofstream))
		os << typeid(status).name() + 6 << endl << status.getPublishTime() << status.getPublishDate() << status.getText() << endl;
	else
	{
		os << "Publish time: " << status.getPublishTime() << ", publish date: "
			<< status.getPublishDate() << "Text: " << status.getText() << endl;
	}
	status.toOs(os);
	return os;
}

istream& operator>>(istream& is, Status& status)
//operator >>
{
	getline(is, status.text);
	return is;
}
