#include "MatrixGraph.h"

int main() 
{
	MatrixGraph mg(3);

	mg.AddEdge(0, 2, 4);
	mg.AddEdge(0, 2, 3);

	mg.ShowMatrix();

	

	return 0;
}