#ifndef __USERS_H
#define __USERS_H

const int NOT_FOUND = -1;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "date.h"
class FanPage;
class Status;
class Time;
#pragma warning (disable:4996)

class UserException : public std::exception
{
public:
	virtual const char* what() const override { return "User name can not be empty!"; }
};

class User
{
private:
	std::string name;
	Date birthDay;
	std::vector<User*> friends;
	std::vector<FanPage*> fanPages;
	std::vector<Status*> statuses;

	User(const User& other) = default;
public:
	User(const std::string userName, Date& dateOfBirth)noexcept(false);
	User(const User&& other)noexcept(false);
	User(std::ifstream& inFile):birthDay(inFile) { inFile >> *this; }

	const std::string getName() const { return name; }
	int getFriendsNum() const { return friends.size(); }
	int getPagesNum() const { return fanPages.size(); }
	int getStatusesNum() const { return statuses.size(); }
	const Date& getBirthDay() const { return birthDay; }
	const std::vector<User*>& getFriendsArr() const { return friends; }
	const std::vector<FanPage*>& getFanPagesArr() const { return fanPages; }
	const std::vector<Status*>& getStatusesArr() const { return statuses; }

	void setNewFriend(User* newFriend) { friends.push_back(newFriend); }
	void setNewFanPage(FanPage* newPage) { fanPages.push_back(newPage); }
	void setNewTextStatus(Time& time, Date& date, std::string text)noexcept(false);
	void setNewTextStatusFromFile(std::ifstream& inFile);
	void setNewPictureStatus(Time& time, Date& date, std::string text, std::string description)noexcept(false);
	void setNewPictureStatusFromFile(std::ifstream& inFile);
	void setNewVideoStatus(Time& time, Date& date, std::string text, std::string description, Time& len)noexcept(false);
	void setNewVideoStatusFromFile(std::ifstream& inFile);

	bool currentlyConncected(std::string name);
	bool currentlyFan(std::string pageName);
	void showAllMyStatuses();
	void showMyLastTenStatuses();
	void showMyFriendsLastTenStatuses();
	int findFriendIndInFriendsArr(User& userToFind);
	int findPageIndInPagesArr(FanPage& pageToFind);
	void removeUserFromFriendsArr(int ind);
	void removePageFromPagesArr(int ind);
	void showAllMyFriends();
	void showAllMyFanPages();

	User& operator+=(User& other);
	User& operator+=(FanPage& other);
	bool operator>(const User& other) const;
	bool operator>(const FanPage& other) const;
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>>(std::istream& is, User& user) { getline(is, user.name); return is; }

	~User();
};
#endif
