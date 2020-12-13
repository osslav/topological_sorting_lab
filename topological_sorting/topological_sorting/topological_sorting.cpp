//#include <iostream>
#include "boolean_matrix.h"

struct Trailer;
struct Lider
{
	int key;					
	int count;					
	Lider* next;					
	Trailer* trailer;	

	Lider() { count = 0;  key = -1;  next = nullptr; trailer = nullptr; };

	void output();
	void topologicalSorting();
	//void clearMemory();
};

struct Trailer
{
	Lider* lider;					
								
	Trailer* next;

	Trailer() { next = nullptr; lider = nullptr; };
};


Lider* enterGraphList()
{
	Lider* graph = nullptr;

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
			

			Lider* startEdgeInGraph = graph, * endEdgeInGraph = graph;
			
			while ((startEdgeInGraph != nullptr) && (startEdgeInGraph->key != startEdge))
			{
				startEdgeInGraph = startEdgeInGraph->next;
			}
			if (startEdgeInGraph == nullptr)
			{
				startEdgeInGraph = new Lider;
				startEdgeInGraph->next = graph;
				startEdgeInGraph->key = startEdge;
				startEdgeInGraph->count = 0;
				graph = startEdgeInGraph;
			}


			while ((endEdgeInGraph != nullptr) && (endEdgeInGraph->key != endEdge))
			{
				endEdgeInGraph = endEdgeInGraph->next;
			}
			if (endEdgeInGraph == nullptr)
			{
				endEdgeInGraph = new Lider;
				endEdgeInGraph->next = graph;
				endEdgeInGraph->key = endEdge;
				endEdgeInGraph->count = 0;
				graph = endEdgeInGraph;
			}

			endEdgeInGraph->count++;
			
			Trailer* newTrailer = new Trailer;
			newTrailer->lider = endEdgeInGraph;
			newTrailer->next = startEdgeInGraph->trailer;

			startEdgeInGraph->trailer = newTrailer;
		}
		else flag = false;
	}

	return graph;
}


void Lider::output()
{
	Lider* vertexGraph = this;
	while (vertexGraph != nullptr)
	{
		std::cout << "Vertex \"" << vertexGraph->key << "\"\n";
		std::cout << "  count input edges: " << vertexGraph->count << '\n';
		std::cout << "  output edges:\n";
		Trailer* edgeGraph = vertexGraph->trailer;
		while (edgeGraph != nullptr)
		{
			std::cout << "  (" << vertexGraph->key << "," << edgeGraph->lider->key << ")\n";
			edgeGraph = edgeGraph->next;
		}
		std::cout << '\n';
		vertexGraph = vertexGraph->next;
	}
}

void  Lider::topologicalSorting()
{
	if (this == nullptr) return;
	
	Lider* newGraph = nullptr;

	Lider* vertexGraph = this;

	bool checkCycle = true;
	while (vertexGraph != nullptr)
	{
		if (vertexGraph->count == 0)
		{
			checkCycle = false;
			Lider* oldHeadNewGraph = newGraph;

			newGraph = new Lider;
			newGraph->count = 0;
			newGraph->trailer = vertexGraph->trailer;
			newGraph->key = vertexGraph->key;
			newGraph->next = oldHeadNewGraph;
		}
		
		vertexGraph = vertexGraph->next;
	}
	if (checkCycle)
	{
		std::cout << "Graph have cycle\n";
		return;
	}

	while (newGraph != nullptr)
	{
		Lider* p = newGraph;
		newGraph = newGraph->next;

		while (p->trailer != nullptr)
		{
			p->trailer->lider->count--;
			if (p->trailer->lider->count == 0)
			{
				Lider* temp = new Lider; 
				temp->key = p->trailer->lider->key;
				temp->trailer = p->trailer->lider->trailer;
				temp->count = 0; 
				temp->next = newGraph;
				newGraph = temp;
			}
			p->trailer = p->trailer->next;
			
		}

		std::cout << p->key << ' ';
		delete p;
	}

	checkCycle = false;
	vertexGraph = this;
	while (vertexGraph != nullptr)
	{
		if (vertexGraph->count != 0)
		{
			vertexGraph->count = 0;
			checkCycle = true;
		}
		vertexGraph = vertexGraph->next;
	}
	if (checkCycle) std::cout << " Graph have cycle.\n";

	vertexGraph = this;
	while (vertexGraph != nullptr)
	{
		Trailer* temp = vertexGraph->trailer;
		while (temp != nullptr)
		{
			temp->lider->count++;
			temp = temp->next;			
		}
		vertexGraph = vertexGraph->next;
	}

	std::cout << '\n';
}


void clearMemory(Lider* &ld)
{
	while (ld != nullptr)
	{
		
		while (ld->trailer != nullptr)
		{
			Trailer* oldTr = ld->trailer;
			ld->trailer = ld->trailer->next;
			delete oldTr;
		}
		
		Lider* oldLd = ld;
		ld = ld->next;
		delete oldLd;
	}
}

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
	if (false)
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
	}
	else
	{
		Lider* A = enterGraphList();
		A->output();
		A->topologicalSorting();

		//A->output();

		clearMemory(A);
	}

	return 0;
}
