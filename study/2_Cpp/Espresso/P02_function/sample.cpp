
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <conio.h>
#include <time.h>

#define q5

//사용자로부터 세 개의 정수를 받은 후 if-else문을 사용하여 가장 작은 값을 반환하는 get_minimum(x1, x2, x3)함수를 작성하고 테스트하라.
#ifdef q1

int get_minimum(int x1, int x2, int x3)
{
	return x1 <= x2 ? (x1 <= x3 ? x1 : x3) : (x2 <= x3 ? x2 : x3);
}

int main()
{
	int a, b, c;

	cout << "세 개의 정수를 입력하세요 : "; cin >> a >> b >> c;

	cout << "입력한 수들 중 가장 작은 수는 " << get_minimum(a, b, c) << "입니다." << endl;

}
#endif

//사용자로부터 연산자와 2개의 정수를 입력받아 계산하는 계산기 프로그램을 작성하라.
//각각의 연산을 함수로 작성할 것.
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
	cout << "연산자를 입력하세요 : + - * / "; cin >> op;

	switch (op) {
		case '+':
			cout << "정수 두개를 공백으로 분리해서 입력하세요 : "; cin >> a >> b;
			result = add(a, b);
			break;

		case '-':
			cout << "정수 두개를 공백으로 분리해서 입력하세요 : "; cin >> a >> b;
			result = minus(a, b);
			break;

		case '*':
			cout << "정수 두개를 공백으로 분리해서 입력하세요 : "; cin >> a >> b;
			result = multiple(a, b);
			break;

		case '/':
			cout << "정수 두개를 공백으로 분리해서 입력하세요 : "; cin >> a >> b;
			if (b == 0) {
				cout << "0으로는 나눌 수 없습니다." << endl;
				cout << "아무키나 누르면 종료됩니다." << endl;
				_getch();
				return 0;
			}
			result = devide(a, b);
			break;

		default:
			cout << "잘못 누르셨습니다." << endl;
			cout << "아무키나 누르면 종료됩니다." << endl;
			_getch();
			return 0;
	}

	cout << a << op << b << "= " << result << endl;
	cout << "아무키나 누르면 종료됩니다." << endl;
	_getch();
}

#endif

//switch문을 사용하여 사용자가 입력한 키가 공백키이면 무슨 키인지 출력하는 프로그램을 작성하라.
#ifdef q3

void white(int ch) {
	cout << endl;
	switch (ch) {
		case 9:
			cout << "tab을 입력하셨습니다. " << endl;
			break;

		case 13:
			cout << "enter를 입력하셨습니다. " << endl;
			break;

		case 32:
			cout << "space를 입력하셨습니다. " << endl;
			break;

		default:
			cout << "공백키가 아닙니다. " << endl;
			break;
	}

}

int main()
{
	cout << "키를 입력하세요 : "; 
	char ch = _getch();

	white(ch);
}

#endif

//사용자로부터 1~100사이의 번호를 입력받아 당첨 여부를 확인하는 프로그램을 작성하라.
//당첨 번호를 생성하는 함수 get_number()와 당첨 여부를 판멸하는 is_winning_ticket() 함수를 작성할 것.
#ifdef q4

int get_number()
{
	srand((unsigned)time(NULL));

	return rand() % 100 + 1;
}

void is_winning_ticket(int a)
{
	int answer = get_number();
	cout << "당첨 숫자 : " << answer << endl;

	if (a == answer) {
		cout << "맞추셨습니다." << endl;
	}
	else {
		cout << "못 맞추셨습니다." << endl;
	}
}

int main()
{
	int a = 0;

	while (true) {
		cout << "1~100사이의 숫자를 입력하세요 (0은 종료) : ";
		cin >> a;
		if (a == 0) {
			return 0;
		}
		if (a >= 1 && a <= 100) {
			is_winning_ticket(a);
		}
	}
}

#endif

#ifdef q5

int ComsChoice()
{
	srand((unsigned)time(NULL));

	int ri = rand() % 3 + 1;;

	switch (ri)
	{
		case 1: { cout << "컴퓨터 : 묵" << endl; } break;
		case 2: { cout << "컴퓨터 : 찌" << endl; } break;
		case 3: { cout << "컴퓨터 : 빠" << endl; } break;
	}

	return ri;
}

void CheckWin(int player) {
	int coms = ComsChoice();

	if (coms == player) {
		cout << "비겼습니다." << endl;
	}
	else if (coms - player == 2 || coms - player == -1) {
		cout << "졌습니다." << endl;
	}
	else {
		cout << "이겼습니다." << endl;
	}
}

int main()
{
	int c;
	while (true) {
		cout << "선택하세요. 1. 묵, 2. 찌, 3. 빠 (0 종료)" << endl;
		cin >> c;

		if (c == 0) {
			return 0;
		}

		if (c >= 1 && c <= 3) {
			switch (c) {
				case 1: { cout << "플레이어 : 묵" << endl; } break;
				case 2: { cout << "플레이어 : 찌" << endl; } break;
				case 3: { cout << "플레이어 : 빠" << endl; } break;
			}
			CheckWin(c);
		}
	}

}

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