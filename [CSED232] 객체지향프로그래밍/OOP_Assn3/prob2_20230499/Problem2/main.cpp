#include "prob2.h"
#include <iostream>
void simpleTest1(OrderedSet* o) {
	add(o, 5);
	add(o, 5);
	add(o, 5);
	add(o, 4);
	add(o, 3);
	for (int i = 0; i < o->m_size; ++i) {
		std::cout << getValue(o, i) << ", ";
	}
	std::cout << std::endl;

}
void simpleTest2(OrderedSet* o) {
	int vals[] = { 10, 20, 35, 35, 10 };
	add(o, vals, sizeof(vals) / sizeof(int));
	for (int i = 0; i < o->m_size; ++i) {
		std::cout << getValue(o, i) << ", ";
	}std::cout << std::endl;

}
void simpleTest3(OrderedSet* o) {
	remove(o, 3);
	for (int i = 0; i < o->m_size; ++i) {
		std::cout << getValue(o, i) << ", ";
	}std::cout << std::endl;

}
void simpleTest4(OrderedSet* o) {
	std::cout << std::boolalpha << contains(o, 20) << std::endl;
	std::cout << std::boolalpha << contains(o, 40) << std::endl;

}
void simpleTest5(OrderedSet* o) {
	std::cout << size(o) << std::endl;
}
int main()
{
	OrderedSet orderedSet;
	std::cout << "<<Simple Test 1>>" << std::endl;
	simpleTest1(&orderedSet);
	std::cout << "<<Simple Test 2>>" << std::endl;
	simpleTest2(&orderedSet);
	std::cout << "<<Simple Test 3>>" << std::endl;
	simpleTest3(&orderedSet);
	std::cout << "<<Simple Test 4>>" << std::endl;
	simpleTest4(&orderedSet);
	std::cout << "<<Simple Test 5>>" << std::endl;
	simpleTest5(&orderedSet);
	return 0;
}
