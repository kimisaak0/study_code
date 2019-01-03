#pragma once
#include <iostream>

struct edge
{
	bool exist;
	int weight;
};

class MatrixGraph
{
	int vertexCount;
	int** matrix;

public:
	bool AddEdge(int StartVertex, int EndVertex, int weight);
	void ShowMatrix();

public:
	MatrixGraph(int vertexCount);
	virtual ~MatrixGraph();
};

//-------------


MatrixGraph::MatrixGraph(int Count)
{
	//VertexCount로 정점을 동적할당하고 edge의 2차원 배열을 만든다. 
	vertexCount = Count;
	matrix = new int*[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		matrix[i] = new int[vertexCount];
		memset(matrix[i], -1, sizeof(int)*vertexCount);
	}
}


bool MatrixGraph::AddEdge(int StartVertex, int EndVertex, int weight)
{
	if (StartVertex >= vertexCount || StartVertex < 0 || EndVertex >= vertexCount || EndVertex < 0) {
		return false;
	}

	matrix[StartVertex][EndVertex] = weight;
	return true;
}

void MatrixGraph::ShowMatrix()
{
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			std::cout << matrix[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < vertexCount; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}