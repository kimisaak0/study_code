#include "child.h"
int main(void)
{
	parents pMan;
	pMan.Character();
	pMan.Appearance();
	pMan.Wealth();

	child aBoy;
	aBoy.Character();		// Parent���� ��� ���� �Լ� ȣ��
	aBoy.Appearance();	// Parent���� ��� ���� �Լ� ȣ��
	aBoy.Wealth();		// Parent���� ��� ���� �Լ� ȣ��
	aBoy.Humanity();		// Child���� �߰��� �Լ� ȣ��
	return 0;
}
