#pragma once

#include <iomanip> 
#include <utility>
#include <string>
#include "Stack.h"
#include "AvlTree.h"

class Tests
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
		isEmpty_noDataInstack_true();
		isEmpty_instantiateStackWithData_false();
		push_pushDataToStack_notEmpty();
		pop_popDataFromStackWithOneNode_empty();
		peek_peekStack_topNodeData();
		pop_popEmptyStack_exception();
		size_pushDataToEmptyStack_one();
		size_InstantiateStackWithData_one();
		size_popDataFromStackWithOneNode_zero();

		insert_insertElementsWithBalancingNeeded1_preorderTree();
		insert_insertElementsWithBalancingNeeded2_preorderTree();
		remove_removeNodeWithTwoChildren_preorderTree();
		remove_removeNodeWithNoChildren_preorderTree();
		remove_removeRootNodeWithTwoChildren_preorderTree();
		remove_removeNodeWithOneChildBalancingNeeded_preorderTree();
	}

	void isEmpty_noDataInstack_true()
	{
		Stack<int> stack = Stack<int>();

		bool stackIsEmpty = stack.isEmpty();

		printTestResult(__func__, stackIsEmpty);
	}

	void isEmpty_instantiateStackWithData_false()
	{
		Stack<int> stack = Stack<int>(5);

		bool stackIsNotEmpty = !stack.isEmpty();

		printTestResult(__func__, stackIsNotEmpty);
	}

	void push_pushDataToStack_notEmpty()
	{
		Stack<int> stack = Stack<int>();
		stack.push(10);

		bool stackIsNotEmpty = !stack.isEmpty();

		printTestResult(__func__, stackIsNotEmpty);
	}

	void pop_popDataFromStackWithOneNode_empty()
	{
		Stack<std::string> stack = Stack<std::string>("string");
		stack.pop();

		bool stackIsEmpty = stack.isEmpty();

		printTestResult(__func__, stackIsEmpty);
	}

	void pop_popEmptyStack_exception()
	{
		Stack<std::string> stack = Stack<std::string>();
		bool exceptionThrown = false;

		try
		{
			stack.pop();
		}
		catch (const std::exception&)
		{
			exceptionThrown = true;
		}

		printTestResult(__func__, exceptionThrown);
	}

	void peek_peekStack_topNodeData()
	{
		Stack<std::string> stack = Stack<std::string>("string1");
		stack.push("string2");
		std::string node = stack.peek();

		bool expectedData = node == "string2";

		printTestResult(__func__, expectedData);
	}

	void peek_peekEmptyStack_exception()
	{
		Stack<std::string> stack = Stack<std::string>();
		bool exceptionThrown = false;

		try
		{
			std::string node = stack.peek();
		}
		catch (const std::exception&)
		{
			exceptionThrown = true;
		}

		printTestResult(__func__, exceptionThrown);
	}

	void size_pushDataToEmptyStack_one()
	{
		Stack<int> stack = Stack<int>();
		stack.push(10);

		bool sizeIsOne = stack.size() == 1;

		printTestResult(__func__, sizeIsOne);
	}

	void size_InstantiateStackWithData_one()
	{
		Stack<int> stack = Stack<int>(2);

		bool sizeIsOne = stack.size() == 1;

		printTestResult(__func__, sizeIsOne);
	}

	void size_popDataFromStackWithOneNode_zero()
	{
		Stack<std::string> stack = Stack<std::string>("string");
		stack.pop();

		bool sizeIsZero = stack.size() == 0;

		printTestResult(__func__, sizeIsZero);
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

