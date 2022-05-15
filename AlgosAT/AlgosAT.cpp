// AlgosAT1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "TestsAvlTree.h"
#include "AvlTree.h"
#include "TestsStack.h"
#include "MaxHeap.h"
#include "TestsMaxHeap.h"

int main()
{
	//MaxHeap<int> heap = MaxHeap<int>(10);

	//heap.insert(73);
	//heap.insert(6);
	//heap.insert(57);
	//heap.insert(88);
	//heap.insert(60);
	//heap.insert(42);
	//heap.insert(83);
	//heap.insert(72);
	//heap.insert(48);
	//heap.insert(85);

	/*heap.insert(9);
	heap.insert(5);
	heap.insert(6);
	heap.insert(3);
	heap.insert(2);
	heap.insert(15);*/

	/*int arr[] = { 73, 6, 57, 88, 60, 42, 83, 72, 48, 85, 5 };
	int size = sizeof(arr) / sizeof(arr[0]);
	MaxHeap<int> heap = MaxHeap<int>(arr, size, 11);
	std::string heapArr = heap.toString();

	heap.remove(73);
	std::string heapArr2 = heap.toString();*/

	TestsMaxHeap testsMaxHeap = TestsMaxHeap();
	testsMaxHeap.runTests();

	//TestsStack testsStack = TestsStack();
	//TestsAvlTree testsAvlTree = TestsAvlTree();

	//testsStack.runTests();
	//testsAvlTree.runTests();
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
