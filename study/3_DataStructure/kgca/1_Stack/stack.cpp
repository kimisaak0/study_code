#include "stack.h"

template <typename T>
bool  stackM<T>::push(int iData)
{
	if (m_iTop >= g_iMaxCount) {
		std::cout << "stack overflow" << std::endl;
		return false;
	}

	m_iData[m_iTop++] = iData;
	return true;
}

template <typename T>
T  stackM<T>::get() const
{
	if (m_iTop <= 0) {
		std::cout << "stack underflow" << std::endl;
		return false;
	}
	return m_iData[m_iTop--];
}

template <typename T>
void stackM<T>::printList() const
{
	for (int iCnt = 0; iCnt < g_iMaxCount; iCnt++) {
		std::cout << m_iData[iCnt] << std::endl;
	}
}

template <typename T>
void stackM<T>::pop() const
{
	std::cout << m_iData[m_iTop - 1] << std::endl;
}

template <typename T>
stackM<T>::stackM()
{
	m_iTop = 0;
}

template <typename T>
stackM<T>::~stackM()
{ }
