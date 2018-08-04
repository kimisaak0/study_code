
//basic, expert
#define expert

#ifdef basic

//화씨 온도를 섭씨 온도로 변환하는 프로그램.

//헤더파일 추가 및 네임스페이스 설정
#include <iostream>
//using namespace std;
using std::cout;
using std::endl;
using std::cin;

int main()
{
	//변수 선언 및 초기화
	//int f_temp = 60;
	//int c_temp;
	double f_temp;
	double c_temp;
	
	cout << "화씨 온도를 입력하세요 : "; cin >> f_temp;

	//계산 결과를 c_temp에 대입
	//c_temp = 5 / 9 * (f_temp - 32);
	c_temp = 5 / 9.0 * (f_temp - 32); // or  c_temp = 5 / (double)9 * (f_temp - 32); 

	//문자열 출력
	//cout << "섭씨 온도는 " << c_temp << "입니다." << endl;
	cout << "섭씨 온도는 " << c_temp << "입니다.\n";

	return 0;
}

#endif

// 1. 실행 결과 : "섭씨 온도는 0입니다."
//    빌드 단축키 : 없음, 디버그 단축키 : F5, 한 단계씩 실행 : F11, 프로시저 단위로 실행 : F10
// 2. 주석 달기
// 3. endl 대신에 "\n"써보기
// 4. using문장 삭제시 :  "C2065 : 선언되지 않은 식별자입니다." 
//    개인적으로 전체 네임스페이스를 사용하는 것보다는 필요한 객체의 네임스페이스만 사용하는걸 선호.
// 5. c_temp의 값이 0으로 나오는 이유 : 나누기 연산자는 피연산자가 모두 정수이면 몫만 정수값으로 반환하기 때문.
// 6. 디버그하며 조사식 확인하기. 
// 7. 프로그램 수정하기 : 둘 중 하나만 실수형태로 바꿔도 결과값을 실수값으로 반환함. 
// 8. 화씨 온도를 사용자에게 입력받기.
// 9. 화씨 온도와 섭씨 온도를 실수로 처리하기.
// 10. 섭씨 온도를 화씨 온도로 변환하는 프로그램 만들기.

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
		cout << "메뉴" << endl;
		cout << "1. 화씨 -> 섭씨" << endl;
		cout << "2. 섭씨 -> 화씨" << endl;
		cout << "그외. 종료" << endl;
		cin >> sw;


		double degree;
		switch (sw) {
			case 1: {
				cout << "화씨 온도 입력 : "; cin >> degree;
				cout << "화씨 " << degree << "는 섭씨 " << f_c(degree) << "입니다" << endl;
				break;
			}

			case 2: {
				cout << "섭씨 온도 입력 : "; cin >> degree;
				cout << "섭씨 " << degree << "는 화씨 " << c_f(degree) << "입니다" << endl;
				break;
			}

			default: {
				return 0;
			}
		}
	}
}

#endif
