#include "Graph.h"
#include "DynamicArray.h"
#include <cstdlib>
#include <chrono>
using namespace std;



int main()
{
	Graph g(9, false);
	g.addEdge(0, 1, 10);
	g.addEdge(0, 2, 12);
	g.addEdge(1, 2, 9);
	g.addEdge(1, 3, 8);
	g.addEdge(3, 6, 8);
	g.addEdge(3, 4, 7);
	g.addEdge(4, 2, 3);
	g.addEdge(4, 5, 3);
	g.addEdge(2, 5, 1);
	g.addEdge(5, 7, 6);
	g.addEdge(3, 7, 5);
	g.addEdge(6, 8, 2);
	g.addEdge(7, 8, 11);
	g.addEdge(6, 7, 9);
	g.printAdjList();
	DynamicArray<Edge> MST = g.kruskalMST();
	cout << "minimum spanning tree edges: " << endl;
	MST.print();

	
	
	
	/*DynamicArray<DynamicArray<int>> da(1);
	for (int i = 0; i < 10; i++)
	{
		DynamicArray<int> ints(1);
		da.append(ints);
		for (int j = i; j < i + 10; j++)
		{
			da[i].append(j);
		}
	}
	da.print();*/

	/*int eles;
	cout << "Enter a number of elements: ";
	cin >> eles;
	DisjointSet<int> ds;
	for (int i = 0; i < eles; i++)
	{
		ds.makeSet(i);
	}

	char choice;
	do
	{
		choice = 'y';
		cout << "Union? (y/n): ";
		cin >> choice;

		if (choice == 'y')
		{
			int e1, e2;
			cout << "Element 1: ";
			cin >> e1;
			cout << "Element 2: ";
			cin >> e2;
			ds.Union(e1, e2);
			ds.print();
		}
	} while (choice == 'y');*/

	return 0;
}