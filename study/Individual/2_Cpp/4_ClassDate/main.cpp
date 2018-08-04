#include "Date.h"

int main()
{
	//'Date'클래스의 'day_1'인스턴스 생성
	Date day_1;		//인자가 없는 생성자.

	//메소드 호출
	day_1.setDate(1990, 5, 18);
	day_1.memo = "내 생일";

	//퍼블릭 필드 직접 출력 (dot(.)연산자 사용)
	std::cout << day_1.memo << std::endl;
	std::cout << day_1.getYear() << "년" << day_1.getMonth() << "월" << day_1.getDay() << "일" << std::endl;


	//'Date'클래스의 'day_2'인스턴스 생성
	Date day_2(2000, 06, 15); //인자가 있는 생성자.
	day_2.memo = "동생 생일";

	std::cout << day_2.memo << std::endl;
	day_2.printDate();


	//인스턴스 동적 생성 (디폴트 생성자가 호출됨)
	Date* day_3 = new Date;

	//동적 생성된 객체의 메소드 호출
	day_3->memo = "오늘";

	//동적 생성된 객체의 퍼블릭 필드 직접 출력 (arrow(->)연산자 사용)
	std::cout << day_3->memo << std::endl;
	day_3->printDate();

	delete day_3;


	//동적 생성할 때 인수있는 생성자 호출하기
	Date* day_4 = new Date(2000, 01, 01);
	std::cout << day_4->memo << std::endl;

	day_4->memo = "새천년의 시작";

	std::cout << day_4->memo << std::endl;
	day_4->printDate();

	delete day_4;
}