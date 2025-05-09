/*
    Programming Assignment #2

*/
#include "heap.h"
#include "tree.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
    [Task 1] Quiz

    // Image of tree is in the Programming Assignmnet 2 PDF file //
    1-1. For such tree, which has the correct pair for preorder traversal
        and post order traversal of the tree?

        (1)	Preorder : 1 2 4 5 6 3 7 9 8
            Postorder : 4 5 6 2 9 7 8 3 1
        (2)	Preorder : 4 5 6 2 9 7 8 3 1
            Postorder : 1 2 4 5 6 3 7 9 8
        (3)	Preorder : 1 2 4 5 6 3 7 9 8
            Postorder : 4 5 6 2 1 9 7 3 8
        (4)	None of the aboves

    1-2.  What is the time complexity of rearranging min-heap into max-heap?

          (1) O(1)
          (2) O(log n)
          (3) O(n)
          (4) O(2^n)

*/
void task_1(ofstream &fout, const char *quiz_num) {
    fout << "[Task 1]" << endl;
    int answer_1_1 = 2; // TODO: Change to your answer
    int answer_1_2 = 2; // TODO: Change to your answer

    if (!strcmp(quiz_num, "1")) {
        fout << answer_1_1 << endl;
    } else if (!strcmp(quiz_num, "2")) {
        fout << answer_1_2 << endl;
    } else {
        cerr << "Wrong quiz number:" << quiz_num << endl;
    }
}

/*
    [Task 2] Parents and Children in a Binary Tree (3pts)

    Description:
        Implement a function that takes a binary tree in the form of a string
   with bracket representation, and outputs each parent node along with the
   number of children it has.

    Input:
        - String with bracket representation of binary tree.
        - It is assumed that the bracket representation input received is in the
   correct format.
        - Duplicated node names are not considered in the input.

    Output:
        - String with parent node and number of children for each parent node.
        - If the input is in the form of 'A(B(D)())(C)', the output should be
   'A2B1D0C0', indicating the number of children each node has, following a
   preorder traversal of the binary tree.
*/

