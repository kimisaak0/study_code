#include <iostream>
using std::endl;
using std::cout;
using std::cin;

//exception
const char* account = "1234-5678"; //계좌번호
int sid = 1122;                    //비밀번호
int balance = 1000;                //잔액
int sk = 0;

class AccountExpt //예외 클래스
{
	char acc[10];
	int sid;
	int secretkey;

public:

	void whatis()
	{
		cout << "계좌번호 : " << acc << endl;
		cout << "비밀번호 : " << sid << endl;
		cout << "비밀키   : " << secretkey << endl;
	}

	AccountExpt(char* str, int id, int key)
	{
		strcpy_s(acc, str);
		sid = id;
		secretkey = key;
	}
};

int main()
{
	char acc[10];
	int id;
	int money;
	int k;

	try { //주요 흐름
		cout << "계좌번호 입력 : "; cin >> acc;
		cout << "비밀번호 4자리 입력 : "; cin >> id;
		cout << "키 입력"; cin >> k;

		if (strcmp(account, acc) || sid != id || sk != k) {
			// a는 이미 있는 예외 클래스를 사용하는 구문, 
			// b는 직접 만든 예외 클래스를 사용하는 구문.

		//	throw std::exception(acc);           //-- a (인자값이 더 많을 땐 어떻게 처리하는가???)
			throw AccountExpt(acc, id, k);       //-- b
		}

		cout << "출금액 입력 : "; cin >> money;
		if (balance < money) {
			throw money;
		}

		balance -= money;
		cout << "잔액 : " << balance << endl;
	}

	//예외 처리하는 부분
	catch (int money) {
		cout << "부족 금액 :" << money - balance << endl;
	}

	//catch (std::exception& expt) { //이미 있는 excpetion클래스 -- a
	//	cout << "다음 입력을 다시 한번 확인하세요" << endl;
	//	cout << "계좌번호: " << expt.what() << endl;
	//}

	catch (AccountExpt& exptM) { //직접 만든 예외 클래스 -- b
		cout << "다음 입력을 다시 한번 확인하세요" << endl;
		exptM.whatis();
	}

	return 0;
}