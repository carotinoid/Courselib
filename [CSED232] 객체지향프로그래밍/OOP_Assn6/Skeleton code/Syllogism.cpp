#include <iostream>
#include "MultiHeadList.h"

using namespace std;

class Syllogism {
private :
	MultiHeadList<pair<string,string>>syl;
public :
	void put(const pair<string, string>& argument) {}
	void qna(const string& q) {}
	void print() {
		cout << "=============" << endl;
		for (int i = 0; i != syl.headSize(); i++) {
			cout << i << " : ";
			for (auto it = syl.begin(i); it != syl.end(); it++) {
				if (it == syl.begin(i)) {
					cout << (*it).first << "->" << (*it).second;
				}
				else {
					cout << "->" << (*it).second;
				}
			}
			cout << endl;
		}
	}
};