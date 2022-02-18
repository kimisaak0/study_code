#pragma once

template <typename T>
struct node
{
	T data;
	node* left;
	node* right;
};

//Ʈ�� ���� ���� �Լ�
template <typename T>
void ChangeData(node<T>* node, T data)
{
	node->data = data;
}

template <typename T>
T& CheckData(node<T>* node)
{
	return node->data;
}

template <typename T>
node<T>* MakeNode(T data)
{
	node<T>* nn = new node<T>;
	nn->data = data;
	nn->left = nullptr;
	nn->right = nullptr;

	return nn;
}

//�۾��� �Լ������ͷ� ���޹޴� ��ȸ �Լ�
template <typename T>
void preorder(node<T>* node, void(*action)(T) )
{
	if (node != nullptr) {
		action(node->data);
		preorder(node->left, action);
		preorder(node->right, action);
	}
}


template <typename T>
void inorder(node<T>* node, void(*action)(T))
{
	if (node != nullptr) {
		inorder(node->left, action);
		action(node->data);
		inorder(node->left, action);
	}
}


template <typename T>
void postorder(node<T>* node, void(*action)(T))
{
	if (node != nullptr) {
		postorder(node->left, action);
		postorder(node->right, action);
		action(node->data);
	}
}


template <typename T>
class BinaryTree
{
	node<T>* rootNode;
	
private:
	

public:
	//��� �����͸� �����ϴ� �Լ�
	node<T>* getRoot();
	node<T>* getRight(node<T>* node);
	node<T>* getLeft(node<T>* node);

	//srcƮ���� Dest����� �ڽ����� ����
	bool  connectLeft(node<T>* DestNode, node<T>* SrcTree);
	bool  connectRight(node<T>* DestNode, node<T>* SrcTree);

public:
	BinaryTree(T data);
	virtual ~BinaryTree();
};

template <typename T>
BinaryTree<T>::BinaryTree(T data)
{
	rootNode = new node<T>;
	rootNode->data = data;
	rootNode->left = nullptr;
	rootNode->right = nullptr;
}


template <typename T>
node<T>* BinaryTree<T>::getRoot()
{
	return rootNode;
}

template <typename T>
node<T>* BinaryTree<T>::getLeft(node<T>* node)
{
	return node->left;
}

template <typename T>
node<T>* BinaryTree<T>::getRight(node<T>* node)
{
	return node->right;
}


template <typename T>
bool  BinaryTree<T>::connectLeft(node<T>* DestNode, node<T>* srcTree)
{
	if (DestNode->left == nullptr) {
		DestNode->left = srcTree;
		return true;
	}

	return false;
}

template <typename T>
bool  BinaryTree<T>::connectRight(node<T>* DestNode, node<T>* srcTree)
{
	if (DestNode->right == nullptr) {
		DestNode->right = srcTree;
		return true;
	}

	return false;
}


template <typename T>
BinaryTree<T>::~BinaryTree()
{

}