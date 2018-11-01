#include "Mgr.h"



int main()
{
	mgr g_CtlMgr;
	g_CtlMgr.inputDataTail();
	g_CtlMgr.showData();

	cout << endl << "총점으로 정렬" << endl;
	g_CtlMgr.sortTotal();
	g_CtlMgr.showData();
	g_CtlMgr.showData(g_CtlMgr.find(8));
	

	//10명만 있기 때문에 11은 검색되지 못한다.
	try {
		if (g_CtlMgr.find(11) == nullptr ) {
			throw 11;
			g_CtlMgr.showData(g_CtlMgr.find(11));
		}
	}
	catch (int ex) {
		cout << ex << "번 학생을 찾을 수 없습니다." << endl;
	}

	cout << "종료";
}