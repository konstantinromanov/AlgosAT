#pragma once

#include <string>
#include <sstream>

template<typename T>
class MaxHeap
{

private:

	int m_capacity{};
	T* m_heap;
	int m_position{ 0 };

	int getLeftPosition(int position)
	{
		return 2 * position + 1;
	}

	int getRightPosition(int position)
	{
		return 2 * position + 2;
	}

	int getParentPosition(int position)
	{
		return (position - 1) / 2;
	}

	void moveUp(int position)
	{
		int parentPosition = getParentPosition(position);

		while (m_heap[parentPosition] < m_heap[position])
		{
			T temp = m_heap[parentPosition];
			m_heap[parentPosition] = m_heap[position];
			m_heap[position] = temp;

			position = parentPosition;
			parentPosition = getParentPosition(parentPosition);
		}
	}

	void moveDown(int position)
	{
		int leftChildPosition = getLeftPosition(position);
		int rightChildPosition = getRightPosition(position);
		int childPosition;

		while (true)
		{
			if (leftChildPosition < m_position && m_heap[leftChildPosition] > m_heap[position])
			{
				childPosition = leftChildPosition;
			}
			else if (rightChildPosition < m_position && m_heap[rightChildPosition] > m_heap[position])
			{
				childPosition = rightChildPosition;
			}
			else
			{
				break;
			}

			T temp = m_heap[childPosition];
			m_heap[childPosition] = m_heap[position];
			m_heap[position] = temp;

			position = childPosition;

			leftChildPosition = getLeftPosition(position);
			rightChildPosition = getRightPosition(position);
		}
	}

	void buildHeap(T* arr, int arrSize)
	{
		for (size_t i = 0; i < arrSize; i++)
		{
			insert(arr[i]);
		}
	}

public:

	MaxHeap(T arr[], int arrSize, int capacity)
	{
		m_capacity = capacity;
		m_heap = new T[m_capacity];
		buildHeap(arr, arrSize);
	}

	MaxHeap(int capacity) {
		m_capacity = capacity;
		m_heap = new T[m_capacity];
	}

	void insert(T data)
	{
		if (m_position == m_capacity)
		{
			throw std::out_of_range("Heap is full");
		}

		m_heap[m_position] = data;

		if (m_position > 0 && m_heap[getParentPosition(m_position)] < data)
		{
			moveUp(m_position);
		}

		m_position++;
	}

	void remove(T data)
	{
		T lastData = m_heap[m_position - 1];
		int deletedPosition{};

		for (size_t i = 0; i < m_position; i++)
		{
			if (m_heap[i] == data)
			{
				m_heap[i] = lastData;
				deletedPosition = i;
				m_position--;

				break;
			}
		}

		int parentPosition = getParentPosition(deletedPosition);

		if (m_heap[parentPosition] < m_heap[deletedPosition])
		{
			moveUp(deletedPosition);
		}

		if (deletedPosition < m_position / 2) // if not leaf nodes, then proceed with check.
		{
			moveDown(deletedPosition);
		}
	}

	std::string toString()
	{
		std::stringstream ss("");
		std::string result;

		for (size_t i = 0; i < m_position; i++)
		{
			ss << m_heap[i] << ' ';
		}

		result = ss.str();

		if (result != "")
		{
			result.pop_back();
		}

		return result;
	};

	int size()
	{
		return m_position;
	}
};

