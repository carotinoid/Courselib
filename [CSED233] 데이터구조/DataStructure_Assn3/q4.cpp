/*
    Programming Assignment #3
*/
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

#include "utils.h"
#include "avl.h"
#include "bst.h"
#include "tree.h"


using namespace std;

/*
    [Task 4] 4.	Duplicate Letter Counting Problem

    Description:
        a.  Implement a class ‘AVLTree’ to efficiently count
        and report the frequency of each alphabet letter in a string using AVL tree operations.
        This involves handling imbalances that might occur during insertions and deletions,
        as well as ensuring that alphabet letters are counted accurately.
        As the string is received, insert each letter sequentially from the beginning to the end into the AVL tree.

        b.	AVL Tree Implementations
            - Modify or implement functions in the ‘AVLTree’ class that insert and delete elements (letters in this case).
            - Implement functions in the ‘AVLTree’ class that print the all node information in pre-order, in-order, and reverse-in-order manner.
            - Ensure the AVL tree can resolve imbalances (LL, LR, RL, RR) that might occur after modifications.
            - You can modify ‘avl.cpp’ and ‘avl.h’ files, and if needed, add public members to the ‘Node’ class implemented in ‘tree.h’.

        c.	Details of the process
            - Sequentially insert each letter from the string. If a node for that letter already exists, delete the existing node, increment the count, and re-insert the node.
            - During the deletion process, if a node has both children, use the replacement method where you find the minimum in the right subtree to replace the node
            - If counts are equal, prioritize based on the lexicographical order of the letters. For example, (c, 1) < (a, 4) < (b, 4).

        d.	Input & Output:
            - Input: A string consisting of at least one alphabetical letter. You don’t need to consider any other input cases and uppercase and lowercase of letters are same.
            - Output: (1) Frequency counts of letters, displayed from the most to the least frequent. If multiple letters have the same frequency, they should be displayed in lexicographical order.
            - Output: (2) The results of the preorder and inorder traversal of the constructed AVL tree after all operations.

        e.	task_4 prints
            i.	The results of reverse-inorder, inorder, preorder traversal of the constructed tree.
            ii.	The format of node for printing is “(letter, count)”
*/


std::string printInOrder(AVLTree& t) {
    std::ostringstream os;
    t.printInOrder(os);
    return os.str();
}

std::string printPreOrder(AVLTree& t) {
    std::ostringstream os;
    t.printPreOrder(os);
    return os.str();
}

std::string printFrequency(AVLTree& t) {
    std::ostringstream os;
    t.printFrequency(os);
    return os.str();
}

void task_4(ostream &fout, string expression)
{
    try
    {
        AVLTree tree;

        /////////////////////////////////////////////////////////
        //////////  TODO: Implement From Here      //////////////

        for (char letter : expression)
        {
            tree.insert(tolower(letter));
        }

        fout << "Frequencies of alphabetic letters in the given string" << endl;
        tree.printFrequency(fout);

        ///////////      End of Implementation      /////////////
        ///////////////////////////////////////////////////////
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

int main(int argc, char **argv)
{
    InstructionSequence instr_seq;
    string expression;
    expression = argv[1];
    task_4(std::cout, expression);
}
