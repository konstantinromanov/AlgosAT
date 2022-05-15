#pragma once
#include <iomanip>
#include <iostream>
#include "MaxHeap.h"

class TestsMaxHeap
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
		insert_insertElementsIntoHeap1_toString();
		insert_insertElementsIntoHeap2_toString();
		remove_initializeHeapWithConstructorAndRemoveElement1_toString();
		remove_initializeHeapWithConstructorAndRemoveElement2_toString();
		initializeHeapWithConstructorAndRemoveElement_toString();
	}

	void insert_insertElementsIntoHeap1_toString()
	{
		MaxHeap<int> heap = MaxHeap<int>(10);

		heap.insert(73);
		heap.insert(6);
		heap.insert(57);
		heap.insert(88);
		heap.insert(60);
		heap.insert(42);
		heap.insert(83);
		heap.insert(72);
		heap.insert(48);
		heap.insert(85);

		std::string heapArr = heap.toString();

		bool heapIsCorrect = heapArr == "88 85 83 72 73 42 57 6 48 60";

		printTestResult(__func__, heapIsCorrect);
	}

	void insert_insertElementsIntoHeap2_toString()
	{
		MaxHeap<int> heap = MaxHeap<int>(10);

		heap.insert(9);
		heap.insert(5);
		heap.insert(6);
		heap.insert(3);
		heap.insert(2);
		heap.insert(15);

		std::string heapArr = heap.toString();

		bool heapIsCorrect = heapArr == "15 5 9 3 2 6";

		printTestResult(__func__, heapIsCorrect);
	}

	void remove_initializeHeapWithConstructorAndRemoveElement1_toString()
	{
		int arr[] = { 73, 6, 57, 88, 60, 42, 83, 72, 48, 85 };
		int size = sizeof(arr) / sizeof(arr[0]);
		MaxHeap<int> heap = MaxHeap<int>(arr, size, 50);
		heap.remove(73);

		std::string heapArr = heap.toString();

		bool heapIsCorrect = heapArr == "88 85 83 72 60 42 57 6 48";

		printTestResult(__func__, heapIsCorrect);
	}

	void remove_initializeHeapWithConstructorAndRemoveElement2_toString()
	{
		int arr[] = { 73, 6, 57, 88, 60, 42, 83, 72, 48, 85, 5 };
		int size = sizeof(arr) / sizeof(arr[0]);
		MaxHeap<int> heap = MaxHeap<int>(arr, size, 50);
		heap.remove(73);

		std::string heapArr = heap.toString();

		bool heapIsCorrect = heapArr == "88 85 83 72 60 42 57 6 48 5";

		printTestResult(__func__, heapIsCorrect);
	}

	void initializeHeapWithConstructorAndRemoveElement_toString()
	{
		int arr[] = { 1, 5, 7, 4, 2, 6, 3 };
		int size = sizeof(arr) / sizeof(arr[0]);
		MaxHeap<int> heap = MaxHeap<int>(arr, size, 50);		

		std::string heapArr = heap.toString();

		bool heapIsCorrect = heapArr == "7 4 6 1 2 5 3";

		printTestResult(__func__, heapIsCorrect);
	}
};

