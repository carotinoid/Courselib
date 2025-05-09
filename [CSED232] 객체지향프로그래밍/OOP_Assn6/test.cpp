#include <iostream>
#include "MultiHeadList.h"

using namespace std;
class Test {
public :
	void basic_test() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		cout << "push_back(1)" << endl;
		print(mhList);
		mhList.push_back(2, 0);
		cout << "push_back(2, 0)" << endl;
		print(mhList);
		mhList.push_back(3, 1);
		cout << "push_back(3, 1)" << endl;
		print(mhList);
		mhList.push_back(4);
		cout << "push_back(4)" << endl;
		print(mhList);
		mhList.push_back(5,1);
		cout << "push_back(5,1)" << endl;
		print(mhList);
		mhList.push_front(6, 2);
		cout << "push_front(6, 2)" << endl;
		print(mhList);
		mhList.pop_back(2);
		cout << "pop_back(2)" << endl;
		print(mhList);
		mhList.pop_front(2);
		cout << "pop_front(2)" << endl;
		print(mhList);
		mhList.push_front(7);
		cout << "push_front(7)" << endl;
		print(mhList);
		mhList.merge(2,1);
		cout << "merge(2,1)" << endl;
		print(mhList);
		mhList.erase(7,0);
		cout << "erase(7,0)" << endl;
		print(mhList);
		mhList.erase(7, 1);
		cout << "erase(7,1)" << endl;
		print(mhList);
		mhList.insert(mhList.begin(1), 8);
		cout << "insert(mhList.begin(1), 8)" << endl;
		print(mhList);
		mhList.insert(++mhList.begin(1), 9);
		cout << "insert(++mhList.begin(1), 9)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(1)+2);
		cout << "erase(mhList.begin(1)+2)" << endl;
		print(mhList);
	}
	void push_back_test() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		cout << "push_back(1)" << endl;
		print(mhList);
		mhList.push_back(2, 0);
		cout << "push_back(2, 0)" << endl;
		print(mhList);
		mhList.push_back(3, 1);
		cout << "push_back(3, 1)" << endl;
		print(mhList);
		mhList.push_back(4);
		cout << "push_back(4)" << endl;
		print(mhList);
		mhList.push_back(5, 1);
		cout << "push_back(5, 1)" << endl;
		print(mhList);
	}
	void push_front_test() {
		MultiHeadList<int> mhList;
		mhList.push_front(1);
		cout << "push_front(1)" << endl;
		print(mhList);
		mhList.push_front(2, 0);
		cout << "push_front(2, 0)" << endl;
		print(mhList);
		mhList.push_front(3, 1);
		cout << "push_front(3, 1)" << endl;
		print(mhList);
		mhList.push_front(4);
		cout << "push_front(4)" << endl;
		print(mhList);
		mhList.push_front(5, 1);
		cout << "push_front(5, 1)" << endl;
		print(mhList);
		mhList.push_front(6, 2);
		cout << "push_front(6, 2)" << endl;
		print(mhList);
	}
	void pop_back_test() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		mhList.push_back(2, 0);
		mhList.push_back(3, 1);
		mhList.push_back(4, 0);
		mhList.push_back(5, 1);
		print(mhList);
		mhList.pop_back(1);
		cout << "pop_back(2)" << endl;
		print(mhList);
		mhList.pop_back(1);
		cout << "pop_back(2)" << endl;
		print(mhList);
		mhList.pop_back(0);
		cout << "pop_back(0)" << endl;
		print(mhList);
		mhList.pop_back(0);
		cout << "pop_back(0)" << endl;
		print(mhList);
		mhList.pop_back(0);
		cout << "pop_back(0)" << endl;
		print(mhList);
	}
	void pop_front_test() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		mhList.push_back(2, 0);
		mhList.push_back(3, 1);
		mhList.push_back(4, 0);
		mhList.push_back(5, 1);
		print(mhList);
		mhList.pop_front(1);
		cout << "pop_front(2)" << endl;
		print(mhList);
		mhList.pop_front(1);
		cout << "pop_front(2)" << endl;
		print(mhList);
		mhList.pop_front(0);
		cout << "pop_front(0)" << endl;
		print(mhList);
		mhList.pop_front(0);
		cout << "pop_front(0)" << endl;
		print(mhList);
		mhList.pop_front(0);
		cout << "pop_front(0)" << endl;
		print(mhList);
	}
	void insert_test() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		mhList.push_back(2, 0);
		mhList.push_back(3, 1);
		mhList.push_back(4, 0);
		mhList.push_back(5, 1);
		print(mhList);
		mhList.insert(mhList.begin(1), 6);
		cout << "insert(mhList.begin(1), 6)" << endl;
		print(mhList);
		mhList.insert(++mhList.begin(1), 7);
		cout << "insert(++mhList.begin(1), 7)" << endl;
		print(mhList);
		mhList.insert(mhList.begin(0), 8);
		cout << "insert(mhList.begin(0), 8)" << endl;
		print(mhList);
		mhList.insert(mhList.begin(0) + 3, 9);
		cout << "insert(mhList.begin(0) + 4, 9)" << endl;
		print(mhList);
		mhList.insert(mhList.begin(0) + 5, 10); // this is not work because mhList.begin(0) + 5 is nullptr.
		cout << "insert(mhList.begin(0) + 5, 10)" << endl;
		print(mhList);
		mhList.insert(mhList.begin(0) + 4, 11);
		cout << "insert(mhList.begin(0) + 4, 11)" << endl;
		print(mhList);
	}
	void erase_test1() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		mhList.push_back(2, 0);
		mhList.push_back(3, 0);
		mhList.push_back(4, 0);
		mhList.push_back(5, 0);
		mhList.push_back(6, 0);
		mhList.push_back(7, 0);
		mhList.push_back(8, 0);
		mhList.push_back(9, 0);
		print(mhList);
		mhList.erase(1, 0);
		cout << "erase(1, 0)" << endl;
		print(mhList);
		mhList.erase(2, 0);
		cout << "erase(2, 0)" << endl;
		print(mhList);
		mhList.erase(5, 0);
		cout << "erase(5, 0)" << endl;
		print(mhList);
		mhList.erase(4, 0);
		cout << "erase(4, 0)" << endl;
		print(mhList);
		mhList.erase(6, 0);
		cout << "erase(6, 0)" << endl;
		print(mhList);
		mhList.erase(9, 0);
		cout << "erase(9, 0)" << endl;
		print(mhList);
		mhList.erase(7, 0);
		cout << "erase(7, 0)" << endl;
		print(mhList);
		mhList.erase(8, 0);
		cout << "erase(8, 0)" << endl;
		print(mhList);
		mhList.erase(3, 0);
		cout << "erase(3, 0)" << endl;
		print(mhList);
	}
	void erase_test2_1() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		mhList.push_back(2, 0);
		mhList.push_back(3, 0);
		mhList.push_back(4, 0);
		mhList.push_back(5, 0);
		mhList.push_back(6, 0);
		mhList.push_back(7, 0);
		mhList.push_back(8, 0);
		mhList.push_back(9, 0);
		print(mhList);
		mhList.erase(mhList.begin(0));
		cout << "erase(mhList.begin(0))" << endl;
		print(mhList);
		mhList.erase(mhList.begin(0) + 7);
		cout << "erase(mhList.begin(0) + 7)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(0) + 1);
		cout << "erase(mhList.begin(0) + 1)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(1) + 3);
		cout << "erase(mhList.begin(1) + 3)" << endl;
		print(mhList);
	}
	void erase_test2_2() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		mhList.push_back(2, 0);
		mhList.push_back(3, 0);
		mhList.push_back(4, 0);
		mhList.push_back(5, 0);
		mhList.push_back(6, 0);
		mhList.push_back(7, 0);
		mhList.push_back(8, 0);
		mhList.push_back(9, 0);
		mhList.push_back(10, 0);
		mhList.push_back(11, 0);
		mhList.push_back(12, 0);
		mhList.erase(mhList.begin(0) + 4);
		cout << "erase(mhList.begin(0) + 4)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(1) + 3);
		cout << "erase(mhList.begin(1) + 3)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(0) + 2);
		cout << "erase(mhList.begin(0) + 2)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(1) + 1);
		cout << "erase(mhList.begin(1) + 1)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(2) + 1);
		cout << "erase(mhList.begin(2) + 1)" << endl;
		print(mhList);
	}
	void merge_test() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		mhList.push_back(2, 0);
		mhList.push_back(3, 1);
		mhList.push_back(4, 0);
		mhList.push_back(5, 1);
		print(mhList);
		mhList.merge(1, 0);
		cout << "merge(1, 0)" << endl;
		print(mhList);
		mhList.push_back(6);
		mhList.push_back(7);
		mhList.push_back(8);
		mhList.push_back(9);
		cout << "++++++++" << endl;
		print(mhList);
		mhList.merge(2, 1);
		cout << "merge(2, 1)" << endl;
		print(mhList);
		mhList.merge(3, 2);
		cout << "merge(3, 2)" << endl;
		print(mhList);
		mhList.merge(0, 2);
		cout << "merge(0, 2)" << endl;
		print(mhList);
		mhList.merge(0, 1);
		cout << "merge(0, 1)" << endl;
		print(mhList);
	}
	void iterator_test() {}

	template <typename T>
	void print(MultiHeadList<T>& mhList) {
		for (int i = 0; i != mhList.headSize(); i++) {
			cout << i << " : ";
			for (auto it = mhList.begin(i); it != mhList.end(); it++) {
				cout << *it << " ";
			}
			cout << endl;
		}
		cout << "=============" << endl;
	}
};