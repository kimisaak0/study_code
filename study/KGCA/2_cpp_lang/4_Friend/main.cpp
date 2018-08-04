#include "token.h"

int main()
{
	TCHAR buffer[] = L"kgca game academy";

	//规过 1 (陛绊客 凯艰 包拌)
	/*TCHAR buffer[] = L"kgca game academy";
	value vl(buffer);
	token tk;
	tk.Show();*/

	//规过 2
	try {
		token tk(buffer);
		tk.Show();
#ifndef _UNICODE
		cout << _T("Show the 3rd token: ") << tk.nth_token(3) << _T("\n");
#else
		wcout << _T("Show the 3rd token: ") << tk.nth_token(3) << _T("\n");
#endif
	}

	catch (TCHAR* pData)
	{
		wcout << _T("Error");
	}

	vector<string> str = split("one:two::three", ':');
}