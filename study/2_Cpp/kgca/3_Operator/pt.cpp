#include "pt.h"

int pt::dynamic = 0;

//�� ���� �⺻ ������ �̷��� ������ �ִ�. 
pt*   pt::operator->()              
{ 
	//���� ���ο� �۾�
	return  this; 
}
pt&   pt::operator* ()              
{
	//���� ���ο� �۾�
	return *this; 
}
void* pt::operator new(size_t size) 
{
	cout << "���������� �� : " << ++dynamic << endl;;
	return ::new pt; 
}
void  pt::operator delete(void* p)  
{
	cout << "���������� �� : " << --dynamic << endl;;
	::delete p; 
}

//��ħ ��Ģ������ ���ϱ⸸ ����.

//���� ����
pt pt::operator++(void) // ++p1
{
	++x, ++y;
	return *this;
}

//���� ����
pt pt::operator++(int)  // p1--;
{
	pt temp = *this;
	++x, ++y;
	return temp;
}

//���� Ÿ�Գ��� ����
pt pt::operator+(const pt &np) const
{
	return pt(x + np.x, y + np.y);
}


//�ٸ� Ÿ�԰��� ���� p2=p1+2;
pt pt::operator+(int n) const // 
{
	return pt(x + n, y + n);
}

// p2= 2 + p1; (friend�Լ���) (��ȯ��Ģ ����)
pt operator+(int n, const pt &np) 
{
	return pt(np.x + n, np.y + n);
}

//���� ������
pt& pt::operator=(const pt &np) {
	x = np.x; y = np.y;
	return *this;
}

//���� ���� ������ (���� Ÿ�Կ� ���ؼ�) pt1 += pt2
pt& pt::operator+=(const pt &np)
{
	x += np.x; y += np.y;
	return *this;
}

//���� ���� ������ (��Ʈ Ÿ�Կ� ���ؼ�) pt1 += int1

pt& pt::operator+=(int n)
{
	x += n; y += n;
	return *this;
}

//int1 += pt1 �� �� �� ������?
int operator+= (int& n, const pt& np) 
{
	//�� �� ������ �ǹ̰� ���� �ٸ���.
	n += np.x + np.y;
	return n;
}

//int1 += pt1 ���� pt�� �����ؼ� pt1�� �����Ѵٸ�?
//pt& pt::operator+=(int n) �̰Ͱ� ���̰� ����. ���� �򰥸��⸸ ����.
//pt& operator+= (int& n, pt& np)
//{
//	//�� �� ������ �ǹ̰� ���� �ٸ���.
//	np.x += n; np.y += n;
//	return np;
//}

bool pt::operator==(const pt &pt) const
{	
	return (this->x == pt.x && this->y == pt.y);
	//&& ������ ����� bool���̴�.
}

bool pt::operator!=(const pt &pt) const
{
	return !(*this == pt);
	//�̹� ������ == �����ڸ� �̿��Ͽ� ����
}
	 

//�ε��� ����
int& pt::operator[](int index)
{
	switch (index % 2) {
		case 0: return x; break;
		case 1: return y; break;
	}
}

//����� ��Ʈ�� ������ ������.
ostream& operator<<(ostream &os, const pt &np)
{
	os << "(" << np.x << ", " << np.y << ")";
	return os;
}
istream& operator>>(istream &is, pt &np)
{
	is >> np.x;
	is >> np.y;
	return is;
}


void pt::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}
void pt::Move(int _x, int _y)
{
	x += _x;
	y += _y;
}
void pt::Show()
{
	printf("(%d,%d)\n", x, y);
}

pt::pt()
{
	cout << "constructor" << endl;
}

pt::pt(int x, int y)
{
	this->x = x;
	this->y = y;
	cout << "constructor" << endl;
}

pt::pt(const pt& obj)
{
	this->x = obj.x;
	this->y = obj.y;
	cout << "���� ������" << endl;
}

pt::~pt()
{
	cout << "Distructor" << endl;
}
