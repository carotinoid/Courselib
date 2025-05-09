#include<iostream>
#include<vector>
#include "test.cpp"
#include "Syllogism.cpp"

using namespace std;

int main() {
	// test of Problem 1
	Test test;
	test.basic_test();
	test.push_back_test();
	test.push_front_test();
	test.pop_back_test();
	test.pop_front_test();
	test.insert_test();
	test.erase_test1();
	test.erase_test2_1();
	test.erase_test2_2();
	test.merge_test();

	// // test of Problem 2
	Syllogism syl;
	syl.put(make_pair("A", "B"));
	syl.print();
	syl.put(make_pair("B", "C"));
	syl.print();
	syl.put(make_pair("E", "F"));
	syl.print();
	syl.put(make_pair("D", "E"));
	syl.print();
	syl.qna("B");
	syl.put(make_pair("C", "D"));
	syl.print();
	syl.qna("B");
}