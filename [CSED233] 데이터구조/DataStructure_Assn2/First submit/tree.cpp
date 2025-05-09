#include "tree.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
    if (start > end)
        return -1;

    string s;

    for (int i = start; i <= end; i++) {

        // if open parenthesis, push it
        if (str[i] == '(')
            s.push_back(str[i]);

            // if close parenthesis
        else if (str[i] == ')') {
            if (s.back() == '(') {
                s.pop_back();

                if (!s.length())
                    return i;
            }
        }
    }
    // if not found return -1
    return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {

    if (start > end)
        return NULL;

    Node *root = new Node(data[start]);
    int index = -1;

    if (start + 1 <= end && data[start + 1] == '(')
        index = findIndex(data, start + 1, end);

    if (index != -1) {
        root->left = _buildFromString(data, start + 2, index - 1);
        root->right = _buildFromString(data, index + 2, end - 1);
    }
    return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
    Node *root = _buildFromString(data, 0, strlen(data) - 1);
    _root = root;
}

void BinaryTree::_printNodeAndChildren(string &list, Node *node) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if(node == NULL)
        return;
    int cnt = 0;
    if(node->left != NULL) cnt++;
    if(node->right != NULL) cnt++;
    list += node->value;
    list += to_string(cnt);
    _printNodeAndChildren(list, node->left);
    _printNodeAndChildren(list, node->right);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string BinaryTree::printNodeAndChildren() {
    string list = "";
    _printNodeAndChildren(list, _root);
    return list;
}


int BinaryTree::findHeightOfNode(Node *node, int value) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    auto arr = new Node*[100];
    int size = 0;
    Node* target;
    arr[0] = _root; size ++;
    while(true)
    {
        if(size <= 0)
        {
            target = NULL;
            break;
        }
        Node *now = arr[0];
        for(int i = 1; i < size; i++) {
            arr[i - 1] = arr[i];
        }
        size --;

        if(now->value == value)
        {
            target = now;
            break;
        }

        if(now->left != NULL) {
            arr[size] = now->left;
            size ++;
        }
        if(now->right != NULL) {
            arr[size] = now->right;
            size ++;
        }
    }
    delete[] arr;

    if(target == NULL) return -1;
    else return _findHeightOfTotal(target);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


int BinaryTree::findLevelOfNode(Node *node, int value) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    auto arr = new Node*[100];
    int arr2[100];
    int size = 0;
    int levelofTarget = -1;
    arr[0] = _root; size ++;
    arr2[0] = 0;
    while(true)
    {
        if(size == 0) break;
        Node *now = arr[0];
        int level = arr2[0];
        if(now->value == value)
        {
            levelofTarget = level;
            break;
        }
        for(int i = 1; i < size; i++) {
            arr[i - 1] = arr[i];
            arr2[i - 1] = arr2[i];
        }
        size --;
        if(now->left != NULL) {
            arr[size] = now->left;
            arr2[size] = level + 1;
            size ++;
        }
        if(now->right != NULL) {
            arr[size] = now->right;
            arr2[size] = level + 1;
            size ++;
        }
    }
    delete[] arr;
    return levelofTarget;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string BinaryTree::levelOrder() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    auto arr = new Node*[100];
    int size = 0;
    string s;
    arr[0] = _root; size ++;
    while(true)
    {
        if(size == 0) break;
        s += arr[0]->value;
        s += " ";
        Node *now = arr[0];
        for(int i = 1; i < size; i++) {
            arr[i - 1] = arr[i];
        }
        size --;
        if(now->left != NULL) {
            arr[size] = now->left;
            size ++;
        }
        if(now->right != NULL) {
            arr[size] = now->right;
            size ++;
        }
    }
    delete[] arr;
    return s;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void BinaryTree::_currentLevel(Node *node){
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    // Useless!
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


string BinaryTree::leafCount() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    auto arr = new Node*[300000];
    int size = 0;
    int leafcount = 0;
    arr[0] = _root; size ++;
    while(true)
    {
        if(size == 0) break;
        Node *now = arr[0];
        for(int i = 1; i < size; i++) {
            arr[i - 1] = arr[i];
        }
        size --;
        if(now->left == NULL && now->right == NULL) leafcount ++;
        if(now->left != NULL) {
            arr[size] = now->left;
            size ++;
        }
        if(now->right != NULL) {
            arr[size] = now->right;
            size ++;
        }
    }
    delete[] arr;
    return to_string(leafcount);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string BinaryTree::getWidth() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int prevlevel = 0, maxwidth = 0, width = 0;
    auto arr = new Node*[300000];
    int arr2[300000];
    int size = 0;
    arr[0] = _root;
    arr2[0] = 0;
    size ++;
    while(true)
    {
        if(size == 0) break;
        Node *now = arr[0];
        int level = arr2[0];
        if(level == prevlevel) {
            width ++;
        }
        else {
            maxwidth = max(maxwidth, width);
            width = 1;
            prevlevel = level;
        }
        for(int i = 1; i < size; i++) {
            arr[i - 1] = arr[i];
            arr2[i - 1] = arr2[i];
        }
        size --;
        if(now->left != NULL) {
            arr[size] = now->left;
            arr2[size] = level + 1;
            size ++;
        }
        if(now->right != NULL) {
            arr[size] = now->right;
            arr2[size] = level + 1;
            size ++;
        }
    }
    maxwidth = max(maxwidth, width);
    delete[] arr;
    return to_string(maxwidth);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////
//////////  You can implement any other functions ////////
int BinaryTree::_findHeightOfTotal(Node *node)
{
    if(node->left == NULL && node->right == NULL) return 0;
    return max((node->left ? _findHeightOfTotal(node->left) : 0), (node->right ? _findHeightOfTotal(node->right) : 0)) + 1;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////