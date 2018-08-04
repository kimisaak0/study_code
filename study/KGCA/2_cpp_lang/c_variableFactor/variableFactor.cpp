#include "variableFactor.h"

int main()
{
	g_debug = true;
	debugOut("int %d\n", 5);
	debugOut("String %s and int %d\n", "hello", 5);
	debugOut("Many inis : %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);

	printInts(5, 1, 2, 3, 4, 5);

	int a = makeSum({ 1,2,3,4,5 });
	cout << a << endl;
	//int b = makeSum({ 1,2,3,3.0 }); // 한가지 타입만 가능하기 때문에 오류남.
}