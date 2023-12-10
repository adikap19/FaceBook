#ifndef __STATUS_H
#define __STATUS_H

#include <iostream>
#include <fstream>
#include <string>
#include "time.h"
#include "date.h"
class StatusPicture;
class StatusVideo;
#pragma warning (disable:4996)

const int TEXT_STATUS = 1;
const int PICTURE_STATUS = 2;
const int VIDEO_STATUS = 3;

class TextException : public std::exception
{
public:
	virtual const char* what() const override { return "Text can not be empty!"; }
};

class Status
{
protected:
	std::string text;
	Time publishTime;
	Date publishDate;

	Status(const Status& other) = default;
public:
	Status(Time& time, Date& date, const std::string stat)noexcept(false);
	Status(std::ifstream& inFile) :publishTime(inFile), publishDate(inFile) { inFile >> *this; }

	const std::string& getText() const { return text; }
	const Time& getPublishTime() const { return publishTime; }
	const Date& getPublishDate() const { return publishDate; }

	virtual bool operator==(const Status& other) const;
	virtual bool operator!=(const Status& other) const;
	bool operator==(const StatusVideo& other) const { return false; }
	bool operator!=(const StatusVideo& other) const { return true; }
	bool operator==(const StatusPicture& other) const { return false; }
	bool operator!=(const StatusPicture& other) const { return true; }
	virtual void toOs(std::ostream& os) const;
	friend std::ostream& operator<<(std::ostream& os, const Status& status);
	friend std::istream& operator>>(std::istream& is, Status& status);
};
#endif
