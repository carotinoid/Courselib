#include <iostream>
#include <fstream>
#include <string>
#include "closed_hash_function.h"
#include "closed_hash_table.h"

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

ClosedHashTable::ClosedHashTable(int table_size, int k, int d1, ClosedHashFunction *hf) : table_size(table_size), k(k), d1(d1)
{
    this->hf = hf;
    this->table = new int[this->table_size];
    this->states = new ClosedTableState[this->table_size];

    for (int i = 0; i < this->table_size; ++i)
    {
        this->states[i] = CLOSED_EMPTY;
    }

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

ClosedHashTable::~ClosedHashTable()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

void ClosedHashTable::print_table(ostream &out)
{
    for (int i = 0; i < this->table_size; i++)
    {
        out << i << ": ";
        if (this->states[i] == CLOSED_EMPTY)
            out << "EMPTY" << endl;
        else if (this->states[i] == CLOSED_OCCUPIED)
            out << this->table[i] << endl;
        else
            out << "UNKNOWN" << endl;
    }
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    if(checkFail) out << "FAIL" << endl;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void ClosedHashTable::insert(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if(checkFail) return;
    int attempt = 1; //if it is bigger than table size, print fail.
    while(true)
    {
        int hashed = hf->Realclosedhashing(key, attempt, d1, k);
        if(states[hashed] == CLOSED_EMPTY)
        {
            table[hashed] = key;
            states[hashed] = CLOSED_OCCUPIED;
            break;
        }
        if(attempt >= table_size)
        {
            checkFail = true;
            break;
        }
        attempt++;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
