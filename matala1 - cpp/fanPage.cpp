#include "users.h"
#include "fanPages.h"
#include "status.h"
#include "statusPicture.h"
#include "statusVideo.h"
#include "time.h"

#include <fstream>

using namespace std;

FanPage::FanPage(const string pageName)noexcept(false)
//constructor
{
	if (pageName[0] == '\0')
		throw FanPageException();
	name = pageName;

	statuses.reserve(3);
	fans.reserve(3);
}

FanPage::FanPage(const FanPage&& other)noexcept(false)
//move constructor
{
	name = other.name;
	statuses = other.statuses;
	fans = other.fans;
}

void FanPage::setNewTextStatus(Time& time, Date& date, string text)noexcept(false)
//This function creates new status and set it to the statuses vector
{
	Status* status = new Status(time, date, text);
	statuses.push_back(status);
}

void FanPage::setNewTextStatusFromFile(ifstream& inFile)
//This function creates new text status from file and set it to the statuses vector
{
	Status* status = new Status(inFile);
	statuses.push_back(status);
}

void FanPage::setNewPictureStatus(Time& time, Date& date, std::string text, std::string description)noexcept(false)
//This function creates new picture status and set it to the statuses vector
{
	Status* status = new StatusPicture(Status(time, date, text), description);
	statuses.push_back(status);
}

void FanPage::setNewPictureStatusFromFile(std::ifstream& inFile)
//This function creates new picture status from file and set it to the statuses vector
{
	Status* status = new StatusPicture(inFile);
	statuses.push_back(status);
}

void FanPage::setNewVideoStatus(Time& time, Date& date, std::string text, std::string description, Time& len)noexcept(false)
//This function creates new video status and set it to the statuses vector
{
	Status* status = new StatusVideo(Status(time, date, text), description, len);
	statuses.push_back(status);
}

void FanPage::setNewVideoStatusFromFile(std::ifstream& inFile)
//This function creates new video status from file and set it to the statuses vector
{
	Status* status = new StatusVideo(inFile);
	statuses.push_back(status);
}

void FanPage::showAllMyStatuses()
//This function shows all the fan page's statuses
{
	vector<Status*>::iterator itr = statuses.begin(), itrEnd = statuses.end();
	int counter = 1;

	if (statuses.size() == 0)
		cout << name << " has no statuses yet." << endl << endl;

	for (; itr != itrEnd; ++itr)
	{
		cout << counter << ") " << (**itr);
		counter++;
	}
}

int FanPage::findFanIndInFansArr(User& userToFind)
//This function returns the user index in the page's arr of fans
{
	vector<User*>::iterator itr = fans.begin(), itrEnd = fans.end();
	int ind = 0;

	for (; itr != itrEnd; ++itr)
	{
		if (userToFind.getName() == (*itr)->getName())
			return ind;
		ind++;
	}
	return NOT_FOUND;
}

void FanPage::removeFanFromFansArr(int ind)
//This function removes a fan from fan's arr
{
	vector<User*>::iterator itr = fans.begin();

	advance(itr, ind);
	fans.erase(itr);
}

void FanPage::showAllMyFans()
//This function shows all of the fan page fans
{
	vector<User*>::iterator itr = fans.begin(), itrEnd = fans.end();
	int counter = 1;

	if (fans.size() == 0)
		cout << name << " has no fans yet." << endl;
	else
	{
		cout << endl << name << "'s fans are: " << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << counter << ") " << (**itr);
			counter++;
		}
	}
	cout << endl;
}

bool FanPage::operator>(const FanPage& other) const
//operator > that compares 2 pages by their fans amount
{
	return (fans.size() > other.fans.size());
}

bool FanPage::operator>(const User& other) const
//operator > that compares fan page and user by their fans/friends amount
{
	return(fans.size() > other.getFriendsNum());
}

ostream& operator<<(ostream& os, const FanPage& page)
//operator <<
{
	os << page.getName() << endl;
	return os;
}

FanPage::~FanPage()
//destructor
{
	vector<Status*>::iterator itr = statuses.begin(), itrEnd = statuses.end();

	for (; itr != itrEnd; ++itr)
		delete(*itr);
}
