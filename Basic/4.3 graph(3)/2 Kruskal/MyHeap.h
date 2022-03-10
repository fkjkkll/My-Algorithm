#pragma once
#include <cassert>

template<class T>
class MyHeap {
public:
	MyHeap(int n = 10);
	MyHeap(const T[], int);
	void push(const T&);
	const T pop();
	int size() { return _size; }
	void resize(int);

private:
	void adjustHeap(int);

private:
	int _size;
	int _capacity;
	T* data;
};

template<class T>
MyHeap<T>::MyHeap(int n) {
	_size = 0;
	_capacity = n;
	data = new T[n];
}

template<class T>
MyHeap<T>::MyHeap(const T a[], int n) {
	_size = n;
	_capacity = n;
	data = new T[n];
	for (int i = 0; i < n; ++i) {
		data[i] = a[i];
	}
	int pos = (n - 1) / 2;
	for (; pos >= 0; --pos) {
		adjustHeap(pos);
	}
}

template<class T>
void MyHeap<T>::adjustHeap(int pos) {
	T tmp = data[pos];
	int i;
	for (i = pos*2+1; i < _size; i = i*2+1) {
		if (i + 1 < _size && data[i] > data[i + 1]) // 两个孩子选则最小的
			++i;
		if (data[i] > tmp) // 最小的都比待调整的结点大，则停止
			break;
		else 
			data[(i - 1) / 2] = data[i];
	}
	data[(i - 1) / 2] = tmp; // 插入father位置
}

template<class T>
void MyHeap<T>::push(const T& e) {
	if (_size == _capacity) this->resize(_size * 2); // 扩容
	data[_size++] = e;
	int son = _size - 1;
	int father = (son - 1) / 2;
	for (; son != father; ) { // 结束条件
		if (data[father] > e)
			data[son] = data[father];
		else
			break;
		son = father;
		father = (son - 1) / 2;
	}
	data[son] = e;
}

template<class T>
const T MyHeap<T>::pop() {
	assert(_size > 0);
	if (_size == 0)
		throw "pop error!";
	T item = data[0];
	data[0] = data[--_size];
	adjustHeap(0);
	return item;
}

template<class T>
void MyHeap<T>::resize(int n) {
	_capacity = n;
	T* tmp = new T[n];
	for (int i = 0; i < _capacity; ++i) {
		if (i < _size)
			tmp[i] = data[i];
	}
	delete[] data;
	data = tmp;
}

