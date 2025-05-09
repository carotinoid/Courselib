#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree(){};
    ~BinarySearchTree(){};

    int insertion(int key);
    int deletion(int key);
    int sum(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int _sumBiggerThan(Node *node, int key);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};