// AlgosAT1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

template<typename T>
class Stack
{

private:


	struct Node
	{
		T data;
		Node* next = nullptr;
	};

	Node* m_top = nullptr;

public:

	Stack()
	{

	}

	Stack(T data)
	{
		m_top = new Node();
		m_top->data = data;
	}

	void push(T data)
	{
		Node* temp = new Node();

		if (!temp)
		{
			std::cout << "Stack Overflow" << std::endl;
		}

		temp->data = data;
		temp->next = m_top;

		m_top = temp;
	}

	void pop()
	{
		Node* temp;

		if (m_top == nullptr)
		{
			std::cout << "Stack underflow" << std::endl;
			throw std::out_of_range("Stack underflow");
		}
		else
		{
			temp = m_top;
			m_top = m_top->next;
			free(temp);
		}
	}

	void display()
	{
		Node* currentNode = m_top;
		if (currentNode == nullptr)
		{
			std::cout << "Stack is empty" << std::endl;
		}

		while (currentNode != nullptr)
		{
			std::cout << currentNode->data << std::endl;
			currentNode = currentNode->next;
		}
	}

	int peek()
	{
		if (!isEmpty())
		{
			return m_top->data;
		}
		else
		{
			std::cout << "Stack underflow" << std::endl;
			throw std::out_of_range("Stack underflow");
		}
	}

	bool isEmpty()
	{
		return m_top == nullptr;
	}
};

int main()
{
	Stack<int> stack = Stack<int>(5);
	bool stackIsEmpty = stack.isEmpty();
	stack.display();
	stack.push(10);
	stackIsEmpty = stack.isEmpty();
	stack.display();
	stack.push(20);
	stack.push(30);
	stack.display();

	stack.pop();
	stack.pop();
	int peek1 = stack.peek();

	stack.pop();
	stack.pop();

	//stack.pop();
	//int peek2 = stack.peek();
	stack.display();

	Stack<std::string> stack2 = Stack<std::string>("string 1");
	bool stackIsEmpty2 = stack2.isEmpty();
	stack2.display();
	stack2.push("string 2");
	stackIsEmpty2 = stack2.isEmpty();
	stack2.display();
	stack2.push("string 3");
	stack2.push("string 4");
	stack2.display();

	stack2.pop();
	stack2.pop();
	//int peek2 = stack2.peek();

	stack2.pop();
	stack2.pop();

	//stack.pop();
	//int peek2 = stack.peek();
	stack2.display();
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
