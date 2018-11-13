#pragma once

template <typename T>
struct node
{
	T data;
	node* left;
	node* right;
};

//트리 관련 전역 함수
template <typename T>
node<T>* MakeNode(T data)
{
	node<T>* nn = new node<T>;
	nn->data = data;
	nn->left = nullptr;
	nn->right = nullptr;

	return nn;
}

//작업을 함수포인터로 전달받는 순회 함수
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
	//노드 포인터를 리턴하는 함수
	node<T>* getRoot();

	void AddData(T data);
	void DeleteData(T data);


public:
	//정렬의 기준이 되는 함수를 매개변수로 갖는 생성자가 필요.
	//오름차순 정렬을 할지 내림차순 정렬을 할지도 결정되어야 함.
	BinarySeachTree();
	virtual ~BinarySeachTree();
};
