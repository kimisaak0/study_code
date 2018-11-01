#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
	{
		// 포인터 변수 할당, 기본 void*에서 int*로 형변환
		printf("\n=====================\n");

		int* pPoint = (int*)malloc(sizeof(int));
		*pPoint = 100;
		printf("%0x번지 : %d\n", pPoint + 0, *(pPoint + 0));
		free(pPoint);
	}

	{
		//포인터 변수 배열 할당
		printf("\n=====================\n");

		int* pPointArray = (int*)malloc(sizeof(int) * 10);
		for (int iCnt = 0; iCnt < 10; iCnt++) {
			pPointArray[iCnt] = iCnt * 10;
			printf("\n0x%08x번지 : %d", &pPointArray[iCnt], *(pPointArray + iCnt));
		}
		free(pPointArray);
	}

	{
		//문자형 포인터 변수 배열 할당
		printf("\n=====================\n");
		char* pCharPoint = NULL;
		int iCount = 0;
		pCharPoint = (char*)malloc(sizeof(char) * 100);
		//멀티바이트에서 _getche()==0라는 것은 확장키가 입력되었다는 뜻이다.
		//방향키 또는 home, end, insert 등은 0x00E0을 반환한다.

		do {
			pCharPoint[iCount++] = _getche(); // 누른 값을 포인터 배열에 저장한다.

			int iValue = 0;
			iValue = _getch();				// 두번째 누른 값을 iValue에 저장한다.

			if (iValue != 0 && iValue != 0x00E0) {	// 두번째 누른값이 확장키가 아니고 방향키등이 아니면 
				pCharPoint[iCount++] = iValue;		// 값을 포인터 배열에 저장한다.
				printf("*"); // password			// 두번째 값이 저장되면 * 출력
			}
		} while (pCharPoint[iCount - 1] != '\r'); //Enter키는 'Wr' + 'Wn'이므로 한바이트씩 입력받을 때는 '\r'으로 확인해야한다.

												  //알파벳 또는 숫자키를 입력시 확장키코드(널문자 추가)로 반환하는 문제가 시스템에 따라 발생한다.
												  /*do {
												  pCharPoint[iCount++] = _getche();
												  } while (pCharPoint[iCount - 1] != '\r');*/


		pCharPoint[iCount - 1] = 0;
		printf("\n");
		printf("0x%08x번지 : %s \n", pCharPoint, pCharPoint);
		for (int iCnt = 0; iCnt < iCount; iCnt++) {
			printf("0x%08x번지 : %c \n", pCharPoint + iCnt, *(pCharPoint + iCnt));
		}
		free(pCharPoint);
	}

	{
		//포인터 배열 변수 할당
		printf("\n=====================\n");
		int* IpPoint[10]; //포인터 배열 선언

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			IpPoint[iCnt] = (int*)malloc(sizeof(int));	//각 포인터 배열에 동적할당
			*IpPoint[iCnt] = iCnt * 10;					//값 입력
			printf("0x%08x번지 : %d \n", IpPoint + iCnt, *IpPoint[iCnt]);	//주소와 값 출력
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) { //포인터 배열에 각각 할당된 것은 각각 풀어줘야 한다.
			free(IpPoint[iCnt]);
		}
	}


	{
		printf("\n=====================\n");

		//2차원 배열 초기화 및 접근
		int iValue[3][2] = { { 10,20 },{ 30,40 },{ 50,60 } };

		for (int iCnt = 0; iCnt < 3; iCnt++) {
			printf("*(iValue + %d) : %p \t iValue[%d] : %p \n",
				iCnt, *(iValue + iCnt), iCnt, iValue[iCnt]);
		}

		printf("\n");

		for (int iCnt = 0; iCnt < 3; iCnt++) {
			for (int kCnt = 0; kCnt < 2; kCnt++) {
				printf("*(*(iValue + %d) + %d) : %d \t *(iValue[%d] +%d) : %d \n",
					iCnt, kCnt, *(*(iValue + iCnt) + kCnt),
					iCnt, kCnt, *((iValue[iCnt]) + kCnt));
			}
		}
	}

	//이중 포인터 할당
	{
		printf("\n=====================\n");
		printf("\n=====이중포인터======\n");

		int *pPtr = NULL;
		int **ppPtr = NULL;
		int num = 10;

		pPtr = &num;

		//포인터의 메모리 주소는 일반포인터에 저장할 수 없으므로 반드시 이중포인터에 저장해야 한다.
		ppPtr = &pPtr;
		printf("%d\n", **ppPtr);

		//이중포인터의 할당은 시스템 비트를 고려해야한다.
		unsigned char *arr[100];
		unsigned char size = sizeof(arr);
		//32 - bit : sizeof(arr) = 400;
		//64 - bit : sizeof(arr) = 800;

#ifdef _WIN64
		//typedef __int64          intptr_t;
		//__int64 == long long
		printf("64 - bit size = %d \n", sizeof(arr));
#elif _WIN32
		//typedef int              intptr_t;
		printf("\n32 - bit size = %d", sizeof(arr));
#endif	
		//8바이트 포인터 배열? 4바이트 포인터 배열?
		//intptr_t 사용하면 시스템 비트수에 따라 변환됨.

		int **ppPoint = NULL;
		ppPoint = (int**)malloc(sizeof(intptr_t) * 10); //이중 포인터에 포인터 주소를 저장할 수 있는 공간 할당.

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			ppPoint[iCnt] = (int*)malloc(sizeof(intptr_t) * 10); // 각 공간에 인트값을 저장할 수 있는 공간 할당.
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) {	//내용 초기화 (당연히 배열로 접근하는게 좋다)
			for (int kCnt = 0; kCnt < 10; kCnt++) {
				ppPoint[iCnt][kCnt] = iCnt * 10 + kCnt;
			}
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			printf("\n");
			for (int kCnt = 0; kCnt < 10; kCnt++) {
				printf("[%d,%d] = %d \n", iCnt, kCnt, ppPoint[iCnt][kCnt]);
				printf("[%d,%d] = %d \n", iCnt, kCnt, *(ppPoint[iCnt] + kCnt));
			}
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			free(ppPoint[iCnt]);
		}

		free(ppPoint);
	}

	{
		printf("\n====== 포인터 배열=========\n");
		char* pArray[6];

		for (int iCnt = 0; iCnt < 6; iCnt++) {
			pArray[iCnt] = (char*)malloc(sizeof(char) * 4);
		}

		for (int iCnt = 0; iCnt < 6; iCnt++) {
			for (int jCnt = 0; jCnt < 3; jCnt++) {
				pArray[iCnt][jCnt] = 65 + (iCnt * 3) + jCnt;
			}
			pArray[iCnt][3] = 0;
		}
		//char와 int는 크기차이가 날 뿐 기본적으로 같다. 
		//int배열 끝에 널문자가 들어가면 문자열로 처리할 수 있다.
		//물론 int의 아스키코드값으로 

		for (int iCnt = 0; iCnt < 6; iCnt++) {
			printf("[%d] = %s \n", iCnt, pArray[iCnt]);
		}

		for (int iCnt = 0; iCnt < 6; iCnt++) {
			free(pArray[iCnt]);
		}
	}
}