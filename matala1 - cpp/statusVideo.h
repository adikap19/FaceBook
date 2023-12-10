#ifndef __STATUSVIDEO_H
#define __STATUSVIDEO_H

#include <iostream>
#include "status.h"
#include "time.h"
#include <string>

class VideoDescriptionException : public std::exception
{
public:
	virtual const char* what() const override { return "Video description can not be empty!"; }
};

class StatusVideo :public Status
{
private:
	std::string videoDescription;
	Time videoLength;

	StatusVideo(const StatusVideo& other) = default;
public:
	StatusVideo(const Status& status, const std::string video, Time& videoLength)noexcept(false);
	StatusVideo(std::ifstream& inFile):Status(inFile), videoLength(inFile){ getline(inFile, videoDescription); }

	std::string getVideoDescription() const { return videoDescription; }
	const Time& getVideoLen() const { return videoLength; }
	virtual void toOs(std::ostream& os) const override;
	virtual bool operator==(const Status& other) const;
	virtual bool operator!=(const Status& other) const;
};
#endif
