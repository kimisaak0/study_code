#pragma once

template <typename T>
struct node
{
	T data;

	node* prev;
	node* next;

	node* left;
	node* right;
};

//트리 관련 전역 함수
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
	nn->prev = nullptr;
	nn->next = nullptr;

	return nn;
}

//작업을 함수포인터로 전달받는 순회 함수
template <typename T>
void preorder(node<T>* _node, void(*action)(T))
{
	node<T>* nptr = _node;

	while (nptr != nullptr) {
		if (nptr->left != nullptr) {
			if (nptr->right != nullptr) {
				nptr->left->next = nptr->right;
			}
			else {
				nptr->left->next = nptr->next;
			}
		}
		if(nptr->right != nullptr) {
			nptr->right->next = nptr->next;
		}

		action(nptr->data);
		if (nptr->left != nullptr) {
			nptr = nptr->left;
		}
		else if (nptr->right != nullptr) {
			nptr = nptr->right;
		}
		else {
			nptr = nptr->next;
		}	
	}
}


template <typename T>
void inorder(node<T>* _node, void(*action)(T))
{
	node<T>* nptr = _node;

	while (nptr->left != nullptr) {
		if (nptr->left != nullptr) {
			nptr->left->next = nptr;
		}
		if (nptr->right != nullptr) {
			nptr->right->next = nptr->next;
		}
		nptr = nptr->left;
	}

	while (nptr != nullptr) {
		if (nptr->left != nullptr) {
			nptr->left->next = nptr;
		}
		if (nptr->right != nullptr) {
			nptr->right->next = nptr->next;
		}

		action(nptr->data);
		 if (nptr->right != nullptr) {
			nptr = nptr->right;
			while (nptr->left != nullptr) {
				if (nptr->left != nullptr) {
					nptr->left->next = nptr;
				}
				if (nptr->right != nullptr) {
					nptr->right->next = nptr->next;
				}
				nptr = nptr->left;
			}
		}
		else {
			nptr = nptr->next;
		}
	}

}


template <typename T>
void postorder(node<T>* _node, void(*action)(T))
{
	node<T>* nptr = _node;

	bool ldsw = false;

	while (nptr != nullptr) {
		if (!ldsw) {
			while (nptr->left != nullptr) {
				if (nptr->left != nullptr) {
					if (nptr->right != nullptr) {
						nptr->left->next = nptr->right;
					}
					else {
						nptr->left->next = nptr;
					}
				}
				if (nptr->right != nullptr) {
					nptr->right->next = nptr;
				}
				nptr = nptr->left;

			}

			if (nptr->left == nullptr && nptr->right != nullptr) {
				if (nptr->left != nullptr) {
					if (nptr->right != nullptr) {
						nptr->left->next = nptr->right;
					}
					else {
						nptr->left->next = nptr;
					}
				}
				if (nptr->right != nullptr) {
					nptr->right->next = nptr;
				}
				nptr = nptr->right;
			}

			ldsw = true;
		}

		if (nptr->left != nullptr && ldsw == true) {
			action(nptr->data);
			nptr = nptr->next;
			ldsw = false;
			if (nptr != nullptr && nptr->next == nullptr) {
				action(nptr->data);
				break;
			}
		}
		else {
			action(nptr->data);
			nptr = nptr->next;
		}
	}
}



template <typename T>
class BinaryTree
{
	node<T>* rootNode;

private:


public:
	//노드 포인터를 리턴하는 함수
	node<T>* getRoot();
	node<T>* getRight(node<T>* node);
	node<T>* getLeft(node<T>* node);

	//src트리를 Dest노드의 자식으로 붙임
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
	rootNode->prev = nullptr;
	rootNode->next = nullptr;
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