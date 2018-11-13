#include "ExpressionTree.h"

int main()
{
	ExpressionTree a;

	a.InputFormula("3+2*5");

	a.inorder(a.ExpTree);
	
	std::cout << '=' << a.calculate(a.ExpTree);
}