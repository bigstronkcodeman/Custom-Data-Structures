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


/*Does what is essentially a depth first search of the tree, starting from the root,
to find the parent of node with a specific key*/
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
		/*If we're decreasing the priority of the 
		root, no extra action is needed. Simply decrease
		the key. Min-heap property will not be violated*/
		if (root->key == key)
		{
			root->key = newKey;
			return;
		}

		/*p is parent of node whose key we are going to decrease*/
		HeapNode<Data>* p = parent(key);

		/*If the node to be decreased is the left most child of p, then... */
		if (p->left->key == key)
		{
			/*Make a new pointer to the node to be decreased, we are going to sever
			its link from the tree*/
			HeapNode<Data>* severedRoot = p->left;
			p->left = p->left->sibling;
			severedRoot->sibling = NULL;

			/*Now that the subtree rooted at the node to be decreased is severed
			from the tree, we can decrease it's key without issue (it is the root
			of its own tree now)*/
			severedRoot->key = newKey;

			/*If p is not the root, ...*/
			if (p != root)
			{
				/*We need to find the grandparent of p, so that we can make
				him point to the heap resulted from merging p and the severed root
				instead of p. Although if p is not his leftmost child, we will actually
				be changing the left sibling of p to point to the heap resulting from 
				merging p and the severed root.*/
				HeapNode<Data>* gp = parent(p->key);
				if (gp->left == p)
				{
					gp->left = merge(severedRoot, p);
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
				/*p is the root, so we just change it to point to the root of the merged heaps.*/
				root = merge(severedRoot, p);
			}
		}
		else
		{
			/*the node to be decreased is not the leftmost child of p,
			so we need to iterate through it's siblings to find it*/
			HeapNode<Data>* pc = p->left;
			while (pc->sibling->key != key)
			{
				pc = pc->sibling;
			}

			/*Sever the subtree rooted at the node whose key we wish to decrease
			so we can decrease the key without consequence.*/
			HeapNode<Data>* severedRoot = pc->sibling;
			pc->sibling = severedRoot->sibling;
			severedRoot->sibling = NULL;
			severedRoot->key = newKey;

			/*If p is not the root, ...*/
			if (p != root)
			{
				/*We need to find the grandparent of p, so that we can make
				him point to the heap resulted from merging p and the severed root
				instead of p. Although if p is not his leftmost child, we will actually
				be changing the left sibling of p to point to the heap resulting from 
				merging p and the severed root.*/
				HeapNode<Data>* gp = parent(p->key);
				if (gp->left == p)
				{
					gp->left = merge(severedRoot, p);
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
				/*p is the root, so we just change it to point to the root of the merged heaps.*/
				root = merge(severedRoot, p);
			}
		}
	}
}
