#include <iostream>
#include "BTree.h"
using namespace std;

int main(){

	int choice;

	do
	{
		cout << "\n========== B-Tree Menu ==========\n";
		cout << "1. Insert\n";
		cout << "2. Delete\n";
		cout << "3. Search\n";
		cout << "4. Display All (Depth First)\n";
		cout << "5. Exit\n";
		cout << "Enter your choice: ";

		cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Insert selected\n";
            break;

        case 2:
            cout << "Delete selected\n";
            break;

        case 3:
            cout << "Search selected\n";
            break;

        case 4:
            cout << "Display selected\n";
            break;

        case 5:
            cout << "Exit\n";
            break;

        default:
            cout << "Invalid choice! Try again,please\n";
        }

    } while (choice != 5);

    return 0;
}
