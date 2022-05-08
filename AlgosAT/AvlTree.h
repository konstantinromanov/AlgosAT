#pragma once

#include <iostream>
#include <vector>

template<typename T>
class AvlTree
{

private:

	struct Node
	{
		T data{};
		Node* left = nullptr;
		Node* right = nullptr;
		int height{ 0 };
		int depth{ 0 };
	};

	Node* m_root = nullptr;
	std::vector<Node*> m_pathNodes;

	void printPreorder(Node* node)
	{
		if (node != nullptr)
		{
			std::cout << node->data << " ";
			printPreorder(node->left);
			printPreorder(node->right);
		}
	}

	void printPostorder(Node* node)
	{
		if (node != nullptr)
		{
			printPostorder(node->left);
			printPostorder(node->right);
			std::cout << node->data << " ";
		}
	}

	void printInorder(Node* node)
	{
		if (node != nullptr)
		{
			printInorder(node->left);
			std::cout << node->data << " ";
			printInorder(node->right);
		}
	}

	int maxHeight(int a, int b)
	{
		return ((a > b) ? a : b);
	}

	int getHeightOfNode(Node* node)
	{
		return (node != nullptr ? node->height : 0);
	}

	int getBalance(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		int leftChildHeight = node->left == nullptr ? 0 : node->left->height;
		int rightChildHeight = node->right == nullptr ? 0 : node->right->height;

		return rightChildHeight - leftChildHeight;
	}

	bool processChild(Node*& node, Node*& currentNode, Node*& child)
	{
		if (child == nullptr)
		{
			node->depth = currentNode->depth + 1;
			child = node;
			m_pathNodes.push_back(node);
			updateHeights();

			return true;
		}

		currentNode = child;

		return false;
	}	
		
	void updateHeights()
	{
		int pathLenght = m_pathNodes.size();
		int prevNodeBalance = 0;
		int nodeBalance = 0;

		for (size_t i = pathLenght - 1; i + 1 > 0; i--)
		{
			m_pathNodes[i]->height = maxHeight(m_pathNodes[i]->height, pathLenght - i);

			nodeBalance = getBalance(m_pathNodes[i]);

			if (nodeBalance < -1 || nodeBalance > 1)
			{
				processBalancing(i, (nodeBalance + prevNodeBalance));
			}

			prevNodeBalance = nodeBalance;
		}
	}
		
	void processBalancing(int node, int rotation)
	{
		switch (rotation)
		{
		case -3: // left left case. 
			rotateRight(node);
			break;
		case -1: // left right case. 
			rotateLeft(node + 1, true);
			rotateRight(node);
			break;
		case 3: // right right case. 
			rotateLeft(node);
			break;
		case 1: // right left case. 
			rotateRight(node + 1, true);
			rotateLeft(node);
			break;
		default:
			break;
		}
	}

	void rotateLeft(int i, bool isLeftRight = false)
	{
		Node* y = m_pathNodes[i]->right;
		Node* T2 = y->left;
		y->left = m_pathNodes[i];
		m_pathNodes[i]->right = T2;

		if (i == 0)
		{
			m_root = y;
		}
		else if (isLeftRight)
		{
			m_pathNodes[i - 1]->left = y;
		}
		else
		{
			m_pathNodes[i - 1]->right = y;
		}

		m_pathNodes[i]->height = maxHeight(getHeightOfNode(m_pathNodes[i]->left), getHeightOfNode(m_pathNodes[i]->right)) + 1;
		y->height = maxHeight(getHeightOfNode(y->left), getHeightOfNode(y->right)) + 1;
	}
		
	void rotateRight(int i, bool isRightLeft = false)
	{
		Node* y = m_pathNodes[i]->left;
		Node* T3 = y->right;
		y->right = m_pathNodes[i];
		m_pathNodes[i]->left = T3;

		if (i == 0)
		{
			m_root = y;
		}
		else if (isRightLeft)
		{
			m_pathNodes[i - 1]->right = y;
		}
		else
		{
			m_pathNodes[i - 1]->left = y;
		}

		m_pathNodes[i]->height = maxHeight(getHeightOfNode(m_pathNodes[i]->left), getHeightOfNode(m_pathNodes[i]->right)) + 1;
		y->height = maxHeight(getHeightOfNode(y->left), getHeightOfNode(y->right)) + 1;
	}

public:

	void insert(T data)
	{
		Node* node = new Node();
		node->depth = 1;
		node->height = 1;
		node->data = data;

		if (m_root == nullptr)
		{
			node->left = nullptr;
			node->right = nullptr;
			m_root = node;
		}
		else
		{
			Node* currentNode = m_root;
			bool isLeaf = false;

			while (!isLeaf)
			{
				m_pathNodes.push_back(currentNode);

				if (data == currentNode->data)
				{
					break; // duplicates not allowed.
				}

				isLeaf = processChild(node, currentNode, (data < currentNode->data ? currentNode->left : currentNode->right));
			}

			m_pathNodes.clear();
		}
	}

	void preOrder()
	{
		printPreorder(m_root);
	}

	void postOrder()
	{
		printPostorder(m_root);
	}

	void inOrder()
	{
		printInorder(m_root);
	}
};

