#include "Mgr.h"



int main()
{
	mgr g_CtlMgr;
	g_CtlMgr.inputDataTail();
	g_CtlMgr.showData();

	cout << endl << "�������� ����" << endl;
	g_CtlMgr.sortTotal();
	g_CtlMgr.showData();
	g_CtlMgr.showData(g_CtlMgr.find(8));
	

	//10�� �ֱ� ������ 11�� �˻����� ���Ѵ�.
	try {
		if (g_CtlMgr.find(11) == nullptr ) {
			throw 11;
			g_CtlMgr.showData(g_CtlMgr.find(11));
		}
	}
	catch (int ex) {
		cout << ex << "�� �л��� ã�� �� �����ϴ�." << endl;
	}

	cout << "����";
}