#pragma once

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// const char& operator []() const {}
// char& operator [] () �� �Լ��� ������ �Լ��� �ȴ�.

//�����ǰ� ������ ������
//1) ���� ������ : .
//2) ������ ���� ������ : .*
//3) ���� ������ : ::
//4) ���� ������ : ? :
//5) ũ�� ������ : sizeof


//�����ǰ� ������ �����ڴ� �� ����ΰ� ���� ������ �����ߴ�.
//�������� ������ ���� �ƴ϶�� �� pointŬ������ ��ȯ�ϵ��� �ߴ�.

class point
{


public:
	//�� �������ϴ��� �� �𸣰ڴ� ������(..)
	point * operator-> () { return this; } // ��� ���� ������
	point& operator* () { return *this; } // ������ ������ ������
	point operator->* (const point& p);	  // ��� ������ ���� ������

	point operator() (...); //�Լ� ȣ�� ������
	point& operator, (point& p) const; //��ǥ ������
									   // void operatorR() const; //ĳ��Ʈ ������ ???

									   //�Ҵ� �� �Ҵ� ��� ������
	void* operator new (size_t i);
	void* operator delete (size_t i);
	void operator new[](size_t i);
	void operator delete[](size_t i);

	point operator[] (point& p); // �迭 ������

								 //[]�� �ε����� �����ϴµ� �� ���� ���δ�.
	int operator[] (int i);

	//���� ����������, �Ű������� ������ ������ �����µ��� ���δ�.
	point operator++ (); // ���� ���� ������
	point operator-- (); // ���� ���� ������
	point operator++ (int); //���� ���� ������
	point operator-- (int); //���� ���� ������

							//���� ��ȣ������.
	point operator+ () const;
	point operator- () const;

	//���� ��Ģ ������. ���� Ŭ�������� ����
	point operator+ (const point& p) const;
	point operator- (const point& p) const;
	point operator* (const point& p) const;
	point operator/ (const point& p) const;
	point operator% (const point& p) const;

	//���� ��Ģ ������. ���� �ٸ� Ÿ�԰��� ����
	//int������ ���길 ���������� �ٸ� Ÿ�԰��� ������ �ʿ��ϸ� ���� �����ؾ��Ѵ�.
	//��ȯ ��Ģ�� ���� ����� ���� ������ �������� �ʴ´�.
	point operator+ (int i);
	friend point operator+ (int i, const point& p);

	point operator- (int i);
	friend point operator- (int i, const point& p);

	point operator* (int i);
	friend point operator* (int i, const point& p);

	point operator/ (int i);
	friend point operator/ (int i, const point& p);

	friend point operator% (const point& p, int i); //�׳� �̷��� �ص� �Ǳ� �Ѵ�.
	friend point operator% (int i, const point& p);



	//�� ������
	bool operator== (const point& p);
	bool operator!= (const point& p);
	bool operator>  (const point& p);
	bool operator<  (const point& p);
	bool operator>= (const point& p);
	bool operator<= (const point& p);


	//�� ������
	bool operator! () const; //����
	bool operator&& (const point& p) const; //�׸���
	bool operator|| (const point& p) const; //�Ǵ�


											//��Ʈ ������
	point operator~ () const; //��Ʈ ����
	point operator& (const point& p); //��Ʈ and;
	point operator| (const point& p); //��Ʈ or;
	point operator^ (const point& p); //��Ʈ xor;
	point operator<< (const point& p); // ��Ʈ ���� ����Ʈ
	point operator>> (const point& p); // ��Ʈ ������ ����Ʈ


									   //���� ������, ���� ���� ������
	point& operator=  (const point& p);
	point& operator+= (const point& p);
	point& operator-= (const point& p);
	point& operator*= (const point& p);
	point& operator/= (const point& p);
	point& operator%= (const point& p);
	point& operator&= (const point& p);
	point& operator|= (const point& p);
	point& operator^= (const point& p);
	point& operator>>= (const point& p);
	point& operator<<= (const point& p);


	//����� ������ ������
	friend std::ostream& operator<<(std::ostream &os, const point& pt);
	friend std::istream& operator>>(std::istream &is, point& pt);

	//�ٸ� Ÿ�԰��� ���� ���Ե� ������ �����ϴ�.
	point& operator+= (int i);

	//�̷��͵� �����ϱ� �ϴ�
	bool operator== (int i);
	friend bool operator== (int i, const point& p);

	bool operator&& (int i);
	friend bool operator&& (int i, const point& p);

	point operator^ (int i);
	friend bool operator^ (int i, const point& p);



	//��¥ ���� �� �ȴ�(..)
};

