#pragma once
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;
// Number of vertices in the graph
#define V 26

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph(){};
  ~Graph(){};

  /////////////////////////////////////////////////////////
  //////  TODO: Add public members if required ///////////
  int UpperToIndex(char letter) { //task 1 & 2
    return letter -'A' + 1;
  }
  char IndexToUpper(int index) { //task 2
    return index + 'A' - 1;
  }
  int FindSCC(int); //task 4
  int FindWCC(int); //task 4 (implmented in graph.cpp)

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);

  string checkCycle();
  string findFurthest(string nodeA);

  int addDirectedEdge(string nodeA, string nodeB);
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  int addDirectedEdgeWCC(string nodeA, string nodeB);
  string getTopologicalSort();
  string StrongConnectedComponents();
  string WeaklyConnectedComponents();

  string dijkstra(string source, int budget, ofstream &fout);

  int kruskalMST(ofstream &);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  //======== task 1, 2 ========== //done
  int undirGraph[100][100] = {0};
  //=============================

  //========== task 3 =========== //done
  int edge[100][100] = {0};
  int node_num[100] = {-1,};
  int count = 0;
  int cnt = 0;
  bool exist[100] = {0};
  //=============================

  //========== task 4 =========== //TODO
  int id = 1, SCCParent[100];
  int nodeID[100];
  bool finished[100];
  int SCCstack[100], SCCstackSize = 0;
  int WCC[100];
  //=============================

  //========== task 5 =========== //done
  int directGraph[26][26] = {0,};
  //=============================

  //========== task 6 =========== //TODO
  struct Edge {
    int nodeA, nodeB, weight;
    int necessary = 0;
  };
  Edge edges[1000];
  Edge typeEdges[1000];
  Edge answer[1000];
  int numans = 0; //This is not nu-mans, this is num-ans
  int numEdges = 0;
  int numTypeEdges = 0;
  int parent[26] = {};
  void SortEdges();
  int Rootof(int);
  void Union(int, int);
  void applyTypeEdges();
  void SortAnsEdges();
  //=============================

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
