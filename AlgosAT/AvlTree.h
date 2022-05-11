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
		int depth{ 0 };
	};

	Node* m_root = nullptr;
	std::vector<Node*> m_pathNodes;

	void printPreorder(Node* node, std::string& output)
	{
		if (node != nullptr)
		{
			//std::cout << node->data << " ";
			std::stringstream ss("");
			ss << node->data;
			output.append(ss.str() + " ");
			printPreorder(node->left, output);
			printPreorder(node->right, output);
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

	void printInorder(Node* node, std::string& output)
	{
		if (node != nullptr)
		{
			printInorder(node->left, output);
			std::stringstream ss("");
			ss << node->data;
			output.append(ss.str() + " ");
			//std::cout << node->data << " ";
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
			//rotate(node, false, false);
			break;
		case -1: // left right case. 
			rotateLeft(node + 1, true);
			rotateRight(node);
			//rotate(node, true, true);
			break;
		case 3: // right right case. 
			rotateLeft(node);
			//rotate(node, true, false);
			break;
		case 1: // right left case. 
			rotateRight(node + 1, true);
			rotateLeft(node);
			//rotate(node, false, true);
			break;
		default:
			break;
		}
	}

	/*void rotate(int i, bool isLeftRotation, bool isDoubleRotaion)
	{
		int len = isDoubleRotaion ? 2 : 1;
		Node* y;
		Node* T2;

		for (size_t i = len; i > 0; i--)
		{
			if (isLeftRotation)
			{
				y = m_pathNodes[i]->right;
				T2 = y->left;
				y->left = m_pathNodes[i];
				m_pathNodes[i]->right = T2;

			}
			else
			{
				y = m_pathNodes[i]->left;
				T2 = y->right;
				y->right = m_pathNodes[i];
				m_pathNodes[i]->left = T2;
			}

			if (i == 0)
			{
				m_root = y;
			}
			else
			{
				if (isDoubleRotaion && isLeftRotation || !isDoubleRotaion && !isLeftRotation)
				{
					m_pathNodes[i - 1]->left = y;
				}
				else
				{
					m_pathNodes[i - 1]->right = y;
				}
			}

			m_pathNodes[i]->height = maxHeight(getHeightOfNode(m_pathNodes[i]->left), getHeightOfNode(m_pathNodes[i]->right)) + 1;
			y->height = maxHeight(getHeightOfNode(y->left), getHeightOfNode(y->right)) + 1;

			isLeftRotation = !isLeftRotation;
		}
	}*/

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

	void remove(T data)
	{
		if (m_root == nullptr)
		{
			return;
		}
		else
		{
			Node* currentNode = m_root;
			bool isLeaf = false;
			Node* leftNode;
			Node* rightNode;

			while (!isLeaf)
			{
				if (data == currentNode->data)
				{
					if (currentNode->left == nullptr && currentNode->right == nullptr) // no children
					{
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

						isLeaf = true;
					}
					else if (currentNode->left == nullptr) // one child
					{
						rightNode = currentNode->right;
						m_pathNodes[m_pathNodes.size() - 1]->right = rightNode;
						isLeaf = true;
					}
					else if (currentNode->right == nullptr)
					{
						leftNode = currentNode->left;
						m_pathNodes[m_pathNodes.size() - 1]->left = leftNode;
						isLeaf = true; // need to update heights
					}
					else // two children
					{
						m_pathNodes.push_back(currentNode);
						int removedNodeIndex = m_pathNodes.size() - 1;

						currentNode = currentNode->right; // one step right
						leftNode = m_pathNodes[removedNodeIndex]->left;

						if (currentNode->left != nullptr)
						{
							rightNode = currentNode;

							while (true) // searching for the smallest value going left
							{
								m_pathNodes.push_back(currentNode);
								currentNode = currentNode->left;

								if (currentNode->left == nullptr)
								{
									if (currentNode->right != nullptr)// if successor has right child, it becomes left child for parent.
									{
										m_pathNodes[m_pathNodes.size() - 1]->left = currentNode->right;
										isLeaf = true;
									}

									m_pathNodes[m_pathNodes.size() - 1]->left = nullptr;

									break;
								}
							}
						}
						else // no left child, means the least max value found.
						{
							rightNode = currentNode->right;
						}

						m_pathNodes[removedNodeIndex] = currentNode;

						if (removedNodeIndex == 0)
						{
							m_root = m_pathNodes[0];
						}
						else
						{
							m_pathNodes[removedNodeIndex - 1]->right = m_pathNodes[removedNodeIndex];
						}

						m_pathNodes[removedNodeIndex]->left = leftNode;
						m_pathNodes[removedNodeIndex]->right = rightNode;
						isLeaf = true;
					}
				}
				else if (data < currentNode->data)
				{
					if (currentNode->left == nullptr)
					{
						isLeaf = true;
					}
					else
					{
						m_pathNodes.push_back(currentNode);
						currentNode = currentNode->left;
					}
				}
				else
				{
					if (currentNode->right == nullptr)
					{
						isLeaf = true;
					}
					else
					{
						m_pathNodes.push_back(currentNode);
						currentNode = currentNode->right;
					}
				}
			}

			m_pathNodes.clear();
		}
	}

	std::string preOrder()
	{
		std::string output;
		printPreorder(m_root, output);
		//std::cout << output;

		return output;
	}

	void postOrder()
	{
		printPostorder(m_root);
	}

	void inOrder()
	{
		std::string output;
		printInorder(m_root, output);
		std::cout << output;
	}
};

