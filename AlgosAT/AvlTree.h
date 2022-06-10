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
			rotateLeft(node + 1);
			rotateRight(node);
			break;
		case RotationType::RightRight: // right right case. 
			rotateLeft(node);
			break;
		case RotationType::RightLeft: // right left case. 
			rotateRight(node + 1);
			rotateLeft(node);
			break;
		default:
			break;
		}
	}

	void connectToParent(Node* parentNode, Node* prevChildNode, Node* newChildNode)
	{
		if (parentNode->right == prevChildNode)
		{
			parentNode->right = newChildNode;
		}
		else
		{
			parentNode->left = newChildNode;
		}
	}

	void rotateLeft(int i)
	{
		Node* nodeToLift = m_pathNodes[i]->right;
		Node* nodeToSwitch = nodeToLift->left;
		nodeToLift->left = m_pathNodes[i];
		m_pathNodes[i]->right = nodeToSwitch;

		if (i == 0)
		{
			m_root = nodeToLift;
		}
		else
		{
			connectToParent(m_pathNodes[i - 1], m_pathNodes[i], nodeToLift);
		}

		updateHeightsAfterRotation(m_pathNodes[i], nodeToLift);
	}

	void rotateRight(int i)
	{
		Node* nodeToLift = m_pathNodes[i]->left;
		Node* nodeToSwitch = nodeToLift->right;
		nodeToLift->right = m_pathNodes[i];
		m_pathNodes[i]->left = nodeToSwitch;

		if (i == 0)
		{
			m_root = nodeToLift;
		}
		else
		{
			connectToParent(m_pathNodes[i - 1], m_pathNodes[i], nodeToLift);
		}

		updateHeightsAfterRotation(m_pathNodes[i], nodeToLift);
	}

	void updateHeightsAfterRotation(Node* prevParent, Node* newParent)
	{
		prevParent->height = maxHeight(getHeightOfNode(prevParent->left), getHeightOfNode(prevParent->right)) + 1;
		newParent->height = maxHeight(getHeightOfNode(newParent->left), getHeightOfNode(newParent->right)) + 1;
	}

	void deleteTwoChildrenNode(Node*& currentNode)
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

	enum class ChildrenType
	{
		NoChildren,
		LeftChild,
		RightChild,
		TwoChildren
	};

	void deleteNodeWithNoChildren(Node*& currentNode) {

		if (currentNode == m_root)
		{
			m_root = nullptr;
		}
		else
		{
			connectToParent(m_pathNodes[m_pathNodes.size() - 1], currentNode, nullptr);
		}

		delete currentNode;
	}

	void deleteNodeWithLeftChild(Node*& currentNode)
	{
		if (currentNode == m_root)
		{
			m_root = currentNode->left == nullptr ? currentNode->right : currentNode->left;
		}
		else
		{
			connectToParent(m_pathNodes[m_pathNodes.size() - 1], currentNode, currentNode->right);
		}

		delete currentNode;
	}

	void deleteNodeWithRightChild(Node*& currentNode)
	{
		if (currentNode == m_root)
		{
			m_root = currentNode->left == nullptr ? currentNode->right : currentNode->left;
		}
		else
		{
			connectToParent(m_pathNodes[m_pathNodes.size() - 1], currentNode, currentNode->right);
		}

		delete currentNode;
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
					deleteNodeWithNoChildren(currentNode);
					break;
				case ChildrenType::LeftChild:
					deleteNodeWithLeftChild(currentNode);
					break;
				case ChildrenType::RightChild:
					deleteNodeWithRightChild(currentNode);
					break;
				case ChildrenType::TwoChildren:
					deleteTwoChildrenNode(currentNode);
					break;
				}

				updateHeights();
				isLeaf = true;
			}
			else
			{
				isLeaf = true; // data was not found in structure.
				return false;
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

