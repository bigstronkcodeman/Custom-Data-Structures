#pragma once
#include <iostream>

#define DEFAULT_SIZE 10000

using namespace std;

template <class Data>
class Stack
{
private:
	int size;
	int topi;
	Data* stack;

public:
	Stack();
	Stack(int sizeIn);
	~Stack();

	bool push(Data key);
	bool pop();
	Data top();
	bool isEmpty();
	bool isFull();
	void print();
};

template <class Data>
Stack<Data>::Stack()
{
	size = DEFAULT_SIZE;
	stack = new Data[size];
	topi = 0;
}

template <class Data>
Stack<Data>::Stack(int sizeIn)
{
	size = sizeIn;
	stack = new Data[size];
	topi = 0; 
}

template <class Data>
Stack<Data>::~Stack()
{
	delete[] stack;
}

template <class Data>
bool Stack<Data>::isFull()
{
	return topi >= size;
}

template <class Data>
bool Stack<Data>::isEmpty()
{
	return topi <= 0;
}

template <class Data>
bool Stack<Data>::push(Data key)
{
	if (!isFull())
	{
		stack[topi++] = key;
		return true;
	}
	return false;
}

template <class Data>
bool Stack<Data>::pop()
{
	if (!isEmpty())
	{
		topi--;
		return true;
	}
	return false;
}

template <class Data>
Data Stack<Data>::top()
{
	return stack[topi - 1];
}

template <class Data>
void Stack<Data>::print()
{
	for (int i = topi - 1; i >= 0; i--)
	{
		cout << stack[i] << endl;
	}
}