
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <conio.h>
#include <time.h>

#define q4

//����ڷκ��� �� ���� ������ ���� �� if-else���� ����Ͽ� ���� ���� ���� ��ȯ�ϴ� get_minimum(x1, x2, x3)�Լ��� �ۼ��ϰ� �׽�Ʈ�϶�.
#ifdef q1

int get_minimum(int x1, int x2, int x3)
{
	return x1 <= x2 ? (x1 <= x3 ? x1 : x3) : (x2 <= x3 ? x2 : x3);
}

int main()
{
	int a, b, c;

	cout << "�� ���� ������ �Է��ϼ��� : "; cin >> a >> b >> c;

	cout << "�Է��� ���� �� ���� ���� ���� " << get_minimum(a, b, c) << "�Դϴ�." << endl;

}
#endif

//����ڷκ��� �����ڿ� 2���� ������ �Է¹޾� ����ϴ� ���� ���α׷��� �ۼ��϶�.
//������ ������ �Լ��� �ۼ��� ��.
#ifdef q2

int add(int a, int b)
{
	return a + b;
}

int minus(int a, int b)
{
	return a - b;
}

int multiple(int a, int b)
{
	return a * b;
}

int devide(int a, int b)
{
	return a / b;
}

int main()
{
	char op;
	int a, b, result = 0;
	cout << "�����ڸ� �Է��ϼ��� : + - * / "; cin >> op;

	switch (op) {
		case '+':
			cout << "���� �ΰ��� �������� �и��ؼ� �Է��ϼ��� : "; cin >> a >> b;
			result = add(a, b);
			break;

		case '-':
			cout << "���� �ΰ��� �������� �и��ؼ� �Է��ϼ��� : "; cin >> a >> b;
			result = minus(a, b);
			break;

		case '*':
			cout << "���� �ΰ��� �������� �и��ؼ� �Է��ϼ��� : "; cin >> a >> b;
			result = multiple(a, b);
			break;

		case '/':
			cout << "���� �ΰ��� �������� �и��ؼ� �Է��ϼ��� : "; cin >> a >> b;
			if (b == 0) {
				cout << "0���δ� ���� �� �����ϴ�." << endl;
				cout << "�ƹ�Ű�� ������ ����˴ϴ�." << endl;
				_getch();
				return 0;
			}
			result = devide(a, b);
			break;

		default:
			cout << "�߸� �����̽��ϴ�." << endl;
			cout << "�ƹ�Ű�� ������ ����˴ϴ�." << endl;
			_getch();
			return 0;
	}

	cout << a << op << b << "= " << result << endl;
	cout << "�ƹ�Ű�� ������ ����˴ϴ�." << endl;
	_getch();
}

#endif

//switch���� ����Ͽ� ����ڰ� �Է��� Ű�� ����Ű�̸� ���� Ű���� ����ϴ� ���α׷��� �ۼ��϶�.
#ifdef q3

void white(int ch) {
	cout << endl;
	switch (ch) {
		case 9:
			cout << "tab�� �Է��ϼ̽��ϴ�. " << endl;
			break;

		case 13:
			cout << "enter�� �Է��ϼ̽��ϴ�. " << endl;
			break;

		case 32:
			cout << "space�� �Է��ϼ̽��ϴ�. " << endl;
			break;

		default:
			cout << "����Ű�� �ƴմϴ�. " << endl;
			break;
	}

}

int main()
{
	cout << "Ű�� �Է��ϼ��� : "; 
	char ch = _getch();

	white(ch);
}

#endif

//����ڷκ��� 1~100������ ��ȣ�� �Է¹޾� ��÷ ���θ� Ȯ���ϴ� ���α׷��� �ۼ��϶�.
//��÷ ��ȣ�� �����ϴ� �Լ� get_number()�� ��÷ ���θ� �Ǹ��ϴ� is_winning_ticket() �Լ��� �ۼ��� ��.
#ifdef q4

int get_number()
{
	srand((unsigned)time(NULL));

	return rand() % 100 + 1;
}

void is_winning_ticket(int a)
{
	int answer = get_number();
	cout << "��÷ ���� : " << answer << endl;

	if (a == answer) {
		cout << "���߼̽��ϴ�." << endl;
	}
	else {
		cout << "�� ���߼̽��ϴ�." << endl;
	}
}

int main()
{
	while (true) {
		int a = 0;
		cout << "1~100������ ���ڸ� �Է��ϼ��� : ";
		cin >> a;
		if (a >= 1 && a <= 100) {
			is_winning_ticket(a);
			return 0;
		}
	}
}

#endif

#ifdef q5
#endif

#ifdef q6
#endif

#ifdef q7
#endif

#ifdef q8
#endif

#ifdef q9
#endif

#ifdef qa
#endif

#ifdef qb
#endif

#ifdef qc
#endif