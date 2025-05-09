#include "graph.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

/*
    [Task 1] Undirected Graph - Cycle

    Description:
        Implement a function that returns whether the given undirected graph
   forms a cycle or not. The given graph is a simple graph, which does not have
   more than one edge between any two vertices and self-loop. A cycle is a path
   of length 3 or more that starts and ends at the same vertices. You can modify
   graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge, Graph::checkCycle

    Input & output
    Input: Pairs odf nodes with alphabet labels that indicate edges.
        - ('A','B'): an edge between node A and node B.
                     The names of the nodes are restricted to uppercase
   alphabetic characters. Output:
        - TRUE if the graph forms a cycle, FALSE otherwise.
        Note that they must be printed in uppercase.

    Testcases:
  Example input
./pa4 1 "[('A','B'), ('B','C'), ('A','C')]"
./pa4 1 "[('A','B'), ('A','C'), ('C','D')]"

  Exmaple output
True
False
*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 1]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addUndirectedEdge(firstNode, secondNode);
    }
    fout << graph.checkCycle() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 2] Undirected Graph - Furthest node

    Description:
        Implement a function that returns nodes which are the furthest distance
        from the given source node in the given undirected graph, and their
   distance. The distance is defined as the number of edges in the shortest path
   from the source node. Also, the given graph is a simple graph. You can modify
   graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge, Graph::findFurthest functions

    Input & output
    Input: Pairs of nodes with alphabet labels that indicate edges.
        - ('A','B'): an edge between node A and node B.
                     The names of the nodes are restricted to uppercase
   alphabetic characters. -	('A',NULL): the source node. You should find a
   node that is furthest from this source node. Output:
        - The furthest node.
        If there are some nodes that have the same distance with the found
   furthest node, print them all in lexicographic order.
        - Distance

    Testcases:
  Example input
./pa4 2 "[('A','B'), ('B','C'), ('D','C'), ('A',NULL)]"
./pa4 2 "[('A','B'), ('B','C'), ('A','C'), ('A',NULL)]"
./pa4 2 "[('A','B'), ('A','C'), ('C','D'), ('C','E'), ('B','D'), ('D','E'), ('A',NULL)]"
./pa4 2 "[('A','B'), ('B','C'), ('D','C'), ('E','F'), ('A',NULL)]"

  Exmaple output (No newline)
D 3
B C 1
D E 2
D 3
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 2]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength() - 1; i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addUndirectedEdge(firstNode, secondNode);
    }
    string sourceNode =
        instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();

    fout << graph.findFurthest(sourceNode) << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 3] Directed Graph - Topological Sort

   a.	Implement a function that performs a topological sort using the given
   directed graph. If there exists more than one result, print the topological
   sort that comes first in the ascending order. To take an example below,
   acceptable topological sorts are ‘A B C D F E’, ‘A C B F E D’, ‘A C D B F E’,
   etc. Among these, the desirable output is ‘A B C D F E’.  Also, print ‘error’
   if the topological sort could not be performed. You can modify graph.cpp and
   graph.h files for this problem.

    * You do not have to think about self loop cases. We will not put such case
   in our test case.

    b.	Input & output
    Input: Pairs of node labels that indicate edges.
    -	('A','B'): an edge from node A to node B.
    -	If the input edge already exists in the graph, ignore the input.

    Output:
    -	Result of topological sort or ‘ERROR’ message

    Testcases:
  Example input
./pa4.exe 3 "[('A','B'),('A','C'),('B','F'),('F','E'),('C','E'),('C','D')]"
./pa4.exe 3 "[('A','B'), ('A','D'), ('B','C'), ('C','E'),('D','E'), ('E','F')]"
./pa4.exe 3 "[('B','C'), ('C','D'), ('D','B')]"
  Example output
A B C D F E
A B C D E F
ERROR
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 3]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addDirectedEdge(firstNode, secondNode);
    }

    fout << graph.getTopologicalSort() << endl;

  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 4] Directed Graph - Strongly & Weakly Connected Components 

    a.	Implement a function that returns the strongly connected components and
   weakly connected components in the given directed graph. Print the strongly
   and weakly connected components in the ascending order. We show an example
   below. You can modify graph.cpp and graph.h and pa4.cpp files for this
   problem.

    b.	Input & output
    Input: Pairs of node labels that indicate edges.
    -	('A','B'): an edge from node A to node B
    -	If the input edge already exists in the graph, ignore the input.

    Output:
    -	Strongly and Weakly connected components in ascending order. Each
   strongly and Weakly connected components are separated with Enter as shown in
   Output examples. Please first print all the strongly connected components
   then start to print the weakly connected components.

    Testcases:
  Example input
./pa4 4 "[('A','B'),('C','A'),('B','C'),('D','B'),('D','E'),('E','G'),('G','F'),('F','E')]"
./pa4 4 "[('A','B'), ('B','C'), ('A','C')]"
./pa4 4 "[('A','B'), ('B','C'), ('C','A')]"
./pa4 4 "[('A','B'), ('B','C'), ('A','C'), ('D','E'), ('E','F'), ('F','D')]"

*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 4]" << endl;
  try {
    Graph graph;
    Graph graph2;

    for (int i = 0; i < instr_seq.getLength(); i++) {
      string firstNode = instr_seq.getInstruction(i).getCommand();
      string secondNode = instr_seq.getInstruction(i).getValueStr();
      graph.addDirectedEdge(firstNode, secondNode);
      graph2.addDirectedEdgeWCC(firstNode, secondNode);
    }

    fout << graph.StrongConnectedComponents() << endl;
    fout << graph2.WeaklyConnectedComponents() << endl;

  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 5] Dijkstra's Algorithm

    Description:
      Implement a function that finds paths from the source node to all other
   nodes that the total cost of path is lower than the given budget. We assume
   that the given graph is a directed, weighted, and weakly-connected graph. All
   weights of edges are positive (i.e. larger than 0). This function should
   return the pair of the reachable destination node and the total cost (sum of
   the weights of the edges) of the path. Additionally, print the path with the
   most nodes and its total cost within the budget at the end. If the path from
   the source node to the destination node doesn’t exist, return an empty line.
   The maximum number of nodes in the graph is 26 (A to Z), without considering
   duplicate nodes.

        TODO: Implement Graph::addDirectedEdge and Graph::dijkstra functions

    Input & output
    Input: A sequence of commands
        - (‘A-B’, integer): an edge from node ‘A’ to node ‘B’ with a weight
   value {integer}.
        - (‘A’, integer) : The first element indicates the source node and the
   second integer indicates the allowed budget. Output:
        - Pairs of the destination node and the total cost of the path (the
   sequence of pairs should be in lexicographical order). Node and cost
   separated with space.
        - Print the path that includes the most nodes within the budget at the
   end.
        - An empty line if the path does not exist. (It should include '\n', a
   newline character.)

    Testcases:
  Example input
./pa4 5 "[('A-B',10),('A-C',3),('B-D',5),('C-B',2), ('C-E',15),('A-D',20),('D-E',11),('A',11)]"
./pa4 5 "[('A-B',10),('A-C',3),('B-D',5),('C-B',2), ('C-E',15),('A-D',20),('D-E',11),('A',1)]"
./pa4 5 "[('A-B',10),('A-C',3),('B-D',5),('C-B',2), ('C-E',15),('A-D',20),('D-E',11),('A',20)]"
./pa4 5 "[('A-B',10),('A-C',3),('B-D',5),('C-B',2), ('C-E',15),('A-D',20),('D-E',11),('D',12)]"

 */

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 5]" << endl;
  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength() - 1; i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      int value = instr_seq.getInstruction(i).getValue();
      string firstNode = command.substr(0, command.find('-'));
      string secondNode =
          command.substr(command.find('-') + 1, command.length());
      graph.addDirectedEdge(firstNode, secondNode, value);
    }

    string command =
        instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();
    string source = command;
    int budget = instr_seq.getInstruction(instr_seq.getLength() - 1).getValue();
    graph.dijkstra(source, budget, fout);
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 6] Advanced Kruskal's Algorithm

    Description:
      Implement a function that finds the Minimum-cost Spanning Tree (MST) of
   the given weighted undirected graph using Kruskal's algorithm, with the
   option to include or exclude specific edges. The MST should include/exclude
   specific edges as indicated by input values of 0 or -1 (please refer to the
   input & output section for clarity). The function should print each added
   edge and its weight as the MST grows. The edge weights will be within the
   range of 1 to 100. When printing an edge, the labels must be in
   lexicographical order. If multiple edges have the same weight, the function
   should select edges in lexicographical order by comparing the first node of
   each edge, and if they are the same, then comparing the second node. The
   function returns the total cost of the MST (i.e., the sum of the edge
   weights). You can assume that the given graph is connected. You are allowed
   to modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::KruskalMST function

    Input: A sequence of commands
    -	('A-B', integer): an edge between node A and node B with a weight value
