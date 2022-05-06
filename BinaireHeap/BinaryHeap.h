#pragma once

#include <functional>
#include <vector>
#include <iostream>

template<class T>
class BinaryHeap {
public:
	BinaryHeap(std::function<bool(T, T)> cmp = std::less<T>()) : m_Heap(std::vector<T>()), m_Cmp(cmp), m_Fixed(true) {};
	BinaryHeap(std::vector<T> nums, std::function<bool(T, T)> cmp = std::less<T>()) : m_Heap(nums), m_Cmp(cmp), m_Fixed(true) {};
	~BinaryHeap() = default;

	const T& findTop() const;
	T removeTop();
	void add(std::vector<T>);
	void add(T);
	void toss(std::vector<T>);
	void toss(T);
	void fixHeap();

	const std::vector<T>& getHeap() const { return m_Heap; };
	std::function<bool(T, T)> getCompare() const { return m_Cmp; };
	bool isFixed() const { return m_Fixed; };

private:
	void swap(int, int);
	void percolateUp(int);
	void percolateDown(int);
	void fixHeap(int);

	std::function<bool(T, T)> m_Cmp;
	std::vector<T> m_Heap;
	bool m_Fixed;
};

/*
==============
IMPLEMENTATION
==============
*/

template<class T>
void BinaryHeap<T>::add(T elt) {
	std::cout << "ADD: adding element " << elt << std::endl;
	m_Heap.push_back(elt);
	percolateUp(m_Heap.size() - 1);
}

template<class T>
void BinaryHeap<T>::add(std::vector<T> vec) {
	for (int i = 0; i < vec.size(); i++) {
		add(vec[i]);
	}
}

template<class T>
void BinaryHeap<T>::percolateUp(int index) {
	if (index < 1) {
		return;
	}
	if (m_Cmp(m_Heap[index], m_Heap[(index - 1) / 2])) {
		swap(index, (index - 1) / 2);
		percolateUp((index - 1) / 2);
	}
}

template<class T>
void BinaryHeap<T>::percolateDown(int index) {
	if (2 * index + 1 >= m_Heap.size()) {
		return;
	}
	int min;
	if (2 * index + 2 >= m_Heap.size()) {
		min = 2 * index + 1;
	}
	else if (m_Cmp(m_Heap[2 * index + 1], m_Heap[2 * index + 2])) {
		min = 2 * index + 1;
	}
	else {
		min = 2 * index + 2;
	}

	if (m_Cmp(m_Heap[min], m_Heap[index])) {
		swap(min, index);
		percolateDown(min);
	}
}

template<class T>
void BinaryHeap<T>::swap(int i, int j) {
	T tmp = m_Heap[i];
	m_Heap[i] = m_Heap[j];
	m_Heap[j] = tmp;
}

template<class T>
void BinaryHeap<T>::toss(std::vector<T> vec) {
	for (int i = 0; i < vec.size(); i++) {
		toss(vec[i]);
	}
}

template<class T>
void BinaryHeap<T>::toss(T elt) {
	std::cout << "TOSS: Tossing element " << elt << std::endl;
	m_Heap.push_back(elt);
	m_Fixed = false;
}

template<class T>
void BinaryHeap<T>::fixHeap() {
	fixHeap(0);
	m_Fixed = true;
	std::cout << "FIXHEAP: Heap fixed" << std::endl;
}

template<class T>
void BinaryHeap<T>::fixHeap(int index) {
	if (2 * index + 1 >= m_Heap.size()) {
		return;
	}
	fixHeap(2 * index + 1);
	if (2 * index + 2 < m_Heap.size()) {
		fixHeap(2 * index + 2);
	}
	percolateDown(index);
}

template<class T>
const T& BinaryHeap<T>::findTop() const {
	if (m_Heap.empty()) {
		std::cerr << "FINDTOP: Heap is empty" << std::endl;
	}
	if (!m_Fixed) {
		fixHeap();
	}

	return m_Heap[0];
}

template<class T>
T BinaryHeap<T>::removeTop() {
	if (m_Heap.empty()) {
		std::cerr << "REMOVETOP: Heap is empty" << std::endl;
	}
	if (!m_Fixed) {
		fixHeap();
	}

	swap(0, m_Heap.size() - 1);
	T top = m_Heap.at(m_Heap.size() - 1);
	m_Heap.pop_back();
	percolateDown(0);
	return top;
}

template<class T>
std::ostream& operator<<(std::ostream& os, BinaryHeap<T> binHeap) {
	os << std::endl;
	std::vector<T> heap = binHeap.getHeap();
	int spaces = 1;
	while (spaces < heap.size() + 1) {
		spaces *= 2;
	}
	int i = 0;
	int n = 1;
	while (i < heap.size()) {
		for (int k = 0; k < spaces/2; k++) {
			os << " ";
		}
		int j = 0;
		while (i + j < heap.size() && j < n) {
			os << heap.at(i + j);
			j++;
			for (int k = 0; k < spaces; k++) {
				os << " ";
			}
		}
		os << std::endl;
		spaces /= 2;
		n *= 2;
		i += j;
	}
	return os;
}

