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

		for (size_t i = pathLenght - 1; i + 1 > 0; i--)
		{
			pathNodes[i]->height = maxHeight(pathNodes[i]->height, pathLenght - i);
		}
	}

	void placeLeaf(Node*& node, Node*& currentNode, Node*& leaf, std::vector<Node*>& pathNodes)
	{
		node->depth = currentNode->depth + 1;
		leaf = node;
		pathNodes.push_back(node);
		updateHeights(pathNodes);
	}

public:

	void insert(T data)
	{
		Node* node = new Node();
		node->depth = 1;
		node->height = 1;
		node->data = data;
		std::vector<Node*> pathNodes;

		if (m_root == nullptr)
		{
			node->left = nullptr;
			node->right = nullptr;

			m_root = node;
		}
		else
		{
			Node* currentNode = m_root;

			while (true)
			{
				pathNodes.push_back(currentNode);

				if (data < currentNode->data)
				{
					if (currentNode->left == nullptr)
					{
						//node->depth = currentNode->depth + 1;
						//currentNode->left = node;
						//pathNodes.push_back(node);
						//updateHeights(pathNodes);
						placeLeaf(node, currentNode, currentNode->left, pathNodes);

						break;
					}

					currentNode = currentNode->left;
				}
				else if (data > currentNode->data)
				{
					if (currentNode->right == nullptr)
					{
						//node->depth = currentNode->depth + 1;
						//currentNode->right = node;
						//pathNodes.push_back(node);
						//updateHeights(pathNodes);
						placeLeaf(node, currentNode, currentNode->right, pathNodes);

						break;
					}

					currentNode = currentNode->right;
				}
				else
				{
					break;
				}
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

