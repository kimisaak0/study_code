#include "Date.h"

int main()
{
	//'Date'Ŭ������ 'day_1'�ν��Ͻ� ����
	Date day_1;		//���ڰ� ���� ������.

	//�޼ҵ� ȣ��
	day_1.setDate(1990, 5, 18);
	day_1.memo = "�� ����";

	//�ۺ� �ʵ� ���� ��� (dot(.)������ ���)
	std::cout << day_1.memo << std::endl;
	std::cout << day_1.getYear() << "��" << day_1.getMonth() << "��" << day_1.getDay() << "��" << std::endl;


	//'Date'Ŭ������ 'day_2'�ν��Ͻ� ����
	Date day_2(2000, 06, 15); //���ڰ� �ִ� ������.
	day_2.memo = "���� ����";

	std::cout << day_2.memo << std::endl;
	day_2.printDate();


	//�ν��Ͻ� ���� ���� (����Ʈ �����ڰ� ȣ���)
	Date* day_3 = new Date;

	//���� ������ ��ü�� �޼ҵ� ȣ��
	day_3->memo = "����";

	//���� ������ ��ü�� �ۺ� �ʵ� ���� ��� (arrow(->)������ ���)
	std::cout << day_3->memo << std::endl;
	day_3->printDate();

	delete day_3;


	//���� ������ �� �μ��ִ� ������ ȣ���ϱ�
	Date* day_4 = new Date(2000, 01, 01);
	std::cout << day_4->memo << std::endl;

	day_4->memo = "��õ���� ����";

	std::cout << day_4->memo << std::endl;
	day_4->printDate();

	delete day_4;
}