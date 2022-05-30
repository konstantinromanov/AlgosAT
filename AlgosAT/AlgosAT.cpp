// AlgosAT1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "TestsAvlTree.h"
#include "AvlTree.h"
#include "TestsStack.h"
#include "MaxHeap.h"
#include "TestsMaxHeap.h"


//template<typename T>
//class HeapSort
//{
//public:
//
//	void ascOrder(T* arr, int size)
//	{
//		MaxHeap<T> heap = MaxHeap<T>(arr, size);
//
//		for (size_t i = size; i > 0; i--)
//		{
//			T val = heap.removeMax();
//			//arr[i - 1] = val;
//		}
//	}
//};

bool isValidInput(std::string input)
{
	for (const char c : input)
	{
		if (!isalnum(c))
		{
			return false;
		}
	}

	return true;
}

class App
{
public:

	App()
	{

	}

	void runApp()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(2);
		//tree.insert(1);
		//tree.insert(4);
		//tree.insert(40);
		//tree.insert(25);
		//tree.remove(20);

		std::string treeOutput;

		std::string userInput;
		std::string treeElementInput;
		int choice = 0;
		bool exitProgram = false;
		int number{};
		int numbeToRemover{};

		do
		{

			/*for (size_t i = 0; i < 3; i++)
			{
				std::cout << i + 1 << ' ' << "Inorder" << std::endl;
			}*/
			std::cout << "-------------------------------------------\n";
			std::cout << std::setw(10) << "Menu\n" << std::endl;

			std::cout << 1 << ' ' << "Preorder" << std::endl;
			std::cout << 2 << ' ' << "Inorder" << std::endl;
			std::cout << 3 << ' ' << "Postorder" << std::endl;
			std::cout << 4 << ' ' << "Insert element" << std::endl;
			std::cout << 5 << ' ' << "Remove element" << std::endl;


			std::cout << "-------------------------------------------\n";
			std::cout << "Choose operation (1 - 5) or 'E' to exit: ";


			std::cin >> userInput;

			if (!isValidInput(userInput))
			{
				std::cout << "Invalid input" << std::endl;
			}

			try
			{

				choice = stoi(userInput);

				switch (choice)
				{

				case 1:
					std::cout << "Preorder: " << std::endl;
					treeOutput = tree.preOrder();
					std::cout << treeOutput << std::endl;
					break;
				case 2:
					std::cout << "Inorder: " << std::endl;
					treeOutput = tree.inOrder();
					std::cout << treeOutput << std::endl;
					break;
				case 3:
					std::cout << "Postorder: " << std::endl;
					treeOutput = tree.postOrder();
					std::cout << treeOutput << std::endl;
					break;
				case 4:
					std::cout << "Enter a number to insert: ";
					std::cin >> treeElementInput;

					try
					{
						number = stoi(treeElementInput);
						tree.insert(number);
						std::cout << "inserted: " << number << std::endl;
					}
					catch (const std::exception&)
					{
						std::cout << treeElementInput << " is invalid input" << std::endl;
					}

					break;
				case 5:
					std::cout << "Enter a number to remove: ";
					std::cin >> treeElementInput;

					try
					{
						numbeToRemover = stoi(treeElementInput);

						if (tree.remove(numbeToRemover))
						{
							std::cout << "removed: " << numbeToRemover << std::endl;
						}
						else
						{
							std::cout << "Number " << numbeToRemover << " not found" << std::endl;
						}
					}
					catch (const std::exception&)
					{
						std::cout << treeElementInput << " is invalid input" << std::endl;
					}

					break;
				default:
					std::cout << "invalid input" << std::endl;
					break;
				}

			}
			catch (const std::exception&)
			{
				if (userInput == "e" || userInput == "E")
				{
					exitProgram = true;
				}
				else
				{
					std::cout << "invalid input" << std::endl;
				}
			}

		} while (!exitProgram);

	}
};

int main()
{	
	// -----------------------------------------
	//TestsMaxHeap testsMaxHeap = TestsMaxHeap();
	//testsMaxHeap.runTests();

	//TestsStack testsStack = TestsStack();
	TestsAvlTree testsAvlTree = TestsAvlTree();

	//testsStack.runTests();
	//testsAvlTree.runTests();

	App app = App();
	app.runApp();
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
