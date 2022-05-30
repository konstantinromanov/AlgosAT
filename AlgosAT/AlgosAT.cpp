// AlgosAT1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "TestsAvlTree.h"
#include "AvlTree.h"
#include "TestsStack.h"
#include "MaxHeap.h"
#include "TestsMaxHeap.h"


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

private:

	void PrintLine(int lenght)
	{
		std::cout << std::string(lenght, '-') << std::endl;
	}

public:

	App()
	{

	}

	void runApp()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(2);

		std::vector<std::string> menuItems = {
		"Insert element",
		"Remove element",
		"Preorder",
		"Inorder",
		"Postorder"
		};

		std::string invalidInput = "Invalid input";
		std::string treeOutput;
		std::string userInput;
		std::string treeElementInput;
		int choice = 0;
		bool exitProgram = false;
		int number{};
		int numbeToRemover{};

		do
		{
			PrintLine(50);
			std::cout << std::setw(10) << "Menu\n" << std::endl;

			for (size_t i = 0; i < menuItems.size(); i++)
			{
				std::cout << i + 1 << ' ' << menuItems.at(i) << std::endl;
			}

			PrintLine(50);
			std::cout << "Choose operation (1 - 5) or 'E' to exit: ";

			std::cin >> userInput;

			if (!isValidInput(userInput))
			{
				std::cout << invalidInput << std::endl;
			}

			try
			{
				choice = stoi(userInput);

				switch (choice)
				{

				case 1:
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
						std::cout << treeElementInput << " is" << invalidInput << std::endl;
					}

					break;
				case 2:
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
						std::cout << treeElementInput << " is" << invalidInput << std::endl;
					}

					break;
				case 3:
					std::cout << "Preorder: " << std::endl;
					treeOutput = tree.preOrder();
					std::cout << treeOutput << std::endl;

					break;
				case 4:
					std::cout << "Inorder: " << std::endl;
					treeOutput = tree.inOrder();
					std::cout << treeOutput << std::endl;

					break;
				case 5:
					std::cout << "Postorder: " << std::endl;
					treeOutput = tree.postOrder();
					std::cout << treeOutput << std::endl;

					break;
				default:
					std::cout << invalidInput << std::endl;

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
					std::cout << invalidInput << std::endl;
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
	//TestsAvlTree testsAvlTree = TestsAvlTree();

	//testsStack.runTests();
	//testsAvlTree.runTests();

	//App app = App();
	//app.runApp();

	AvlTree<int> tree = AvlTree<int>();
	tree.insert(38);
	tree.insert(31);
	tree.insert(68);
	tree.insert(7);
	tree.insert(33);
	tree.insert(41);
	tree.insert(6);
	tree.insert(9);	

	tree.drawTree();

	tree.remove(68);

	tree.drawTree();

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
