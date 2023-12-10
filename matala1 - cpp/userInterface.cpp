#include "faceBook.h"
#include "users.h"
#include "fanPages.h"
#include "status.h"
#include "statusPicture.h"
#include "statusVideo.h"
#include "time.h"
#include "date.h"
#include "userInterface.h"
#include <fstream>

using namespace std;

void UserInterface::printMenu()
//This function prints the menu for the user
{
	cout << "Choose the next move:" << endl <<
		"1.Create user" << endl <<
		"2.Create fanPage" << endl <<
		"3.Add new status to user/fan page" << endl <<
		"4.Show user/fan page's statuses" << endl <<
		"5.Show user's friend's 10 last statuses" << endl <<
		"6.Add connection between 2 users" << endl <<
		"7.Cancel connection between 2 users" << endl <<
		"8.Like fanPage" << endl <<
		"9.Unlike fanPage" << endl <<
		"10.Show all FaceBook's members" << endl <<
		"11.Show all the friends/fans of user/fan page" << endl <<
		"12.Exit" << endl << endl;
}

void UserInterface::activateChoice(int choice)
//This function gets the action we chose to activate and runs it
{
	switch (choice)
	{
	case 1:
		optionOne();
		break;
	case 2:
		optionTwo();
		break;
	case 3:
		optionThree();
		break;
	case 4:
		optionFour();
		break;
	case 5:
		optionFive();
		break;
	case 6:
		optionSix();
		break;
	case 7:
		optionSeven();
		break;
	case 8:
		optionEight();
		break;
	case 9:
		optionNine();
		break;
	case 10:
		web.showAllMembers();
		break;
	case 11:
		optionEleven();
		break;
	case 12:
	{
		cout << "Exiting program." << endl;
		ofstream outFile("FaceBook.txt", ios::trunc);
		outFile << web << endl;
		outFile.close();
		break;
	}
	default:
		cout << "Choice is not valid." << endl << endl;
		break;
	}
}

int UserInterface::chooseWhoToDoTheActionFor()
//This function returns 1 if we decide to do the action for user / 2 for fan page
{
	int decision;

	cout << "Choose whether to do this action for user(press 1) or for fan page(press 2):" << endl;
	cin >> decision;

	while (decision != USER && decision != FAN_PAGE)
	{
		cout << "Invalid choice. Enter again:" << endl;
		ignoreLine();
		cin >> decision;
	}
	return decision;
}

