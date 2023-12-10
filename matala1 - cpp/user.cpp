#include "users.h"
#include "fanPages.h"
#include "status.h"
#include "statusPicture.h"
#include "statusVideo.h"
#include "date.h"
#include "time.h"

#include<fstream>

using namespace std;

User::User(const string userName, Date& dateOfBirth)noexcept(false) :birthDay(dateOfBirth)
//constructor
{
	if (userName[0] == '\0')
		throw UserException();

	name = userName;

	friends.reserve(3);
	fanPages.reserve(3);
	statuses.reserve(3);
}

User::User(const User&& other)noexcept(false) :birthDay(other.birthDay)
//move constructor
{
	name = other.name;
	friends = other.friends;
	fanPages = other.fanPages;
	statuses = other.statuses;
}

void User::setNewTextStatus(Time& time, Date& date, string text)noexcept(false)
//This function creates new text status and set it to the statuses vector
{
	Status* status = new Status(time, date, text);
	statuses.push_back(status);
}

void User::setNewTextStatusFromFile(ifstream& inFile)
//This function creates new text status from file and set it to the statuses vector
{
	Status* status = new Status(inFile);
	statuses.push_back(status);
}

void User::setNewPictureStatus(Time& time, Date& date, std::string text, std::string description)noexcept(false)
//This function creates new picture status and set it to the statuses vector
{
	Status* status = new StatusPicture(Status(time, date, text), description);
	statuses.push_back(status);
}

void User::setNewPictureStatusFromFile(std::ifstream& inFile)
//This function creates new picture status from file and set it to the statuses vector
{
	Status* status = new StatusPicture(inFile);
	statuses.push_back(status);
}

void User::setNewVideoStatus(Time& time, Date& date, std::string text, std::string description, Time& len)noexcept(false)
//This function creates new video status and set it to the statuses vector
{
	Status* status = new StatusVideo(Status(time, date, text), description, len);
	statuses.push_back(status);
}

void User::setNewVideoStatusFromFile(std::ifstream& inFile)
//This function creates new video status from file and set it to the statuses vector
{
	Status* status = new StatusVideo(inFile);
	statuses.push_back(status);
}

bool User::currentlyConncected(string name)
//This function checks if the user and the name he wants to connect to - are already friends
{
	vector< User*>::iterator itr = friends.begin(), itrEnd = friends.end();

	for (; itr != itrEnd; ++itr)
		if ((*itr)->name == name)
			return true;
	return false;
}

bool User::currentlyFan(string pageName)
//This function checks if the user we got is already a fan of this page
{
	vector<FanPage*>::iterator itr = fanPages.begin(), itrEnd = fanPages.end();

	for (; itr != itrEnd; ++itr)
		if ((*itr)->getName() == pageName)
			return true;
	return false;
}

void User::showAllMyStatuses()
//This function prints all statuses of the user
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

void User::showMyLastTenStatuses()
//This function prints the last 10 statuses of the user
{
	vector<Status*>::iterator itr = statuses.begin(), itrEnd = statuses.end();

	if (statuses.size() == 0)
		cout << name << " has no statuses yet." << endl << endl;
	else if (statuses.size() <= 10)
		for (; itr != itrEnd; ++itr)
			cout << (**itr);
	else
	{
		itr = itrEnd - 10;
		for (; itr != itrEnd; ++itr)
			cout << (**itr);
	}
}

void User::showMyFriendsLastTenStatuses()
//This function prints the last 10 statuses of the user's friends
{
	vector< User*>::iterator itr = friends.begin(), itrEnd = friends.end();
	int counter = 1;

	if (friends.size() == 0)
		cout << name << " has no friends yet." << endl << endl;
	else
	{
		cout << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << counter << ") " << (*itr)->getName() << "'s 10 last statuses:" << endl;
			(*itr)->showMyLastTenStatuses();
			counter++;
		}
	}
}

int User::findFriendIndInFriendsArr(User& userToFind)
//This function returns the index of the user we got, in the user's arr of friends
{
	vector<User*>::iterator itr = friends.begin(), itrEnd = friends.end();
	int ind = 0;

	for (; itr != itrEnd; ++itr)
	{
		if (userToFind.getName() == (*itr)->getName())
			return ind;
		ind++;
	}
	return NOT_FOUND;
}

int User::findPageIndInPagesArr(FanPage& pageToFind)
//This function returns the index of the page we got, in the user's arr of fan pages
{
	vector< FanPage*>::iterator itr = fanPages.begin(), itrEnd = fanPages.end();
	int ind = 0;

	for (; itr != itrEnd; ++itr)
	{
		if (pageToFind.getName() == (*itr)->getName())
			return ind;
		ind++;
	}
	return NOT_FOUND;
}

void User::removeUserFromFriendsArr(int ind)
//This function removes a user from another user's friends arr
{
	vector< User*>::iterator itr = friends.begin();

	advance(itr, ind);
	friends.erase(itr);
}

void User::removePageFromPagesArr(int ind)
//This function removes a page from users fan pages arr
{
	vector< FanPage*>::iterator itr = fanPages.begin();

	advance(itr, ind);
	fanPages.erase(itr);
}

void User::showAllMyFriends()
//This function shows all of the user friends
{
	vector<User*>::iterator itr = friends.begin(), itrEnd = friends.end();
	int counter = 1;

	if (friends.size() == 0)
		cout << name << " has no friends yet." << endl;
	else
	{
		cout << endl << name << "'s friends are: " << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << counter << ") " << (**itr);
			counter++;
		}
	}
	cout << endl;
}

void User::showAllMyFanPages()
//This function shows all the fan pages the user likes
{
	vector<FanPage*>::iterator itr = fanPages.begin(), itrEnd = fanPages.end();
	int counter = 1;

	cout << "The pages " << name << " likes are: " << endl;

	for (; itr != itrEnd; ++itr)
	{
		cout << counter << ") " << (**itr) << endl;
		counter++;
	}
	cout << endl;
}

User& User::operator+=(User& other)
//operator += to connect 2 users
{
	this->setNewFriend(&other);
	other.setNewFriend(this);
	return *this;
}

User& User::operator+=(FanPage& other)
//operator += to connect user and fan page
{
	this->setNewFanPage(&other);
	other.setNewFan(this);
	return *this;
}

bool User::operator>(const User& other) const
//operator > that compares 2 users by their friends amount
{
	return (friends.size() > other.friends.size());
}

bool User::operator>(const FanPage& other) const
//operator > that compares user and fan page by their friends\fans amount
{
	return (friends.size() > other.getFansNum());
}

ostream& operator<<(ostream& os, const User& user)
//operator <<
{
	if (typeid(os) == typeid(ofstream))
		os << user.getBirthDay() << user.getName() << endl;
	else
		os << user.getName() << ", date of birth: " << user.getBirthDay();
	return os;
}

User::~User()
//destructor
{
	vector<Status*>::iterator itr = statuses.begin(), itrEnd = statuses.end();

	for (; itr != itrEnd; ++itr)
		delete(*itr);
}
