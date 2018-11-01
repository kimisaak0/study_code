#include "FunctionTemplates.h"

int main()
{
	int x = 10;
	int y = 20;
	std::cout << x << ", " << y << std::endl;
	Swap(x, y); //int�� ���ڷ� �޴� swap�Լ��� ȣ���
	std::cout << x << ", " << y << std::endl;
	std::cout << add(x, y) << std::endl;

	double a = 10.1;
	double b = 20.2;
	std::cout << a << ", " << b << std::endl;
	Swap(a, b); //double�� ���ڷ� �޴� Swap�Լ��� ȣ���
	std::cout << a << ", " << b << std::endl;
	std::cout << add(a, b) << std::endl;

	char c1[5] = "asdf";
	char c2[5] = "qwer";
	std::cout << add(c1, c2) << std::endl;

	std::string s1 = "abc";
	std::string s2 = "def";
	std::cout << s1 << ", " << s2 << std::endl;
	Swap(s1, s2); //string�� ���ڷ� �޴� Swap�Լ��� ȣ���
	std::cout << s1 << ", " << s2 << std::endl;
	std::cout << add(s1, s2) << std::endl;


}