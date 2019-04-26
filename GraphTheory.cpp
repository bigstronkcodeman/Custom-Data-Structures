#include "Graph.h"
#include "DynamicArray.h"
#include "DisjointSet.h"
#include <string>
using namespace std;



int main()
{
	Graph g(6, true);
	g.addEdge(0, 3);
	g.addEdge(0, 1);
	g.addEdge(1, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 4);
	g.addEdge(3, 1);
	g.addEdge(4, 3);
	g.addEdge(5, 5);
	g.printEdgeList();
	g.printAdjList();
	g.DFS(0);
	g.DFS(2);
	g.classifyEdges();
	g.printTimes();
	g.printEdgeList();

	cout << "\ntransposing...\n\n";

	g.transpose();
	g.printEdgeList();
	g.printAdjList();
	g.DFS(1);
	g.DFS(5);
	g.classifyEdges();
	g.printTimes();
	g.printEdgeList();

	
	
	
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

	/*DisjointSet<int> ds;
	for (int i = 0; i < 15; i++)
	{
		ds.makeSet(i);
	}
	ds.Union(0, 1);
	ds.Union(3, 2);
	ds.Union(2, 1);
	ds.Union(5, 1);
	ds.Union(10, 14);
	ds.Union(9, 10);
	ds.print();*/


	return 0;
}