void task_2(ofstream &fout, const char *tree_string) {
    fout << "[Task 2]" << endl;
    try {
        BinaryTree tree;
        tree.buildFromString(tree_string);
        string result = tree.printNodeAndChildren();
        fout << result;
        fout << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*

    [Task 3] Height, Level and Level Order of Binary Tree (2 pts)

    a.	Implement BinaryTree::findHeightOfNode, BinaryTree::findLevelOfNode and BinaryTree::levelOrder function
    that can traverse a binary tree with given level order traverse mode and finds the level and height of a specific node.
    You can additionally implement other functions to facilitate the traversal of a binary tree
    (HINT : BinaryTree::_currentLevel used in level order traverse mode.)
    ** We only consider 1 to 9 integer inputs for binary tree nodes.

    b.	Input & Output

    Input:
    -	String with bracket representation and String representing specific node.

    Output:
    -	A sequence of node values acquired from the ① level order traverse mode and the ② height and ③ level of a specific node.
        The value is separated with a white space for traverse mode, and/pa2.exe 3 "4(2(3)(1))(6(5))" "6" height level with enter. Check the example below.
    -	You should print out -1 for each height and level for nodes that are not in the binary tree.


*/
void task_3(ofstream &fout, const char *tree_string,
            char nodeValue) {
    fout << "[Task 3]" << endl;
    try {
        BinaryTree tree;
        tree.buildFromString(tree_string);

        fout << tree.levelOrder() << endl;
        fout << tree.findHeightOfNode(tree.getRoot(), nodeValue) << endl;
        fout << tree.findLevelOfNode(tree.getRoot(), nodeValue) << endl;

    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 4] 4.	Width & Leaf count of Binary Tree (3 pts)

    a.	Implement BinaryTree::leafCount & BinaryTree::getWidth function.
    BinaryTree::leafCount calculates the number of leaves of the given binary tree.
    BinaryTree::getWidth calculates width, the largest number of nodes at any single level.
    Maximum depth of the tree is limited to 100.

    b.	Input & Output

    Input:
    -	String with bracket representation
    -	Specify what you want to check. Either “leaf” or “width”

    Output:
    -	The number of the leaves of the given binary tree for “leaf” command.
    -	Width of the the given binary tree for “width” instruction.

*/

int orderIndex;
int inorder[100];
int order[100];
int inorderIdx[100];

void task_4(ofstream &fout, const char *tree_string, const char *instr_seq) {
    fout << "[Task 4]" << endl;

    try {
        BinaryTree tree;
        tree.buildFromString(tree_string);

        if (strcmp(instr_seq, "leaf") == 0) {
            fout << tree.leafCount() << endl;
        } else if (strcmp(instr_seq, "width") == 0) {
            fout << tree.getWidth() << endl;
        } else {
            fout << "ERROR" << endl;
        }

    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 5] Priority Queue Implementation (2 pts)
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 5]" << endl;
    try
    {
        PriorityQueue pq;
        for (int i = 0; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0)
            {
                int input_value = instr_seq.getInstruction(i).getValue();

                /* BEGIN_YOUR_CODE*/
                if (pq.insert(input_value, input_value) == 0)
                {
                    fout << "ERROR " << endl;
                    exit(-1);
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("delete") == 0)
            {
                /* BEGIN_YOUR_CODE*/
                if (!pq.removeMax()) {
                    fout << "EMPTY ";
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("getMax") == 0)
            {
                if (pq.empty())
                {
                    fout << "EMPTY ";
                }
                else
                {
                    int value = pq.getMax().value;
                    string answer;
                    answer += to_string(value) + " ";
                    fout << answer;
                }
            }
            else if (command.compare("isEmpty") == 0)
            {
                if (pq.empty())
                {
                    fout << "TRUE ";
                }
                else
                {
                    fout << "FALSE ";
                }
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << pq.printPQ() << endl;
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

/*
    [Task 6] Advanced Priority Queue (3 pts)
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 6]" << endl;
    try
    {
        PriorityQueue pq;
        for (int i = 0; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0)
            {
                int input_value = instr_seq.getInstruction(i).getValue();

                /* BEGIN_YOUR_CODE*/
                if (pq.insert(input_value, input_value) == 0)
                {
                    fout << "ERROR " << endl;
                    exit(-1);
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("delete") == 0)
            {
                /* BEGIN_YOUR_CODE*/
                if (!pq.removeMax()) {
                    fout << "EMPTY ";
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("getMax") == 0)
            {
                if (pq.empty())
                {
                    fout << "EMPTY ";
                }
                else
                {
                    int value = pq.getMax().value;
                    string answer;
                    answer += to_string(value) + " ";
                    fout << answer;
                }
            }
            else if (command.compare("isEmpty") == 0)
            {
                /* BEGIN_YOUR_CODE*/
                if (pq.empty())
                {
                    fout << "TRUE ";
                }
                else
                {
                    fout << "FALSE ";
                }
                /* END_YOUR_CODE */
            }
            else if (command.compare("changeMax") == 0)
            {
                int input_value = instr_seq.getInstruction(i).getValue();
                /* BEGIN_YOUR_CODE */
                if (pq.changeMax(input_value) == 0)
                {
                    fout << "ERROR " ;
                }
                /* END_YOUR_CODE */
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << pq.printPQ() << endl;
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    const char *instr_seq;
    const char *instr_seq2;
    int node_value;
    string result;
    InstructionSequence instr_seq_heap;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3) {
        instr_seq = argv[2];
        if (task_num == 3)
            instr_seq2 = argv[3];
        if (task_num >= 5)
            instr_seq_heap.parseInstructions(argv[2]);
    }

    // Running the task(s)
    switch (task_num) {
        case 1:
            task_1(fout, instr_seq);
            break;
        case 2:
            task_2(fout, instr_seq);
            break;
        case 3:
            task_3(fout, instr_seq, instr_seq2[0]);
            break;
        case 4:
            task_4(fout, instr_seq, argv[3]);
            break;
        case 5:
            task_5(fout, instr_seq_heap);
            break;
        case 6:
            task_6(fout, instr_seq_heap);
            break;
        case 0:
            task_1(fout, "1");
            task_1(fout, "2");
            task_2(fout, TASK_2_DEFAULT_ARGUMENT);
            task_3(fout, TASK_3_DEFAULT_ARGUMENT, TASK_3_DEFAULT_ARGUMENT_2[0]);
            task_4(fout, TASK_4_DEFAULT_ARGUMENT, TASK_4_DEFAULT_ARGUMENT_2);

            instr_seq_heap.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq_heap);

            instr_seq_heap.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq_heap);
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}