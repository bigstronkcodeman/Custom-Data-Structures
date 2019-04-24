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
	LinkedList<Edge> edges;
	Vertex* verts;

	void addDirectedEdge(int vfrom, int vto);
	void addUndirectedEdge(int u, int v);
	Edge* getEdge(int u, int v);

public:
	Graph();
	Graph(int size);
	Graph(int size, bool isDirected);
	~Graph();

	void addEdge(int u, int v);
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
	Node<Edge>* listPtr = edges.getHeadPtr();
	while (listPtr != NULL && (listPtr->key.u != &verts[u] || listPtr->key.v != &verts[v]))
	{
		listPtr = listPtr->next;
	}

	return listPtr != NULL ? &(listPtr->key) : NULL;
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
		Node<Edge>* listNode = edges.getHeadPtr();
		while (listNode != NULL)
		{
			int u = listNode->key.u->id;
			int v = listNode->key.v->id;
			if (isTreeEdge(u, v))
			{
				listNode->key.type = TREE;
			}
			else if (isBackEdge(u, v))
			{
				listNode->key.type = BACK;
			}
			else if (isForwardEdge(u, v))
			{
				listNode->key.type = FORWARD;
			}
			else if (isCrossEdge(u, v))
			{
				listNode->key.type = CROSS;
			}
			listNode = listNode->next;
		}
	}
}

void Graph::transpose() //performs an in-place transpose on a directed graph, reversing the direction of all edges
{
	if (directed)
	{
		reset();
		bool** transposed = new bool*[vertCount];
		for (int i = 0; i < vertCount; i++)
		{
			transposed[i] = new bool[vertCount];
			for (int j = 0; j < vertCount; j++)
			{
				transposed[i][j] = false;
			}
		}

		int* adjSize = new int[vertCount];
		for (int i = 0; i < vertCount; i++)
		{
			adjSize[i] = adjList[i].size();
		}

		for (int i = 0; i < vertCount; i++)
		{
			int numRemovals = 0;
			while (!adjList[i].isEmpty() && numRemovals < adjSize[i])
			{
				Vertex* u = adjList[i].getHead();
				if (!transposed[u->id][i])
				{
					adjList[i].deleteHead();
					numRemovals++;
					adjList[u->id].insertTail(&verts[i]);
					Edge* e = getEdge(i, u->id);
					transposed[i][u->id] = true;
					Vertex* temp = e->u;
					e->u = e->v;
					e->v = temp;
				}
			}
		}

		for (int i = 0; i < vertCount; i++)
		{
			delete[] transposed[i];
		}
		delete[] transposed;
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

	Node<Edge>* listPtr = edges.getHeadPtr();

	if (listPtr->key.type == UNCLASSIFIED)
	{
		return;
	}

	while (listPtr != NULL)
	{
		listPtr->key.type = UNCLASSIFIED;
		listPtr = listPtr->next;
	}
}