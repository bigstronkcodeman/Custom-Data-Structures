#pragma once
#pragma once

const int DEFAULT_CAPACITY = 10;

template <class Data>
class Stack
{
private:
	Data* items;
	size_t _top;
	size_t capacity;

	void grow();
	void shrink();

public:
	Stack();
	~Stack();

	void push(Data item);
	void pop();
	Data& top();
	bool is_empty();
};

template <class Data>
Stack<Data>::Stack() {
	capacity = DEFAULT_CAPACITY;
	items = new Data[capacity];
	_top = 0;
}

template <class Data>
Stack<Data>::~Stack() {
	delete[] items;
}

template <class Data>
void Stack<Data>::grow() {
	capacity *= 2;
	Data* new_block = new Data[capacity];
	for (size_t i = 0; i < _top; ++i) {
		new_block[i] = items[i];
	}
	delete[] items;
	items = new_block;
}

template <class Data>
void Stack<Data>::shrink() {
	capacity /= 2;
	Data* new_block = new Data[capacity];
	for (size_t i = 0; i < _top; ++i) {
		new_block[i] = items[i];
	}
	delete[] items;
	items = new_block;
}

template <class Data>
void Stack<Data>::push(Data item) {
	if (_top + 1 > capacity) {
		grow();
	}
	items[_top++] = item;
}

template <class Data>
void Stack<Data>::pop() {
	try {
		if (_top > 0) {
			if (_top - 1 < capacity / 2) {
				shrink();
			}
			--_top;
		}
		else {
			throw "Stack is empty!";
		}
	}
	catch (char const* err) {
		std::cout << err << '\n';
	}
}

template <class Data>
Data& Stack<Data>::top() {
	try {
		if (_top > 0) {
			return items[_top - 1];
		}
		else {
			throw "Stack is empty!";
		}
	}
	catch (char const* err) {
		std::cout << err << '\n';
	}
}

template <class Data>
bool Stack<Data>::is_empty() {
	return (_top == 0);
}
