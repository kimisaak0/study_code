#pragma once
//�ϴ� ������ �����ϱ� ���ؼ� ���������� ������ ����.

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
			if (nNode->data < nptr->data) {  			// ���ο� �����Ͱ� ���� ��ġ�� ����� �����ͺ��� ���� ���
				if (nptr->left != nullptr) {            // ���� ��ġ�� ��忡 ���� ��尡 �̹� ������
					nptr = nptr->left;                  // ���� ����� ��ġ�� ���� ���� �̵�
				}										   
				else {				                    // ���� ��尡 ������
					nptr->left = nNode;                 // ���� ��ġ�� ���� ��忡 ���ο� �����͸� ���δ�.
					break;
				}
			}
			else if (nNode->data > nptr->data) {        // ���ο� �����Ͱ� ���� ��ġ�� ����� �����ͺ��� ũ�ų� ���� ���
				if (nptr->right != nullptr) {           // ���� ��ġ�� ��忡 ������ ��尡 �̹� ������
					nptr = nptr->right;                 // ���� ����� ��ġ�� ������ ���� �̵�
				}
				else {                                  // ������ ��尡 ������
					nptr->right = nNode;                // ���� ��ġ�� ������ ��忡 ���ο� �����͸� ���δ�. 
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