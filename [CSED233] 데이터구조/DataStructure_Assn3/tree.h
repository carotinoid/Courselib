#pragma once
#include <string>

using namespace std;

class Node
{
public:
    Node(int key) : key(key), height(0), left(NULL), right(NULL) {}
    int key;
    int height;
    Node *left;
    Node *right;
    /////////////////////////////////////////////////////////
    //////  TODO: Add public members if required ///////////
    int calculateHeight()
    {
        int leftHeight, rightHeight;
        if(this->left == NULL) leftHeight = 0;
        else leftHeight = this->left->calculateHeight();
        if(this->right == NULL) rightHeight = 0;
        else rightHeight = this->right->calculateHeight();
        return this->height = max(leftHeight, rightHeight) + 1;
    }
    char letter = ' ';
    int frequency;
    Node(char letter, int frequency)
    {
        left = NULL;
        right = NULL;
        this->letter = letter;
        this->frequency = frequency;
    }
    string print_letter() { return string(1, letter); };
    Node *parent = NULL;
    int balanceFactor()
    {
        int leftHeight, rightHeight;
        if(this->left == NULL) leftHeight = 0;
        else leftHeight = this->left->height;
        if(this->right == NULL) rightHeight = 0;
        else rightHeight = this->right->height;
        return leftHeight - rightHeight;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    string print_key() { return to_string(key); };
};

class BinaryTree
{
public:
    BinaryTree() { _root = NULL; };
    ~BinaryTree()
    {
        delete[] _root;
        _root = NULL;
    };
    string preOrder();
    string inOrder();

protected:
    Node *_root;

private:
    void _inOrder(string &output, Node *cur);
    void _preOrder(string &output, Node *cur);
};
