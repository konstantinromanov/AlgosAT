#pragma once

#include <iomanip> 
#include <utility>
#include <string>
#include "Stack.h"
#include "AvlTree.h"

class TestsAvlTree
{

private:

	void printTestResult(const char* testName, bool assertValue)
	{
		std::cout
			<< std::setw(75) << std::left << std::string(testName) + ":"
			<< std::setw(25) << std::right << (assertValue ? "passed" : "not passed") << std::endl;
		std::cout << std::string(100, '-') << std::endl;
	}

public:

	void runTests()
	{
		insert_insertElementsWithBalancingNeeded1_preorderTree();
		insert_insertElementsWithBalancingNeeded2_preorderTree();
		remove_removeNodeWithTwoChildren_preorderTree();
		remove_removeNodeWithNoChildren_preorderTree();
		remove_removeRootNodeWithTwoChildren_preorderTree();
		remove_removeNodeWithOneChildBalancingNeeded_preorderTree();
	}

	void insert_insertElementsWithBalancingNeeded1_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(10);
		tree.insert(20);
		tree.insert(30);
		tree.insert(40);
		tree.insert(50);
		tree.insert(25);

		std::string treePreorder = tree.preOrder();

		bool treeIsCorrect = treePreorder == "30 20 10 25 40 50 ";

		printTestResult(__func__, treeIsCorrect);
	}

	void insert_insertElementsWithBalancingNeeded2_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(9);
		tree.insert(5);
		tree.insert(10);
		tree.insert(0);
		tree.insert(6);
		tree.insert(11);
		tree.insert(-1);
		tree.insert(1);
		tree.insert(2);

		std::string treePreorder = tree.preOrder();

		bool treeIsCorrect = treePreorder == "9 1 0 -1 5 2 6 10 11 ";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeNodeWithTwoChildren_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(10);
		tree.insert(20);
		tree.insert(30);
		tree.insert(40);
		tree.insert(25);
		tree.remove(30);

		std::string treePreorder = tree.preOrder();

		bool treeIsCorrect = treePreorder == "20 10 40 25 ";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeNodeWithNoChildren_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(10);
		tree.insert(20);
		tree.insert(30);
		tree.insert(40);
		tree.insert(25);
		tree.remove(25);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "20 10 30 40 ";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeRootNodeWithTwoChildren_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(10);
		tree.insert(20);
		tree.insert(30);
		tree.insert(40);
		tree.insert(25);
		tree.remove(20);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "25 10 30 40 ";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeNodeWithOneChildBalancingNeeded_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(9);
		tree.insert(5);
		tree.insert(10);
		tree.insert(0);
		tree.insert(6);
		tree.insert(11);
		tree.insert(-1);
		tree.insert(1);
		tree.insert(2);
		tree.remove(10);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "1 0 -1 9 5 2 6 11 ";

		printTestResult(__func__, treeIsCorrect);
	}
};

