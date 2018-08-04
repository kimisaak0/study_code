#include <stdio.h>

void HanoiTab(int n, char from, char temp, char to);
void HanoiTower(int n, char from, char temp, char to);


int main()
{
	int n;
	printf("원반 갯수를 입력하세요 : ");
	scanf_s("%d", &n);

	HanoiTab(n, 'A', 'B', 'C');
}

// 1. 디스크는 한번에 하나씩 옮겨야 한다.
// 2. 위에 놓인 디스크는 아래쪽의 디스크보다 클 수 없다.

void HanoiTab(int n, char from, char temp, char to)
{
	if (n > 0)
	{
		//a를 c를 임시저장소로 활용하여 b로 놓는다.
		HanoiTab(n - 1, from, to, temp);
		
		printf("[%d]번 %c -> %c\n", n, from, to);

		//b를 a를 임시저장소로 활용하여 c로 놓는다.
		HanoiTab(n - 1, temp, from, to);
	}
}


// 1. 처음 n-1개의 디스크를 A에서 C를 이용하여 B로 이동한다.
// 2. 마지막 n번째 디스크를 A에서 C로 옮긴다.
// 3. n-1개의 디스크를 다시 B에서 A를 이용하여 C로 이동한다.
void HanoiTower(int n, char from, char temp, char to)
{
	if (n == 1)
	{
		printf("[%d]번 %c -> %c\n", n, from, to);
	}
	else {
		//a를 c를 임시저장소로 활용하여 b로 놓는다.
		HanoiTab(n - 1, from, to, temp);
		printf("[%d]번 %c -> %c\n", n, from, to);
		//b를 a를 임시저장소로 활용하여 c로 놓는다.
		HanoiTab(n - 1, temp, from, to);
	}
}

