#include <iostream>
#include "MultiHeadList.h"

using namespace std;

class Syllogism {
private :
	MultiHeadList<pair<string,string>>syl;
public :

	/// @brief Add a new relation of propositions to the syllogism.
	/// @param argument A pair of strings representing the relation of propositions.
	void put(const pair<string, string>& argument) {
		// First, add the argument to the multi-head list.
		syl.push_back(argument);

		// Repeatedly merge two heads if they are connected until no more heads can be merged.
		bool done = false;
		while(!done)
		{
			done = true;
			for(int i = 0; i != syl.headSize(); i++) {
				for(int j = 0; j != syl.headSize(); j++) {
					if(i == j) continue;
					if((*syl.rbegin(i)).second == (*syl.begin(j)).first) {
						syl.merge(i, j);
						done = false;
						break;
					}
				}
				if(!done) break;
			}
		}
	}

	/// @brief Print the conclusion of the given proposition.
	/// @details Check all the propositions in the syllogism multi-head list to find the question.
	/// @param q A string representing the proposition to be question.
	void qna(const string& q) {
		for(int i = 0; i != syl.headSize(); i++) {
			for(auto it = syl.begin(i); it != syl.end(); it++) {
				if((*it).first == q) {
					cout << "If " << q << ", then " << (*syl.rbegin(i)).second << endl;
					return;
				}
			}
		}
		cout << "Not found" << endl;
	}

	// given.
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