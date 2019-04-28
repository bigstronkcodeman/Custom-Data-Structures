#include "LinkedList.h"
#include "DynamicArray.h"
#pragma once

template<class Data>
struct HeapNode
{
	HeapNode<Data>* left;
	HeapNode<Data>* sibling;
	Data key;

	HeapNode() : key()
	{
		left = NULL;
		sibling = NULL;
	}

	HeapNode(Data keyIn) : key(keyIn)
	{
		left = NULL;
		sibling = NULL;
	}
};

template<class Data>
class PairingHeap
{
private:
	HeapNode<Data>* root;
	int numItems;

	HeapNode<Data>* merge(HeapNode<Data>* h1, HeapNode<Data>* h2);
	HeapNode<Data>* mergePairs(HeapNode<Data>* h);
	void destructHelper(HeapNode<Data>* node);

public:
	PairingHeap();
	~PairingHeap();

	void insert(Data key);
	Data getMin();
	Data extractMin();
	int size();
	void decreaseKey(Data key, Data newKey);
	HeapNode<Data>* parent(Data key);
	HeapNode<Data>* parentHelper(Data key, HeapNode<Data>* node);
};

template<class Data>
PairingHeap<Data>::PairingHeap()
{
	root = NULL;
	numItems = 0;
}

template<class Data>
void PairingHeap<Data>::destructHelper(HeapNode<Data>* node)
{
	if (node == NULL)
	{
		return;
	}

	destructHelper(node->left);
	destructHelper(node->sibling);
	delete node;
}

template<class Data>
PairingHeap<Data>::~PairingHeap()
{
	if (root != NULL)
	{
		destructHelper(root);
	}
}

template<class Data>
void PairingHeap<Data>::insert(Data key)
{
	HeapNode<Data>* newNode = new HeapNode<Data>(key);
	root = merge(newNode, root);
	numItems++;
}

template<class Data>
Data PairingHeap<Data>::getMin()
{
	if (root == NULL)
	{
		cout << "empty heap, exiting" << endl;
		exit(1);
	}
	return root->key;
}

template<class Data>
HeapNode<Data>* PairingHeap<Data>::merge(HeapNode<Data>* h1, HeapNode<Data>* h2)
{
	if (h1 == NULL)
	{
		return h2;
	}
	if (h2 == NULL)
	{
		return h1;
	}
	if (h1->key < h2->key)
	{
		h2->sibling = h1->left;
		h1->left = h2;
		return h1;
	}
	else
	{
		h1->sibling = h2->left;
		h2->left = h1;
		return h2;
	}
}

template<class Data>
HeapNode<Data>* PairingHeap<Data>::mergePairs(HeapNode<Data>* h)
{
	if (h == NULL || h->sibling == NULL)
	{
		return h;
	}
	HeapNode<Data>* nextPair = h->sibling->sibling;
	return merge(merge(h, h->sibling), mergePairs(nextPair));
 }

template<class Data>
Data PairingHeap<Data>::extractMin()
{
	if (root == NULL)
	{
		cout << "heap underflow, exiting" << endl;
		exit(1);
	}
	Data result = root->key;
	root = mergePairs(root->left);
	numItems--;
	return result;
}

template<class Data>
int PairingHeap<Data>::size()
{
	return numItems;
}

template<class Data>
HeapNode<Data>* PairingHeap<Data>::parentHelper(Data key, HeapNode<Data>* node)
{
	if (node == NULL || (node == root && root->key == key))
	{
		return NULL;
	}

	HeapNode<Data>* child = node->left;
	while (child != NULL && !(child->key == key))
	{
		child = child->sibling;
	}

	if (child == NULL)
	{
		child = node->left;
		HeapNode<Data>* p = NULL;
		while (child != NULL)
		{
			if (child->left != NULL)
			{
				if (child->left->key == key)
				{
					return child;
				}
				p = parentHelper(key, child);
			}
			if (p != NULL)
			{
				return p;
			}
			child = child->sibling;
		}
		return NULL;
	}
	else
	{
		return node;
	}
}

template<class Data>
HeapNode<Data>* PairingHeap<Data>::parent(Data key)
{
	return parentHelper(key, root);
}

template<class Data>
void PairingHeap<Data>::decreaseKey(Data key, Data newKey)
{
	if (newKey < key)
	{
		if (root->key == key)
		{
			root->key = newKey;
			return;
		}

		HeapNode<Data>* p = parent(key);
		if (p->left->key == key)
		{
			HeapNode<Data>* severedRoot = p->left;
			severedRoot->key = newKey;
			p->left = p->left->sibling;
			severedRoot->sibling = NULL;
			if (p != root)
			{
				HeapNode<Data>* gp = parent(p->key);
				if (gp->left == p)
				{
					gp->left = merge(severedRoot, p);
					return;
				}
				else
				{
					HeapNode<Data>* gpc = gp->left;
					while (gpc->sibling != p)
					{
						gpc = gpc->sibling;
					}
					gpc->sibling = merge(severedRoot, p);
				}
			}
			else
			{
				root = merge(severedRoot, p);
			}
		}
		else
		{
			HeapNode<Data>* pc = p->left;
			while (pc->sibling->key != key)
			{
				pc = pc->sibling;
			}
			HeapNode<Data>* severedRoot = pc->sibling;
			severedRoot->key = newKey;
			pc->sibling = severedRoot->sibling;
			severedRoot->sibling = NULL;
			if (p != root)
			{
				HeapNode<Data>* gp = parent(p->key);
				if (gp->left == p)
				{
					gp->left = merge(severedRoot, p);
					return;
				}
				else
				{
					HeapNode<Data>* gpc = gp->left;
					while (gpc->sibling != p)
					{
						gpc = gpc->sibling;
					}
					gpc->sibling = merge(severedRoot, p);
				}
			}
			else
			{
				root = merge(severedRoot, p);
			}
		}
	}
}