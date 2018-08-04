#include "Region.h"

int Region::notation = Region::POINT_POINT;

Region::Region()
{
	SetRect(0, 0, 0, 0);
	//영역을 0으로 초기화
}

Region::Region(int l, int t, int r, int b)
{
	SetRect(l, t, r, b);
	//영역을 주어진 값으로 초기화
}


Region::~Region()
{
}

void Region::SetRect(int l, int t, int r, int b) 
{
	m_iLeft = l;	//시작점의 x좌표 설정
	m_iTop = t;		//시작점의 y좌표 설정
	m_iRight = r;	//끝점의 x좌표 설정
	m_iBottom = b;	//끝점의 y좌표 설정
}

int			Region::GetWidth() const
{
	return m_iRight - m_iLeft;
}//가로길이 얻기

const int	Region::GetHeight() const
{
	return m_iBottom - m_iTop;
}//세로길이 얻기

void		Region::GetStartPoint(int &x, int &y) const 
{
	x = m_iLeft;
	y = m_iTop;
}	//시작점 얻기

void		Region::GetEndPoint(int &x, int &y) const
{
	x = m_iRight;
	y = m_iBottom;
}//끝점 얻기

void		Region::GetCenterPoint(int &x, int &y) const
{
	x = (m_iLeft + m_iRight) / 2;
	y = (m_iHeight + m_iBottom) / 2;
}//중심점 얻기

bool		Region::IsPointInRegion(int x, int y) const
{
	if (x > m_iLeft && x < m_iRight && y > m_iHeight && y < m_iBottom) {
		return true;
	}
	else {
		return false;
	}
}//점이 영역 안에 있는지

void Region::Move(int x, int y)
{
	m_iLeft += x;
	m_iTop += y;
	m_iRight += x;
	m_iHeight += y;
}//위치 이동

void Region::Resize(int width, int height)
{
	if (width > 0 && height > 0) {
		m_iRight = m_iLeft + width;
		m_iBottom = m_iTop + height;
	}
	else {
		std::cout << "길이가 음수가 될 수 없습니다." << std::endl;
	}
}//크기 변경

void Region::UnionRegion(const Region &r1, const Region &r2)
{
	m_iLeft =	r1.m_iLeft	 < r2.m_iLeft	? r1.m_iLeft   : r2.m_iLeft;
	m_iTop =	r1.m_iTop	 < r2.m_iTop	? r1.m_iTop	   : r2.m_iTop;
	m_iRight =	r1.m_iRight  > r2.m_iRight  ? r1.m_iRight  : r2.m_iRight;
	m_iBottom = r1.m_iBottom > r2.m_iBottom ? r1.m_iBottom : r2.m_iBottom;
};		//합집합

bool Region::IntersectRegion(const Region &r1, const Region &r2)
{
	m_iLeft = r1.m_iLeft	 > r2.m_iLeft	? r1.m_iLeft   : r2.m_iLeft;
	m_iTop = r1.m_iTop		 > r2.m_iTop	? r1.m_iTop	   : r2.m_iTop;
	m_iRight = r1.m_iRight	 < r2.m_iRight  ? r1.m_iRight  : r2.m_iRight;
	m_iBottom = r1.m_iBottom < r2.m_iBottom ? r1.m_iBottom : r2.m_iBottom;
	
	//한점 또는 라인이 중첩되었을 때는 교차로 판정하지 않음.
	//교집합이 존재하지 않는 경우
	if (m_iLeft >= m_iRight || m_iTop >= m_iBottom) {
		SetRect(0, 0, 0, 0);
		return false;
	}
	return true;
};	//교집합


void Region::SetNotation(int n)
{
	notation = n%2;

}//출력 방식 지정

void Region::Show()
{
	if (notation == POINT_POINT) {
		printf("(%d,%d) , (%d,%d) \n", m_iLeft, m_iTop, m_iRight, m_iBottom);
	}
	else if(notation == POINT_SIZE) {
		printf("(%d, %d), [%d x %d]\n", m_iLeft, m_iTop, GetWidth(), GetHeight());

	}
}//영역 출력


