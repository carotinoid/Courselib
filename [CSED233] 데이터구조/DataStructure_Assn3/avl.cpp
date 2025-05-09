#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

AVLTree::AVLTree()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  /*  Write your codes if you need  */

  _root = NULL;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

AVLTree::~AVLTree()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  /*  Write your codes if you need  */

  delete[] _root;
  _root = NULL;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}


void AVLTree::insert(char letter)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int frequency = 1;
  Node* check = find(_root, letter);
  if(check != NULL)
  {
    frequency = check->frequency + 1;
    remove(letter);
  }
  _insert(_root, letter, frequency);
  if(_root != NULL) _root->calculateHeight();
  _upBubblingRotateFrom(find(_root, letter));

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
void AVLTree::remove(char letter)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *target = find(_root, letter);
  if(target == NULL) return;
  Node *parent = target->parent;
  if(target->parent == NULL) //root
  {
    if(target->left == NULL && target->right == NULL)
    {
      delete target;
      _root = NULL;
    }
    else if(target->left != NULL && target->right == NULL)
    {
      _root = target->left;
      _root->parent = NULL;
      delete target;
    }
    else if(target->left == NULL && target->right != NULL)
    {
      _root = target->right;
      _root->parent = NULL;
      delete target;
    }
    else //target is root, 2 degree
    {
      Node* temp = target->right;
      while(temp->left != NULL) temp = temp->left;
      if(target->right == temp)
      {
        target->letter = temp->letter;
        target->frequency = temp->frequency;
        if(temp->right != NULL)
        {
          target->right = temp->right;
          temp->right->parent = target;
        }
        else target->right = NULL;
        delete temp;
      }
      else
      {
        target->letter = temp->letter;
        target->frequency = temp->frequency;
        if(temp->right != NULL)
        {
          temp->parent->left = temp->right;
          temp->right->parent = temp->parent;
        }
        else temp->parent->left = NULL;
        delete temp;
      }

    }
  }
  else // non-root
  {
    if(target->left == NULL && target->right == NULL) // 0 degree
    {
      if(target->parent->left == target) target->parent->left = NULL;
      else target->parent->right = NULL;
      delete target;
    }
    else if(target->left != NULL && target->right == NULL) // 1 degree, left child
    {
      if(target->parent->left == target) target->parent->left = target->left;
      else target->parent->right = target->left;
      target->left->parent = target->parent;
      delete target;
    }
    else if(target->left == NULL && target->right != NULL) // 1 degree, right child
    {
      if(target->parent->left == target) target->parent->left = target->right;
      else target->parent->right = target->right;
      target->right->parent = target->parent;
      delete target;
    }
    else // 2 degree
    {
      Node* temp = target->right;
      while(temp->left != NULL) temp = temp->left;
      if(target->right == temp)
      {
        target->letter = temp->letter;
        target->frequency = temp->frequency;
        if(temp->right != NULL)
        {
          target->right = temp->right;
          temp->right->parent = target;
        }
        else target->right = NULL;
        delete temp;
      }
      else
      {
        target->letter = temp->letter;
        target->frequency = temp->frequency;
        if(temp->right != NULL)
        {
          temp->parent->left = temp->right;
          temp->right->parent = temp->parent;
        }
        else temp->parent->left = NULL;
        delete temp;
      }
    }
  }
  if(_root != NULL) _root->calculateHeight();
  _upBubblingRotateFrom(parent);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
void AVLTree::printInOrder(ostream &fout)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;
  _inOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  fout << output << endl;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
void AVLTree::printPreOrder(ostream &fout)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  fout << output << endl;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
void AVLTree::printFrequency(ostream &fout)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;
  _reverseInOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  fout << output << endl;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

void AVLTree::_leftRotate(Node *cur)
{
  Node* newRoot = cur->right;
  cur->right = newRoot->left;
  if (newRoot->left != nullptr) {
      newRoot->left->parent = cur;
  }
  newRoot->parent = cur->parent;
  if (cur->parent == nullptr) {
      _root = newRoot;
  } else if (cur == cur->parent->left) {
      cur->parent->left = newRoot;
  } else {
      cur->parent->right = newRoot;
  }
  newRoot->left = cur;
  cur->parent = newRoot;

  if(_root != NULL) _root->calculateHeight();
}

