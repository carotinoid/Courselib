#pragma once
#include "bst.h"

using namespace std;

class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    void insert(char letter);
    void remove(char letter);

    void printInOrder(ostream &fout);
    void printPreOrder(ostream &fout);
    void printFrequency(ostream &fout);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    void _inOrder(string &output, Node *cur);
    void _preOrder(string &output, Node *cur);
    void _reverseInOrder(string &output, Node *cur);
    void _insert(Node *cur, char letter, int frequency);
    void _upBubblingRotateFrom(Node *cur);
    void _leftRotate(Node *cur);
    void _rightRotate(Node *cur);
    Node* find(Node *top, char letter);
    Node* _root = NULL;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};