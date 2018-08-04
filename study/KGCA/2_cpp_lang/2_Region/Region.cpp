#include "Region.h"

int Region::notation = Region::POINT_POINT;

Region::Region()
{
	SetRect(0, 0, 0, 0);
	//������ 0���� �ʱ�ȭ
}

Region::Region(int l, int t, int r, int b)
{
	SetRect(l, t, r, b);
	//������ �־��� ������ �ʱ�ȭ
}


Region::~Region()
{
}

void Region::SetRect(int l, int t, int r, int b) 
{
	m_iLeft = l;	//�������� x��ǥ ����
	m_iTop = t;		//�������� y��ǥ ����
	m_iRight = r;	//������ x��ǥ ����
	m_iBottom = b;	//������ y��ǥ ����
}

int			Region::GetWidth() const
{
	return m_iRight - m_iLeft;
}//���α��� ���

const int	Region::GetHeight() const
{
	return m_iBottom - m_iTop;
}//���α��� ���

void		Region::GetStartPoint(int &x, int &y) const 
{
	x = m_iLeft;
	y = m_iTop;
}	//������ ���

void		Region::GetEndPoint(int &x, int &y) const
{
	x = m_iRight;
	y = m_iBottom;
}//���� ���

void		Region::GetCenterPoint(int &x, int &y) const
{
	x = (m_iLeft + m_iRight) / 2;
	y = (m_iHeight + m_iBottom) / 2;
}//�߽��� ���

bool		Region::IsPointInRegion(int x, int y) const
{
	if (x > m_iLeft && x < m_iRight && y > m_iHeight && y < m_iBottom) {
		return true;
	}
	else {
		return false;
	}
}//���� ���� �ȿ� �ִ���

void Region::Move(int x, int y)
{
	m_iLeft += x;
	m_iTop += y;
	m_iRight += x;
	m_iHeight += y;
}//��ġ �̵�

void Region::Resize(int width, int height)
{
	if (width > 0 && height > 0) {
		m_iRight = m_iLeft + width;
		m_iBottom = m_iTop + height;
	}
	else {
		std::cout << "���̰� ������ �� �� �����ϴ�." << std::endl;
	}
}//ũ�� ����

void Region::UnionRegion(const Region &r1, const Region &r2)
{
	m_iLeft =	r1.m_iLeft	 < r2.m_iLeft	? r1.m_iLeft   : r2.m_iLeft;
	m_iTop =	r1.m_iTop	 < r2.m_iTop	? r1.m_iTop	   : r2.m_iTop;
	m_iRight =	r1.m_iRight  > r2.m_iRight  ? r1.m_iRight  : r2.m_iRight;
	m_iBottom = r1.m_iBottom > r2.m_iBottom ? r1.m_iBottom : r2.m_iBottom;
};		//������

bool Region::IntersectRegion(const Region &r1, const Region &r2)
{
	m_iLeft = r1.m_iLeft	 > r2.m_iLeft	? r1.m_iLeft   : r2.m_iLeft;
	m_iTop = r1.m_iTop		 > r2.m_iTop	? r1.m_iTop	   : r2.m_iTop;
	m_iRight = r1.m_iRight	 < r2.m_iRight  ? r1.m_iRight  : r2.m_iRight;
	m_iBottom = r1.m_iBottom < r2.m_iBottom ? r1.m_iBottom : r2.m_iBottom;
	
	//���� �Ǵ� ������ ��ø�Ǿ��� ���� ������ �������� ����.
	//�������� �������� �ʴ� ���
	if (m_iLeft >= m_iRight || m_iTop >= m_iBottom) {
		SetRect(0, 0, 0, 0);
		return false;
	}
	return true;
};	//������


void Region::SetNotation(int n)
{
	notation = n%2;

}//��� ��� ����

void Region::Show()
{
	if (notation == POINT_POINT) {
		printf("(%d,%d) , (%d,%d) \n", m_iLeft, m_iTop, m_iRight, m_iBottom);
	}
	else if(notation == POINT_SIZE) {
		printf("(%d, %d), [%d x %d]\n", m_iLeft, m_iTop, GetWidth(), GetHeight());

	}
}//���� ���


