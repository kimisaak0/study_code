#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
	{
		// ������ ���� �Ҵ�, �⺻ void*���� int*�� ����ȯ
		printf("\n=====================\n");

		int* pPoint = (int*)malloc(sizeof(int));
		*pPoint = 100;
		printf("%0x���� : %d\n", pPoint + 0, *(pPoint + 0));
		free(pPoint);
	}

	{
		//������ ���� �迭 �Ҵ�
		printf("\n=====================\n");

		int* pPointArray = (int*)malloc(sizeof(int) * 10);
		for (int iCnt = 0; iCnt < 10; iCnt++) {
			pPointArray[iCnt] = iCnt * 10;
			printf("\n0x%08x���� : %d", &pPointArray[iCnt], *(pPointArray + iCnt));
		}
		free(pPointArray);
	}

	{
		//������ ������ ���� �迭 �Ҵ�
		printf("\n=====================\n");
		char* pCharPoint = NULL;
		int iCount = 0;
		pCharPoint = (char*)malloc(sizeof(char) * 100);
		//��Ƽ����Ʈ���� _getche()==0��� ���� Ȯ��Ű�� �ԷµǾ��ٴ� ���̴�.
		//����Ű �Ǵ� home, end, insert ���� 0x00E0�� ��ȯ�Ѵ�.

		do {
			pCharPoint[iCount++] = _getche(); // ���� ���� ������ �迭�� �����Ѵ�.

			int iValue = 0;
			iValue = _getch();				// �ι�° ���� ���� iValue�� �����Ѵ�.

			if (iValue != 0 && iValue != 0x00E0) {	// �ι�° �������� Ȯ��Ű�� �ƴϰ� ����Ű���� �ƴϸ� 
				pCharPoint[iCount++] = iValue;		// ���� ������ �迭�� �����Ѵ�.
				printf("*"); // password			// �ι�° ���� ����Ǹ� * ���
			}
		} while (pCharPoint[iCount - 1] != '\r'); //EnterŰ�� 'Wr' + 'Wn'�̹Ƿ� �ѹ���Ʈ�� �Է¹��� ���� '\r'���� Ȯ���ؾ��Ѵ�.

												  //���ĺ� �Ǵ� ����Ű�� �Է½� Ȯ��Ű�ڵ�(�ι��� �߰�)�� ��ȯ�ϴ� ������ �ý��ۿ� ���� �߻��Ѵ�.
												  /*do {
												  pCharPoint[iCount++] = _getche();
												  } while (pCharPoint[iCount - 1] != '\r');*/


		pCharPoint[iCount - 1] = 0;
		printf("\n");
		printf("0x%08x���� : %s \n", pCharPoint, pCharPoint);
		for (int iCnt = 0; iCnt < iCount; iCnt++) {
			printf("0x%08x���� : %c \n", pCharPoint + iCnt, *(pCharPoint + iCnt));
		}
		free(pCharPoint);
	}

	{
		//������ �迭 ���� �Ҵ�
		printf("\n=====================\n");
		int* IpPoint[10]; //������ �迭 ����

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			IpPoint[iCnt] = (int*)malloc(sizeof(int));	//�� ������ �迭�� �����Ҵ�
			*IpPoint[iCnt] = iCnt * 10;					//�� �Է�
			printf("0x%08x���� : %d \n", IpPoint + iCnt, *IpPoint[iCnt]);	//�ּҿ� �� ���
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) { //������ �迭�� ���� �Ҵ�� ���� ���� Ǯ����� �Ѵ�.
			free(IpPoint[iCnt]);
		}
	}


	{
		printf("\n=====================\n");

		//2���� �迭 �ʱ�ȭ �� ����
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

	//���� ������ �Ҵ�
	{
		printf("\n=====================\n");
		printf("\n=====����������======\n");

		int *pPtr = NULL;
		int **ppPtr = NULL;
		int num = 10;

		pPtr = &num;

		//�������� �޸� �ּҴ� �Ϲ������Ϳ� ������ �� �����Ƿ� �ݵ�� ���������Ϳ� �����ؾ� �Ѵ�.
		ppPtr = &pPtr;
		printf("%d\n", **ppPtr);

		//������������ �Ҵ��� �ý��� ��Ʈ�� ����ؾ��Ѵ�.
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
		//8����Ʈ ������ �迭? 4����Ʈ ������ �迭?
		//intptr_t ����ϸ� �ý��� ��Ʈ���� ���� ��ȯ��.

		int **ppPoint = NULL;
		ppPoint = (int**)malloc(sizeof(intptr_t) * 10); //���� �����Ϳ� ������ �ּҸ� ������ �� �ִ� ���� �Ҵ�.

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			ppPoint[iCnt] = (int*)malloc(sizeof(intptr_t) * 10); // �� ������ ��Ʈ���� ������ �� �ִ� ���� �Ҵ�.
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) {	//���� �ʱ�ȭ (�翬�� �迭�� �����ϴ°� ����)
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
		printf("\n====== ������ �迭=========\n");
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
		//char�� int�� ũ�����̰� �� �� �⺻������ ����. 
		//int�迭 ���� �ι��ڰ� ���� ���ڿ��� ó���� �� �ִ�.
		//���� int�� �ƽ�Ű�ڵ尪���� 

		for (int iCnt = 0; iCnt < 6; iCnt++) {
			printf("[%d] = %s \n", iCnt, pArray[iCnt]);
		}

		for (int iCnt = 0; iCnt < 6; iCnt++) {
			free(pArray[iCnt]);
		}
	}
}