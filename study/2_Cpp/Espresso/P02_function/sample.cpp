
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <conio.h>
#include <time.h>

#define qc

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
	int a = 0;

	while (true) {
		cout << "1~100������ ���ڸ� �Է��ϼ��� (0�� ����) : ";
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

//��ǻ�Ϳ� ������������ �ϴ� ���α׷��� �ۼ��϶�.
#ifdef q5

int ComsChoice()
{
	srand((unsigned)time(NULL));

	int ri = rand() % 3 + 1;;

	switch (ri)
	{
		case 1: { cout << "��ǻ�� : ��" << endl; } break;
		case 2: { cout << "��ǻ�� : ��" << endl; } break;
		case 3: { cout << "��ǻ�� : ��" << endl; } break;
	}

	return ri;
}

void CheckWin(int player) {
	int coms = ComsChoice();

	if (coms == player) {
		cout << "�����ϴ�." << endl;
	}
	else if (coms - player == 2 || coms - player == -1) {
		cout << "�����ϴ�." << endl;
	}
	else {
		cout << "�̰���ϴ�." << endl;
	}
}

int main()
{
	int c;
	while (true) {
		cout << "�����ϼ���. 1. ��, 2. ��, 3. �� (0 ����)" << endl;
		cin >> c;

		if (c == 0) {
			return 0;
		}

		if (c >= 1 && c <= 3) {
			switch (c) {
				case 1: { cout << "�÷��̾� : ��" << endl; } break;
				case 2: { cout << "�÷��̾� : ��" << endl; } break;
				case 3: { cout << "�÷��̾� : ��" << endl; } break;
			}
			CheckWin(c);
		}
	}

}

#endif


//����ڷκ��� �ҵ��� �Է¹޾� �ҵ� ������ ���� �ҵ漼�� ����ϴ� ���α׷��� �ۼ��϶�. 
//(�ҵ� 1000�� ���� 8 % , 1000�� �ʰ� - 4000�� ���� 17 % , 4000�� �ʰ� - 8000�� ���� 26 % , 8000�� �ʰ� 35 % �� ����)
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
		cout << "���ҵ��� �������� �Է��ϼ���. (0�� ����) " << endl;
		cin >> _salary;

		if (_salary == 0) {
			return 0;
		}

		printf("���ҵ��� %d�����̸� �ҵ漼�� %d���Դϴ�.\n", _salary, get_tax_2018(_salary));
	}
}
#endif

//�� ���� ���̰� 100���� ���� �ﰢ�� �� ��Ÿ����� ������ �����ϴ� �ﰢ���� ã�� ������ ���̸� ����ϴ� ���α׷��� �ۼ��϶�. (���߹ݺ����� ����� ��)
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

//�־��� ������ �Ҽ�(Prime number)���� �˻��ϴ� �Լ��� �ۼ��ϰ�, �̸� �̿��� 1���� 100������ ��� �Ҽ��� ����϶�.
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

//2���� �������� �� ���� �Ÿ��� ����ϴ� ���α׷��� �ۼ��϶�.
#ifdef q9
float dist_2d(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main()
{
	float x1, y1, x2, y2;
	cout << "ù���� ���� ��ǥ�� �Է��ϼ���. (ex: 3.2 4.3)" << endl;
	cin >> x1 >> y1;

	cout << "�ι��� ���� ��ǥ�� �Է��ϼ���. (ex: 3.2 4.3)" << endl;
	cin >> x2 >> y2;

	printf("��1(%.2f, %.2f)�� ��2(%.2f,%.2f)������ �Ÿ��� %f�Դϴ�.", x1, y1, x2, y2, dist_2d(x1, y1, x2, y2));

	return 0;
}

#endif

//2�� �������� �Ǽ����� ����ϴ� �Լ��� �ۼ��϶�.
#ifdef qa
void quad_eqn(double a, double b, double c) {
	if (b*b - 4*a*c >= 0) {
		double plus = (-b + sqrt(b*b - 4*a*c)) / 2*a;
		double minus = (-b - sqrt(b*b - 4*a*c)) / 2*a;

		if (plus == minus) {
			cout << "�߱� : " << plus << endl;
		}
		else {
			cout << "ù��°�� : " << minus << " �ι�°�� : " << plus << endl;
		}
	}
	else {
		cout << "�Ǳ��� �����ϴ�." << endl;
	}

}

int main()
{
	double da, db, dc;
	cout << "a*x^2+b*x+c�� a,b,c�� �������� �����Ͽ� �Է��ϼ��� (ex : 2x^2+3x+4 -> 2 3 4 )" << endl;
	cin >> da >> db >> dc;

	quad_eqn(da, db, dc);
}
#endif

//save(int amount)�Լ��� ȣ���Ͽ� �����ϰ�, ȣ��ɶ����� �� ������� ����ϴ� ���α׷��� �ۼ��϶�.
#ifdef qb
int save(int amount) {
	static int total = 0;
	total += amount;

	printf("%d�� �����ؼ� ���� �� ���ݾ��� %d���Դϴ�. \n", amount, total);

	return total;
}

int main()
{
	while(true) {
		int money;
		cout << "�󸶸� �����Ͻðڽ��ϱ�? (0�� ����)" << endl;
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
	cout << "�� ������ ������ ���� ����ұ��?" << endl;
	cin >> end;

	cout << triple(end) << endl;
}
#endif