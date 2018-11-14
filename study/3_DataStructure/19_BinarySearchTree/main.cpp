#include "BST.h"
#include <iostream>

void print(int data) {
	std::cout << data << std::endl;
}


int main()
{
	BinarySearchTree bst;

	bst.AddNode(10);
	bst.AddNode(4);
	bst.AddNode(3);
	bst.AddNode(21);
	bst.AddNode(41);
	bst.AddNode(5);
	bst.AddNode(81);
	bst.AddNode(51);
	bst.AddNode(11);
	bst.AddNode(1);
	bst.AddNode(6);
	bst.AddNode(2);
	
	inorder(bst.Search(21), print);

}