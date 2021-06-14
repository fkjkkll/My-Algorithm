#pragma once
#include <cassert>

template<class T>
class MyQueue {
	template<class T>
	class DataItem {
		public:
			T element;
			DataItem<T>* next;
	};

public:
	MyQueue() {
		_size = 0;
		_head = _tail = nullptr;
	}
	const T& front() const;
	const T& back() const;
	void push(const T&);
	void pop();
	void clear();
	bool empty() { return _size == 0; }
	int size() { return _size; }

private:
	int _size;
	DataItem<T>* _head;
	DataItem<T>* _tail;
};

template<class T>
const T& MyQueue<T>::front() const {
	assert(this->_size > 0);
	return _head->element;
}

template<class T>
const T& MyQueue<T>::back() const {
	assert(this->_size > 0);
	return _tail->element;
}

template<class T>
void MyQueue<T>::push(const T& e) {
	DataItem<T>* t = new DataItem<T>;
	t->element = e;
	t->next = nullptr;
	if (_size == 0)
		_head = _tail = t;
	else {
		_tail->next = t;
		_tail = t;
	}
	++ _size;
}

template<class T>
void MyQueue<T>::pop() {
	if (_size < 1)
		return;
	DataItem<T>* l = _head;
	_head = _head->next;
	-- _size;
	delete l;
	if (_size == 0)
		_tail = nullptr;
}

template<class T>
void MyQueue<T>::clear() {
	while (_head) {
		_tail = _head->next;
		delete _head;
		_head = _tail;
	}
	_size = 0;
}