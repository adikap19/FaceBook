#ifndef __FACEBOOK_H
#define __FACEBOOK_H

#include <iostream>
#include <list>
#include <string>
#include "users.h"
#include "fanPages.h"
#include <fstream>
#pragma warning (disable:4996)

class Status;

class FaceBook
{
private:
	std::list<User> users;
	std::list<FanPage> fanPages;

	FaceBook(const FaceBook& other);
public:
	FaceBook(std::ifstream& inFile);

	int getNumOfUsers() const { return users.size(); }
	int getNumOfFanPages() const { return fanPages.size(); }

	void setNewUser(User& newUser) { users.push_back(std::move(newUser)); }
	void setNewFanPage(FanPage& newFanPage) { fanPages.push_back(std::move(newFanPage)); }

	User* findUserByName(std::string name);
	FanPage* findFanPageByName(std::string name);
	void unConnect(User& first, User& second);
	void unLike(User& first, FanPage& page);
	void showAllMembers();

	friend std::ostream& operator<<(std::ostream& os, const FaceBook& web);
	void getDataFromFile(std::ifstream& inFile);
	void getDataOfOneUser(std::ifstream& inFile);
	void getStatuseFromFile(std::ifstream& inFile, User& user);
	void getDataOfOneFanPage(std::ifstream& inFile);
};
#endif
