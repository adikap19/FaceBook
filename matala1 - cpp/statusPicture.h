#ifndef __STATUSPICTURE_H
#define __STATUSPICTURE_H

#include <iostream>
#include <fstream>
#include "status.h"
#include <string>

class PictureDescriptionException : public std::exception
{
public:
	virtual const char* what() const override { return "Picture description can not be empty!"; }
};

class StatusPicture :public Status
{
private:
	std::string pictureDescription;

	StatusPicture(const StatusPicture& other) = default;
public:
	StatusPicture(const Status& status, const std::string picture)noexcept(false);
	StatusPicture(std::ifstream& inFile):Status(inFile) { getline(inFile, pictureDescription); }

	std::string getPictureDescription() const { return pictureDescription; }
	virtual void toOs(std::ostream& os) const override;
	virtual bool operator==(const Status& other) const;
	virtual bool operator!=(const Status& other) const;
};
#endif
