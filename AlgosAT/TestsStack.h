#pragma once
#include <iomanip> 
#include <utility>
#include <string>
#include "Stack.h"

class TestsStack
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
};

