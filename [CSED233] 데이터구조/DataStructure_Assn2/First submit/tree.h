#pragma once
#include <string>
#include <fstream>
using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
    BinaryTree() { _root = NULL; };
    Node* getRoot() {return _root;}

    ~BinaryTree() {
    delete[] _root;
    _root = NULL;
    };
    void buildFromString(const  char *data);

    int findHeightOfNode(Node *node, int height);
    int findLevelOfNode(Node *node, int level);



    string levelOrder();
    string printNodeAndChildren();

    string leafCount();
    string getWidth();

private:
    Node *_root;
    Node *_buildFromString(const char *data, int start, int end);
    /////////////////////////////////////////////////////////
    //////  TODO: Add Private members if required ///////////
    void _printNodeAndChildren(string &list, Node *node);
    void _currentLevel(Node *node);

    int _findHeightOfTotal(Node *node);

    static const int MAX_DEPTH = 100;
    int levelCounts[MAX_DEPTH] = {0};

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};