// void AVLTree::_leftRotate(Node *cur)
// {
//   Node* temp = cur->right;
//   cur->right = temp->left;
//   temp->left = cur;
//   if(cur->parent == NULL) _root = temp;
//   else if(cur->parent->left == cur) cur->parent->left = temp;
//   else cur->parent->right = temp;
//   cur->calculateHeight();
//   temp->calculateHeight();
// }

void AVLTree::_rightRotate(Node *cur)
{
  Node* newRoot = cur->left;
  cur->left = newRoot->right;
  if (newRoot->right != nullptr) {
      newRoot->right->parent = cur;
  }
  newRoot->parent = cur->parent;
  if (cur->parent == nullptr) {
      _root = newRoot;
  } else if (cur == cur->parent->right) {
      cur->parent->right = newRoot;
  } else {
      cur->parent->left = newRoot;
  }
  newRoot->right = cur;
  cur->parent = newRoot;

  if(_root != NULL) _root->calculateHeight();
}

// void AVLTree::_rightRotate( Node *cur)
// {
//   Node* temp = cur->left;
//   cur->left = temp->right;
//   temp->right = cur;
//   if(cur->parent == NULL) _root = temp;
//   else if(cur->parent->left == cur) cur->parent->left = temp;
//   else cur->parent->right = temp;
//   cur->calculateHeight(); //TODO if() _root -> calculateHeight();
//   temp->calculateHeight(); // parent connection fix
// }

void AVLTree::_upBubblingRotateFrom(Node *target)
{
  if(target == NULL) return;
  if(_root == target) return;
  Node* parent = target->parent;
  while(true)
  {
    if(target->balanceFactor() == 2)
    {
      if(target->left->balanceFactor() == -1) _leftRotate(target->left);
      _rightRotate(target);
    } else if(target->balanceFactor() == -2)
    {
      if(target->right->balanceFactor() == 1) _rightRotate(target->right);
      _leftRotate(target);
    }
    target = parent;
    if(target == NULL) break;
    parent = target->parent;
    if(_root != NULL) _root->calculateHeight();
  }
}

void AVLTree::_insert(Node *cur, char letter, int frequency)
{
  if(cur == NULL) //root
  {
    cur = new Node(letter, frequency);
    _root = cur;
    return;
  }
  if(cur->frequency > frequency or (cur->frequency == frequency and cur->letter > letter))
  {
    if(cur->left == NULL)
    {
      cur->left = new Node(letter, frequency);
      cur->left->parent = cur;
      return;
    }
    _insert(cur->left, letter, frequency);
  } else
  {
    if(cur->right == NULL)
    {
      cur->right = new Node(letter, frequency);
      cur->right->parent = cur;
      return;
    }
    _insert(cur->right, letter, frequency);
  }
}

void AVLTree::_inOrder(string &output, Node *cur)
{
  if (cur == NULL)
    return;

  _inOrder(output, cur->left);
  output.append("(");
  output.append(cur->print_letter());
  output.append(", ");
  output.append(to_string(cur->frequency));
  output.append(") ");
  _inOrder(output, cur->right);
}

void AVLTree::_preOrder(string &output, Node *cur)
{
  if (cur == NULL)
    return;

  output.append("(");
  output.append(cur->print_letter());
  output.append(", ");
  output.append(to_string(cur->frequency));
  output.append(") ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->right);
}

void AVLTree::_reverseInOrder(string &output, Node *cur)
{
  if (cur == NULL)
    return;

  _reverseInOrder(output, cur->right);
  output.append("(");
  output.append(cur->print_letter());
  output.append(", ");
  output.append(to_string(cur->frequency));
  output.append(") ");
  _reverseInOrder(output, cur->left);
}

Node* AVLTree::find(Node *top, char letter)
{
  Node *target = NULL;
  if(top == NULL) return NULL;
  if(top->left != NULL) target = find(top->left, letter);
  if(top->right != NULL && target == NULL) target = find(top->right, letter);
  if(top->letter == letter) target = top;
  return target;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////