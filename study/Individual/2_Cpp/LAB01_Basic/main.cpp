
//basic, expert
#define expert

#ifdef basic

//ȭ�� �µ��� ���� �µ��� ��ȯ�ϴ� ���α׷�.

//������� �߰� �� ���ӽ����̽� ����
#include <iostream>
//using namespace std;
using std::cout;
using std::endl;
using std::cin;

int main()
{
	//���� ���� �� �ʱ�ȭ
	//int f_temp = 60;
	//int c_temp;
	double f_temp;
	double c_temp;
	
	cout << "ȭ�� �µ��� �Է��ϼ��� : "; cin >> f_temp;

	//��� ����� c_temp�� ����
	//c_temp = 5 / 9 * (f_temp - 32);
	c_temp = 5 / 9.0 * (f_temp - 32); // or  c_temp = 5 / (double)9 * (f_temp - 32); 

	//���ڿ� ���
	//cout << "���� �µ��� " << c_temp << "�Դϴ�." << endl;
	cout << "���� �µ��� " << c_temp << "�Դϴ�.\n";

	return 0;
}

#endif

// 1. ���� ��� : "���� �µ��� 0�Դϴ�."
//    ���� ����Ű : ����, ����� ����Ű : F5, �� �ܰ辿 ���� : F11, ���ν��� ������ ���� : F10
// 2. �ּ� �ޱ�
// 3. endl ��ſ� "\n"�Ẹ��
// 4. using���� ������ :  "C2065 : ������� ���� �ĺ����Դϴ�." 
//    ���������� ��ü ���ӽ����̽��� ����ϴ� �ͺ��ٴ� �ʿ��� ��ü�� ���ӽ����̽��� ����ϴ°� ��ȣ.
// 5. c_temp�� ���� 0���� ������ ���� : ������ �����ڴ� �ǿ����ڰ� ��� �����̸� �� ���������� ��ȯ�ϱ� ����.
// 6. ������ϸ� ����� Ȯ���ϱ�. 
// 7. ���α׷� �����ϱ� : �� �� �ϳ��� �Ǽ����·� �ٲ㵵 ������� �Ǽ������� ��ȯ��. 
// 8. ȭ�� �µ��� ����ڿ��� �Է¹ޱ�.
// 9. ȭ�� �µ��� ���� �µ��� �Ǽ��� ó���ϱ�.
// 10. ���� �µ��� ȭ�� �µ��� ��ȯ�ϴ� ���α׷� �����.

#ifdef expert

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

double f_c(double f_temp) {
	double c_temp = 5 / 9.0 * (f_temp - 32);
	return c_temp;
}

double c_f(double c_temp) {
	double f_temp = 9 / 5.0 * c_temp + 32;
	return f_temp;
}

int main()
{
	while (true) {
		int sw;
		cout << "�޴�" << endl;
		cout << "1. ȭ�� -> ����" << endl;
		cout << "2. ���� -> ȭ��" << endl;
		cout << "�׿�. ����" << endl;
		cin >> sw;


		double degree;
		switch (sw) {
			case 1: {
				cout << "ȭ�� �µ� �Է� : "; cin >> degree;
				cout << "ȭ�� " << degree << "�� ���� " << f_c(degree) << "�Դϴ�" << endl;
				break;
			}

			case 2: {
				cout << "���� �µ� �Է� : "; cin >> degree;
				cout << "���� " << degree << "�� ȭ�� " << c_f(degree) << "�Դϴ�" << endl;
				break;
			}

			default: {
				return 0;
			}
		}
	}
}

#endif
