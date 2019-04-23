#pragma once
#include <iostream>
using namespace std;

template<class Data>
struct Node
{
	Data key;
	Node<Data>* next;
	Node<Data>* prev;

	Node(Data keyIn);
};

template<class Data>
Node<Data>::Node(Data keyIn)
{
	key = keyIn;
	next = NULL;
	prev = NULL;
}

template<class Data>
class LinkedList
{
private:
	int count;
	Node<Data>* head;
	Node<Data>* tail;

public:
	LinkedList();
	LinkedList(const LinkedList& other);
	~LinkedList();

	void insertHead(Data key);
	void insertTail(Data key);
	bool deleteKey(Data key);
	bool deleteHead();
	bool deleteTail();
	void printHead();
	void printTail();
	Data getHead();
	Data getTail();
	Data get(int i);
	Data* getPtr(int i);
	int size();
	bool searchKey(Data key);
	Node<Data>* getHeadPtr();
};

template<class Data>
LinkedList<Data>::LinkedList()
{
	count = 0;
	head = NULL;
	tail = NULL;
}

template<class Data>
LinkedList<Data>::LinkedList(const LinkedList& other)
{
	Node<Data>* next;
	for (Node<Data>* ptr = head; ptr != NULL; ptr = next)
	{
		next = ptr->next;
		delete ptr;
	}

	head = NULL;
	tail = NULL;
	for (Node<Data>* ptr = other.head; ptr != NULL; ptr = ptr->next)
	{
		insertTail(ptr->key);
	}
	count = other.count;
}

template<class Data>
LinkedList<Data>::~LinkedList()
{
	Node<Data>* next;
	for (Node<Data>* ptr = head; ptr != NULL; ptr = next)
	{
		next = ptr->next;
		delete ptr;
	}
}

template<class Data>
void LinkedList<Data>::insertHead(Data key)
{
	if (head == NULL)
	{
		head = new Node<Data>(key);
		tail = head;
	}
	else
	{
		Node<Data>* newNode = new Node<Data>(key);
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	count++;
}

template<class Data>
void LinkedList<Data>::insertTail(Data key)
{
	if (tail == NULL)
	{
		tail = new Node<Data>(key);
		head = tail;
	}
	else
	{
		Node<Data>* newNode = new Node<Data>(key);
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	count++;
}

template<class Data>
bool LinkedList<Data>::deleteKey(Data key)
{
	Node<Data>* ptr = head;
	while (ptr != NULL && ptr->key != key)
	{
		ptr = ptr->next;
	}

	if (ptr == NULL)
	{
		return false;
	}

	if (ptr == tail)
	{
		tail = ptr->prev;
	}
	if (ptr == head)
	{
		head = ptr->next;
	}
	
	if (ptr->next != NULL) ptr->next->prev = ptr->prev;
	if (ptr->prev != NULL) ptr->prev->next = ptr->next;

	delete ptr;
	count--;

	return true;
}

template<class Data>
bool LinkedList<Data>::deleteHead()
{
	if (head != NULL)
	{
		Node* ptr = head;
		head = head->next;
		head->prev = NULL;
		delete ptr;
		count--;
		return true;
	}
	return false;
}

template<class Data>
bool LinkedList<Data>::deleteTail()
{
	if (tail != NULL)
	{
		Node* ptr = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete ptr;
		count--;
		return true;
	}
	return false;
}

template<class Data>
Data LinkedList<Data>::getHead()
{
	return head->key;
}

template<class Data>
Data LinkedList<Data>::getTail()
{
	return tail->key;
}

template<class Data>
Data LinkedList<Data>::get(int i)
{
	if (i < count)
	{
		Node<Data>* ptr = head;
		for (int j = 0; j < i; j++)
		{
			ptr = ptr->next;
		}
		return ptr->key;
	}
	return NULL;
}

template<class Data>
void LinkedList<Data>::printHead()
{
	for (Node<Data>* ptr = head; ptr != NULL; ptr = ptr->next)
	{
		cout << ptr->key << " -> "; //gotta overload cout << operator for objects to use print
	}
	cout << "X" << endl;
}

template<class Data>
void LinkedList<Data>::printTail()
{
	cout << "X <- ";
	Node<Data>* ptr = tail;
	for (ptr; ptr->prev != NULL; ptr = ptr->prev)
	{
		cout << ptr->key << " <- "; //gotta overload cout << operator for objects to use print
	}
	cout << ptr->key << endl;
}

template<class Data>
int LinkedList<Data>::size()
{
	return count;
}

template<class Data>
bool LinkedList<Data>::searchKey(Data key)
{
	for (Node<Data>* ptr = head; ptr != NULL; ptr = ptr->next)
	{
		if (ptr->key == key)
		{
			return true;
		}
	}
	return false;
}

template<class Data>
Data* LinkedList<Data>::getPtr(int i)
{
	if (i < count)
	{
		Node<Data>* ptr = head;
		for (int j = 0; j < i; j++)
		{
			ptr = ptr->next;
		}
		return &(ptr->key);
	}
	return NULL;
}

template<class Data>
Node<Data>* LinkedList<Data>::getHeadPtr()
{
	Node<Data>* hcopy = head;
	return hcopy;
}