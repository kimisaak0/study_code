#pragma once

template <typename T>
struct node
{
	T data;
	node* left;
	node* right;
};


template <typename T>
class BinaryTree
{
	node<T>* rootNode;

private:
	

public:
	node<T>* getRoot();

	bool  connectRight(node<T>* srcTree, node<T>* DestNode = rootNode);
	bool  connectLeft(node<T>* srcTree, node<T>* DestNode = rootNode);

public:
	BinaryTree();
	virtual ~BinaryTree();
};

template <typename T>
BinaryTree<T>::BinaryTree()
{
	rootNode = new node<T>;
	rootNode->left = nullptr;
	rootNode->right = nullptr;
}

template <typename T>
node<T>* BinaryTree<T>::getRoot()
{
	return rootNode;
}

template <typename T>
bool  BinaryTree<T>::connectRight(node<T>* srcTree, node<T>* DestNode)
{

}

template <typename T>
bool  BinaryTree<T>::connectLeft(node<T>* srcTree, node<T>* DestNode)
{

}

template <typename T>
BinaryTree<T>::~BinaryTree()
{

}