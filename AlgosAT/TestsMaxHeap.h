#pragma once
#include <iomanip>
#include <iostream>
#include "MaxHeap.h"


template<typename T>
class ValidationHelper
{

public:

	bool validateMaxHeap(MaxHeap<T> heap)
	{
		bool heapIsCorrect = true;

		int leftChildPosition{ 1 };
		int rightChildPosition{ 2 };
		int counter = 0;

		while (leftChildPosition < heap.size() && rightChildPosition < heap.size())
		{

			T test1 = heap[counter];
			T test2 = heap[leftChildPosition];
			T test3 = heap[rightChildPosition];
			if (heap[counter] < heap[leftChildPosition] || heap[counter] < heap[rightChildPosition])
			{
				heapIsCorrect = false;
				break;
			}

			counter++;
			leftChildPosition = counter * 2 + 1;
			rightChildPosition = counter * 2 + 2;
		}

		return heapIsCorrect;
	}

	T findMax(T* arr, int size)
	{
		int max = arr[0];

		for (size_t i = 0; i < size; i++)
		{
			if (max < arr[i])
			{
				max = arr[i];
			}
		}

		return max;
	}
};


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
		initializeHeapWithConstructor_fillRandomArray_validateArr();
		getMax_fillRandomArray_firstElementMustBeMax();
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

	void initializeHeapWithConstructor_fillRandomArray_validateArr()
	{
		const int arrSize = 1000;
		int arr[arrSize];
		srand(time(0));

		for (size_t i = 0; i < arrSize; i++)
		{
			arr[i] = rand();
		}		

		MaxHeap<int> heap = MaxHeap<int>(arr, arrSize, arrSize);		
		ValidationHelper<int> validation = ValidationHelper<int>();

		bool heapIsCorrect = validation.validateMaxHeap(heap);		

		printTestResult(__func__, heapIsCorrect);
	}

	void getMax_fillRandomArray_firstElementMustBeMax()
	{
		const int arrSize = 1000;
		int arr[arrSize];
		srand(time(0));

		for (size_t i = 0; i < arrSize; i++)
		{
			arr[i] = rand();
		}

		ValidationHelper<int> validation = ValidationHelper<int>();
		MaxHeap<int> heap = MaxHeap<int>(arr, arrSize, arrSize);

		int maxVal = heap.getMax();

		bool heapIsCorrect = validation.findMax(arr, arrSize) == maxVal;

		printTestResult(__func__, heapIsCorrect);
	}
};

