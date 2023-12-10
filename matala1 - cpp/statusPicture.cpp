#include "statusPicture.h"
#include "status.h"
#include <fstream>

using namespace std;

StatusPicture::StatusPicture(const Status& status, const string picture)noexcept(false):Status(status)
//constructor
{
	if (picture[0] == '\0')
		throw PictureDescriptionException();

	pictureDescription = picture;
}

void StatusPicture::toOs(ostream& os) const 
//Picture details addition to statuses opperator << 
{
	if (typeid(os) == typeid(ofstream))
		os << pictureDescription << endl;
	else
		os << "Picture description: " << pictureDescription << endl << endl;
}

bool StatusPicture::operator==(const Status& other) const
//This function checks if 2 picture statuses are the same post and return true if so
{
	if (!Status::operator==(other))
		return false;

	const StatusPicture* temp = dynamic_cast<const StatusPicture*>(&other);
	if (temp == nullptr)
		return false;
	return (pictureDescription == temp->pictureDescription);
}

bool StatusPicture::operator!=(const Status& other) const
//This function checks if 2 statuses are the same post and return true if they are different
{
	return !(*this == other);
}
