#include "Arithmetic.h"

//数学运算函数：
List operator+(List a, List b) {
	List* res = new List;
	Node* p = a.head;
	Node* q = b.head;
	for (; p != nullptr; p = p->next) {
		res->push_back(p->coeff, p->index);
	}
	for (; q != nullptr; q = q->next) {
		res->push_back(q->coeff, q->index);
	}
	return *res;
}
List operator-(List a, List b) {
	List* res = new List;
	Node* p = a.head;
	Node* q = b.head;
	for (; p != nullptr; p = p->next) {
		res->push_back(p->coeff, p->index);
	}
	for (; q != nullptr; q = q->next) {
		res->push_back(-(q->coeff), (q->index));
	}
	return *res;
}
List operator*(List a, List b) {
	List* res = new List;
	Node* p = a.head;
	Node* q = b.head;
	for (p = a.head; p != nullptr; p = p->next) {
		for (q = b.head; q != nullptr; q = q->next) {
			res->push_back((p->coeff * q->coeff), (p->index + q->index));
		}
	}
	return *res;
}