// AlgosAT1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Tests.h"
#include "AvlTree.h"

int main()
{
	AvlTree<int> tree = AvlTree<int>();
	tree.insert(10);
	tree.insert(20);
	//tree.insert(5);
	tree.insert(30);
	tree.insert(40);
	tree.insert(50);
	//tree.insert(25);

	/*tree.insert(13);
	tree.insert(10);
	
	tree.insert(11);
	tree.insert(5);
	tree.insert(4);
	tree.insert(6);*/

	tree.preOrder();

	Tests tests = Tests();
	//tests.runTests();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
