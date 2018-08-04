#include "SalaryCalculator.h"

int main()
{
	//순수 가상 함수가 하나라도 있는 클래스를 추상 클래스라고 하며, 추상 클래스는 인스턴스화를 할 수 없다. (=객체를 만들 수 없다.)
	//Employee fvfuse;

	SalaryCalculator department;

	//직원 등록.
	department.AddEmployee(new Temporary("권상우", 1, 200));
	department.AddEmployee(new Temporary("조인성", 1, 220));
	department.AddEmployee(new Salaryman("감우성", 2, 3));
	department.AddEmployee(new Salaryman("강동원", 2, 5));
	department.AddEmployee(new Permanent("황정민", 3, 3));
	department.AddEmployee(new Salaryman("박중훈", 3, 15));
	department.AddEmployee(new Salaryman("최민식", 4, 20));
	department.AddEmployee(new Permanent("정진영", 4, 3));
	department.AddEmployee(new Temporary("안성기", 5, 50));
	department.AddEmployee(new Permanent("송강호", 5, 4));
	

	//최종적으로 이번달에 지불해야할 급여는?
	department.ShowList();
}