#pragma once
//일단 구현에 집중하기 위해서 데이터형을 정수로 고정.

struct node
{
	int data;
	node* left;
	node* right;
};


class PQ_BST
{
public:
	node* TreePointer;

private:
	node* &RootNode = TreePointer;
	int   iCount;

	int*  tRet;

private:
	node* MakeNode(int data);

public:
	void Add(int data);
	int Remove();
	int Retrieve();
	int Count();

public:
	PQ_BST();
	virtual	~PQ_BST();
};

//----------------------------->>

node* PQ_BST::MakeNode(int data)
{
	node* nn = new node;
	nn->data = data;
	nn->left = nullptr;
	nn->right = nullptr;

	return nn;
}

//----------------------------->>

PQ_BST::PQ_BST()
{
	TreePointer = nullptr;
	iCount = 0;
	tRet = new int;
}

void PQ_BST::Add(int data)
{
	node* nptr = nullptr;
	
	iCount++;

	if (RootNode == nullptr) {
		RootNode = MakeNode(data);
	}
	else {
		nptr = RootNode;
		node* nNode = MakeNode(data);
	
		while (true) {
			if (nNode->data < nptr->data) {  			// 새로운 데이터가 현재 위치의 노드의 데이터보다 작을 경우
				if (nptr->left != nullptr) {            // 현재 위치의 노드에 왼쪽 노드가 이미 있으면
					nptr = nptr->left;                  // 현재 노드의 위치를 왼쪽 노드로 이동
				}										   
				else {				                    // 왼쪽 노드가 없으면
					nptr->left = nNode;                 // 현재 위치의 왼쪽 노드에 새로운 데이터를 붙인다.
					break;
				}
			}
			else if (nNode->data > nptr->data) {        // 새로운 데이터가 현재 위치의 노드의 데이터보다 크거나 같을 경우
				if (nptr->right != nullptr) {           // 현재 위치의 노드에 오른쪽 노드가 이미 있으면
					nptr = nptr->right;                 // 현재 노드의 위치를 오른쪽 노드로 이동
				}
				else {                                  // 오른쪽 노드가 없으면
					nptr->right = nNode;                // 현재 위치의 오른쪽 노드에 새로운 데이터를 붙인다. 
					break;    
				}
			}
		}
	}
}

int PQ_BST::Remove()
{
	iCount--;

	node* nptr = RootNode;
	node* delNode;

	if (nptr->left == nullptr) {
		*tRet = nptr->data;

		delNode = nptr;

		if (nptr->right != nullptr) {
			RootNode = nptr->right;
		}
		else {
			RootNode = nullptr;
		}
	}
	else {

		while (nptr->left != nullptr && nptr->left->left != nullptr) {
			nptr = nptr->left;
		}

		*tRet = nptr->left->data;

		delNode = nptr->left;

		if (nptr->left->right != nullptr) {
			nptr->left = nptr->left->right;
		}
		else {
			nptr->left = nullptr;
		}
	}

	delete delNode;

	return *tRet;
}

int PQ_BST::Retrieve()
{
	node* nptr = RootNode;

	if (nptr->left == nullptr) {
		*tRet = nptr->data;
	}
	else {
		while (nptr->left != nullptr && nptr->left->left != nullptr) {
			nptr = nptr->left;
		}
		*tRet = nptr->left->data;
	}

	return *tRet;
}

int PQ_BST::Count()
{
	return iCount;
}

PQ_BST::~PQ_BST()
{
	delete tRet;
}