#pragma once
#include <iostream>
#include <string>
#include "open_hash_function.h"

using namespace std;

enum OpenTableState
{
    OPEN_EMPTY,
    OPEN_OCCUPIED,
};

class HashNode
{
public:
    int key;
    HashNode *next;
    HashNode(int key)
    {
        this->key = key;
        this->next = NULL;
    }
};

class OpenHashTable
{
public:
    OpenHashTable(int table_size, OpenHashFunction *hf);
    ~OpenHashTable();

    void print_result(ostream &out);

    void insert(int key);
    void delete_(int key);

private:
    const int table_size;
    OpenHashFunction *hf;
    HashNode **table;
    OpenTableState *states;
    int collision;
    int longest;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
