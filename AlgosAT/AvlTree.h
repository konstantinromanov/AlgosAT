#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
	};

	Node* m_root = nullptr;
	std::vector<Node*> m_pathNodes;

	void printPreorder(Node* node, std::string& output)
	{
		if (node != nullptr)
		{
			std::stringstream ss("");
			ss << node->data;
			output.append(ss.str() + " ");
			printPreorder(node->left, output);
			printPreorder(node->right, output);
		}
	}

	void printPostorder(Node* node, std::string& output)
	{
		if (node != nullptr)
		{
			printPostorder(node->left, output);
			printPostorder(node->right, output);
			std::stringstream ss("");
			ss << node->data;
			output.append(ss.str() + " ");
		}
	}

	void printInorder(Node* node, std::string& output)
	{
		if (node != nullptr)
		{
			printInorder(node->left, output);
			std::stringstream ss("");
			ss << node->data;
			output.append(ss.str() + " ");
			printInorder(node->right, output);
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

		return getHeightOfNode(node->right) - getHeightOfNode(node->left);
	}

	void processChild(Node*& node, Node*& currentNode, Node*& child)
	{
		child = node;
		m_pathNodes.push_back(node);
		updateHeights();
	}

	enum class Direction
	{
		Left,
		Right
	};

	void updateHeights()
	{
		int pathLenght = m_pathNodes.size();
		int prevNodeBalance = 0;
		int nodeBalance = 0;

		for (size_t i = pathLenght - 1; i + 1 > 0; i--)
		{
			m_pathNodes[i]->height = maxHeight(getHeightOfNode(m_pathNodes[i]->left), getHeightOfNode(m_pathNodes[i]->right)) + 1;

			nodeBalance = getBalance(m_pathNodes[i]);

			if (nodeBalance < -1)
			{
				processBalancing(i, getRotationType(m_pathNodes[i], Direction::Left));
			}
			else if (nodeBalance > 1)
			{
				processBalancing(i, getRotationType(m_pathNodes[i], Direction::Right));
			}

			prevNodeBalance = nodeBalance;
		}
	}

	enum class RotationType
	{
		LeftLeft,
		LeftRight,
		RightRight,
		RightLeft
	};

	RotationType getRotationType(Node* node, Direction direction)
	{
		RotationType output;

		if (direction == Direction::Left)
		{
			output = getBalance(node->left) <= 0 ? RotationType::LeftLeft : RotationType::LeftRight;
		}
		else
		{
			output = getBalance(node->right) >= 0 ? RotationType::RightRight : RotationType::RightLeft;
		}

		return output;
	}

	void processBalancing(int node, RotationType rotation)
	{
		switch (rotation)
		{
		case RotationType::LeftLeft: // left left case. 
			rotateRight(node);
			break;
		case RotationType::LeftRight: // left right case. 
			rotateLeft(node + 1, true);
			rotateRight(node);
			break;
		case RotationType::RightRight: // right right case. 
			rotateLeft(node);
			break;
		case RotationType::RightLeft: // right left case. 
			rotateRight(node + 1, true);
			rotateLeft(node);
			break;
		default:
			break;
		}
	}

	void rotateLeft(int i, bool isDoubleRotaion = false)
	{
		Node* y = m_pathNodes[i]->right;
		Node* T2 = y->left;
		y->left = m_pathNodes[i];
		m_pathNodes[i]->right = T2;

		if (i == 0)
		{
			m_root = y;
		}
		else if (isDoubleRotaion)
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

	void rotateRight(int i, bool isDoubleRotaion = false)
	{
		Node* y = m_pathNodes[i]->left;
		Node* T3 = y->right;
		y->right = m_pathNodes[i];
		m_pathNodes[i]->left = T3;

		if (i == 0)
		{
			m_root = y;
		}
		else if (isDoubleRotaion)
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

	void processTwoChildrenNode(Node*& currentNode)
	{
		m_pathNodes.push_back(currentNode);
		int removedNodeIndex = m_pathNodes.size() - 1;

		currentNode = currentNode->right; // one step right		

		if (currentNode->left != nullptr)
		{
			while (currentNode->left != nullptr) // searching for the smallest value going left
			{
				m_pathNodes.push_back(currentNode);
				currentNode = currentNode->left;
			}

			m_pathNodes[m_pathNodes.size() - 1]->left = currentNode->right != nullptr ? currentNode->right : nullptr;
		}
		else // no left child, means the least max value found.
		{
			m_pathNodes[removedNodeIndex]->right = currentNode->right;
		}

		m_pathNodes[removedNodeIndex]->data = currentNode->data;
	}

	enum class ChildrenType
	{
		NoChildren,
		LeftChild,
		RightChild,
		TwoChildren
	};

	void processNodeWithNoChildren(Node*& currentNode) {

		if (currentNode == m_root)
		{
			m_root = nullptr;
		}
		else
		{
			if (m_pathNodes[m_pathNodes.size() - 1]->right == currentNode)
			{
				m_pathNodes[m_pathNodes.size() - 1]->right = nullptr;
			}
			else
			{
				m_pathNodes[m_pathNodes.size() - 1]->left = nullptr;
			}
		}
	}

	void processNodeWithLeftChild(Node*& currentNode)
	{
		m_pathNodes[m_pathNodes.size() - 1]->left = currentNode->left;
	}

	void processNodeWithRightChild(Node*& currentNode)
	{
		m_pathNodes[m_pathNodes.size() - 1]->right = currentNode->right;
	}

	void moveToNextNode(Node*& currentNode, Direction direction)
	{
		m_pathNodes.push_back(currentNode);
		currentNode = direction == Direction::Left ? currentNode->left : currentNode->right;
	}

	ChildrenType getNodeType(Node* currentNode)
	{
		ChildrenType output;

		if (currentNode->left == nullptr && currentNode->right == nullptr)
		{
			output = ChildrenType::NoChildren;
		}
		else if (currentNode->left == nullptr)
		{
			output = ChildrenType::RightChild;
		}
		else if (currentNode->right == nullptr)
		{
			output = ChildrenType::LeftChild;
		}
		else
		{
			output = ChildrenType::TwoChildren;
		}

		return output;
	}

public:

	void insert(T data)
	{
		Node* node = new Node();
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

				Node*& child = data < currentNode->data ? currentNode->left : currentNode->right;

				if (child == nullptr)
				{
					processChild(node, currentNode, child);
					isLeaf = true;
				}
				else
				{
					currentNode = child;
				}
			}

			m_pathNodes.clear();
		}
	}

	void remove(T data)
	{
		if (m_root == nullptr)
		{
			return;
		}

		Node* currentNode = m_root;
		bool isLeaf = false;

		while (!isLeaf)
		{
			if (data < currentNode->data && currentNode->left != nullptr)
			{
				moveToNextNode(currentNode, Direction::Left);
			}
			else if (data > currentNode->data && currentNode->right != nullptr)
			{
				moveToNextNode(currentNode, Direction::Right);
			}
			else if (data == currentNode->data)
			{
				switch (getNodeType(currentNode))
				{
				case ChildrenType::NoChildren:
					processNodeWithNoChildren(currentNode);
					break;
				case ChildrenType::LeftChild:
					processNodeWithLeftChild(currentNode);
					break;
				case ChildrenType::RightChild:
					processNodeWithRightChild(currentNode);
					break;
				case ChildrenType::TwoChildren:
					processTwoChildrenNode(currentNode);
					break;
				}

				isLeaf = true;
			}
			else
			{
				isLeaf = true; // data was not found in structure.
			}
		}

		updateHeights();
		m_pathNodes.clear();
	}

	std::string preOrder()
	{
		std::string output;
		printPreorder(m_root, output);

		return output;
	}

	std::string postOrder()
	{
		std::string output;
		printPostorder(m_root, output);

		return output;
	}

	std::string inOrder()
	{
		std::string output;
		printInorder(m_root, output);

		return output;
	}
};

