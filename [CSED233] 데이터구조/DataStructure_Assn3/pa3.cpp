/*
    Programming Assignment #3
*/
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#include "utils.h"
#include "avl.h"
#include "bst.h"
#include "sort.h"
#include "tree.h"
#include "open_hash_function.h"
#include "open_hash_table.h"
#include "closed_hash_function.h"
#include "closed_hash_table.h"

using namespace std;

/*
    [Task 1] Bubble sort

    Description:
        Implement a function that sorts a given array using the bubble sort
        algorithm in ascending order. You can modify sort.cpp and sort.h files for
        this problem.

        TODO: Implement sortAlg::bubbleSort function

    Input:
        - ('insertion',integer): insert integer into the array
        - ('bubbleSort',NULL): sort the array using bubble sort algorithm

    Output:
        Print every value in the array whenever the k-th lowest key rises to
        k-th position, including the initial state, separating the values with white
        space. Please use a built-in function to print the array. We won’t test array
        size over 20 or array size of 0.

    Testcase:
./pa3.exe 1 "[('insertion',7), ('insertion',6),('insertion',5), ('insertion',4),('insertion',3), ('insertion',2), ('insertion',1), ('bubbleSort',NULL)]"
./pa3.exe 1 "[('insertion',17), ('insertion',20), ('insertion',2), ('insertion',21), ('insertion',4), ('bubbleSort',NULL)]"
./pa3.exe 1 "[('insertion',42), ('insertion',20),('insertion',17), ('insertion',13),('insertion',28), ('insertion',14),('bubbleSort',NULL)]"

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 1]" << endl;
    try
    {
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insertion") == 0)
            {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            }
            else if (command.compare("bubbleSort") == 0)
            {
                sort.printArray(fout);
                sort.bubbleSort(fout);
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

/*
    [Task 2] Merge sort

    Description:
        Implement a function that sorts a given array using the merge sort
        algorithm in descending order using non-recursive merge sort.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::mergeSort function
        TODO: Implement sortAlg::merge function

    Input:
        - ('insertion',integer): insert integer into the array
        - ('mergeSort',NULL): sort the array using merge sort algorithm

    Output:
        Starting from the initial state of the array, print all values of the
        array at each iteration step after performing the necessary sorting.
        Print the array values at the initial state and at each iteration step where sorting is performed.
        Separate the values in the array with a space for each iteration step.
        You don’t need to consider exceptional cases such as overflow or an empty array. We will not test such cases.

    Testcase:
./pa3.exe 2 "[('insertion',1),('insertion',2),('insertion',3),('insertion',4),('insertion',5),('insertion',6), ('insertion',7),('mergeSort',NULL)]"
./pa3.exe 2 "[('insertion',36), ('insertion',20),('insertion',17), ('insertion',13),('insertion',14), ('insertion',28),('insertion',15), ('insertion',23),('insertion',32),('mergeSort',NULL)]"
./pa3.exe 2 "[('insertion',56),('insertion',42),('insertion',20),('insertion',17),('insertion',13),('insertion',28),('insertion',14),('mergeSort',NULL)]"

*/

