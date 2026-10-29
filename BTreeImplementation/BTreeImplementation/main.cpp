#include <iostream>
#include "BTree.h"
using namespace std;

int main(){

	int choice;
    Btree<int , 3>tree ;

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
            {
                int value;

                cout << "Enter the value to insert: ";
                cin >> value;

                if (tree.insert(value))
                {
                    cout << "Value inserted successfully!" << endl;
                }
                else
                {
                    cout << "Value already exists!" << endl;
                }

                break;
            }

        case 2:
            cout << "Delete selected\n";
            break;

        case 3:
        {
            int value;
            int index = -1;
            cout << "Enter the value : ";
            cin >> value;
            auto result = tree.search(value, index);

            if (result != nullptr)
            {
                cout << "Key found!" << endl;
                cout << "Index: " << index << endl;
                cout << "Value: " << result->key[index] << endl;
            }
            else
            {
                cout << "Key not found!" << endl;
            }
        }

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


//input test


//Btree<int, 3> tree;
//
//InternalNode<int, 3> root;
//root.is_leaf = false;
//root.num_keys = 2;
//root.key[0] = 20;
//root.key[1] = 40;
//
//LeafNode<int, 3> left;
//left.is_leaf = true;
//left.num_keys = 2;
//left.key[0] = 5;
//left.key[1] = 10;
//
//LeafNode<int, 3> middle;
//middle.is_leaf = true;
//middle.num_keys = 2;
//middle.key[0] = 25;
//middle.key[1] = 30;
//
//LeafNode<int, 3> right;
//right.is_leaf = true;
//right.num_keys = 2;
//right.key[0] = 50;
//right.key[1] = 60;
//
//root.child[0] = &left;
//root.child[1] = &middle;
//root.child[2] = &right;

//tree.root = &root;



