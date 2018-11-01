#include "pt.h"

int pt::dynamic = 0;

//이 넷의 기본 형식은 이렇게 정해져 있다. 
pt*   pt::operator->()              
{ 
	//뭔가 새로운 작업
	return  this; 
}
pt&   pt::operator* ()              
{
	//뭔가 새로운 작업
	return *this; 
}
void* pt::operator new(size_t size) 
{
	cout << "동적생성된 수 : " << ++dynamic << endl;;
	return ::new pt; 
}
void  pt::operator delete(void* p)  
{
	cout << "동적생성된 수 : " << --dynamic << endl;;
	::delete p; 
}

//빡침 사칙연산은 더하기만 하자.

//전위 증가
pt pt::operator++(void) // ++p1
{
	++x, ++y;
	return *this;
}

//후위 증가
pt pt::operator++(int)  // p1--;
{
	pt temp = *this;
	++x, ++y;
	return temp;
}

//같은 타입끼리 연산
pt pt::operator+(const pt &np) const
{
	return pt(x + np.x, y + np.y);
}


//다른 타입과의 연산 p2=p1+2;
pt pt::operator+(int n) const // 
{
	return pt(x + n, y + n);
}

// p2= 2 + p1; (friend함수임) (교환법칙 정의)
pt operator+(int n, const pt &np) 
{
	return pt(np.x + n, np.y + n);
}

//대입 연산자
pt& pt::operator=(const pt &np) {
	x = np.x; y = np.y;
	return *this;
}

//증가 대입 연산자 (같은 타입에 대해서) pt1 += pt2
pt& pt::operator+=(const pt &np)
{
	x += np.x; y += np.y;
	return *this;
}

//증가 대입 연산자 (인트 타입에 대해서) pt1 += int1

pt& pt::operator+=(int n)
{
	x += n; y += n;
	return *this;
}

//int1 += pt1 은 할 수 있을까?
int operator+= (int& n, const pt& np) 
{
	//할 수 있지만 의미가 많이 다르다.
	n += np.x + np.y;
	return n;
}

//int1 += pt1 으로 pt를 리턴해서 pt1에 저장한다면?
//pt& pt::operator+=(int n) 이것과 차이가 없다. 괜히 헷갈리기만 하지.
//pt& operator+= (int& n, pt& np)
//{
//	//할 수 있지만 의미가 많이 다르다.
//	np.x += n; np.y += n;
//	return np;
//}

bool pt::operator==(const pt &pt) const
{	
	return (this->x == pt.x && this->y == pt.y);
	//&& 연산의 결과는 bool값이다.
}

bool pt::operator!=(const pt &pt) const
{
	return !(*this == pt);
	//이미 정의한 == 연산자를 이용하여 정의
}
	 

//인덱싱 연산
int& pt::operator[](int index)
{
	switch (index % 2) {
		case 0: return x; break;
		case 1: return y; break;
	}
}

//입출력 스트림 연산자 재정의.
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
	cout << "복사 생성자" << endl;
}

pt::~pt()
{
	cout << "Distructor" << endl;
}
