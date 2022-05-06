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

	void updateHeights(std::vector<Node*> pathNodes)
	{
		int pathLenght = pathNodes.size();
		bool left;

		for (size_t i = pathLenght - 1; i + 1 > 0; i--)
		{
			pathNodes[i]->height = maxHeight(pathNodes[i]->height, pathLenght - i);

			int nodeBalance = getBalance(pathNodes[i]);

			std::string rotation1;
			//std::string rotation2;
			//bool test;

			if (nodeBalance < -1)
			{
				rotation1 = (pathNodes[i + 1]->left != nullptr && pathNodes[i + 1]->left->data == pathNodes[i + 2]->data ? "left" : "right");
				//rotation1 = (pathNodes[i]->left->data == pathNodes[i + 1]->data ? "left" : "right");
				//rotation2 = (pathNodes[i + 1]->left->data == pathNodes[i + 2]->data ? "left" : "right");
			}
			else if (nodeBalance > 1)
			{
				//test = (pathNodes[i + 1]->left );
				//rotation1 = (pathNodes[i]->left != nullptr && pathNodes[i]->left->data == pathNodes[i + 1]->data ? "left" : "right");
				rotation1 = (pathNodes[i + 1]->left != nullptr && pathNodes[i + 1]->left->data == pathNodes[i + 2]->data ? "left" : "right");
			}
		}
	}

	bool processChild(Node*& node, Node*& currentNode, Node*& child)
	{
		if (child == nullptr)
		{
			node->depth = currentNode->depth + 1;
			child = node;
			m_pathNodes.push_back(node);
			updateHeights(m_pathNodes);

			return true;
		}

		currentNode = child;

		return false;
	}

	int getBalance(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		int leftChildHeight = node->left == nullptr ? 0 : node->left->height;
		int rightChildHeight = node->right == nullptr ? 0 : node->right->height;		

		int result = rightChildHeight - leftChildHeight;
		return result;
	}

public:

	void insert(T data)
	{
		Node* node = new Node();
		node->depth = 1;
		node->height = 1;
		node->data = data;

		m_pathNodes.clear();

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

