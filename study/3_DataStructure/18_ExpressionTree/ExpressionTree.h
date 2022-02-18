#pragma once
#include "Queue_list.h"
#include "stack_list.h"

#include <iostream>

#include <tchar.h>
#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#define tcin std::wcin

#else
#define tcout std::cout
#define tcin std::cin

#endif

struct node
{
	TCHAR data;
	node* left;
	node* right;
};

node* MakeNode(TCHAR data)
{
	node* nn = new node;
	nn->data = data;
	nn->left = nullptr;
	nn->right = nullptr;

	return nn;
}




class ExpressionTree
{
	TCHAR infixStr[256];
	QueueList<TCHAR> PostfixQueue;
	StackList<TCHAR> OperatorStack;
	StackList<node*> NodeStack;

private:
	int Prioty(TCHAR op1);
	void InToPost();
	node* constructTree(node* root, node* left, node* right);
	void MakeEXPTree();

public:
	node * ExpTree;

public:
	void InputFormula(const TCHAR* str);
	void inorder(node* n);
	int calculate(node* n);

public:
	ExpressionTree();
	virtual ~ExpressionTree();
};

ExpressionTree::ExpressionTree()
{

}

void ExpressionTree::InputFormula(const TCHAR* str)
{
	_tcscpy_s(infixStr, str);
	InToPost();
	MakeEXPTree();
}


int ExpressionTree::Prioty(TCHAR op)
{
	if (op == '+' || op == '-') { return 1; }
	if (op == '*' || op == '/') { return 2; }
}

void ExpressionTree::InToPost()
{
	int iStrlen = _tcslen(infixStr) + 1;

	for (int i = 0; i < iStrlen; i++) {
		if (isdigit(infixStr[i])) { PostfixQueue.Add(infixStr[i]); }
		else {
			if (OperatorStack.Count() == 0) { OperatorStack.Push(infixStr[i]); }
			else {
				if (Prioty(OperatorStack.Peek()) < Prioty(infixStr[i])) { OperatorStack.Push(infixStr[i]); }
				else {
					PostfixQueue.Add(OperatorStack.Pop());
					i--;
					continue;
				}
			}
		}
	}
}

node* ExpressionTree::constructTree(node* root, node* left, node* right)
{
	root->data = root->data;
	root->left = left;
	root->right = right;

	return root;
}

void ExpressionTree::MakeEXPTree()
{
	int count = PostfixQueue.Count();
	for (int i = 0; i < count; i++) {
		char oper = PostfixQueue.Peek();
		PostfixQueue.Remove();
		
		NodeStack.Push(MakeNode(oper));
		if (oper == '+' || oper == '-' || oper == '*' || oper == '/') {
			node* root = NodeStack.Pop();
			node* right = NodeStack.Pop();
			node* left = NodeStack.Pop();

			NodeStack.Push(constructTree(root, left, right));
		}
	}

	ExpTree = NodeStack.Peek();
}

void ExpressionTree::inorder(node* n)
{
	if (n != nullptr) {
		inorder(n->left);
		std::cout << n->data;
		inorder(n->right);
	}
}

int ExpressionTree::calculate(node* n)
{
	int op1, op2;

	if (n->left == nullptr && n->right == nullptr) {
		return n->data - 48;
	}

	op1 = calculate(n->left);
	op2 = calculate(n->right);

	switch (n->data) {
		case '+': {return op1 + op2; } break;
		case '-': {return op1 - op2; } break;
		case '*': {return op1 * op2; } break;
		case '/': {return op1 / op2; } break;
	}

	return 0;
}

ExpressionTree::~ExpressionTree()
{

}