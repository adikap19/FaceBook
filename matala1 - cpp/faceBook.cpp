#include "faceBook.h"
#include "users.h"
#include "fanPages.h"
#include "date.h"
#include "time.h"
#include "status.h"
#include <list>

using namespace std;

FaceBook::FaceBook(ifstream& inFile)
//faceBook constructor that gets his data from text file
{
	int usersAmount, fanPagesAmount;
	 
	inFile >> usersAmount;
	inFile.get();
	for (int i = 0; i < usersAmount; i++)
	{
		User user(inFile);
		setNewUser(user);
	}

	inFile >> fanPagesAmount;
	inFile.get();
	for (int i = 0; i < fanPagesAmount; i++)
	{
		FanPage page(inFile);
		setNewFanPage(page);
	}
}

User* FaceBook::findUserByName(string name)
//This function returns the wanted user
{
	list<User>::iterator itr = users.begin(), itrEnd = users.end();

	for (; itr != itrEnd; ++itr)
		if ((*itr).getName() == name)
			return &(*itr);

	return nullptr; //if the name is not exist
}

FanPage* FaceBook::findFanPageByName(string name)
//This function returns the wanted fan page
{
	list<FanPage>::iterator itr = fanPages.begin(), itrEnd = fanPages.end();

	for (; itr != itrEnd; ++itr)
		if ((*itr).getName() == name)
			return &(*itr);

	return nullptr; //if the name is not exist
}

void FaceBook::unConnect(User& first, User& second)
//This function removes the users from each other array
{
	int secondInd = first.findFriendIndInFriendsArr(second);
	int firstInd = second.findFriendIndInFriendsArr(first);

	first.removeUserFromFriendsArr(secondInd);
	second.removeUserFromFriendsArr(firstInd);
}

void FaceBook::unLike(User& user, FanPage& page)
//This function removes the user and the page from each other arrays
{
	int pageInd = user.findPageIndInPagesArr(page);
	int userInd = page.findFanIndInFansArr(user);

	page.removeFanFromFansArr(userInd);
	user.removePageFromPagesArr(pageInd);
}

void FaceBook::showAllMembers()
//This function represent all the users and fan pages of the web
{
	list<User>::iterator userItr = users.begin(), userItrEnd = users.end();
	list<FanPage>::iterator pageItr = fanPages.begin(), pageItrEnd = fanPages.end();
	int counter = 1;

	if (users.size() == 0)
		cout << "FaceBook has no users signed up yet." << endl;
	else
	{
		cout << "All the users are: " << endl;
		for (; userItr != userItrEnd; ++userItr)
		{
			cout << counter << ") " << (*userItr);
			counter++;
		}
	}
	if (fanPages.size() == 0)
		cout << "FaceBook has no fan pages created yet." << endl;
	else
	{
		counter = 1;
		cout << endl << "All the fan pages are: " << endl;
		for (; pageItr != pageItrEnd; ++pageItr)
		{
			cout << counter << ") " << (*pageItr);
			counter++;
		}
	}
	cout << endl;
}

