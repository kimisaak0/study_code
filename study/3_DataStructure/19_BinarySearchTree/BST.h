#pragma once
//일단 이진탐색트리의 구현에 집중하기 위해서 데이터형을 정수로 고정.

struct node
{
	int data;
	node* left;
	node* right;
};

void preorder(node* node, void(*action)(int))
{
	if (node != nullptr) {
		action(node->data);
		preorder(node->left, action);
		preorder(node->right, action);
	}
}

void inorder(node* node, void(*action)(int))
{
	if (node != nullptr) {
		inorder(node->left, action);
		action(node->data);
		inorder(node->right, action);
	}
}

void postorder(node* node, void(*action)(int))
{
	if (node != nullptr) {
		postorder(node->left, action);
		postorder(node->right, action);
		action(node->data);
	}
}

class BinarySearchTree
{
public:
	node* TreePointer;

private:
	node* &RootNode = TreePointer;

private:
	node* MakeNode(int data);
	node* Search(node* nptr, int key);
	node* delSearch(node* nptr, int key);
	node* DeleteNode(node* nptr);

public:
	node* Search(int key);
	void AddNode(int data);
	void DeleteNode(int key);

public:
	BinarySearchTree();
	virtual	~BinarySearchTree();
};

//----------------------------->>

node* BinarySearchTree::MakeNode(int data)
{
	node* nn = new node;
	nn->data = data;
	nn->left = nullptr;
	nn->right = nullptr;

	return nn;
}

node* BinarySearchTree::Search(node* nptr, int key)
{
	if (nptr == nullptr) {
		return nullptr;
	}
	else if (nptr->data == key) {
		return nptr;
	}
	else if (nptr->data > key) {
		return Search(nptr->left, key);
	}
	else {
		return Search(nptr->right, key);
	}
}

node* BinarySearchTree::delSearch(node* nptr, int key)
{
	if (nptr == nullptr) {
		return nullptr;
	}

	else if (nptr->data > key) {
		if (nptr->left->data == key) {
			return nptr;
		}
		else {
			return delSearch(nptr->left, key);
		}
	}
	else if (nptr->data < key) {
		if (nptr->right->data == key) {
			return nptr;
		}
		else {
			return delSearch(nptr->right, key);
		}
	}
	else if (nptr->data == key) {
		return nptr;
	}
}

node* BinarySearchTree::DeleteNode(node* nptr)
{
	node* ret;
	if (nptr->left == nullptr && nptr->right == nullptr) {
		ret = nullptr;
	}
	else if (nptr->left != nullptr &&nptr->right == nullptr) {
		ret = nptr->left;		
	}
	else if (nptr->left == nullptr && nptr->right != nullptr) {
		ret = nptr->right;
	}
	else {
		ret = nptr;
		node* prev = nullptr;
		while (nptr->right != nullptr) {
			nptr->data = nptr->right->data;
			prev = nptr;
			nptr = nptr->right;
		}
		prev->right = nullptr;
	}

	delete nptr;
	return ret;
}

//----------------------------->>



BinarySearchTree::BinarySearchTree()
{
	TreePointer = nullptr;
}

node* BinarySearchTree::Search(int key)
{
	return Search(RootNode, key);
}

void BinarySearchTree::AddNode(int data)
{
	node* nptr = nullptr;

	if (RootNode == nullptr) {
		RootNode = MakeNode(data);
	}
	else {
		nptr = RootNode;
		node* nNode = MakeNode(data);

		while (true) {
			if (nNode->data < nptr->data) {
				if (nptr->left != nullptr) {
					nptr = nptr->left;
				}
				else {
					nptr->left = nNode;
					break;
				}
			}
			else if(nNode->data > nptr->data) {
				if (nptr->right != nullptr) {
					nptr = nptr->right;
				}
				else {
					nptr->right = nNode;
					break;
				}
			}
			else {
				if (nptr->left == nullptr) {
					nptr->left = nNode;
					break;
				}
				else if (nptr->right == nullptr) {
					nptr->right = nNode;
					break;
				}
				else {
					nptr = nptr->left;
				}
			}
		}
	}
}

void BinarySearchTree::DeleteNode(int key)
{
	node* sNode = delSearch(RootNode, key);

	if (sNode == RootNode) {
		DeleteNode(sNode);
	}
	else if(sNode->left != nullptr && sNode->left->data == key) {
		sNode->left = DeleteNode(sNode->left);
	}
	else if (sNode->right != nullptr && sNode->right->data == key) {
		sNode->right = DeleteNode(sNode->right);
	}
}

BinarySearchTree::~BinarySearchTree()
{

}