#include "status.h"
#include "statusVideo.h"

#include<fstream>

using namespace std;

StatusVideo::StatusVideo(const Status& status, const std::string video, Time& videoLen)noexcept(false) :Status(status), videoLength(videoLen)
//constructor
{
	if (video[0] == '\0')
		throw VideoDescriptionException();

	videoDescription = video;
}

void StatusVideo::toOs(std::ostream& os) const
//Video details addition to statuses opperator << 
{
	if (typeid(os) == typeid(ofstream))
		os << videoLength << videoDescription << endl;
	else
		os << "Video description: " << videoDescription << ", video length: " << videoLength << endl << endl;
}

bool StatusVideo::operator==(const Status& other) const
//This function checks if 2 picture statuses are the same post and return true if so
{
	if (!Status::operator==(other))
		return false;

	const StatusVideo* temp = dynamic_cast<const StatusVideo*>(&other);
	if (temp == nullptr)
		return false;
	return ((videoDescription == temp->videoDescription) && (videoLength == temp->videoLength));
}

bool StatusVideo::operator!=(const Status& other) const
//This function checks if 2 statuses are the same post and return true if they are different
{
	return !(*this == other);
}