of {integer}. -	(‘A-B’, 0): an edge that should be excluded in MST -	(‘A-B’,
-1): an edge that should be included in MST -	('MST', NULL): find MST using
Kruskal's algorithm. Output: -	For each time the tree grows, print the labels
of the nodes indicating the added edges in lexicographical order and the weight
of the edge as a string separated with a white space. -	Print the cost of MST.

    Testcases:
  Example input
./pa4 6 "[('A-B', 3), ('C-A', 1), ('C-B', 4), ('B-D', 1), ('C-D', 2), ('D-E', 5), ('MST', NULL)]"
./pa4 6 "[('D-B', 1), ('D-C', 2), ('E-D', 5), ('B-A', 3), ('C-A', 1), ('C-B', 4), ('B-D', -1), ('MST', NULL)]"
./pa4 6 "[('A-B', 1), ('B-C', 1), ('C-D', 1), ('D-A', 1), ('A-C', 1), ('B-D', 1), ('MST', NULL)]"
./pa4 6 "[('D-B', 1), ('D-C', 2), ('E-D', 5), ('B-A', 3), ('C-A', 1), ('C-B', 4), ('A-B', 0), ('MST', NULL)]"

 */

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
  fout << "[Task 6]" << endl;

  try {
    Graph graph;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("MST") == 0) {
        fout << graph.kruskalMST(fout) << endl;
      } else {
        string firstNode = command.substr(0, command.find('-'));
        string secondNode =
            command.substr(command.find('-') + 1, command.length());
        int value = instr_seq.getInstruction(i).getValue();

        /////////////////////////////////////////////////////////
        //////////  TODO: Implement From Here      //////////////
        graph.addUndirectedEdge(firstNode, secondNode, value);

        ///////////      End of Implementation      /////////////
        ///////////////////////////////////////////////////////
      }
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence instr_seq;

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
    try {
      instr_seq.parseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
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
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, instr_seq);
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

    instr_seq.parseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq);

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