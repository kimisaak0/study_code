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
void preorder(node<T>* node, void(*action)(T))
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
class BinarySeachTree
{
	node<T>* rootNode;

public:
	//��� �����͸� �����ϴ� �Լ�
	node<T>* getRoot();

	void AddData(T data);
	void DeleteData(T data);


public:
	//������ ������ �Ǵ� �Լ��� �Ű������� ���� �����ڰ� �ʿ�.
	//�������� ������ ���� �������� ������ ������ �����Ǿ�� ��.
	BinarySeachTree();
	virtual ~BinarySeachTree();
};