void UserInterface::optionOne()
//sign in new user
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			createNewUser();
			isValid = true;
		}
		catch (MemberAlreadyExistException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionTwo()
//sign in new fan page
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			createFanPage();
			isValid = true;
		}
		catch (MemberAlreadyExistException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionThree()
//This function adds Status to user/fan page
{
	bool isValid = false;

	while (!isValid)
	{
		try
		{
			if (chooseWhoToDoTheActionFor() == USER)
			{
				ignoreLine();
				addStatusToUser();
			}
			else
			{
				ignoreLine();
				addStatusToFanPage();
			}
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
	cout << endl;
}

void UserInterface::optionFour()
//This function shows all the statuses of user/fan page
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			showStatusesOfMember();
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionFive()
//This funcion shows the last ten statuses of a user friends
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			showLastTenStatusesOfFriends();
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionSix()
//This funcion connects two users
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			addConnectionToUser();
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionSeven()
//This funcion unConnects two users
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			cancelUsersConnection();
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionEight()
//This funcion connects user and fan page
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			addConnectionToFanPage();
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionNine()
//This funcion unConnects user and fan page
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			cancelUserAndFanPageConnection();
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::optionEleven()
//This funcion shows all the member connections
{
	ignoreLine();
	bool isValid = false;
	while (!isValid)
	{
		try
		{
			showAllConnectionsOfMember();
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::createNewUser()noexcept(false)
//This function creates new user to faceBook
{
	string userName;
	bool isValidData = false;

	cout << "Enter user's name:" << endl;

	while (!isValidData)
	{
		getline(cin, userName);

		if (web.findUserByName(userName) != nullptr)
			throw MemberAlreadyExistException(userName);
		else
		{
			cout << "Enter user's date of birth(day, month, year):" << endl;
			Date birthDay = initDate();
			ignoreLine();
			try
			{
				User newUser(userName, birthDay);
				web.setNewUser(newUser);
				isValidData = true;
			}
			catch (UserException& e) { cout << e.what() << endl; }
			catch (...) { cout << "Unknown Error" << endl; }
			if (!isValidData)
				cout << endl << "Please enter user's name again:" << endl;
		}
	}
	cout << endl;
}

void UserInterface::createFanPage()noexcept(false)
//This function creates new fan page to facebook
{
	string pageName;
	bool isValidName = false;

	cout << "Enter fan page's name:" << endl;

	while (!isValidName)
	{
		getline(cin, pageName);

		if (web.findFanPageByName(pageName) != nullptr)
			throw MemberAlreadyExistException(pageName);
		else
		{
			try
			{
				FanPage newPage(pageName);
				web.setNewFanPage(newPage);
				isValidName = true;
			}
			catch (FanPageException& e) { cout << e.what() << endl; }
			catch (...) { cout << "Unknown Error" << endl; }
			if (!isValidName)
				cout << endl << "Please enter fan page's name again:" << endl;
		}
	}
	cout << endl;
}

void UserInterface::addStatusToUser()noexcept(false)
//This function adds new status to user
{
	string name, text, description;
	bool isValidStatus = false;
	Time statTime, videoLen;
	Date statDate;
	int statusType;

	cout << "Enter the name of the user you want to add new status to: " << endl;
	getline(cin, name);
	User* addStatusTo = web.findUserByName(name);

	if (addStatusTo == nullptr)
		throw MemberNotFoundException();
	getStatusDateAndTime(statTime, statDate);

	while (!isValidStatus)
	{
		try
		{
			statusType = getStatusDataFromUser(text, videoLen, description);

			if (statusType == TEXT_STATUS)
				addStatusTo->setNewTextStatus(statTime, statDate, text);
			else if (statusType == PICTURE_STATUS)
				addStatusTo->setNewPictureStatus(statTime, statDate, text, description);
			else
				addStatusTo->setNewVideoStatus(statTime, statDate, text, description, videoLen);

			isValidStatus = true;
		}
		catch (PictureDescriptionException& e) { cout << e.what() << endl; }
		catch (VideoDescriptionException& e) { cout << e.what() << endl; }
		catch (HourException& e) { cout << e.what() << endl; }
		catch (MinutesException& e) { cout << e.what() << endl; }
		catch (TextException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
		if (!isValidStatus)
			cout << endl << "Please try again." << endl;
	}
}

void UserInterface::addStatusToFanPage()noexcept(false)
//This function adds new status to fan page
{
	string name, text, description;
	bool isValidStatus = false;
	Time statTime, videoLen;
	Date statDate;
	int statusType;

	cout << "Enter the name of the fan page you want to add new status to: " << endl;
	getline(cin, name);
	FanPage* addStatusTo = web.findFanPageByName(name);

	if (addStatusTo == nullptr)
		throw MemberNotFoundException();
	getStatusDateAndTime(statTime, statDate);

	while (!isValidStatus)
	{
		try
		{
			statusType = getStatusDataFromUser(text, videoLen, description);

			if (statusType == TEXT_STATUS)
				addStatusTo->setNewTextStatus(statTime, statDate, text);
			else if (statusType == PICTURE_STATUS)
				addStatusTo->setNewPictureStatus(statTime, statDate, text, description);
			else
				addStatusTo->setNewVideoStatus(statTime, statDate, text, description, videoLen);

			isValidStatus = true;
		}
		catch (PictureDescriptionException& e) { cout << e.what() << endl; }
		catch (VideoDescriptionException& e) { cout << e.what() << endl; }
		catch (HourException& e) { cout << e.what() << endl; }
		catch (MinutesException& e) { cout << e.what() << endl; }
		catch (TextException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
		if (!isValidStatus)
			cout << endl << "Please try again." << endl;
	}
}

int UserInterface::chooseStatusType()
//This function returns the type of status the user wants to a add
{
	int choice;

	cout << "Please choose which status you want to add: enter 1 for text, 2 for picture and 3 for video" << endl;
	cin >> choice;

	while (choice != TEXT_STATUS && choice != PICTURE_STATUS && choice != VIDEO_STATUS)
	{
		cout << "Invalid choice. Enter again:" << endl;
		ignoreLine();
		cin >> choice;
	}
	return choice;
}

void UserInterface::getStatusDateAndTime(Time& statTime, Date& statDate)
//This functipon gets the status date and time
{
	statTime = initTime();
	cout << "Enter current date(day, month, year):" << endl;
	statDate = initDate();
}

int UserInterface::getStatusDataFromUser(string& text, Time& videoLen, string& description)noexcept(false)
//This fuction get the needed data for the status the user wanted to add
{
	int statusType, hours, minutes;

	statusType = chooseStatusType();
	ignoreLine();

	if (statusType == PICTURE_STATUS)
	{
		cout << "Enter picture description: " << endl;
		getline(cin, description);
	}
	else if (statusType == VIDEO_STATUS)
	{
		cout << "Enter video length(hours, minutes):" << endl;
		cin >> hours >> minutes;
		Time temp(hours, minutes);
		videoLen = temp;
		cout << "Enter video description:" << endl;
		ignoreLine();
		getline(cin, description);
	}

	cout << endl << "Enter text:" << endl;
	getline(cin, text);
	return statusType;
}

void UserInterface::showStatusesOfMember()noexcept(false)
//This function shows all the statuses of user/fan page that we get in the function
{
	string name;

	if (chooseWhoToDoTheActionFor() == USER)
	{
		cout << "Enter the name of the user you want to see his statuses: " << endl;
		ignoreLine();
		getline(cin, name);
		User* showStatusesOf = web.findUserByName(name);

		if (showStatusesOf == nullptr)
			throw MemberNotFoundException();

		cout << endl << showStatusesOf->getName() << "'s statuses:" << endl;
		showStatusesOf->showAllMyStatuses();
	}
	else
	{
		cout << "Enter the name of the fan page you want to see his statuses: " << endl;
		ignoreLine();
		getline(cin, name);
		FanPage* showStatusesOf = web.findFanPageByName(name);

		if (showStatusesOf == nullptr)
			throw MemberNotFoundException();

		cout << endl << showStatusesOf->getName() << "'s statuses:" << endl;
		showStatusesOf->showAllMyStatuses();
	}
}

void UserInterface::showLastTenStatusesOfFriends()noexcept(false)
//This function gets a member and prints his friends's last 10 statuses
{
	string name;

	cout << "Enter the name of the user you want to see his friend's last 10 statuses: " << endl;
	getline(cin, name);
	User* showFriendsStat = web.findUserByName(name);

	if (showFriendsStat == nullptr)
		throw MemberNotFoundException();

	showFriendsStat->showMyFriendsLastTenStatuses();
}

void UserInterface::addConnectionToUser()noexcept(false)
//This function get the names of 2 users and connect them
{
	string name;
	bool isValid = false;

	cout << "Enter the first user's name: " << endl;
	getline(cin, name);
	User* firstUser = web.findUserByName(name);

	if (firstUser == nullptr)
		throw MemberNotFoundException();

	while (!isValid)
	{
		try
		{
			connectWithAnotherUser(*firstUser);
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (TryToConnectSelfException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::connectWithAnotherUser(User& user)noexcept(false)
//This function connects 2 users
{
	string nameToConnect;

	cout << "Enter name of the user that you want him to be friends with:" << endl;
	getline(cin, nameToConnect);
	User* wantedUser = web.findUserByName(nameToConnect);

	if (wantedUser == nullptr)
		throw MemberNotFoundException();
	if (user.getName() == wantedUser->getName())
		throw TryToConnectSelfException();

	if (!(user.currentlyConncected(wantedUser->getName())))
	{
		user += (*wantedUser);
		cout << user.getName() << " and " << wantedUser->getName() << " are now friends." << endl << endl;
	}
	else
		cout << user.getName() << " and " << wantedUser->getName() << " are already friends." << endl << endl;
}

void UserInterface::addConnectionToFanPage()noexcept(false)
//This function adds fan to fan page
{
	string name;
	bool isValid = false;

	cout << "Enter the name of the user who wants to like a page:" << endl;
	getline(cin, name);
	User* fan = web.findUserByName(name);

	if (fan == nullptr)
		throw MemberNotFoundException();

	while (!isValid)
	{
		try
		{
			connectWithFanPage(*fan);
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::connectWithFanPage(User& fan)noexcept(false)
//This function connects user and fan page
{
	string pageName;

	cout << "Enter name of the fan page that you want him to like:" << endl;
	getline(cin, pageName);
	FanPage* wantedPage = web.findFanPageByName(pageName);

	if (wantedPage == nullptr)
		throw MemberNotFoundException();

	if (!(fan.currentlyFan(wantedPage->getName())))
	{
		fan += (*wantedPage);
		cout << fan.getName() << " now likes " << wantedPage->getName() << " fan page." << endl << endl;
	}
	else
		cout << fan.getName() << " already liked " << wantedPage->getName() << " fan page." << endl << endl;
}

void UserInterface::cancelUsersConnection()noexcept(false)
//This function gets 2 users and unConnect their friendShip
{
	string name1;
	bool isValid = false;

	cout << "Enter the name of the user that wants to unconnect another user:" << endl;
	getline(cin, name1);
	User* firstUser = web.findUserByName(name1);

	if (firstUser == nullptr)
		throw MemberNotFoundException();

	while (!isValid)
	{
		try
		{
			unconnectUserFromAnother(*firstUser);
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::unconnectUserFromAnother(User& firstUser)noexcept(false)
//This function cancel the connrction between the user we got and the user the function recieve
{
	string name2;

	cout << "Enter the name of the user he wants to unconnect:" << endl;
	getline(cin, name2);
	User* secondUser = web.findUserByName(name2);

	if (secondUser == nullptr)
		throw MemberNotFoundException();

	if (firstUser.currentlyConncected(secondUser->getName()))
	{
		web.unConnect(firstUser, *secondUser);
		cout << firstUser.getName() << " and " << secondUser->getName() << " are not friends anymore." << endl << endl;
	}
	else
		cout << firstUser.getName() << " and " << secondUser->getName() << " are not connected. Can not cancel the connection." << endl << endl;
}

void UserInterface::cancelUserAndFanPageConnection()noexcept(false)
//This function gets user and fan page an unConnect them from each other
{
	string userName;
	bool isValid = false;

	cout << "Enter the name of the user that wants to unLike fan page:" << endl;
	getline(cin, userName);
	User* user = web.findUserByName(userName);

	if (user == nullptr)
		throw MemberNotFoundException();

	while (!isValid)
	{
		try
		{
			unconnectUserFromFanPage(*user);
			isValid = true;
		}
		catch (MemberNotFoundException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
	}
}

void UserInterface::unconnectUserFromFanPage(User& user)noexcept(false)
//This function cancel the connrction between the page we got and the user the function recieve
{
	string pageName;

	cout << "Enter the name of the fan page he wants to unLike:" << endl;
	getline(cin, pageName);
	FanPage* page = web.findFanPageByName(pageName);

	if (page == nullptr)
		throw MemberNotFoundException();

	if (user.currentlyFan(page->getName()))
	{
		web.unLike(user, *page);
		cout << user.getName() << " unLiked " << page->getName() << " fan page." << endl << endl;
	}
	else
		cout << user.getName() << " already unLiked " << page->getName() <<
		". Can not cancel the connection." << endl << endl;
}

void UserInterface::showAllConnectionsOfMember()noexcept(false)
//This function shows all the friends/fans of user/fan page
{
	string name;

	if (chooseWhoToDoTheActionFor() == USER)
	{
		cout << "Enter the name of the user you want to see his friends:" << endl;
		ignoreLine();
		getline(cin, name);
		User* user = web.findUserByName(name);

		if (user == nullptr)
			throw MemberNotFoundException();
		user->showAllMyFriends();
	}
	else
	{
		cout << "Enter the name of the fan page you want to see his fans:" << endl;
		ignoreLine();
		getline(cin, name);
		FanPage* page = web.findFanPageByName(name);

		if (page == nullptr)
			throw MemberNotFoundException();
		page->showAllMyFans();
	}
}

Time UserInterface::initTime()
//This function initials hour and checks it validity
{
	int hours, minutes;
	bool isValidaHour = false;

	cout << "Enter current hour(hours, minutes):" << endl;

	while (!isValidaHour)
	{
		cin >> hours >> minutes;
		try
		{
			Time hour(hours, minutes);
			return hour;
		}
		catch (HourException& e) { cout << e.what() << endl; }
		catch (MinutesException& e) { cout << e.what() << endl; }
		catch (TimeException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
		if (!isValidaHour)
			cout << endl << "Please enter the current Hour again(hours, minutes):" << endl;
	}
}

Date UserInterface::initDate()
//This function initials date and checks it validity
{
	int day, month, year;
	bool isValidDate = false;

	while (!isValidDate)
	{
		cin >> day >> month >> year;
		try
		{
			Date date(day, month, year);
			return date;
		}
		catch (DayException& e) { cout << e.what() << endl; }
		catch (MonthException& e) { cout << e.what() << endl; }
		catch (YearException& e) { cout << e.what() << endl; }
		catch (DateException& e) { cout << e.what() << endl; }
		catch (...) { cout << "Unknown Error" << endl; }
		if (!isValidDate)
			cout << endl << "Please enter the date again(day, month, year):" << endl;
	}
}

void UserInterface::ignoreLine()
{
	cin.clear();
	cin.ignore(100, '\n');
}
