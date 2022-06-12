#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

template<typename T>
class AvlTree
{

private:

	struct Node
	{
		T data{};
		Node* left = nullptr;
		Node* right = nullptr;
		int height{ 1 };
	};

	Node* m_root = nullptr;
	std::vector<Node*> m_pathNodes;

	void printPreorder(Node* node, std::string& output)
	{
		if (node != nullptr)
		{
			output.append(toString(node->data) + " ");
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
			output.append(toString(node->data) + " ");
		}
	}

	void printInorder(Node* node, std::string& output)
	{
		if (node != nullptr)
		{
			printInorder(node->left, output);
			output.append(toString(node->data) + " ");
			printInorder(node->right, output);
		}
	}

	std::string toString(T val)
	{
		std::stringstream ss("");
		ss << val;
		return ss.str();
	};

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

	void insertNodeAsChild(Node*& node, Node*& child)
	{
		child = node;
		m_pathNodes.push_back(node);
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
		RotationType type;

		if (direction == Direction::Left)
		{
			type = getBalance(node->left) <= 0 ? RotationType::LeftLeft : RotationType::LeftRight;
		}
		else
		{
			type = getBalance(node->right) >= 0 ? RotationType::RightRight : RotationType::RightLeft;
		}

		return type;
	}

	void processBalancing(int indexOfCurrentNode, RotationType rotation)
	{
		switch (rotation)
		{
		case RotationType::LeftLeft: // left left case. 
			rotateRight(indexOfCurrentNode);
			break;
		case RotationType::LeftRight: // left right case. 
			rotateLeft(indexOfCurrentNode + 1);
			rotateRight(indexOfCurrentNode);
			break;
		case RotationType::RightRight: // right right case. 
			rotateLeft(indexOfCurrentNode);
			break;
		case RotationType::RightLeft: // right left case. 
			rotateRight(indexOfCurrentNode + 1);
			rotateLeft(indexOfCurrentNode);
			break;
		default:
			break;
		}
	}

	void rotateLeft(int indexOfCurrentNode)
	{
		Node* nodeToLift = m_pathNodes[indexOfCurrentNode]->right;
		Node* nodeToSwitch = nodeToLift->left;
		nodeToLift->left = m_pathNodes[indexOfCurrentNode];
		m_pathNodes[indexOfCurrentNode]->right = nodeToSwitch;

		connectToParent(indexOfCurrentNode, nodeToLift);
		updateHeightsAfterRotation(m_pathNodes[indexOfCurrentNode], nodeToLift);
	}

	void rotateRight(int indexOfCurrentNode)
	{
		Node* nodeToLift = m_pathNodes[indexOfCurrentNode]->left;
		Node* nodeToSwitch = nodeToLift->right;
		nodeToLift->right = m_pathNodes[indexOfCurrentNode];
		m_pathNodes[indexOfCurrentNode]->left = nodeToSwitch;

		connectToParent(indexOfCurrentNode, nodeToLift);
		updateHeightsAfterRotation(m_pathNodes[indexOfCurrentNode], nodeToLift);
	}

	void connectToParent(int indexOfCurrentNode, Node* nodeToLift)
	{
		if (m_pathNodes[indexOfCurrentNode] == m_root)
		{
			m_root = nodeToLift;
		}
		else
		{
			Node* parentNode = m_pathNodes[indexOfCurrentNode - 1];

			if (parentNode->right == m_pathNodes[indexOfCurrentNode])
			{
				parentNode->right = nodeToLift;
			}
			else
			{
				parentNode->left = nodeToLift;
			}
		}
	}

	void updateHeightsAfterRotation(Node* prevParent, Node* newParent)
	{
		prevParent->height = maxHeight(getHeightOfNode(prevParent->left), getHeightOfNode(prevParent->right)) + 1;
		newParent->height = maxHeight(getHeightOfNode(newParent->left), getHeightOfNode(newParent->right)) + 1;
	}