ostream& operator<<(ostream& os, const FaceBook& web)
{
	int usersAmount = web.getNumOfUsers();
	int fanPagesAmount = web.getNumOfFanPages();

	list <User>::const_iterator itrUser = web.users.begin(), itrUserEnd = web.users.end();
	list <FanPage>::const_iterator itrFanPage = web.fanPages.begin(), itrFanPageEnd = web.fanPages.end();

	os << usersAmount << endl;
	for (; itrUser != itrUserEnd; ++itrUser)
		os << (*itrUser);

	os << fanPagesAmount << endl;
	for (; itrFanPage != itrFanPageEnd; ++itrFanPage)
		os << (*itrFanPage);

	itrUser = web.users.begin();

	for (; itrUser != itrUserEnd; ++itrUser)
	{
		int friendsAmount = (*itrUser).getFriendsNum();
		int likedPagesAmount = (*itrUser).getPagesNum();
		int statusesAmount = (*itrUser).getStatusesNum();

		vector <User*>::const_iterator itrFriends = (*itrUser).getFriendsArr().begin(), itrFriendsEnd = (*itrUser).getFriendsArr().end();
		vector <FanPage*>::const_iterator itrLikedPages = (*itrUser).getFanPagesArr().begin(), itrLikedPagesEnd = (*itrUser).getFanPagesArr().end();
		vector <Status*>::const_iterator itrStatuses = (*itrUser).getStatusesArr().begin(), itrStatusesEnd = (*itrUser).getStatusesArr().end();

		os << (*itrUser).getName() << endl;

		os << friendsAmount << endl;
		for (; itrFriends != itrFriendsEnd; ++itrFriends)
			os << (*itrFriends)->getName() << endl;

		os << likedPagesAmount << endl;
		for (; itrLikedPages != itrLikedPagesEnd; ++itrLikedPages)
			os << (**itrLikedPages);

		os << statusesAmount << endl;
		for (; itrStatuses != itrStatusesEnd; ++itrStatuses)
			os << (**itrStatuses);
	}

	itrFanPage = web.fanPages.begin();


	for (; itrFanPage != itrFanPageEnd; ++itrFanPage)
	{
		int statusesAmount = (*itrFanPage).getStatusesNum();

		vector <Status*>::const_iterator itrStatuses = (*itrFanPage).getStatusesArr().begin(), itrStatusesEnd = (*itrFanPage).getStatusesArr().end();

		os << (*itrFanPage).getName() << endl;

		os << statusesAmount << endl;
		for (; itrStatuses != itrStatusesEnd; ++itrStatuses)
			os << (**itrStatuses);
	}

	return os;
}

void FaceBook::getDataFromFile(ifstream& inFile)
//This function gets the previous actions and data of every member in FaceBook from the file
{
	int usersAmount = getNumOfUsers(), fanPagesAmount = getNumOfFanPages();

	for (int i = 0; i < usersAmount; i++)
		getDataOfOneUser(inFile);

	for (int i = 0; i < fanPagesAmount; i++)
		getDataOfOneFanPage(inFile);
}

void FaceBook::getDataOfOneUser(ifstream& inFile)
//This function gets the previous actions and data of user in FaceBook from the file
{
	string name;
	int numOfFriend, numOfPages, numOfStatuses;

	getline(inFile, name);
	User* user = findUserByName(name);

	inFile >> numOfFriend;
	inFile.get();
	for (int i = 0; i < numOfFriend; i++)
	{
		string friendName;
		getline(inFile, friendName);
		User* connection = findUserByName(friendName);

		if(!(user->currentlyConncected(friendName)))
			*user += *connection;
	}

	inFile >> numOfPages;
	inFile.get();
	for (int i = 0; i < numOfPages; i++)
	{
		string pageName;
		getline(inFile, pageName);
		FanPage* likedPage = findFanPageByName(pageName);
		*user += *likedPage;
	}

	inFile >> numOfStatuses;
	inFile.get();
	for (int i = 0; i < numOfStatuses; i++)
		getStatuseFromFile(inFile, *user);
}

void FaceBook::getStatuseFromFile(ifstream& inFile, User& user)
//This function gets status and place it in the user's statuses vector
{
	string statusType;
	getline(inFile, statusType);

	if (statusType == "Status")
		user.setNewTextStatusFromFile(inFile);
	else if (statusType == "StatusPicture")
		user.setNewPictureStatusFromFile(inFile);
	else
		user.setNewVideoStatusFromFile(inFile);
}

void FaceBook::getDataOfOneFanPage(ifstream& inFile)
//This function gets the previous actions and data of fan page in FaceBook from the file
{
	string name;
	int numOfStatuses;

	getline(inFile, name);
	FanPage* page = findFanPageByName(name);

	inFile >> numOfStatuses;
	inFile.get();

	for (int i = 0; i < numOfStatuses; i++)
	{
		string statusType;
		getline(inFile, statusType);

		if (statusType == "Status")
			page->setNewTextStatusFromFile(inFile);
		else if (statusType == "StatusPicture")
			page->setNewPictureStatusFromFile(inFile);
		else
			page->setNewVideoStatusFromFile(inFile);
	}
}
