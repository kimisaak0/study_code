#include "stack.cpp"

#include <stack>


int main()
{
	std::stack<int> stlstack;

	stlstack.push(1);
	stlstack.push(2);
	stlstack.emplace(6);
	stlstack.push(3);

	std::cout << stlstack.top();
	stlstack.pop();

}