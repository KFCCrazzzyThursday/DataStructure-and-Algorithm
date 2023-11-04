#pragma once
#include<iostream>
using namespace std;

template<typename T>
struct Node {
	T data;
	Node<T>* next;

	Node() :data(*new T()), next(nullptr) {};
};

template<typename T>
class Stack {
private:
	Node<T>* head;
	int size;

public:
	Stack() :head(new Node<T>), size(0) {};
	~Stack();
	void push(T ele);
	T top();
	bool pop();
	bool isempty();
	int Size();
};

template<typename T>
class Queue {
private:
	Stack<T>* s1;
	Stack<T>* s2;
public:
	Queue() :s1(new Stack<T>), s2(new Stack<T>) {};
	~Queue() {
		delete s1;
		delete s2;
	};

	void push(T ele);
	bool pop();
	bool isempty();
	T front();
};


template<typename T>
inline Stack<T>::~Stack() {
	Node<T>* p = this->head;
	while (p != nullptr) {
		Node<T>* temp = p;
		p = p->next;
		delete temp;
	}
	head = nullptr;
	size = 0;
}

template<typename T>
inline void Stack<T>::push(T ele) {
	Node<T>* p = this->head;
	if (size == 0) {
		p->data = ele;
		size++;
		return;
	}

	while (p->next != nullptr) {
		p = p->next;
	}
	p->next = new Node<T>();
	p->next->data = ele;
	size++;
}

template<typename T>
inline T Stack<T>::top() {
	if (this->size == 0) {
		T* tmp = new T();
		return *tmp;
	}
	Node<T>* p = this->head;
	while (p->next != nullptr) {
		p = p->next;
	}
	return p->data;
}

template<typename T>
inline bool Stack<T>::pop() {
	Node<T>* p = this->head;
	Node<T>* q = p->next;
	if (size == 0) return false;
	if (q == nullptr) {
		T* emp = new T();
		this->head->data = *emp;
		this->head->next = nullptr;
		size--;
		return true;
	}
	while (q != nullptr && q->next != nullptr) {
		p = p->next;
		q = p->next;
	}
	delete q;
	p->next = nullptr;
	size--;
	return true;
}

template<typename T>
inline bool Stack<T>::isempty() {
	return (size == 0);
}

template<typename T>
inline int Stack<T>::Size() {
	return size;
}

template<typename T>
inline void Queue<T>::push(T ele) {
	s1->push(ele);
}

template<typename T>
inline bool Queue<T>::pop() {
	if (s1->Size() == 0) return false;
	while (s1->Size() > 0) {
		s2->push(s1->top());
		s1->pop();
	}
	s2->pop();
	while (s2->Size() > 0) {
		s1->push(s2->top());
		s2->pop();
	}
	return true;
}

template<typename T>
inline bool Queue<T>::isempty() {
	return s1->Size() == 0;
}

template<typename T>
inline T Queue<T>::front() {
	if (s1->Size() == 0) {
		T* emp = new T();
		return *emp;
	}
	while (s1->Size() > 0) {
		s2->push(s1->top());
		s1->pop();
	}
	T res = s2->top();
	while (s2->Size() > 0) {
		s1->push(s2->top());
		s2->pop();
	}
	return res;
}
