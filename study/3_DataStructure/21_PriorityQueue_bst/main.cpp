#include "PriorityQueue_bst.h"
#include <iostream>

int main()
{

	PQ_BST pq;

	pq.Add(4);
	pq.Add(3);
	pq.Add(1);
	pq.Add(10);
	pq.Add(7);
	pq.Add(5);
	pq.Add(8);
	pq.Add(9);

	std::cout << pq.Remove() << std::endl;
	std::cout << pq.Remove() << std::endl;
	std::cout << pq.Remove() << std::endl;
	std::cout << pq.Remove() << std::endl;
	std::cout << pq.Remove() << std::endl;
	std::cout << pq.Remove() << std::endl;
	std::cout << pq.Remove() << std::endl;
	std::cout << pq.Remove() << std::endl;

}