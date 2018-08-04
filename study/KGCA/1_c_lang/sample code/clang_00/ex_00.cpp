#include <stdio.h>

int main()
{
	printf("KGCA 게임아카데미\n");

	printf("======= CODE 000 ======\n");
	int		i = 65;
	float	f = 123.456;
	
	printf("변수 i의 값 : %d\n", i); // 정수
	printf("변수 g의 값 : %g\n", f); // %f / %e 중에 적당한 방식으로 출력 (자리수 맞춤)
	printf("변수 f의 값 : %f\n", f); // 소수점 6자리 출력
	printf("변수 e의 값 : %f\n", f); // 지수형식으로 출력 (소문자 e를 사용)
	printf("변수 E의 값 : %f\n", f); // 지수형식으로 출력 (대문자 E를 사용)

	printf("======= CODE 001 ======\n");
	printf("숫자의 폭이 지정폭 보다 크면 폭은 무시하고 전체 출력\n");
	printf("소수점 이하 자리수를 지정하면 해당 자리수로 반올림한다.\n");
	printf("변수     5d의 값	: | %5d |\n", i); // 정수
	printf("변수    05d의 값	: | %05d |\n", i); // 정수
	printf("변수    -5d의 값	: | %-5d |\n", i); // 정수
	printf("변수   8.4g의 값	: | %8.4g I\n", f); //  %f / %e 중에 적당한 방식으로 출력 (자리수 맞춤)
	printf("변수  -8.4g의 값	: | %-8.4g I\n", f); //  %f / %e 중에 적당한 방식으로 출력 (자리수 맞춤)
	printf("변수  20.4f의 값	: | %020.4f I\n", f); //  소수점 6자리 출력
	printf("변수 -20.4f의 값	: | %-20.4f I\n", f); //  소수점 6자리 출력
	printf("변수  20.4e의 값	: | %20.4e I\n", f); // 지수형식으로 출력 (소문자 e를 사용)
	printf("변수 -20.4e의 값	: | %-20.4e I\n", f); // 지수형식으로 출력 (소문자 e를 사용)

	printf("======= CODE 002 =======\n\n");
	int		iValue;
	float	fValue;
	char	strValue[20];
	char	cValue;
	printf("정수를 입력하시오: "); scanf_s("%d", &iValue); while (getchar() != '\n');
	printf("실수를 입력하시오: "); scanf_s("%f", &fValue); while (getchar() != '\n');
	printf("문자1을 입력하시오 : "); scanf_s("%c", &cValue); while (getchar() != '\n');
	printf("문자열을 입력하시오 : "); scanf_s("%s", strValue, sizeof(strValue)); while (getchar() != '\n');

	//while (getchar() != '\n'); 버퍼를 지우는 용도

	//fflush()는 표준에 출력 스트림 버퍼(stdout)에 있는 내용을 모두 출력하는 것으로 정의되어 있을 뿐
	//입력 스트림의 버퍼(stdin)에 대해서는 정의된 내용이 없으므로 호환성을 위해서는 사용하지 않는 것이 좋다고 한다.
	//실제로 vs2017에서는 제대로 작동하지 않는다. 
	//또한 표준에는 입력버퍼를 비우는 함수가 정의되어 있지 않다고 한다.

	printf("\n");
	printf("  iValue = %d \n", iValue);
	printf("  fValue = %f \n", fValue);
	printf("  cValue = %c \n", cValue);
	printf("strValue = %s \n", strValue);

}