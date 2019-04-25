#pragma once
#include <iostream>

using namespace std;

template<class Data>
class DynamicArray
{
private:
	int capacity;
	int size;
	Data* arr;

	void extend();
	void shrink();

public:
	DynamicArray();
	DynamicArray(int capacityIn);
	DynamicArray(int capacityIn, Data* in);
	DynamicArray(const DynamicArray<Data>& other);
	~DynamicArray();

	void append(Data e);
	void prepend(Data e);
	void insert(Data e, int i);
	Data removeFront();
	Data removeBack();
	bool isFull();
	void print();
	int length();

	Data& operator[](int index);
	void operator=(const DynamicArray<Data>& other);
};

template<class Data>
DynamicArray<Data>::DynamicArray() : capacity(10), size(0)
{
	arr = new Data[capacity];
}

template<class Data>
DynamicArray<Data>::DynamicArray(int capacityIn) : capacity(capacityIn), size(0)
{
	arr = new Data[capacity];
}

template<class Data>
DynamicArray<Data>::DynamicArray(int capacityIn, Data* in) : capacity(capacityIn), size(capacityIn)
{
	arr = new Data[capacity];
	for (int i = 0; i < capacity; i++)
	{
		arr[i] = in[i];
	}
}

template<class Data>
DynamicArray<Data>::DynamicArray(const DynamicArray<Data>& other)
{
	capacity = other.capacity;
	size = other.size;
	arr = new Data[capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
}

template<class Data>
DynamicArray<Data>::~DynamicArray()
{
	delete[] arr;
}

template<class Data>
void DynamicArray<Data>::extend()
{
	if (capacity == 0)
	{
		capacity = 1;
	}
	else
	{
		capacity = capacity * 2;
	}

	Data* newArr = new Data[capacity];
	for (int i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}
	delete[] arr;
	arr = newArr;
}

template<class Data>
void DynamicArray<Data>::shrink()
{
	if (capacity > 0 && size <= capacity / 2)
	{
		Data* newArr = new Data[capacity / 2];
		for (int i = 0; i < size; i++)
		{
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
		capacity /= 2;
	}
	else
	{
		cout << "bad shrink" << endl;
	}
}

template<class Data>
void DynamicArray<Data>::append(Data e)
{
	if (isFull())
	{
		extend();
	}
	arr[size++] = e;
}

template<class Data>
void DynamicArray<Data>::prepend(Data e)
{
	if (isFull())
	{
		extend();
	}
	
	for (int i = size - 1; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}

	arr[0] = e;
	size++;
}

template<class Data>
void DynamicArray<Data>::insert(Data e, int i)
{
	if (isFull())
	{
		extend();
	}

	for (int j = size - 1; j >= i; j--)
	{
		arr[j + 1] = arr[j];
	}

	arr[i] = e;
	size++;
}

template<class Data>
Data DynamicArray<Data>::removeBack()
{
	if (size <= 0)
	{
		cout << "array is empty" << endl;
		return NULL;
	}

	Data last = arr[size - 1];

	if (size - 1 < capacity / 2)
	{
		shrink();
	}

	size--;
	return last;
}

template<class Data>
Data DynamicArray<Data>::removeFront()
{
	Data first = arr[0];
	for (int i = 1; i < size; i++)
	{
		arr[i - 1] = arr[i];
	}
	size--;
	return first;
}

template<class Data>
Data& DynamicArray<Data>::operator[](int index)
{
	return arr[index];
}

template<class Data>
void DynamicArray<Data>::operator=(const DynamicArray<Data>& other)
{
	capacity = other.capacity;
	size = other.size;
	delete[] arr;
	arr = new Data[capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
}

template<class Data>
bool DynamicArray<Data>::isFull()
{
	return size >= capacity;
}

template<class Data>
void DynamicArray<Data>::print()
{
	for (int i = 0; i < size; i++)
	{
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
}

template<class Data>
int DynamicArray<Data>::length()
{
	return size;
}