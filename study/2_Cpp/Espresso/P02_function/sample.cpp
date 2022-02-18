
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <conio.h>
#include <time.h>

#define qc

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

//컴퓨터와 가위바위보를 하는 프로그램을 작성하라.
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


//사용자로부터 소득을 입력받아 소득 구간에 따른 소득세를 계산하는 프로그램을 작성하라. 
//(소득 1000만 이하 8 % , 1000만 초과 - 4000만 이하 17 % , 4000만 초과 - 8000만 이하 26 % , 8000만 초과 35 % 로 가정)
#ifdef q6
int get_tax(int salary) 
{
	int tax;
	if (salary <= 10000000) {
		tax = 0.08;
	}
	else if (10000000 < salary && salary <= 40000000) {
		tax = 0.17;
	}
	else if (40000000 < salary && salary <= 80000000) {
		tax = 0.26;
	}
	else {
		tax = 0.35;
	}

	return salary * tax;
}

int get_tax_2018(int salary)
{
	float tax;
	if (salary <= 1200) {
		tax = 0.06;
	}
	else if (1200 < salary && salary <= 4600) {
		tax = 0.15;
	}
	else if (4600 < salary && salary <= 8800) {
		tax = 0.24;
	}
	else if (8800 < salary && salary <= 15000) {
		tax = 0.35;
	}
	else if (15000 < salary && salary <= 30000) {
		tax = 0.38;
	}
	else if (30000 < salary && salary <= 50000) {
		tax = 0.40;
	}
	else {
		tax = 0.42;
	}

	return (salary*10000) * tax;
}

int main()
{
	int _salary;
	while (true) {
		cout << "연소득을 만단위로 입력하세요. (0은 종료) " << endl;
		cin >> _salary;

		if (_salary == 0) {
			return 0;
		}

		printf("연소득이 %d만원이면 소득세는 %d원입니다.\n", _salary, get_tax_2018(_salary));
	}
}
#endif

//각 변의 길이가 100보다 작은 삼각형 중 피타고라스의 정리가 성립하는 삼각형을 찾아 각변의 길이를 출력하는 프로그램을 작성하라. (삼중반복문을 사용할 것)
#ifdef q7
void checkOrtho() 
{
	for (int a = 1; a <= 100; a++) {
		for (int b = 1; b <= 100; b++) {
			for (int c = 1; c <= 100; c++) {
				if (a * a + b * b == c * c && c < a + b) {
					printf("a = %d, b = %d, c = %d \n", a, b, c);
				}
			}
		}
	}
}

int main()
{
	checkOrtho();

	return 0;
}
#endif

//주어진 정수가 소수(Prime number)인지 검사하는 함수를 작성하고, 이를 이용해 1부터 100사이의 모든 소수를 출력하라.
#ifdef q8

bool checkPrime(int n) 
{
	if (n < 2) {
		return false;
	}

	if (n == 2) {
		return true;
	}
	
	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

int main()
{
	int enter = 0;
	for (int a = 1; a <= 100; a++) {
		if (checkPrime(a)) {
			printf(" %2d ", a);
			if (enter++ == 4) {
				enter = 0;
				cout << endl;
			}
		}
	}
}

#endif

//2차원 공간상의 두 점의 거리를 계산하는 프로그램을 작성하라.
#ifdef q9
float dist_2d(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main()
{
	float x1, y1, x2, y2;
	cout << "첫번쨰 점의 좌표를 입력하세요. (ex: 3.2 4.3)" << endl;
	cin >> x1 >> y1;

	cout << "두번쨰 점의 좌표를 입력하세요. (ex: 3.2 4.3)" << endl;
	cin >> x2 >> y2;

	printf("점1(%.2f, %.2f)와 점2(%.2f,%.2f)사이의 거리는 %f입니다.", x1, y1, x2, y2, dist_2d(x1, y1, x2, y2));

	return 0;
}

#endif

//2차 방정식의 실수근을 계산하는 함수를 작성하라.
#ifdef qa
void quad_eqn(double a, double b, double c) {
	if (b*b - 4*a*c >= 0) {
		double plus = (-b + sqrt(b*b - 4*a*c)) / 2*a;
		double minus = (-b - sqrt(b*b - 4*a*c)) / 2*a;

		if (plus == minus) {
			cout << "중근 : " << plus << endl;
		}
		else {
			cout << "첫번째근 : " << minus << " 두번째근 : " << plus << endl;
		}
	}
	else {
		cout << "실근이 없습니다." << endl;
	}

}

int main()
{
	double da, db, dc;
	cout << "a*x^2+b*x+c의 a,b,c를 공백으로 구분하여 입력하세요 (ex : 2x^2+3x+4 -> 2 3 4 )" << endl;
	cin >> da >> db >> dc;

	quad_eqn(da, db, dc);
}
#endif

//save(int amount)함수를 호출하여 저금하고, 호출될때마다 총 저축액을 출력하는 프로그램을 작성하라.
#ifdef qb
int save(int amount) {
	static int total = 0;
	total += amount;

	printf("%d원 저금해서 현재 총 저금액은 %d원입니다. \n", amount, total);

	return total;
}

int main()
{
	while(true) {
		int money;
		cout << "얼마를 저금하시겠습니까? (0은 종료)" << endl;
		cin >> money;

		if (money == 0) {
			return 0;
		}

		save(money);
	}
}
#endif

#ifdef qc
int triple(int i) {
	if (i == 1) {
		return 1;
	}
	else if(i<1) {
		return 0;
	}
	else {
		return i*i*i + triple(i - 1);
	}
}

int main()
{
	int end;
	cout << "몇 세제곱 까지의 합을 계산할까요?" << endl;
	cin >> end;

	cout << triple(end) << endl;
}
#endif