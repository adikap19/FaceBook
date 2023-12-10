#ifndef __FANPAGES_H
#define __FANPAGES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#pragma warning (disable:4996)

class User;
class Status;
class Time;

class FanPageException : public std::exception
{
public:
	virtual const char* what() const override { return "Fan page name can not be empty!"; }
};

class FanPage
{
private:
	std::string name;
	std::vector<Status*> statuses;
	std::vector<User*> fans;

	FanPage(const FanPage& other) = default;
public:
	FanPage(const std::string name = nullptr)noexcept(false);
	FanPage(const FanPage&& other)noexcept(false);
	FanPage(std::ifstream& inFile) { inFile >> *this; }

	const std::string getName() const { return name; }
	int getStatusesNum() const { return statuses.size(); }
	int getFansNum() const { return fans.size(); }
	const std::vector<Status*>& getStatusesArr() const { return statuses; }

	void setNewFan(User* newFan) { fans.push_back(newFan); }
	void setNewTextStatus(Time& time, Date& date, std::string text)noexcept(false);
	void setNewTextStatusFromFile(std::ifstream& inFile);
	void setNewPictureStatus(Time& time, Date& date, std::string text, std::string description)noexcept(false);
	void setNewPictureStatusFromFile(std::ifstream& inFile);
	void setNewVideoStatus(Time& time, Date& date, std::string text, std::string description, Time& len)noexcept(false);
	void setNewVideoStatusFromFile(std::ifstream& inFile);

	void showAllMyStatuses();
	int findFanIndInFansArr(User& userToFind);
	void removeFanFromFansArr(int ind);
	void showAllMyFans();

	bool operator>(const FanPage& other) const;
	bool operator>(const User& other) const;
	friend std::ostream& operator<<(std::ostream& os, const FanPage& page);
	friend std::istream& operator>>(std::istream& is, FanPage& page) { getline(is, page.name); return is;}

	~FanPage();
};
#endif
