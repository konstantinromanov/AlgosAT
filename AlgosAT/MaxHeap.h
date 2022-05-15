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

	bool m_isLastLeft = false;
	
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

	void swapData(int position)
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

public:

	int size()
	{
		return m_position;
	}

	MaxHeap(int capacity) {
		m_capacity = capacity;
		m_heap = new T[m_capacity];			
	}

	void insert(T data)
	{	
		m_heap[m_position] = data;
		
		if (m_position > 0 && m_heap[getParentPosition(m_position)] < data)
		{
			swapData(m_position);
		}
		
		m_position++;
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
		result.pop_back();
		return result;
	};
};

