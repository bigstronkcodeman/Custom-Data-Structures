#include "DynamicArray.h"
#include <iostream>

template<class Data>
struct SingletonSet
{
	int p;
	int i;
	int rank = 0;
	int size = 1;
	Data key;
};

template<class Data>
class DisjointSet
{
private:
	DynamicArray<SingletonSet<Data>> sets;
	int numElements;
	int numSets;

public:
	DisjointSet();
	DisjointSet(Data in[]);
	~DisjointSet();

	void makeSet(Data in);
	int find(int i);
	bool Union(int i, int j);
	DynamicArray<Data> get(int i);
	void print();
};

template<class Data>
DisjointSet<Data>::DisjointSet() : sets(), numElements(0), numSets(0) {}

template<class Data>
DisjointSet<Data>::DisjointSet(Data in[])
{
	int size = *(&in + 1) - in;
	for (int i = 0; i < size; i++)
	{
		sets.append(in[i]);
	}
}

template<class Data>
DisjointSet<Data>::~DisjointSet() {}

template<class Data>
void DisjointSet<Data>::makeSet(Data in)
{
	SingletonSet<Data> set;
	set.i = numElements;
	set.p = -1;
	set.key = in;
	set.rank = 0;
	set.size = 1;
	sets.append(set);
	numSets++;
	numElements++;
}

template<class Data>
int DisjointSet<Data>::find(int i)
{
	if (sets[i].p != -1)
	{
		sets[i].p = find(sets[i].p);
		return sets[i].p;
	}
	return i;
}

template<class Data>
bool DisjointSet<Data>::Union(int i, int j)
{
	int iRoot = find(i);
	int jRoot = find(j);

	if (iRoot == jRoot)
	{
		return false;
	}

	if (sets[iRoot].rank < sets[jRoot].rank)
	{
		iRoot = iRoot + jRoot;
		jRoot = iRoot - jRoot;
		iRoot = iRoot - jRoot;
	}

	sets[jRoot].p = iRoot;
	
	if (sets[iRoot].rank == sets[jRoot].rank)
	{
		sets[iRoot].rank++;
	}
	sets[iRoot].size += sets[jRoot].size;
	numSets--;
}

template<class Data>
DynamicArray<Data> DisjointSet<Data>::get(int i)
{
	DynamicArray<Data> arr;
	int iRoot = find(i);
	for (int j = 0; j < numElements; j++)
	{
		if (find(j) == iRoot)
		{
			arr.append(sets[j].key);
		}
	}
	return arr;
}

template<class Data>
void DisjointSet<Data>::print()
{
	DynamicArray<DynamicArray<Data>> arr;
	for (int i = 0; i < numElements; i++)
	{
		if (find(i) == i)
		{
			arr.append(get(i));
		}
	}

	for (int i = 0; i < arr.length(); i++)
	{
		cout << "(";
		for (int j = 0; j < arr[i].length(); j++)
		{
			cout << arr[i][j];
			if (j != arr[i].length() - 1)
			{
				cout << ", ";
			}
		}
		cout << ")";
		if (i != arr.length() - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}