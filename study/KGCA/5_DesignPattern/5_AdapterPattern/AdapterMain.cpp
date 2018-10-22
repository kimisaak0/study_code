//적응자 패턴은 기존에 만들어놓은 클래스와 유사한 클래스가 필요하지만,
//제공해야하는 인터페이스가 다를 경우 호환성을 갖게 해주는 패턴이다.
//Adapter pattern에는 Class Adapter와 Object Adapter의 두가지가 있다.

#include <iostream>
#include <conio.h>
using namespace std;

//#define CLASS_ADT
#define OBJECT_ADT

//기본 사각형
class Rectangle
{
private:
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;

public:
	Rectangle(int l, int t, int r, int b)
	{
		m_left    = l;
		m_top     = t;
		m_right   = r;
		m_bottom  = b;
	}

	void Draw() 
	{
		printf("LT : (%d, %d), RB : (%d, %d) \n", m_left, m_top, m_right, m_bottom);
	}
};

//기능 클래스  
class TextView
{
private:
	int m_left;
	int m_top;
	int m_width;
	int m_height;

public:
	Rectangle GetExtent()
	{
		return Rectangle(m_left, m_top, m_left + m_width, m_top + m_height);
	}

public:
	TextView()
	{
		m_left = 0;
		m_top = 0;
		m_width = 0;
		m_height = 0;
	}
	TextView(int left, int top, int width, int height)
	{
		m_left = left;
		m_top = top;
		m_width = width;
		m_height = height;
	}
};

//인터페이스 클래스
class Shape
{
protected:
	int m_x1;
	int m_y1;
	int m_x2; 
	int m_y2;

public:
	virtual Rectangle BoundingBox() = 0;

public:
	Shape() 
	{
		m_x1 = 0, m_y1 = 0, m_x2 = 0, m_y2 = 0;
	}

	Shape(int _x1, int _y1, int _x2, int _y2)
	{
		m_x1 = _x1, m_y1 = _y1, m_x2 = _x2, m_y2 = _y2;
	}
};



#if defined(CLASS_ADT)
//클래스 어댑터 (인터페이스는 public으로, 동작은 private로 상속받는다)
//클래스 어댑터의 핵심은 상속받은 인터페이스로 사용자가 원하는 동작을 하게 만드는 것.
class TextShape : public Shape, private TextView
{
public:

	Rectangle BoundingBox()
	{
		
		//return Rectangle(m_x1, m_y1, m_x2, m_y2);
		return GetExtent();
	}

public:
	TextShape(int x1, int y1, int x2, int y2) : TextView(x1, y1, x2-x1, y2-y1) {}
};

void DisplayBoundingBox(Shape* pSeletedShpae)
{
	(pSeletedShpae->BoundingBox()).Draw();
}

#elif defined OBJECT_ADT
//객체 어댑터

//인터페이스만 상속받고 동작은 상속받지 않았다.
class TextShape : public Shape
{
private:
	//동작과 관련된 객체를 포함한다.
	TextView* m_pText;
	//TextView m_Text; 
	//set함수가 없어서 텍스트 뷰의 멤버 변수 값을 바꿀 수가 없다...
	//포인터를 쓰면 값을 그 멤버변수를 생성할 때 넘겨줄 수 있다.

public:
	Rectangle BoundingBox()
	{
		//동작과 관련된 멤버를 불러내서 그 동작을 시킨다.
		return m_pText->GetExtent();
	}

public:
	TextShape()
	{
		m_pText = new TextView(m_x1, m_y1, m_x2- m_x1, m_y2- m_y1);
	}

	TextShape(int x1, int y1, int x2, int y2) : Shape(x1, y1, x2, y2) 
	{
		m_pText = new TextView(m_x1, m_y1, m_x2 - m_x1, m_y2 - m_y1);
	}
};

void DisplayBoundingBox(Shape* pSeletedShpae)
{
	(pSeletedShpae->BoundingBox()).Draw();
}

#else 
//어댑터 없음

void DisplayBoundingBox(Shape* pSeletedShpae, TextView* pSeletedText)
{
	if (pSeletedText != nullptr) {
		(pSeletedText->GetExtent()).Draw();
	}
	else if (pSeletedShpae != nullptr) {
		(pSeletedShpae->BoundingBox()).Draw();
	}
	else {
		cout << "두 인자값이 모두 nullptr입니다." << endl;
	}
}
#endif

int main()
{
#if defined CLASS_ADT || defined OBJECT_ADT
	TextShape text(5,5,5,5);
	DisplayBoundingBox(&text);
	_getch();
#else
	TextView text;
	DisplayBoundingBox(NULL, &text);
#endif
}

