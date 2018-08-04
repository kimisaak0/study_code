#include <iostream>
using std::endl;
using std::cout;
using std::cin;

//exception
const char* account = "1234-5678"; //���¹�ȣ
int sid = 1122;                    //��й�ȣ
int balance = 1000;                //�ܾ�
int sk = 0;

class AccountExpt //���� Ŭ����
{
	char acc[10];
	int sid;
	int secretkey;

public:

	void whatis()
	{
		cout << "���¹�ȣ : " << acc << endl;
		cout << "��й�ȣ : " << sid << endl;
		cout << "���Ű   : " << secretkey << endl;
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

	try { //�ֿ� �帧
		cout << "���¹�ȣ �Է� : "; cin >> acc;
		cout << "��й�ȣ 4�ڸ� �Է� : "; cin >> id;
		cout << "Ű �Է�"; cin >> k;

		if (strcmp(account, acc) || sid != id || sk != k) {
			// a�� �̹� �ִ� ���� Ŭ������ ����ϴ� ����, 
			// b�� ���� ���� ���� Ŭ������ ����ϴ� ����.

		//	throw std::exception(acc);           //-- a (���ڰ��� �� ���� �� ��� ó���ϴ°�???)
			throw AccountExpt(acc, id, k);       //-- b
		}

		cout << "��ݾ� �Է� : "; cin >> money;
		if (balance < money) {
			throw money;
		}

		balance -= money;
		cout << "�ܾ� : " << balance << endl;
	}

	//���� ó���ϴ� �κ�
	catch (int money) {
		cout << "���� �ݾ� :" << money - balance << endl;
	}

	//catch (std::exception& expt) { //�̹� �ִ� excpetionŬ���� -- a
	//	cout << "���� �Է��� �ٽ� �ѹ� Ȯ���ϼ���" << endl;
	//	cout << "���¹�ȣ: " << expt.what() << endl;
	//}

	catch (AccountExpt& exptM) { //���� ���� ���� Ŭ���� -- b
		cout << "���� �Է��� �ٽ� �ѹ� Ȯ���ϼ���" << endl;
		exptM.whatis();
	}

	return 0;
}