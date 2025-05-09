#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
int BinarySearchTree::_sumBiggerThan(Node *node, int key)
{
    if(node == NULL) return 0;
    int sum = 0;
    if(node->key > key) sum += node->key;
    if(node->left != NULL) sum += _sumBiggerThan(node->left, key);
    if(node->right != NULL) sum += _sumBiggerThan(node->right, key);
    return sum;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int BinarySearchTree::insertion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int status;
    if(_root == NULL)
    {
        _root = new Node(key);
        status = 0;
    } else
    {
        Node *node = _root;
        while(true)
        {
            if(node->key == key) {
                status = -1;
                break;
            } else if(node->key > key) {
                if(node->left == NULL) {
                    node->left = new Node(key);
                    status = 0;
                    break;
                } else {
                    node = node->left;
                }
            } else {
                if(node->right == NULL) {
                    node->right = new Node(key);
                    status = 0;
                    break;
                } else {
                    node = node->right;
                }
            }
        }
    }
    if(_root != NULL) _root->calculateHeight();
    return status; // 0 if success, -1 if already exists
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::deletion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int status;
    if(_root == NULL)
    {
        status = -1;
    } else
    {
        Node *node = _root;
        Node *parent = NULL;
        while(true)
        {
            if(node->key == key)
            { // found
                if(node->left == NULL && node->right == NULL) { //degree 0
                    if(parent == NULL) { //root
                        delete _root;
                        _root = NULL;
                    } else { //not root
                        if(parent->left == node) {
                            delete parent->left;
                            parent->left = NULL;
                        } else {
                            delete parent->right;
                            parent->right = NULL;
                        }
                    }
                } else if(node->left == NULL) { // degree 1, right child
                    if(parent == NULL) { // root
                        _root = node->right;
                    } else {// not root
                        if(parent->left == node) {
                            parent->left = node->right;
                        } else {
                            parent->right = node->right;
                        }
                    }
                    delete node;
                } else if(node->right == NULL) { // degree 1, left child
                    if(parent == NULL) { // root
                        _root = node->left;
                    } else { // not root
                        if(parent->left == node) {
                            parent->left = node->left;
                        } else {
                            parent->right = node->left;
                        }
                    }
                    delete node;
                } else { // degree 2
                    Node *minNode = node->right;
                    Node *minParent = node;
                    while(minNode->left != NULL) {
                        minParent = minNode;
                        minNode = minNode->left;
                    }
                    node->key = minNode->key;
                    if(minParent->left == minNode) {
                        minParent->left = minNode->right;
                    } else {
                        minParent->right = minNode->right;
                    }
                    delete minNode;
                }
                status = 0;
                break;
            }
            else if(node->key > key)
            { // finding to left
                if(node->left == NULL) {
                    status = -1;
                    break;
                } else {
                    parent = node;
                    node = node->left;
                }
            }
            else
            { // finding tto right
                if(node->right == NULL) {
                    status = -1;
                    break;
                } else {
                    parent = node;
                    node = node->right;
                }
            }
        }
    }
    if(_root != NULL) _root->calculateHeight();
    return status;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int BinarySearchTree::sum(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return _sumBiggerThan(_root, key);
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}