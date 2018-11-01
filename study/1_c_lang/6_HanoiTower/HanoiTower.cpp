#include <stdio.h>

void HanoiTab(int n, char from, char temp, char to);
void HanoiTower(int n, char from, char temp, char to);


int main()
{
	int n;
	printf("���� ������ �Է��ϼ��� : ");
	scanf_s("%d", &n);

	HanoiTab(n, 'A', 'B', 'C');
}

// 1. ��ũ�� �ѹ��� �ϳ��� �Űܾ� �Ѵ�.
// 2. ���� ���� ��ũ�� �Ʒ����� ��ũ���� Ŭ �� ����.

void HanoiTab(int n, char from, char temp, char to)
{
	if (n > 0)
	{
		//a�� c�� �ӽ�����ҷ� Ȱ���Ͽ� b�� ���´�.
		HanoiTab(n - 1, from, to, temp);
		
		printf("[%d]�� %c -> %c\n", n, from, to);

		//b�� a�� �ӽ�����ҷ� Ȱ���Ͽ� c�� ���´�.
		HanoiTab(n - 1, temp, from, to);
	}
}


// 1. ó�� n-1���� ��ũ�� A���� C�� �̿��Ͽ� B�� �̵��Ѵ�.
// 2. ������ n��° ��ũ�� A���� C�� �ű��.
// 3. n-1���� ��ũ�� �ٽ� B���� A�� �̿��Ͽ� C�� �̵��Ѵ�.
void HanoiTower(int n, char from, char temp, char to)
{
	if (n == 1)
	{
		printf("[%d]�� %c -> %c\n", n, from, to);
	}
	else {
		//a�� c�� �ӽ�����ҷ� Ȱ���Ͽ� b�� ���´�.
		HanoiTab(n - 1, from, to, temp);
		printf("[%d]�� %c -> %c\n", n, from, to);
		//b�� a�� �ӽ�����ҷ� Ȱ���Ͽ� c�� ���´�.
		HanoiTab(n - 1, temp, from, to);
	}
}

