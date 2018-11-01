#include <stdio.h>

void decR(int& R) { R--; }
void constR(const int& R) {  }
int& returnR_1(int& R) { return R; }
int returnR_2(int& R) { return R; }

int main()
{
	int iA = 0, iB = 1;

	int &rA = iA;

	//컴파일 에러 (초기화되지 않은 참조자 선언이다.)
	//int &rB;     

	//컴파일 에러 (참조자가 상수를 가리킬 수 없다.)
	//int &rC = 10;

	//참조자를 이용한 값 변경
	rA = 10;
	printf("%d \n", iA);

	//함수의 매개변수가 참조자

	//주소로 넘기지 않아도 된다.
	decR(iB);
	//컴파일 에러! 상수를 넘길 수는 없다.
	//decR(10);

	//참조가가 가리키는 변수를 바꿔봤다.
	printf("%d \n", rA);
	rA = iB;
	printf("%d \n", rA);

	//상수 참조자

	//상수 참조자는 상수를 참조할 수 있다.
	const int& rD = 10;

	//함수의 매개변수가 상수 참조자.
	//매개변수로 상수를 넘길 수 있다.
	constR(10);

	//함수의 반환값이 참조자여야 할 때
	// = 반환값을 참조자에 대입해야 할 때

	int& rE = returnR_1(rA);

	//컴파일 에러 (반환값이 상수인 것과 같다.)
	//int& rF = returnR_2(rA);

}
