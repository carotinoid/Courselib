#pragma once
#include <iostream>
#include <string>
#include "closed_hash_function.h"
using namespace std;

enum ClosedTableState
{
    CLOSED_EMPTY,
    CLOSED_OCCUPIED,
};

class ClosedHashTable
{
public:
    ClosedHashTable(int table_size, int k, int d1, ClosedHashFunction *hf);
    ~ClosedHashTable();

    void print_table(ostream &out);
    void insert(int key);

private:
    const int table_size;
    const int k;
    const int d1;
    ClosedHashFunction *hf;
    int *table;
    ClosedTableState *states;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    bool checkFail = false;
    ///////////      End of cImplementation      /////////////
    /////////////////////////////////////////////////////////
};
