#include "child.h"

void child::Humanity()
{
	cout << "넘치는 인간미" << endl;
}

void child::Character()
{
	cout << "불 같은 성품" << endl;
}
void child::Apperance()
{
	parents::Appearance();		  //기반 클래스에서 정의한 기능
	cout << "훤칠한 키" << endl;  //파생 클래스에서 확장된 기능
}

//child::child()
//{
//	cout << "child 생성자" << endl;
//}

child::child() : parents(1000)
{
	cout << "--------child 생성자" << endl;
}

child::~child()
{
	cout << "--------child 소멸자" << endl;
}
