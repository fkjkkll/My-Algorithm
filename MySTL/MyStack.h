#pragma once
#include <cassert>

template<class T>
class MyStack{
	template<class T>
	class DataItem {
		public:
			T element;
			DataItem<T>* next;
	};

public:
	MyStack() { 
		_size = 0;
		data = nullptr;
	}
	const T& top();
	void push(const T&);
	void pop();
	void clear();
	bool empty() { return _size == 0; }
	int size() { return _size; }

private:
	int _size;
	DataItem<T>* data;
};

template<class T>
const T& MyStack<T>::top() {
	assert(this->_size > 0);
	return data->element;
}

template<class T>
void MyStack<T>::push(const T& e) {
	DataItem<T>* t = new DataItem<T>;
	t->element = e;
	t->next = this->data;
	this->data = t;
	++ this->_size;
}

template<class T>
void MyStack<T>::pop() {
	if (_size < 1)
		return;
	DataItem<T>* l = this->data;
	this->data = this->data->next;
	-- this->_size;
	delete l;
}

template<class T>
void MyStack<T>::clear() {
	DataItem<T>* l = this->data;
	DataItem<T>* r;
	while (l) {
		r = l->next;
		delete l;
		l = r;
	}
	this->data = nullptr;
	this->_size = 0;
}