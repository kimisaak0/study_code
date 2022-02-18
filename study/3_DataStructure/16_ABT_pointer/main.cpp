#include "BinaryTree.h"
#include <iostream>

void print(int data) {
	std::cout << data << std::endl;
}

int main()
{
	BinaryTree<int> bt2(1);

	bt2.connectLeft(bt2.getRoot(), MakeNode(2));
	bt2.connectRight(bt2.getRoot(), MakeNode(3));
	bt2.connectLeft(bt2.getLeft(bt2.getRoot()), MakeNode(4));

	bt2.connectRight(bt2.getRight(bt2.getRoot()), MakeNode(7));

	postorder(bt2.getRoot(), print);

}