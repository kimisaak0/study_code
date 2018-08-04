#pragma once
#include <iostream>

template <typename T>
class stackM {
private:
	static const int g_iMaxCount = 3;

	int m_iTop;
	T m_iData[g_iMaxCount];

public:

	bool push(int iData);
	void pop() const;
	T get() const;

	void printList() const;

	int  getMaxCount() const 
	{
		return g_iMaxCount;
	}

	stackM();
	virtual ~stackM();

};
