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
		remove_removeLeafNode_preorderTree();
		remove_removeNodeWithRightChild_preorderTree();
		remove_removeNodeWithTwoChildrenSuccessorRight_preorderTree();
		remove_removeRootWithTwoChildrenSuccessorLeftLeaf_preorderTree();
		remove_removeRootWithTwoChildrenSuccessorHasRightChild_preorderTree();
		remove_removeRootWithLeftChild_preorderTree();
		remove_removeRightLeafNodeParentFormTheLeft_preorderTree();
		remove_removeLeftLeafNodeParentFromTheRight_preorderTree();
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

		bool treeIsCorrect = treePreorder == "30 20 10 25 40 50";

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

		bool treeIsCorrect = treePreorder == "9 1 0 -1 5 2 6 10 11";

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

		bool treeIsCorrect = treePreorder == "20 10 40 25";

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
		bool treeIsCorrect = treePreorder == "20 10 30 40";

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
		bool treeIsCorrect = treePreorder == "25 10 30 40";

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
		bool treeIsCorrect = treePreorder == "1 0 -1 9 5 2 6 11";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeLeafNode_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();

		int arr[] = { 50, 25, 75, 10, 33, 56, 89, 4, 11, 30, 40, 52, 61, 82, 95 };
		int arrLenght = sizeof(arr) / sizeof(arr[0]);

		for (size_t i = 0; i < arrLenght; i++)
		{
			tree.insert(arr[i]);
		}

		tree.remove(4);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "50 25 10 11 33 30 40 75 56 52 61 89 82 95";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeNodeWithRightChild_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();

		int arr[] = { 50,25,75,10,33,56,89,11,30,40,52,61,82,95 };
		int arrLenght = sizeof(arr) / sizeof(arr[0]);

		for (size_t i = 0; i < arrLenght; i++)
		{
			tree.insert(arr[i]);
		}

		tree.remove(10);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "50 25 11 33 30 40 75 56 52 61 89 82 95";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeNodeWithTwoChildrenSuccessorRight_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();

		int arr[] = { 50, 25, 75, 11, 33, 56, 89, 30, 40, 52, 61, 82, 95 };
		int arrLenght = sizeof(arr) / sizeof(arr[0]);

		for (size_t i = 0; i < arrLenght; i++)
		{
			tree.insert(arr[i]);
		}

		tree.remove(56);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "50 25 11 33 30 40 75 61 52 89 82 95";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeRootWithTwoChildrenSuccessorLeftLeaf_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();

		int arr[] = { 50, 25, 75, 11, 33, 61, 89, 30, 40, 52, 82, 95 };
		int arrLenght = sizeof(arr) / sizeof(arr[0]);

		for (size_t i = 0; i < arrLenght; i++)
		{
			tree.insert(arr[i]);
		}

		tree.remove(50);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "52 25 11 33 30 40 75 61 89 82 95";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeRootWithTwoChildrenSuccessorHasRightChild_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();

		int arr[] = { 50, 25, 75, 11, 33, 61, 89, 10, 12, 30, 40, 52, 62, 82, 95, 55 };
		int arrLenght = sizeof(arr) / sizeof(arr[0]);

		for (size_t i = 0; i < arrLenght; i++)
		{
			tree.insert(arr[i]);
		}

		tree.remove(50);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "52 25 11 10 12 33 30 40 75 61 55 62 89 82 95";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeRootWithLeftChild_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();
		tree.insert(2);
		tree.insert(1);
		tree.remove(2);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "1";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeRightLeafNodeParentFormTheLeft_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();

		int arr[] = { 34, 24, 45, 16, 32, 39, 47, 18, 30, 33, 38 };
		int arrLenght = sizeof(arr) / sizeof(arr[0]);

		for (size_t i = 0; i < arrLenght; i++)
		{
			tree.insert(arr[i]);
		}

		tree.remove(47);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "34 24 16 18 32 30 33 39 38 45";

		printTestResult(__func__, treeIsCorrect);
	}

	void remove_removeLeftLeafNodeParentFromTheRight_preorderTree()
	{
		AvlTree<int> tree = AvlTree<int>();

		int arr[] = { 34, 24, 45, 16, 32, 39, 47, 33, 38, 40 };
		int arrLenght = sizeof(arr) / sizeof(arr[0]);

		for (size_t i = 0; i < arrLenght; i++)
		{
			tree.insert(arr[i]);
		}

		tree.remove(16);

		std::string treePreorder = tree.preOrder();
		bool treeIsCorrect = treePreorder == "34 32 24 33 45 39 38 40 47";

		printTestResult(__func__, treeIsCorrect);
	}
};

