#ifndef __USER_INTERFACE_H
#define __USER_INTERFACE_H

#include <iostream>
class FaceBook;
class Status;
class User;
class Time;
class Date;
#pragma warning (disable:4996)

const int USER = 1;
const int FAN_PAGE = 2;

class MemberAlreadyExistException : public std::exception
{
private:
	std::string str;
public:
	MemberAlreadyExistException(std::string name) { str = "Member who's name is "; str += name; str += " already in the system, Try again.\n"; }
	virtual const char* what() const override { return str.c_str(); }
};

class MemberNotFoundException : public std::exception
{
public:
	virtual const char* what() const override { return "Member not found, Try again.\n"; }
};

class TryToConnectSelfException : public std::exception
{
public:
	virtual const char* what() const override { return "User can not connect to himself, Try again.\n"; }
};

class UserInterface
{
private:
	FaceBook& web;

	UserInterface(const UserInterface& other) = default;
public:
	UserInterface(FaceBook& web) :web(web) {}
	void printMenu();
	void activateChoice(int choice);
	int chooseWhoToDoTheActionFor();
	void optionOne();
	void optionTwo();
	void optionThree();
	void optionFour();
	void optionFive();
	void optionSix();
	void optionSeven();
	void optionEight();
	void optionNine();
	void optionEleven();
	void createNewUser()noexcept(false);
	void createFanPage()noexcept(false);
	int chooseStatusType();
	void getStatusDateAndTime(Time& statTime, Date& statDate);
	int getStatusDataFromUser(std::string& text, Time& videoLen, std::string& description)noexcept(false);
	void addStatusToUser()noexcept(false);
	void addStatusToFanPage()noexcept(false);
	void showStatusesOfMember()noexcept(false);
	void showLastTenStatusesOfFriends()noexcept(false);
	void addConnectionToUser()noexcept(false);
	void connectWithAnotherUser(User& user)noexcept(false);
	void addConnectionToFanPage()noexcept(false);
	void connectWithFanPage(User& fan)noexcept(false);
	void cancelUsersConnection()noexcept(false);
	void unconnectUserFromAnother(User& firstUser)noexcept(false);
	void cancelUserAndFanPageConnection()noexcept(false);
	void unconnectUserFromFanPage(User& user)noexcept(false);
	void showAllConnectionsOfMember()noexcept(false);
	Time initTime();
	Date initDate();
	void ignoreLine();
};
#endif