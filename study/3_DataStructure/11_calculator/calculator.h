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

class calculator
{
	TCHAR infixStr[256];
	QueueList<TCHAR> PostfixQueue;
	StackList<TCHAR> OperatorStack;
	StackList<int>  OperandStack;

public:
	void InputFormula(const TCHAR* str);
	void InToPost();
	int Prioty(TCHAR op1);
	int Calculate();

	int run(const TCHAR* str);

public:
	calculator();
	virtual ~calculator();
};

calculator::calculator()
{

}

void calculator::InputFormula(const TCHAR* str)
{
	_tcscpy_s(infixStr, str);
}

int calculator::Prioty(TCHAR op)
{
	if (op == '+' || op == '-') { return 1; }
	if (op == '*' || op == '/') { return 2; }
}

void calculator::InToPost()
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

int calculator::Calculate()
{
	do {
		TCHAR buf = PostfixQueue.Peek();
		if (isdigit(buf)) {
			OperandStack.Push(buf-48);
			PostfixQueue.Remove();
		}
		else {
			PostfixQueue.Remove();

			int i1, i2;
			i2 = OperandStack.Pop();
			i1 = OperandStack.Pop();

			if (buf == '+') { OperandStack.Push(i1 + i2); }
			else if (buf == '-') { OperandStack.Push(i1 - i2); }
			else if (buf == '*') { OperandStack.Push(i1 * i2); }
			else if (buf == '/') { OperandStack.Push(i1 / i2); }
		}
	} while (PostfixQueue.Count() != 0);

	return OperandStack.Peek();
}

int calculator::run(const TCHAR* str) 
{
	InputFormula(str);
	InToPost();
	return Calculate();
}


calculator::~calculator()
{

}