#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "DynamicArray.h"
#include "DisjointSet.h"
#include "PairingHeap.h"

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

	void operator=(const Vertex& other)
	{
		parent = other.parent;
		id = other.id;
		discovered = other.discovered;
		finished = other.finished;
		color = other.color;
	}

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
	double weight;
	EdgeType type;

	Edge()
	{
		u = NULL;
		v = NULL;
		weight = 0;
		type = UNCLASSIFIED;
	}

	Edge(Vertex& x, Vertex& y)
	{
		u = &x;
		v = &y;
		weight = 0;
		type = UNCLASSIFIED;
	}

	Edge(Vertex& x, Vertex& y, int weightIn)
	{
		u = &x;
		v = &y;
		weight = weightIn;
		type = UNCLASSIFIED;
	}

	bool operator==(const Edge& other)
	{
		return u == other.u &&
			v == other.v &&
			weight == other.weight &&
			type == other.type;
	}

	void operator=(const Edge& other)
	{
		u = other.u;
		v = other.v;
		weight = other.weight;
		type = other.type;
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
	os << "<" << e.weight << ">";
	os << "(" << e.u << ", " << e.v << ")";
	switch (e.type)
	{
	case UNCLASSIFIED:
		cout << "U";
		break;
	case TREE:
		cout << "T";
		break;
	case FORWARD:
		cout << "F";
		break;
	case BACK:
		cout << "B";
		break;
	case CROSS:
		cout << "C";
		break;
	}
	return os;
}

class Graph
{
private:
	int vertCount;
	int edgeCount;
	bool directed;
	LinkedList<Vertex*>* adjList;
	DynamicArray<Edge> edges;
	Vertex* verts;

	void addDirectedEdge(int vfrom, int vto, int weight);
	void addUndirectedEdge(int u, int v, int weight);
	Edge* getEdge(int u, int v);
	void relax(int u, int v, DynamicArray<int>& distance);

public:
	Graph();
	Graph(int size);
	Graph(int size, bool isDirected);
	~Graph();

	void addEdge(int u, int v, int weight = 0);
	void printAdjList();
	void printEdgeList();
	void printTimes();
	void DFS();
	void DFS(int u);
	void BFS();
	void BFS(int u);
	bool searchEdge(int u, int v);
	bool isAncestor(int u, int v);
	bool isParent(int u, int v);
	bool isTreeEdge(int u, int v);
	bool isBackEdge(int u, int v);
	bool isForwardEdge(int u, int v);
	bool isCrossEdge(int u, int v);
	bool beenTraversed();
	void classifyEdges();
	void transpose();
	void reset();
	bool isAcyclic();
	void sortEdges();
	DynamicArray<Edge> kruskalMST();
	DynamicArray<Edge> primMST();
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

void Graph::addEdge(int u, int v, int weight)
{
	if (!searchEdge(u, v))
	{
		if (directed)
		{
			addDirectedEdge(u, v, weight);
		}
		else
		{
			addUndirectedEdge(u, v, weight);
		}
		edgeCount++;
	}
	else
	{
		cout << "edge already in graph" << endl;
	}
}

void Graph::addDirectedEdge(int vfrom, int vto, int weight)
{
	if (vfrom < vertCount && vto < vertCount)
	{
		edges.append(Edge(verts[vfrom], verts[vto], weight));
		adjList[vfrom].insertTail(&verts[vto]);
	}
	else
	{
		cout << "bad edge, unable to add\n";
	}
}

void Graph::addUndirectedEdge(int u, int v, int weight)
{
	if (u < vertCount && v < vertCount)
	{
		edges.append(Edge(verts[u], verts[v], weight));
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
	cout << "edge list: \n";
	edges.print();
}

void Graph::printTimes()
{
	cout << "vertex start/finish times:" << endl;
	for (int i = 0; i < vertCount; i++)
	{
		cout << "V" << i << ": [" << verts[i].discovered << ", " << verts[i].finished << "]" << endl;
	}
}

bool Graph::searchEdge(int u, int v)
{
	return adjList[u].searchKey(&verts[v]);
}

Edge* Graph::getEdge(int u, int v)
{
	for (int i = 0; i < edges.length(); i++)
	{
		if (edges[i].u == &verts[u] && edges[i].v == &verts[v])
		{
			return &edges[i];
		}
	}

	return NULL;
}

void Graph::DFS()
{
	reset();

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
		int time = 0;
		Stack<Vertex*> stack(vertCount);
		stack.push(&verts[s]);
		while (!stack.isEmpty())
		{
			Vertex* u = stack.top();
			if (u->color == WHITE)
			{
				cout << "visiting vertex " << u << endl;
				u->color = GREY;
				u->discovered = time++;

				for (int i = 0; i < adjList[u->id].size(); i++)
				{
					Vertex* v = adjList[u->id].get(i);
					if (v->color == WHITE)
					{
						v->parent = u;
						stack.push(v);
					}
				}
			}
			else if (u->color == GREY)
			{
				u->color = BLACK;
				u->finished = time++;
				stack.pop();
			}
			else
			{
				stack.pop();
			}
		}
		cout << "finished." << endl;
	}
}

void Graph::BFS()
{
	reset();

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

			}

			for (int i = 0; i < adjList[u->id].size(); i++)
			{
				Vertex* v = adjList[u->id].get(i);
				if (v->color == WHITE)
				{
					cout << "visiting vertex " << v << endl;
					v->color = GREY;
					v->discovered = time++;
					v->parent = u;
					queue.enqueue(v);
				}
			}

			if (u->color == GREY)
			{
				u->color = BLACK;
				u->finished = time++;
			}
		}
		cout << "finished." << endl;
	}
}

