#include "BinaryTree.h"
#include <iostream>

void print(int data) {
	std::cout << data << std::endl;
}

int main()
{
	BinaryTree<int> bt(0);
	std::cout << CheckData(bt.getRoot()) << std::endl;

	BinaryTree<int> bt2(1);

	bt2.connectLeft(bt2.getRoot(), MakeNode(2));
	std::cout << CheckData(bt2.getLeft(bt2.getRoot())) << std::endl;

	preorder(bt2.getRoot(), print);

}