void task_2(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 2]" << endl;
    try
    {
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insertion") == 0)
            {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            }
            else if (command.compare("mergeSort") == 0)
            {
                sort.printArray(fout);
                sort.mergeSort(fout, 0, sort.arr_size - 1);
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

/*
    [Task 3] BST Insertion / Deletion / Summation

    a.	Implement functions that inserts and deletes an element into a binary search tree (BST).
    Also you should find the sum of nodes that is larger than specific node value,
    and print the pre-order and in-order of the tree.
    You can modify bst.cpp and bst.h files for this problem.

    -	Input of nodes are integers from 1 to 99

    b.	Input & output of BinarySearchTree::insertion
        - Input: ('insertion',integer): Key of the element to be inserted. The key has a positive integer value.
        - Output: Return the -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    c.	Input & output of BinarySearchTree::deletion
        - Input: ('deletion',integer): Key of the element to be deleted.
        - Output: Return -1 if the key does not exist in the tree, 0 otherwise. If the key does not exist, do not delete any element
        Note that replace the smallest key in right subtree when delete the node with degree 2

    d.	Input & output of BinarySearchTree::sum
        - Input: ('sum',integer): Sum of the nodes greater than the integer.
        - Output: Return the sum of nodes that is larger than the key value.

    e.	task_3 prints
        i.	the return for each insertion/deletion for command (‘insertion’, integer)/ (‘deletion’, integer) and
        ii.	the return summation of nodes that is larger than a specific node value for command (‘sum’, integer) and
        iii.	the results of preorder and inorder traversal of the constructed tree for command (‘print’, NULL).
        (If empty tree, don’t return preorder or inorder traveral results)
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 3]" << endl;
    try
    {
        BinarySearchTree tree;
        int ret;
        for (int i = 0; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0)
            {
                ret = tree.insertion(key);
                fout << ret << endl;
            }
            else if (command.compare("deletion") == 0)
            {
                ret = tree.deletion(key);
                fout << ret << endl;
            }
            else if (command.compare("sum") == 0)
            {
                ret = tree.sum(key);
                fout << ret << endl;
            }
            else if (command.compare("print") == 0)
            {
                fout << tree.preOrder() << endl;
                fout << tree.inOrder() << endl;
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

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

void task_4(ofstream &fout, string expression)
{
    fout << "[Task 4]" << endl;
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
        fout << "Inorder" << endl;
        tree.printInOrder(fout);
        fout << "Preorder" << endl;
        tree.printPreOrder(fout);

        ///////////      End of Implementation      /////////////
        ///////////////////////////////////////////////////////
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

/*
    [Task 5] Open hash table

    Description:
        Suppose there is an open hash table with digit-folding-method.
        This hash table uses a singly linked list as a collision handling method.
        This hash table is used with integer keys and hashing into a table of size M.
        Every component of the key is folded with a size of 1(digit)
        and calculates their sum as described in our Lecture Note.

        M which is the size of the hash table, insertions,
        and deletions of integers are given as instructions.
        First, for each insertion, record if a collision occurred.
        A collision occurs when a key is inserted into a non-empty slot.
        After all operations are complete, print the total number of collisions that occurred
        and the length of the longest chain in the hash table.

        You can modify open_hash_function.cpp, open_hash_table.cpp,
        open_hash_function.h and open_hash_table.h files for this problem.

    Input: Two commands (The order is always 'M', and 'insertion')
        - ('M', integer): The size of a key
        - ('insertion', integer): A key to be hashed (in decimal)
        - ('deletion', integer): delete integer from the hash table.

    Output: For each slot of the hash table, print out
        - the number of collisions occurred during execution.
        - the length of the longest chain in the final table.

*/

void task_5(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 5]" << endl;
    try
    {
        int M;
        OpenHashFunction *hf;
        OpenHashTable *ht;

        if (instr_seq.getLength() < 2 ||
            instr_seq.getInstruction(0).getCommand().compare("M") != 0)
        {
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        M = instr_seq.getInstruction(0).getValue();
        hf = new OpenHashFunction(M);
        ht = new OpenHashTable(M, hf);

        for (int i = 1; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0)
            {
                ht->insert(key);
            }
            else if (command.compare("deletion") == 0)
            {
                ht->delete_(key);
            }
            else
            {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }

        ht->print_result(fout);

        delete ht;
        delete hf;
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

/*
    [Task 6] Closed hash table

    Description:
        Implement insertion of a closed hash table with rehashing implementation.
        This hash table is used with integer keys and hashing into a table of size M.
        This hash table uses pseudo-random probing as a collision handling method.
        The index of the key k  after i-th collision, h_i (k), is:

        h_i (k)=(h(k)+d_i) mod M

        where  h(k) is the digit-folding method hash function.
        It works same with the hash function in task 5.

        d_1,d_2,…,d_(M-1) is a pseudo-random permutation of integers 1, … , M-1
        and it is generated by shift-register sequence.
        Please refer to slide “Example: Shift-Register Sequence” in “Hashing” Lecture Note for detail.

        Given M, k, d_1 for the shift-register sequence and inserted integers, print the result hash table.
        If the hash table is full or the collision cannot be resolved, stop the insertion,
        and print results of the insertions made up to that point, then print FAIL.
        Refer to instruction b & c for more detail.

        You don’t need to consider a deletion of a key, multiple insertions of the same key.
        You can modify closed_hash_function.cpp, closed_hash_table.cpp,
        closed_hash_function.h and closed_hash_table.h files for this problem.

    Input: A sequence of commands
        - ('M',integer): the size of a hash table.
                        (The first command is always 'M')
        - ('k',integer): a constant used for shift-register sequence.
                        (The second command is always 'k')
        - ('d',integer): the first probing offset for the shift-register sequence .
                        (The third command is always 'd')
        - ('insertion',integer): insert integer into the hash table.

    Output: For each slot of the hash table, print out
        - the value, if the state of the slot is occupied.
        - 'EMPTY' if the state of the slot is empty.
        'FAIL' if the hash table is full or the collision cannot be resolved.

*/

void task_6(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 6]" << endl;
    try
    {
        int M, k, d1;
        ClosedHashFunction *hf;
        ClosedHashTable *ht;

        if (instr_seq.getLength() < 2 ||
            instr_seq.getInstruction(0).getCommand().compare("M") != 0)
        {
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        M = instr_seq.getInstruction(0).getValue();
        k = instr_seq.getInstruction(1).getValue();
        d1 = instr_seq.getInstruction(2).getValue();
        hf = new ClosedHashFunction(M);
        ht = new ClosedHashTable(M, k, d1, hf);

        for (int i = 3; i < instr_seq.getLength(); i++)
        {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0)
            {
                ht->insert(key);
            }
            else
            {
                cout << command << endl;
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }

        ht->print_table(fout);

        delete ht;
        delete hf;
    }
    catch (const char *e)
    {
        cerr << e << endl;
    }
}

int main(int argc, char **argv)
{
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence instr_seq;
    string expression;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open())
    {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3)
    {
        if (task_num == 4)
        {
            expression = argv[2];
        }
        else
        {
            try
            {
                instr_seq.parseInstructions(argv[2]);
            }
            catch (const char *e)
            {
                cerr << e << endl;
                return -1;
            }
        }
    }

    // Running the task(s)
    switch (task_num)
    {
    case 1:
        task_1(fout, instr_seq);
        break;
    case 2:
        task_2(fout, instr_seq);
        break;
    case 3:
        task_3(fout, instr_seq);
        break;
    case 4:
        task_4(fout, expression);
        break;
    case 5:
        task_5(fout, instr_seq);
        break;
    case 6:
        task_6(fout, instr_seq);
        break;
    case 0:
        instr_seq.parseInstructions(TASK_1_DEFAULT_ARGUMENT);
        task_1(fout, instr_seq);

        instr_seq.parseInstructions(TASK_2_DEFAULT_ARGUMENT);
        task_2(fout, instr_seq);

        instr_seq.parseInstructions(TASK_3_DEFAULT_ARGUMENT);
        task_3(fout, instr_seq);

        expression = TASK_4_DEFAULT_ARGUMENT;
        task_4(fout, expression);

        instr_seq.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
        task_5(fout, instr_seq);

        instr_seq.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
        task_6(fout, instr_seq);
        break;
    default:
        cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