bool Graph::isAncestor(int u, int v)  //is u an ancestor of v ?
{
	Vertex* p = verts[v].parent;
	while (p != NULL && p != &verts[u])
	{
		p = p->parent;
	}

	if (p == NULL || p == verts[v].parent)
	{
		return false;
	}
	return true;
}

bool Graph::isParent(int u, int v) //is u the parent of v ?
{
	return verts[v].parent == &verts[u];
}

bool Graph::isTreeEdge(int u, int v)
{
	if (beenTraversed() && searchEdge(u, v))
	{
		if (isParent(u, v))
		{
			return true;
		}
		return false;
	}
	else
	{
		cout << "invalid edge" << endl;
		return false;
	}
}

bool Graph::isBackEdge(int u, int v)
{
	if (beenTraversed() && searchEdge(u, v))
	{
		if (isAncestor(v, u) || u == v)
		{
			return true;
		}
		return false;
	}
	else
	{
		cout << "invalid edge" << endl;
		return false;
	}
}

bool Graph::isForwardEdge(int u, int v)
{
	if (beenTraversed() && searchEdge(u, v))
	{
		if (isAncestor(u, v))
		{
			return true;
		}
		return false;
	}
	else
	{
		cout << "invalid edge" << endl;
		return false;
	}
}

bool Graph::isCrossEdge(int u, int v)
{
	if (beenTraversed() && searchEdge(u, v))
	{
		if (!isAncestor(u, v))
		{
			return true;
		}
		return false;
	}
	else
	{
		cout << "invalid edge" << endl;
		return false;
	}
}

bool Graph::beenTraversed()  //have we finished visiting every node ?
{
	for (int i = 0; i < vertCount; i++)
	{
		if (verts[i].color != BLACK)
		{
			return false;
		}
	}
	return true;
}

void Graph::classifyEdges()
{
	if (beenTraversed())
	{
		for (int i = 0; i < edges.length(); i++)
		{
			int u = edges[i].u->id;
			int v = edges[i].v->id;
			if (isTreeEdge(u, v))
			{
				edges[i].type = TREE;
			}
			else if (isBackEdge(u, v))
			{
				edges[i].type = BACK;
			}
			else if (isForwardEdge(u, v))
			{
				edges[i].type = FORWARD;
			}
			else if (isCrossEdge(u, v))
			{
				edges[i].type = CROSS;
			}
		}
	}
}

void Graph::transpose() //performs an in-place transpose on a directed graph, reversing the direction of all edges
{
	if (directed)
	{
		reset();

		int* adjSize = new int[vertCount];
		for (int i = 0; i < vertCount; i++)
		{
			adjSize[i] = adjList[i].size();
		}

		for (int i = 0; i < vertCount; i++)
		{
			int numRemovals = 0;
			while (numRemovals < adjSize[i])
			{
				Vertex* u = adjList[i].getHead();
				adjList[i].deleteHead();
				numRemovals++;
				adjList[u->id].insertTail(&verts[i]);
				Edge* e = getEdge(i, u->id);
				Vertex* temp = e->u;
				e->u = e->v;
				e->v = temp;
			}
		}

		delete[] adjSize;
	}
	else
	{
		cout << "cannot transpose undirected graph" << endl;
	}
}

void Graph::reset()
{
	for (int i = 0; i < vertCount; i++)
	{
		verts[i].color = WHITE;
		verts[i].discovered = INF;
		verts[i].finished = INF;
		verts[i].parent = NULL;
	}


	if (edges[0].type == UNCLASSIFIED) //if some edges are unclassified, then they must all be
	{
		return;
	}

	for (int i = 0; i < edges.length(); i++)
	{
		edges[i].type = UNCLASSIFIED;
	}
}

bool Graph::isAcyclic()
{
	if (!beenTraversed())
	{
		DFS();
	}

	for (int i = 0; i < edges.length(); i++)
	{
		if (edges[i].type == BACK)
		{
			return false;
		}
	}
	return true;
}

void Graph::sortEdges() //insertion sort because lazy
{
	for (int i = 1; i < edges.length(); i++)
	{
		Edge e = edges[i];
		int k = i - 1;
		while (k >= 0 && edges[k].weight > e.weight)
		{
			edges[k + 1] = edges[k];
			k--;
		}
		edges[k + 1] = e;
	}
}


DynamicArray<Edge> Graph::kruskalMST()
{
	DisjointSet<Vertex> ds;
	for (int i = 0; i < vertCount; i++)
	{
		ds.makeSet(verts[i]);
	}

	sortEdges();

	DynamicArray<Edge> MSTedges;
	for (int i = 0; i < edges.length(); i++)
	{
		if (ds.find(edges[i].u->id) != ds.find(edges[i].v->id))
		{
			MSTedges.append(edges[i]);
			ds.Union(edges[i].u->id, edges[i].v->id);
		}
	}
	return MSTedges;
}

//DynamicArray<Edge> Graph::primMST()
//{
//	struct PrimVert
//	{
//		int id;
//		int dist;
//
//		bool operator<(const PrimVert& other)
//		{
//			return dist < other.dist;
//		}
//
//		bool operator>(const PrimVert& other)
//		{
//			return dist > other.dist;
//		}
//
//		bool operator==(const PrimVert& other)
//		{
//			return dist == other.dist;
//		}
//	};
//
//	DynamicArray<PrimVert> vertices;
//	for (int i = 0; i < vertCount; i++)
//	{
//		PrimVert pv;
//		pv.id = i;
//		pv.dist = INF;
//		vertices.append(pv);
//	}
//	vertices[0].dist = 0;
//
//	PairingHeap<PrimVert&> ph;
//	for (int i = 0; i < vertCount; i++)
//	{
//		ph.insert(vertices[i]);
//	}
//
//
//}