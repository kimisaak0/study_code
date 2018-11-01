#include "child.h"
int main(void)
{
	parents pMan;
	pMan.Character();
	pMan.Appearance();
	pMan.Wealth();

	child aBoy;
	aBoy.Character();		// Parent에서 상속 받은 함수 호출
	aBoy.Appearance();	// Parent에서 상속 받은 함수 호출
	aBoy.Wealth();		// Parent에서 상속 받은 함수 호출
	aBoy.Humanity();		// Child에서 추가된 함수 호출
	return 0;
}
