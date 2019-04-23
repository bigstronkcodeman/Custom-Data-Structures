#include "Graph.h"

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
	g.DFS();
	g.printTimes();
	g.classifyEdges();
	g.printEdgeList();

	return 0;
}
