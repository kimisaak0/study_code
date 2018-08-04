#pragma once
#include <iostream>

//const char* p = 0; //���� ������, ��� ������
//char* const p = 0; //��� ������, ���� ������
//const char* const p = 0; //��� ������, ��� ������
//void  a() const { } // ��� �Լ� : �Լ����� ��� ���� �� ���� �Ұ���
//const �Լ������� const �Լ��� ȣ�� ����

//const int a() { }	// ��ȯ���� ���, ��� �����θ� ��ȯ ���� ���� �� ����. 

class Region
{
public:
	enum { POINT_POINT, POINT_SIZE };	//�������� ����, �������� ����
	int m_iWidth;
	int m_iHeight;

private:
	//�簢�� ������ �����ϱ� ���� ���������
	int m_iLeft;	//�������� x��ǥ
	int m_iTop;		//�������� y��ǥ
	int m_iRight;	//������ x��ǥ
	int m_iBottom;	//������ y��ǥ

	//��¹���� �����ϱ� ���� ��� ����
	static int notation;	//POINT_POINT OR POINT_SIZE


public :
	const Region* Get() const { return this; }
	const Region& GetRef() const { return *this; }

	//�簢�� ������ ���� ������ ��� �Լ���
	const int GetLeft() { return m_iLeft; }
	const int GetTop() { return m_iTop; }
	const int* GetRight() { return &m_iRight; }
	const int& GetBottom() { return m_iBottom; }

	int GetWidth() const;						//���α��� ���
	const int GetHeight() const;				//���α��� ���
	void GetStartPoint(int &x, int &y) const;	//������ ���
	void GetEndPoint(int &x, int &y) const;		//���� ���
	void GetCenterPoint(int &x, int &y) const;	//�߽��� ���
	bool IsPointInRegion(int x, int y) const;	//���� ���� �ȿ� �ִ���

	//�簢�� ������ �����ϰ� ó���ϴ� �Լ���
	void SetRect(int l, int t, int r, int b);	//���� ����
	void Move(int x, int y);					//��ġ �̵�
	void Resize(int width, int height);			//ũ�� ����
	void UnionRegion(const Region &r1, const Region &r2);		//������
	bool IntersectRegion(const Region &r1, const Region &r2);	//������

	//�簢�� ������ ǥ���ϱ� ���� �Լ���
	void Show();								//���� ���
	static void SetNotation(int n);		//��� ��� ����

public:
	Region();
	Region(int l, int t, int r, int b);
	~Region();
};

