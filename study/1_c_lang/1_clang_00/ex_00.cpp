#include <stdio.h>

int main()
{
	printf("KGCA ���Ӿ�ī����\n");

	printf("======= CODE 000 ======\n");
	int		i = 65;
	float	f = 123.456;
	
	printf("���� i�� �� : %d\n", i); // ����
	printf("���� g�� �� : %g\n", f); // %f / %e �߿� ������ ������� ��� (�ڸ��� ����)
	printf("���� f�� �� : %f\n", f); // �Ҽ��� 6�ڸ� ���
	printf("���� e�� �� : %f\n", f); // ������������ ��� (�ҹ��� e�� ���)
	printf("���� E�� �� : %f\n", f); // ������������ ��� (�빮�� E�� ���)

	printf("======= CODE 001 ======\n");
	printf("������ ���� ������ ���� ũ�� ���� �����ϰ� ��ü ���\n");
	printf("�Ҽ��� ���� �ڸ����� �����ϸ� �ش� �ڸ����� �ݿø��Ѵ�.\n");
	printf("����     5d�� ��	: | %5d |\n", i); // ����
	printf("����    05d�� ��	: | %05d |\n", i); // ����
	printf("����    -5d�� ��	: | %-5d |\n", i); // ����
	printf("����   8.4g�� ��	: | %8.4g I\n", f); //  %f / %e �߿� ������ ������� ��� (�ڸ��� ����)
	printf("����  -8.4g�� ��	: | %-8.4g I\n", f); //  %f / %e �߿� ������ ������� ��� (�ڸ��� ����)
	printf("����  20.4f�� ��	: | %020.4f I\n", f); //  �Ҽ��� 6�ڸ� ���
	printf("���� -20.4f�� ��	: | %-20.4f I\n", f); //  �Ҽ��� 6�ڸ� ���
	printf("����  20.4e�� ��	: | %20.4e I\n", f); // ������������ ��� (�ҹ��� e�� ���)
	printf("���� -20.4e�� ��	: | %-20.4e I\n", f); // ������������ ��� (�ҹ��� e�� ���)

	printf("======= CODE 002 =======\n\n");
	int		iValue;
	float	fValue;
	char	strValue[20];
	char	cValue;
	printf("������ �Է��Ͻÿ�: "); scanf_s("%d", &iValue); while (getchar() != '\n');
	printf("�Ǽ��� �Է��Ͻÿ�: "); scanf_s("%f", &fValue); while (getchar() != '\n');
	printf("����1�� �Է��Ͻÿ� : "); scanf_s("%c", &cValue); while (getchar() != '\n');
	printf("���ڿ��� �Է��Ͻÿ� : "); scanf_s("%s", strValue, sizeof(strValue)); while (getchar() != '\n');

	//while (getchar() != '\n'); ���۸� ����� �뵵

	//fflush()�� ǥ�ؿ� ��� ��Ʈ�� ����(stdout)�� �ִ� ������ ��� ����ϴ� ������ ���ǵǾ� ���� ��
	//�Է� ��Ʈ���� ����(stdin)�� ���ؼ��� ���ǵ� ������ �����Ƿ� ȣȯ���� ���ؼ��� ������� �ʴ� ���� ���ٰ� �Ѵ�.
	//������ vs2017������ ����� �۵����� �ʴ´�. 
	//���� ǥ�ؿ��� �Է¹��۸� ���� �Լ��� ���ǵǾ� ���� �ʴٰ� �Ѵ�.

	printf("\n");
	printf("  iValue = %d \n", iValue);
	printf("  fValue = %f \n", fValue);
	printf("  cValue = %c \n", cValue);
	printf("strValue = %s \n", strValue);

}