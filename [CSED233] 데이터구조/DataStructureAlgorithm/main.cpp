#include <iostream>
#include <vector>
#include "custom_algorithm.h"

using namespace std;

int main()
{
    vector<int> v = {51, 42, 64, 51, 87, 11, 23, 99, 1, 5};
    da::insertion_sort(v, 1);
    for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
    da::insertion_sort(v, 0);
    for(int i = 0; i < v.size(); i++) cout << v[i] << " ";

}