#pragma once
#include <iostream>
#include <vector>
#include <sstream>

#include "TestsAvlTree.h"

class App
{

private:

	void printLine(int lenght)
	{
		std::cout << std::string(lenght, '-') << std::endl;
	}

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

	std::vector<int> readInput()
	{
		std::string input;
		std::getline(std::cin, input);

		std::stringstream ss(input);

		std::vector<int>numbers;
		int number;

		while (ss >> number) {

			numbers.push_back(number);

			if (ss.peek() == ' ' || ss.peek() == ',')
			{
				ss.ignore();
			}
		}

		return numbers;
	}

public:

	App()
	{

	}

	void runApp()
	{
		AvlTree<int> tree = AvlTree<int>();

		std::vector<std::string> menuItems = {
		"Insert element",
		"Remove element",
		"Preorder",
		"Inorder",
		"Postorder",
		"Draw tree"
		};

		std::string invalidInput = "Invalid input";
		std::string treeOutput;
		std::string userInput;
		std::string treeElementInput;
		int choice = 0;
		bool exitProgram = false;
		int number{};
		int numbeToRemover{};
		std::vector<int> numbers{};

		std::cout << "This program creates AVL Tree and can perform simple operations on it" << std::endl << std::endl;

		do
		{
			printLine(50);
			std::cout << std::setw(10) << "Menu\n" << std::endl;

			for (size_t i = 0; i < menuItems.size(); i++)
			{
				std::cout << i + 1 << ' ' << menuItems.at(i) << std::endl;
			}

			printLine(50);
			std::cout << "Choose operation (1 - 6) or 'E' to exit: ";

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
					std::cout << "Enter a number or numbers separated by space or comma to insert: ";
					std::cin.ignore();
					numbers = readInput();

					for (size_t i = 0; i < numbers.size(); i++)
					{
						tree.insert(numbers[i]);
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
				case 6:
					std::cout << "AVL tree: " << std::endl << std::endl;
					tree.drawTree();

					break;
				default:
					std::cout << invalidInput << std::endl;

					break;
				}

				std::cout << std::endl << std::endl << std::endl;
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
