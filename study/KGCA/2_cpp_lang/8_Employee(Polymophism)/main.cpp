#include "SalaryCalculator.h"

int main()
{
	//���� ���� �Լ��� �ϳ��� �ִ� Ŭ������ �߻� Ŭ������� �ϸ�, �߻� Ŭ������ �ν��Ͻ�ȭ�� �� �� ����. (=��ü�� ���� �� ����.)
	//Employee fvfuse;

	SalaryCalculator department;

	//���� ���.
	department.AddEmployee(new Temporary("�ǻ��", 1, 200));
	department.AddEmployee(new Temporary("���μ�", 1, 220));
	department.AddEmployee(new Salaryman("���켺", 2, 3));
	department.AddEmployee(new Salaryman("������", 2, 5));
	department.AddEmployee(new Permanent("Ȳ����", 3, 3));
	department.AddEmployee(new Salaryman("������", 3, 15));
	department.AddEmployee(new Salaryman("�ֹν�", 4, 20));
	department.AddEmployee(new Permanent("������", 4, 3));
	department.AddEmployee(new Temporary("�ȼ���", 5, 50));
	department.AddEmployee(new Permanent("�۰�ȣ", 5, 4));
	

	//���������� �̹��޿� �����ؾ��� �޿���?
	department.ShowList();
}