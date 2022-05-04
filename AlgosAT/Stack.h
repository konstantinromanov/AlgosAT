#pragma once

#include <iostream>

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
	size_t m_size = 0;

public:

	Stack()
	{

	}

	Stack(T data)
	{
		m_top = new Node();
		m_top->data = data;
		m_size++;
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
		m_size++;
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
			m_size--;
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

	T peek()
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

	size_t size() 
	{
		return m_size;
	}
};
