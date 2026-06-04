#include "World.h"
#include<iomanip>
#include<ctime>

int main() {
	srand(time(0));
	
	//set world
	int wolfs, rabbits, grass;
	cout << left << setw(30) << "Rule: The total number of organisms must not exceed 200."<<endl;
	cout << left << setw(30) << "The life cycle of the world depends on the established population size of your organisms." << endl<<endl;
	cout <<left<< setw(30) << "Set the number of wolfs: ";
	cin >> wolfs;
	cout << left << setw(30) << "Set the number of rabbits: ";
	cin >> rabbits;
	cout << left << setw(30) << "Set the number of grass: ";
	cin >> grass;

	World world(wolfs, rabbits, grass);
	world.display();
	//system("cls");
	bool exit = false;

	//menu
	while(!exit)
	{
		cout << left << setw(5) << "1." << setw(5) << "Next turn" << endl;
		cout << left << setw(5) << "2." << setw(5) << "Next 10 turns" << endl;
		cout << left << setw(5) << "3." << setw(5) << "Exit" << endl;
		int a;
		cin >> a;
		switch (a) {
		case 1:
			world.update();
			world.display();
			break;
		case 2:
			for (int i = 0;i < 10;i++) {
				world.update();
				world.display();
			}
			break;
		case 3:
			exit = true;
			break;
		default:
			cout << "Please chose one from the list." << endl;
		}
		//system("cls");
	}
}