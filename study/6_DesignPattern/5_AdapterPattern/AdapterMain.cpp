//������ ������ ������ �������� Ŭ������ ������ Ŭ������ �ʿ�������,
//�����ؾ��ϴ� �������̽��� �ٸ� ��� ȣȯ���� ���� ���ִ� �����̴�.
//Adapter pattern���� Class Adapter�� Object Adapter�� �ΰ����� �ִ�.

#include <iostream>
#include <conio.h>
using namespace std;

//#define CLASS_ADT
#define OBJECT_ADT

//�⺻ �簢��
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

//��� Ŭ����  
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

//�������̽� Ŭ����
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
//Ŭ���� ����� (�������̽��� public����, ������ private�� ��ӹ޴´�)
//Ŭ���� ������� �ٽ��� ��ӹ��� �������̽��� ����ڰ� ���ϴ� ������ �ϰ� ����� ��.
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
//��ü �����

//�������̽��� ��ӹް� ������ ��ӹ��� �ʾҴ�.
class TextShape : public Shape
{
private:
	//���۰� ���õ� ��ü�� �����Ѵ�.
	TextView* m_pText;
	//TextView m_Text; 
	//set�Լ��� ��� �ؽ�Ʈ ���� ��� ���� ���� �ٲ� ���� ����...
	//�����͸� ���� ���� �� ��������� ������ �� �Ѱ��� �� �ִ�.

public:
	Rectangle BoundingBox()
	{
		//���۰� ���õ� ����� �ҷ����� �� ������ ��Ų��.
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
//����� ����

void DisplayBoundingBox(Shape* pSeletedShpae, TextView* pSeletedText)
{
	if (pSeletedText != nullptr) {
		(pSeletedText->GetExtent()).Draw();
	}
	else if (pSeletedShpae != nullptr) {
		(pSeletedShpae->BoundingBox()).Draw();
	}
	else {
		cout << "�� ���ڰ��� ��� nullptr�Դϴ�." << endl;
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

