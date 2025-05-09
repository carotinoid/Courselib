#include <iostream>
#include <fstream>
#include <string>
#include "open_hash_function.h"
#include "open_hash_table.h"

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

OpenHashTable::OpenHashTable(int table_size, OpenHashFunction *hf) : table_size(table_size)
{
    this->hf = hf;
    this->collision = 0;
    this->longest = 0;
    table = new HashNode *[this->table_size];
    for (int i = 0; i < this->table_size; i++)
    {
        table[i] = NULL;
    }
    this->states = new OpenTableState[this->table_size];

    for (int i = 0; i < this->table_size; ++i)
    {
        this->states[i] = OPEN_EMPTY;
    }

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

OpenHashTable::~OpenHashTable()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] table;
    delete[] this->states;
}

void OpenHashTable::print_result(ostream &out)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    for(int i = 0; i < table_size; i++)
    {
        if(table[i] != NULL)
        {
            HashNode *now = table[i];
            int cnt = 0;
            while(now != NULL)
            {
                cnt++;
                now = now->next;
            }
            if(cnt > longest) longest = cnt;
        }
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    out << collision << " " << longest << endl;
}

void OpenHashTable::insert(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int hashed = hf->openhashing(key);
    if(states[hashed] == OPEN_EMPTY)
    {
        table[hashed] = new HashNode(key);
        states[hashed] = OPEN_OCCUPIED;
    }
    else
    {
        collision++;
        HashNode *newNode = new HashNode(key);
        HashNode *now = table[hashed];
        while(now->next != NULL) now = now->next;
        now->next = newNode;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void OpenHashTable::delete_(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int hashed = hf->openhashing(key);
    if(states[hashed] == OPEN_EMPTY) return;
    HashNode *now = table[hashed];
    if(now->key == key)
    {
        table[hashed] = now->next;
        delete now; return;
    }
    else
    {
        while(now->next != NULL)
        {
            if(now->next->key == key)
            {
                HashNode *temp = now->next;
                now->next = now->next->next;
                delete temp; return;
            }
            now = now->next;
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
