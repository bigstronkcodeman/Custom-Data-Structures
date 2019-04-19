#include "Graph.h"

using namespace std;

int main()
{
	Graph g(4, true);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);
	g.printEdgeList();
	g.printAdjList();
	g.BFS(2);
	g.DFS();

	return 0;
}
