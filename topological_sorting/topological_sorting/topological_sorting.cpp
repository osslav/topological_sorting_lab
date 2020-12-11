//#include <iostream>
#include "boolean_matrix.h"


BoolMatrix enterGraphMatrix()						//возможен граф без вершин
{
	std::cout << "Enter count vertex: ";
	int countVertex;
	std::cin >> countVertex;
	while (countVertex < 0)
	{
		std::cout << "Error. Count vertex must be >= 0. Enter again: ";
		std::cin >> countVertex;
	}
	
	BoolMatrix graph(countVertex, countVertex);
	
	if (countVertex != 0)
	{
		std::cout << "Input of graph edges.\nIf you want to go out enter \"-1\". \n";
		bool flag = true;
		while (flag)
		{
			std::cout << "Enter graph edge: ";
			int startEdge, endEdge;

			std::cin >> startEdge;
			if (startEdge != -1)
			{
				std::cin >> endEdge;
				while ((startEdge <= 0) || (startEdge > countVertex) || (startEdge <= 0) || (startEdge > countVertex))
				{
					std::cout << "Enter graph edge again: ";
					std::cin >> startEdge;
					std::cin >> endEdge;
				}

				graph.setOneInd(startEdge - 1, endEdge - 1);
			}
			else flag = false;
		}
	}


	return graph;
}

int* topologicalSorting(BoolMatrix graph)
{
	int countVertex = graph.getCountCol();
	if (countVertex == 0) return nullptr;

	BoolVector flagColoumn(countVertex, true);
	
	int* result = new int[countVertex + 1];
	result[0] = countVertex;
	int counterResult = 1;

	bool flagEnd = true;
	BoolVector disjunctionStr = graph.disjunctionAllStr();
	while (flagEnd)
	{
		bool flagCheckCycles = true;
		for (int i = 0; i < countVertex; i++)
		{
			if (flagColoumn[i] && !disjunctionStr[i])
			{
				flagColoumn.setZeroInd(i);
				graph[i].setZero();
				result[counterResult] = i;
				counterResult++;

				flagCheckCycles = false;
			}
		}
		if (flagCheckCycles)
		{
			delete[] result;
			return nullptr;
		}

		disjunctionStr = graph.disjunctionAllStr();
		flagEnd = flagColoumn.searchWeight();
	}

	
	return result;
}


int main()
{
	BoolMatrix A = enterGraphMatrix();
	A.outputInverse();

	int* result = topologicalSorting(A);

	if (result == nullptr)
		if (A.getCountCol() == 0) std::cout << "Graph is empty\n";
		else
			std::cout << "Graph have cycle\n";
	else
		for (int i = 0; i < result[0]; i++)
			std::cout << (result[i + 1] + 1) << ' ';

	return 0;
}
