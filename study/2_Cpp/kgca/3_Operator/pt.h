#pragma once
#include <iostream>
using namespace std;

//const char& operator []() const;
//char& operator [] ();
//�� �Լ��� ������ �Լ��� �ȴ�. ... const �Լ��� �ƴϳ��� ����.

class pt
{
	static int dynamic;
	int x, y;
public:
	void SetPosition(int _x, int _y);
	void Move(int _x, int _y);
	void Show();

	//������ ������ ������
	pt* operator->();
	pt& operator* ();

	//���� ������ ������
	pt operator++();      // ++p1(����)
	pt operator++(int);  // p1++;(����)

	// ���׿����� p3 = p1 + p2
	pt operator+(const pt& np) const;

	// ���׿����� p3 = p1 + 2, p3 = 2 + p1
	pt operator+(int n) const; // p2=p1*2;
	friend pt operator+(int n, const pt& np); // p2= 2 * p1;
	

	pt &operator=(const pt &pt);

	pt &operator+=(const pt &pt);
	pt &operator+=(int n);

	//�ǹ� ���� �峭��
	friend int operator+= (int& n, const pt& np);
	//friend pt& operator+= (int& n, pt& np);

	bool operator==(const pt &pt) const;
	bool operator!=(const pt &pt) const;

	int &operator[](int index);
	void *operator new(size_t size);
	void operator delete(void *p);

	//std::cout << *pFindA << *pFindB;
	friend ostream &operator<<(ostream &os, const pt &pt);
	friend istream &operator>>(istream &is, pt &pt);

	void (pt::*m_fp) ();	//�Լ� ������ ����

	void Execute() {		//�Լ� ������ ����
		if (m_fp != NULL)
		{
			(this->*m_fp)();
		}
	}
	void operator > (pt* the)
	{
		if (m_fp != NULL)
		{
			(the->*m_fp)();
		}
	}
public:
	pt();
	pt(int x, int y);
	pt(const pt& obj);

	~pt();

};

