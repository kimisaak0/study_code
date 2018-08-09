#include "header.h"

int main()
{
	vector<person> coll(5);
	
	//전역함수 호출
	for_each(coll.begin(), coll.end(), g_fun);
	for_each(coll.begin(), coll.end(), bind2nd(mem_fun_ref(&person::show), 1));
	foo(coll);

	vector<person*> coll2;
	coll2.push_back(new person);
	prtfoo(coll2);

	vector<person> vecList;
	generate_n(back_inserter(vecList), 10, setData);
	for_each(vecList.begin(), vecList.end(), bind2nd(mem_fun_ref(&person::show), 100));

	//mem_fun(&A::F)(class,x) ==> class->F(x)
	//mem_fun_ref(&B::F)(class,x) ==> class.F(x)
}