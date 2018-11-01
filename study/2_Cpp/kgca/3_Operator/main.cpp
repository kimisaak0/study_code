#include "pt.h"

//함수 포인터 관련 ... 이해가 잘 안됨.
void (pt::*fp) ();
void Execute(pt* the)
{
	if (fp != NULL)
	{
		(the->*fp)();
	}
}

int main()
{
	pt p1(0, 0), p2, p3, p4;

	p2 = ++p1;
	cout << p2 << p1 << endl;

	p1->Show();
	(*p1)->Show();
	pt* pData = new pt();
	pData->Show();

	p3 = p1++;
	cout << p3 << p1 << endl;

	p4 = p2 + p3;
	cout << p4 << endl;
	
	pt p5(10, 20), p6, p7;
	p6 = p5 + 2;
	p7 = 2 + p5;
	cout << p6 << p7 << endl;

	if (p6 == p7) { cout << "같다" << endl; }
	if (p6 != p7) { cout << "다르다" << endl; }

	cout << p6[0] << p6[1] << endl;

	pt p8;
	cin >> p8; 
	cout << p8;

	pt* d = new pt;
	d->SetPosition(10, 10);
	cout << *d;

	//전역 함수 포인터
	fp = &pt::Show;
	Execute(d);

	//클래스멤버함수 함수포인터
	d->m_fp = &pt::Show;
	(*d) > &p8;
	d->Execute();

	delete d;

	return 0;
}