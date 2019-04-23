#include <string>
#include <iostream>

#define DEFAULT_SIZE 10000

using namespace std;

template<class Data>
class Queue
{
private:
	int front;
	int back;
	int size;
	int numItems;
	Data* queue;

public:
	Queue();
	Queue(int size);
	Queue(const Queue& other);
	~Queue();

	bool enqueue(Data key);
	Data dequeue();
	Data getFront();
	void print();
	bool isFull();
	bool isEmpty();
	void operator=(const Queue& other);
};


template<class Data>
Queue<Data>::Queue()
{
	size = DEFAULT_SIZE;
	queue = new Data[size];
	front = 0;
	back = 0;
	numItems = 0;
}

template<class Data>
Queue<Data>::Queue(int sizeIn)
{
	size = sizeIn;
	queue = new Data[size];
	front = 0;
	back = 0;
	numItems = 0;
}

template<class Data>
Queue<Data>::Queue(const Queue& other)
{
	size = other.size;
	queue = new Data[size];
	for (int i = 0; i < size; i++)
	{
		queue[i] = other.queue[i];
	}
	front = other.front;
	back = other.back;
	numItems = other.numItems;
}

template<class Data>
Queue<Data>::~Queue()
{
	delete[] queue;
}

template<class Data>
bool Queue<Data>::enqueue(Data key)
{
	if (!isFull())
	{
		queue[back] = key;
		back = ++back % size;
		numItems++;
		return true;
	}
	return false;
}

template<class Data>
Data Queue<Data>::dequeue()
{
	if (!isEmpty())
	{
		Data copy = queue[front];
		front = ++front % size;
		numItems--;
		return copy;
	}
	cout << "Queue underflow, exiting\n";
	exit(1);
}

template<class Data>
Data Queue<Data>::getFront()
{
	return queue[front];
}

template<class Data>
void Queue<Data>::print()
{
	for (int i = 0; i < numItems; i++)
	{
		cout << queue[(front + i) % size] << " ";
	}
	cout << endl;
}

template<class Data>
bool Queue<Data>::isFull()
{
	return numItems >= size;
}

template<class Data>
bool Queue<Data>::isEmpty()
{
	return numItems <= 0;
}

template<class Data>
void Queue<Data>::operator=(const Queue& other)
{
	size = other.size;
	queue = new Data[size];
	for (int i = 0; i < size; i++)
	{
		queue[i] = other.queue[i];
	}
	front = other.front;
	back = other.back;
	numItems = other.numItems;
}