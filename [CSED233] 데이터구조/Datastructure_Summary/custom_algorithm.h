#include <iostream>
#include <vector>

namespace da
{
    /*
    # 2. c++.pdf
    How C++ workds?
    1. Create a C++ source file and save it.
    2. Compile. Using a compiler, creates a machine-code interpretation of your program. Using a linker, includes any required library functions needed.
    3. Execute program and see resultes.

    ## The Structure of simple C++ program.

    - Headerfile?
    #include <> is a headerfile library. Header files add functionality to  C++ programs. You can make your own header files as well.
    Ex) #include <iostream>, #include <cstdlib>...

    - Comments?
    Comments can be used to explain c++ code and to make it more readable.
    singled-line comment : //, multi-lined comment : /* *\/

    - Main function
    Always appear in a C++ program: int main(). This is called a function. Any code inside it's curly brackets {} will be executed.

    - Variables and Types
    - Standard function and namespace(std)
    - Inputs and Outputs
    - Enumberations
    - address and pointers
    - arrays
    - pointers and arrays
    - strings
    - structures
    - dynamic memory allocation
        - new and delete
        - garbage collection
    - references

    - expressions and operators
    - casting(implied and explicit)
    - for loops and break statement, continue statement
    - Functions, signatures(prototype)
    - Class

    ---

    # 3. algorithm.pdf
    - Algorithm
    A step-by-step procedure for solving a problem in a finite amount of time.
    How to compare two algorithms?
    One measure is efficiency
    - Running time (time complexity)
    - Space requirements (space complexity)
    Two ways of comparison
    - Empirical studies (programming & testing)
    - Theoretical analysis (mathematical proofs)

    **Empirical studies**
    Programming & testing -> much effort to implement the algorithm, and result may not apply to other inputs which are not included in the experiment. and for fair comparison, the same H/W and S/W environment should be used.

    So, No need to be so exact.
    Actually, for exmaple, $6N^2$ and $20N^@$ are very similar when N is big enough. so Theoretical analysis, is high-level description of the algorithm instead of an implementation.
    - Running time - as a function of the input size $n$, Consider all possible inputs.

    Best case
    - Big-Omega notation
    $T(n)$ is $\Omega(f(n))$ if there exist a constant $c>0$ & an integer constant $n_0 \ge 1$ such that $T(n) \ge c f(n) forall n \ge n_0$
    - Lower bound

    Average case
    - Difficult to analyze
    - Big-Theta notation
    T(n) is $\Theta(f(n))$ if $T(n)$ is $O(f(n)) and \Sigma(f(n))$
    $c_1 f(n) /le T(n) /le c_2 f(n) for all n /ge n_0$

    Worst case
    - Easier to analyze
    - Big-Oh notation
    - Upper bound
    An algorithm is $O(f(n))$ if there exist a constant $c>0$ & an integer constant $n_0 \ge 1$ such that $T(n) \le cf(n)$ for all $n \ge n_0$.
    Then we write $T(n) \in O(f(n))$, or $T(n) = O(f(n))$.
    Ex) T(n) = (n+1)^2, is O(n^2)

    ## Properties of Big-Oh
    Addition rule, Product Rule, and others.

    Typical growth rates:
    - Theta(1) - constant
    - Theta(log n) - logarithmic
    - Theta(n) - linear
    - Theta(n log n) - log linear
    - Theta(n^2) - quadratic
    - Theta(n^3) - cubic
    - Theta(2^n) - exponential
    - Theta(n!) - factorial

    **Limitation of Analysis**
    - Not account for constant factors, but constant factor ay dominate.
    ex, 1000n vs n^2, when interested only in n < 1000.
    - Not account for different memory access times at different levels of memory hierarchy.
    ex, Cache memory << MM << HDD.
    - Programs that do more computation may take less time than those that do less computation.
        - Cost fetch from MM >> Cost operated in CPU.
        - Memory access could take more that computation.

    Relatives of Big-Oh
    - Little-oh
    - little-omega
    not used as often as big-series.

    ---

    # 4. List, Stack, and Queue.
    ## Lists.
    list L = <a1, a2, a3, ..., an>
    a finite, ordered collection of elements.
    n : length(size) of the list.

    position of a_i is i.
    sorted list / unsorted list.

    List operations
    - insert(x, p, l) : insert element x at position p in list l.
    - delete(p, l) : delete element at position p in list l.
    - Next(p, L) : returns the position oor pointer immediately following position p.
    - Previous(p, L) : returns the position or pointer previous to p.
    - Locate(x, L) : returns the position of x on L.
    - Retrieve(p, L) : returns element at position p on L.
    - MakeNull(L) : causes L to become an empty list and returns potion END(L).
    - First(L) : returns the position of the first element of L.
    ... and Check out STL's vector. :)

    Array-based list
    ~
    Pointer-based list
    ~
    Cursor-based list
    ~

    ## Stack
    ~

    ## Queue
    ~
    Array-based queue
    ~
    linked queue
    ~
    Type of queue : queue, circular queue, priority queue, double-ended queue.

    ## Testing
    ~

    # 5. trees.pdf
    # 6. Priority Queue
    # 7. Sorting
    Sorting?
    Types of Sorting
    - Memory usage,
    - Comparison
    - Stability

    - Some typical sorting algorithms
        - Bubble sort
*/

    void bubble_sort(std::vector<int>& vec, int t = 1)
    {
        // t == 1 -> ascending order
        if(t == 1)
        {
            for(int i = 0; i < vec.size(); i++)
                for(int j = 0; j < vec.size() - i - 1; j ++)
                    if(vec[j] > vec[j+1]) std::swap(vec[j], vec[j+1]);
        }
        else //if(t == 0) -> descending order
        {
            for(int i = 0; i < vec.size(); i++)
                for(int j = 0; j < vec.size() - i - 1; j ++)
                    if(vec[j] < vec[j+1]) std::swap(vec[j], vec[j+1]);
        }
    }
/*
        - Selection sort
*/
    void selection_sort(std::vector<int>& vec, int t = 1)
    {
        if(t == 1)
        {
            for(int i = 0; i < vec.size() - 1; i++)
            {
                int minidx = i;
                for(int j = i + 1; j < vec.size(); j++) if(vec[j] < vec[minidx]) minidx = j;
                std::swap(vec[i], vec[minidx]);
            }
        }
        else
        {
            for(int i = 0; i < vec.size() - 1; i++)
            {
                int maxidx = i;
                for(int j = i + 1; j < vec.size(); j++) if(vec[j] > vec[maxidx]) maxidx = j;
                std::swap(vec[i], vec[maxidx]);
            }
        }
    }
/*
        - Insertion sort
*/
    void insertion_sort(std::vector<int>& vec, int t = 1)
    {
        if(t == 1)
        {
            for(int i = 1; i < vec.size(); i++)
                for(int j = i; j > 0; j--)
                    if(vec[j] < vec[j-1]) std::swap(vec[j], vec[j-1]);
                    else break;
        }
        else
        {
            for(int i = 1; i < vec.size(); i++)
                for(int j = i; j > 0; j--)
                    if(vec[j] > vec[j-1]) std::swap(vec[j], vec[j-1]);
                    else break;
        }
    }
/*
        - Bucket sort
*/

/*
        - Merge sort
        - (recursive) Quick sort
        - Quick sort
            How to chooes pivot?
        - Heap sort

    Quick sort vs merge sort

    # 8. binear search trees
*/
}