	void deleteTwoChildrenNode(Node* currentNode)
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
		delete currentNode;
	}
		
	void deleteNodeWithOneOrNoChild(Node* currentNode, Node* nodeToLift = nullptr)
	{
		m_pathNodes.push_back(currentNode);
		connectToParent(m_pathNodes.size() - 1, nodeToLift);
		m_pathNodes.pop_back();

		delete currentNode;
	}

	void moveToNextNode(Node*& currentNode, Direction direction)
	{
		m_pathNodes.push_back(currentNode);
		currentNode = direction == Direction::Left ? currentNode->left : currentNode->right;
	}

	enum class ChildrenType
	{
		NoChildren,
		LeftChild,
		RightChild,
		TwoChildren
	};

	ChildrenType getNodeType(Node* currentNode)
	{
		ChildrenType type;

		if (currentNode->left == nullptr && currentNode->right == nullptr)
		{
			type = ChildrenType::NoChildren;
		}
		else if (currentNode->left == nullptr)
		{
			type = ChildrenType::RightChild;
		}
		else if (currentNode->right == nullptr)
		{
			type = ChildrenType::LeftChild;
		}
		else
		{
			type = ChildrenType::TwoChildren;
		}

		return type;
	}

	int getMaxLengthOfNode(Node* node, int number)
	{
		if (node != nullptr)
		{
			int currCharNumber = toString(node->data).length();

			if (currCharNumber > number)
			{
				number = currCharNumber;
			}

			number = getMaxLengthOfNode(node->left, number);
			number = getMaxLengthOfNode(node->right, number);
		}

		return number;
	}

	std::string buildNodeStr(std::string number, int width)
	{
		std::string resultStr;

		int left = (width - number.length()) / 2;
		int right = width - (left + number.length());

		resultStr = std::string(left, ' ') + number + std::string(right, ' ');

		return resultStr;
	}

public:

	void insert(T data)
	{
		Node* node = new Node();
		node->data = data;

		if (m_root == nullptr)
		{
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
					insertNodeAsChild(node, child);
					updateHeights();
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

	bool remove(T data)
	{
		if (m_root == nullptr)
		{
			return false;
		}

		Node* currentNode = m_root;

		while (true)
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
					deleteNodeWithOneOrNoChild(currentNode);
					break;
				case ChildrenType::LeftChild:
					deleteNodeWithOneOrNoChild(currentNode, currentNode->left);
					break;
				case ChildrenType::RightChild:
					deleteNodeWithOneOrNoChild(currentNode, currentNode->right);
					break;
				case ChildrenType::TwoChildren:
					deleteTwoChildrenNode(currentNode);
					break;
				}

				updateHeights();
				break;
			}
			else
			{
				return false; // data was not found in structure.
			}
		}

		m_pathNodes.clear();

		return true;
	}

	std::string preOrder()
	{
		std::string output;
		printPreorder(m_root, output);

		if (!output.empty())
		{
			output.pop_back();
		}

		return output;
	}

	std::string postOrder()
	{
		std::string output;
		printPostorder(m_root, output);

		if (!output.empty())
		{
			output.pop_back();
		}

		return output;
	}

	std::string inOrder()
	{
		std::string output;
		printInorder(m_root, output);

		if (!output.empty())
		{
			output.pop_back();
		}

		return output;
	}

	void drawTree()
	{
		bool stay = true;

		if (m_root == nullptr)
		{
			return;
		}

		std::vector<Node*> currRow;
		std::vector<Node*> prevRow;
		prevRow.push_back(m_root);
		int currRowLenght = 1;
		int treeWidth = m_root->height;

		int currLevel = 1;
		int lengthOfNodeString = getMaxLengthOfNode(m_root, 1);

		int maxRowElem = pow(2, (m_root->height - 1));
		int maxRowWidth = maxRowElem * lengthOfNodeString + maxRowElem * 2;

		do
		{
			int rowElem = pow(2, (currLevel - 1));
			int elWidth = maxRowWidth / rowElem;

			for (size_t i = 0; i < currRowLenght; i++)
			{
				std::string output = ((prevRow[i] == nullptr) ? " " : toString(prevRow[i]->data));
				std::string currNode = buildNodeStr(output, elWidth);
				std::cout << currNode;
			}

			std::cout << std::endl;

			currLevel++;
			stay = false;
			currRow.clear();

			for (size_t i = 0; i < currRowLenght; i++)
			{
				if (prevRow[i] != NULL && prevRow[i]->left != nullptr || prevRow[i] != NULL && prevRow[i]->right != nullptr)
				{
					stay = true;
				}

				currRow.push_back(prevRow[i] != NULL ? prevRow[i]->left : NULL);
				currRow.push_back(prevRow[i] != NULL ? prevRow[i]->right : NULL);
			}

			if (!stay)
			{
				break;
			}

			for (size_t i = 0; i < currRowLenght; i++)
			{
				std::string currTreeLines;

				if (prevRow[i] == NULL || prevRow[i]->left == nullptr && prevRow[i]->right == nullptr)
				{
					currTreeLines = " ";
				}
				else if (prevRow[i]->left == nullptr)
				{
					currTreeLines = "\\";
				}
				else if (prevRow[i]->right == nullptr)
				{
					currTreeLines = "/";
				}
				else
				{
					currTreeLines = "/\\";
				}

				std::cout << buildNodeStr(currTreeLines, elWidth);
			}

			std::cout << std::endl;

			prevRow = currRow;
			currRowLenght *= 2;

		} while (true);
	}
};

