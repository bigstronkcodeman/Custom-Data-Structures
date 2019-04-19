#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"

#define DEFAULT_GRAPH_SIZE 10
#define INF 2147483647

using namespace std;

enum Color
{
	WHITE,
	GREY,
	BLACK
};

enum EdgeType
{
	UNCLASSIFIED,
	TREE,
	BACK,
	FORWARD,
	CROSS
};

struct Vertex
{
	Vertex* parent;
	int id;
	int discovered;
	int finished;
	Color color;

	bool operator==(const Vertex& other)
	{
		return parent == other.parent &&
			id == other.id &&
			discovered == other.discovered &&
			finished == other.finished &&
			color == other.color;
	}
};

struct Edge
{
	Vertex* u;
	Vertex* v;
	int weight;

	Edge()
	{
		u = NULL;
		v = NULL;
		weight = 0;
	}

	Edge(Vertex& x, Vertex& y)
	{
		u = &x;
		v = &y;
		weight = 0;
	}

	Edge(Vertex& x, Vertex& y, int weightIn)
	{
		u = &x;
		v = &y;
		weight = weightIn;
	}

	bool operator==(const Edge& other)
	{
		return u == other.u &&
			v == other.v &&
			weight == other.weight;
	}
};

ostream& operator<<(ostream& os, const Vertex& v)
{
	os << v.id;
	return os;
}

ostream& operator<<(ostream& os, const Vertex* v)
{
	os << v->id;
	return os;
}

ostream& operator<<(ostream& os, const Edge& e)
{
	os << "(" << e.u << ", " << e.v << ")";
	return os;
}

class Graph
{
private:
	int vertCount;
	int edgeCount;
	bool directed;
	LinkedList<Vertex*>* adjList;
	LinkedList<Edge> edges;
	Vertex* verts;

	void addDirectedEdge(int vfrom, int vto);
	void addUndirectedEdge(int u, int v);
	bool searchEdge(int u, int v);

public:
	Graph();
	Graph(int size);
	Graph(int size, bool isDirected);
	~Graph();

	void addEdge(int u, int v);
	void printAdjList();
	void printEdgeList();
	void DFS();
	void DFS(int u);
	void BFS();
	void BFS(int u);
};

Graph::Graph()
{
	vertCount = DEFAULT_GRAPH_SIZE;
	edgeCount = 0;
	adjList = new LinkedList<Vertex*>[vertCount];
	verts = new Vertex[vertCount];
	for (int i = 0; i < vertCount; i++)
	{
		Vertex v;
		v.parent = NULL;
		v.discovered = INF;
		v.finished = INF;
		v.id = i;
		v.color = WHITE;
		verts[i] = v;
	}
	directed = false;
}

Graph::Graph(int size)
{
	vertCount = size;
	edgeCount = 0;
	adjList = new LinkedList<Vertex*>[vertCount];
	verts = new Vertex[vertCount];
	for (int i = 0; i < vertCount; i++)
	{
		Vertex v;
		v.parent = NULL;
		v.discovered = INF;
		v.finished = INF;
		v.id = i;
		v.color = WHITE;
		verts[i] = v;
	}
	directed = false;
}

Graph::Graph(int size, bool isDirected)
{
	vertCount = size;
	edgeCount = 0;
	adjList = new LinkedList<Vertex*>[vertCount];
	verts = new Vertex[vertCount];
	for (int i = 0; i < vertCount; i++)
	{
		Vertex v;
		v.parent = NULL;
		v.discovered = INF;
		v.finished = INF;
		v.id = i;
		v.color = WHITE;
		verts[i] = v;
	}
	directed = isDirected;
}


Graph::~Graph()
{
	delete[] adjList;
	delete[] verts;
}

void Graph::addEdge(int u, int v)
{
	if (!searchEdge(u, v))
	{
		if (directed)
		{
			addDirectedEdge(u, v);
			edgeCount++;
		}
		else
		{
			addUndirectedEdge(u, v);
			edgeCount++;
		}
	}
	else
	{
		cout << "edge already in graph" << endl;
	}
}

void Graph::addDirectedEdge(int vfrom, int vto)
{
	if (vfrom < vertCount && vto < vertCount)
	{
		edges.insertTail(Edge(verts[vfrom], verts[vto]));
		adjList[vfrom].insertTail(&verts[vto]);
	}
	else
	{
		cout << "bad edge, unable to add\n";
	}
}

void Graph::addUndirectedEdge(int u, int v)
{
	if (u < vertCount && v < vertCount)
	{
		edges.insertTail(Edge(verts[u], verts[v]));
		adjList[u].insertTail(&verts[v]);
		adjList[v].insertTail(&verts[u]);
	}
	else
	{
		cout << "bad edge, unable to add\n";
	}
}

void Graph::printAdjList()
{
	cout << "adjacency list: " << endl;
	for (int i = 0; i < vertCount; i++)
	{
		cout << "V" << i << ": ";
		adjList[i].printHead();
	}
}

void Graph::printEdgeList()
{
	cout << "edge list: ";
	edges.printHead();
}

bool Graph::searchEdge(int u, int v)
{
	return adjList[u].searchKey(&verts[v]);
}

void Graph::DFS()
{
	for (int i = 0; i < vertCount; i++)
	{
		verts[i].color = WHITE;
		verts[i].parent = NULL;
	}

	for (int i = 0; i < vertCount; i++)
	{
		if (verts[i].color == WHITE)
		{
			DFS(i);
		}
	}
}

void Graph::DFS(int s)
{
	if (s < vertCount)
	{
		cout << "depth first search: " << endl;
		for (int i = 0; i < vertCount; i++)
		{
			verts[i].color = WHITE;
			verts[i].parent = NULL;
		}
		int time = 0;
		Stack<Vertex*> stack(vertCount);
		stack.push(&verts[s]);
		while (!stack.isEmpty())
		{
			Vertex* u = stack.top();
			stack.pop();
			if (u->color == WHITE)
			{
				cout << "visiting vertex " << u << endl;
				u->color = GREY;
				u->discovered = time++;
			
				for (int i = 0; i < adjList[u->id].size(); i++)
				{
					Vertex* v = adjList[u->id].get(i);
					v->parent = u;
					stack.push(v);
				}
				u->color = BLACK;
				u->finished = time++;
			}
		}
		cout << "finished." << endl;
	}
}

void Graph::BFS()
{
	for (int i = 0; i < vertCount; i++)
	{
		verts[i].color = WHITE;
		verts[i].parent = NULL;
	}

	for (int i = 0; i < vertCount; i++)
	{
		if (verts[i].color == WHITE)
		{
			BFS(i);
		}
	}
}

void Graph::BFS(int s)
{
	if (s < vertCount)
	{
		cout << "breadth first search:" << endl;
		for (int i = 0; i < vertCount; i++)
		{
			verts[i].color = WHITE;
			verts[i].parent = NULL;
		}
		int time = 0;
		Queue<Vertex*> queue(vertCount);
		queue.enqueue(&verts[s]);
		while (!queue.isEmpty())
		{
			Vertex* u = queue.dequeue();
			if (u->color == WHITE)
			{
				cout << "visiting vertex " << u << endl;
				u->color = GREY;
				u->discovered = time++;
				
				for (int i = 0; i < adjList[u->id].size(); i++)
				{
					Vertex* v = adjList[u->id].get(i);
					v->parent = u;
					queue.enqueue(v);
				}
				
				u->color = BLACK;
				u->finished = time++;
			}
		}
		cout << "finished." << endl;
	}
}