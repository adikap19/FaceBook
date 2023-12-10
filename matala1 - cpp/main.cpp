#include "faceBook.h"
#include "userInterface.h"
#include <fstream>

using namespace std;

int main()
{
	int nextAction = 0;

	ifstream inFile("FaceBook.txt");
	FaceBook web(inFile);
	UserInterface UI(web);
	web.getDataFromFile(inFile);
	inFile.close();

	cout << "Welcome to FaceBook!" << endl << endl;
	do
	{
		UI.printMenu();
		cin >> nextAction;
		while (cin.fail())
		{
			UI.ignoreLine();
			cout << "Choice is not valid." << endl << endl;
			UI.printMenu();
			cin >> nextAction;
		}
		UI.activateChoice(nextAction);

	} while (nextAction != 12);

	return 0;
}
