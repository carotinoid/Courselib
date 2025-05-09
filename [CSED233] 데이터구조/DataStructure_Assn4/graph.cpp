#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;
#include <algorithm>

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */


void Graph::SortEdges() {
  for(int i = 0; i < numEdges; i++) {
    for(int j = 0; j < numEdges - 1; j++) {
      if(edges[j].necessary == 0 and edges[j + 1].necessary == 1) {
        swap(edges[j], edges[j + 1]);
      }
      else if(edges[j].necessary == 1 and edges[j+1].necessary == 0) {
        continue;
      }
      else {
        if(edges[j].weight > edges[j + 1].weight) {
          swap(edges[j], edges[j + 1]);
        }
        else if(edges[j].weight == edges[j + 1].weight) {
          if(node_num[edges[j].nodeA] > node_num[edges[j + 1].nodeA]) {
            swap(edges[j], edges[j + 1]);
          }
          else if(node_num[edges[j].nodeA] == node_num[edges[j + 1].nodeA]) {
            if(node_num[edges[j].nodeB] > node_num[edges[j + 1].nodeB]) {
              swap(edges[j], edges[j + 1]);
            }
          }
        }
      }
    }
  }
}

void Graph::SortAnsEdges() {
  for(int i = 0; i < numans; i++) {
    for(int j = 0; j < numans - 1; j++) {
      if(answer[j].weight > answer[j + 1].weight) {
        swap(answer[j], answer[j + 1]);
      }
      else if(answer[j].weight == answer[j + 1].weight) {
        if(node_num[answer[j].nodeA] > node_num[answer[j + 1].nodeA]) {
          swap(answer[j], answer[j + 1]);
        }
        else if(node_num[answer[j].nodeA] == node_num[answer[j + 1].nodeA]) {
          if(node_num[answer[j].nodeB] > node_num[answer[j + 1].nodeB]) {
            swap(answer[j], answer[j + 1]);
          }
        }
      }
    }
  }
}

int Graph::Rootof(int x) {
  if(parent[x] == x) return x;
  return parent[x] = Rootof(parent[x]);
}

void Graph::Union(int x, int y) {
  x = Rootof(x);
  y = Rootof(y);
  if(x == y) return;
  parent[x] = y;
}

void Graph::applyTypeEdges() {
  for(int i = 0; i < numTypeEdges; i++) {
    int nodeA = typeEdges[i].nodeA;
    int nodeB = typeEdges[i].nodeB;
    int weight = typeEdges[i].weight;
    int target = -1;
    for(int j = 0; j < numEdges; j++) {
      if(edges[j].nodeA == nodeA and edges[j].nodeB == nodeB) {
        target = j;
        break;
      }
    }
    if(weight == 0 and target != -1) {
      edges[target].necessary = 1;
    }
    if(weight == -1 and target != -1) {
      for(int j = target; j < numEdges - 1; j++) {
        edges[j] = edges[j + 1];
      }
      numEdges--;
    }
  }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

/////////1,2

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  // task 1
  undirGraph[UpperToIndex(nodeA[0])][UpperToIndex(nodeB[0])] = 1;
  undirGraph[UpperToIndex(nodeB[0])][UpperToIndex(nodeA[0])] = 1;
  exist[UpperToIndex(nodeA[0])] = 1;
  exist[UpperToIndex(nodeB[0])] = 1;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int i, j;
  int A = (int)nodeA[0] - 65;
  int B = (int)nodeB[0] - 65;
  if(B < A) swap(A, B);
  for (i = 0; i < count; i++) {
    if (node_num[i] == A)
      break;
  }
  if (i == count) {
    node_num[count] = A;
    count++;
  }
  for (j = 0; j < count; j++) {
    if (node_num[j] == B)
      break;
  }
  if (j == count) {
    node_num[count] = B;
    count++;
  }
  if(weight == 0 or weight == -1) typeEdges[numTypeEdges++] = {i, j, weight};
  else edges[numEdges++] = {i, j, weight};
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
  return 0;
}

string Graph::checkCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  // task 1
  // variables
  int visited[100] = {};
  int stack[100] = {};
  int stack_before[100] = {};
  int top = 0;
  bool cycle = false;

  while(true) {
    // finding initial node if there is
    int start = -1;
    for(int i = 1; i < 100; i++) {
      if(exist[i] == 1 and visited[i] == 0) {
        start = i;
        break;
      }
    }
    if(start == -1) break;

    // push start node to stack
    stack[++top] = start;
    stack_before[top] = -1;
    visited[start] = 1;

    // DFS to check cycle
    while(top > 0) {
      int cur = stack[top];
      int cur_before = stack_before[top--];

      for(int i = 1; i < 100; i++) {
        if(undirGraph[cur][i] == 1) {
          if(visited[i] && i != cur_before) {
            cycle = true;
            break;
          }
          if(visited[i] && i == cur_before) continue;
          stack[++top] = i;
          stack_before[top] = cur;
          visited[i] = 1;
        }
      }
    }
  }
  // return result
  if(cycle) return "TRUE";
  else return "FALSE";

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::findFurthest(string nodeA) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  // task 2
  // variables
  int start = UpperToIndex(nodeA[0]);
  int distance[100] = {};
  const int INTMAX = 2147483647;
  for(int i = 0; i < 100; i++) distance[i] = INTMAX;

  int stack[100] = {};
  int stack_distance[100] = {};
  int top = 0;

  // push start node to stack
  stack[++top] = start;
  stack_distance[top] = 0;
  distance[start] = 0;

  // DFS to find furthest node
  while(top > 0) {
    int cur = stack[top];
    int cur_distance = stack_distance[top--];

    for(int i = 1; i < 100; i++) {
      if(undirGraph[cur][i] == 1) {
        if(distance[i] > cur_distance + 1) {
          distance[i] = cur_distance + 1;
          stack[++top] = i;
          stack_distance[top] = cur_distance + 1;
        }
      }
    }
  }


  // make distance array(result)
  string result = "";
  int max_distance = 0;
  for(int i = 1; i < 100; i++) {
    if(distance[i] == INTMAX) continue;
    if(distance[i] > max_distance) {
      max_distance = distance[i];
      result = IndexToUpper(i);
    }
    else if(distance[i] == max_distance) {
      result += '\n';
      result += IndexToUpper(i);
    }
  }
  result += "\n" + to_string(max_distance);

  // // debug-------------------------
  // result += "\n\n";
  // for(int i = 1; i <= 26; i++) {
  //   if(distance[i] == INTMAX) continue;
  //   result += "i: " + to_string(i) + ", node: " + IndexToUpper(i) + ", distance: " + to_string(distance[i]) + "\n";
  // }
  // //-------------------------------

  // return result
  return result;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  int i, j;
  int A = (int)nodeA[0] - 65;
  int B = (int)nodeB[0] - 65;
  for (i = 0; i < count; i++) {
    if (node_num[i] == A)
      break;
  }
  if (i == count) {
    node_num[count] = A;
    count++;
  }
  for (j = 0; j < count; j++) {
    if (node_num[j] == B)
      break;
  }
  if (j == count) {
    node_num[count] = B;
    count++;
  }
  edge[i][j] = 1;
  exist[i] = 1;
  exist[j] = 1;

  return 0;
}

int Graph::addDirectedEdgeWCC(string nodeA, string nodeB) {

  int A = (int)nodeA[0] - 'A';
  int B = (int)nodeB[0] - 'A';

  if (A < 0 || A >= 100 || B < 0 || B >= 100) {
    return -1;
  }

  edge[A][B] = 1;
  edge[B][A] = 1;

  exist[A] = true;
  exist[B] = true;

  if (A >= cnt)
    cnt = A + 1;
  if (B >= cnt)
    cnt = B + 1;

  return 0;
}

string Graph::getTopologicalSort()
{
  // varaibles
  int indegree[100] = {};
  int queue[100] = {};
  int size = 0;
  int visited[100] = {};
  string result = "";

  // calculate indegree
  for(int i = 0; i < count; i++) {
    for(int j = 0; j < count; j++) {
      if(edge[i][j] == 1) {
        indegree[j]++;
      }
    }
  }

  // topological sort
  // initial push
  bool init_check = true;
  for(int i = 0; i < count; i++) {
    if(indegree[i] == 0) {
      init_check = false;
      queue[size++] = i;
      visited[i] = 1;
    }
  }
  if(init_check) return "ERROR";
  
  // repeat
  while(size > 0) {
    // choose cur that node_num[queue[i]] is smallest node.
    int cur = queue[0];
    int cur_index = 0;
    for(int i = 1; i < size; i++) {
      if(node_num[queue[i]] < node_num[cur]) {
        cur = queue[i];
        cur_index = i;
      }
    }
    // pop
    for(int i = cur_index; i < size - 1; i++) {
      queue[i] = queue[i + 1];
    }
    size--;
    result += char(node_num[cur] + 'A');
    result += " ";
    for(int i = 0; i < count; i++) {
      if(edge[cur][i] == 1) {
        indegree[i]--;
        if(indegree[i] == 0 && !visited[i]) {
          queue[size++] = i;
          visited[i] = 1;
        }
      }
    }
  }
  // return result
  return result;
}

string Graph::StrongConnectedComponents()
{
  for(int i = 0; i < count; i++) {
    SCCParent[i] = i;
    finished[i] = false;
  }

  while(true) {
    bool check = true;
    for(int i = 0; i < count; i++) if(finished[i] == false) check = false;
    if(check) break;

    int start;
    for(start = 0; start < count; start++) if(finished[start] == false) break;

    FindSCC(start);
  }
  // return result

  string result = "";
  int anscheck[100] = {};
  while(true) {
    bool check = true;
    for(int i = 0; i < count; i++) if(anscheck[i] == false) check = false;
    if(check) break;

    int start;
    for(start = 0; start < count; start++) if(anscheck[start] == false) break;

    for(int i = 0; i < count; i++) {
      if(SCCParent[i] == SCCParent[start]) {
        anscheck[i] = true;
        result += char(node_num[i] + 'A');
        result += " ";
      }
    }
    result += "\n";
  }
  if(result.back() == '\n') result.pop_back();
  return result;
}

string Graph::WeaklyConnectedComponents()
{
  for(int i = 0; i < count; i++) {
    WCC[i] = i;
    finished[i] = false;
  }

  while(true) {
    bool check = true;
    for(int i = 0; i < 100; i++) if(exist[i] == true and finished[i] == false) check = false;
    if(check) break;

    int start;
    for(start = 0; start < 100; start++) if(exist[start] == true and finished[start] == false) break;

    FindWCC(start);
  }

  string result = "";
  bool anscheck[100];
  for(int i = 0; i < 100; i++)  anscheck[i] = false;
  while(true) {
    bool check = true;
    for(int i = 0; i < 100; i++) if(exist[i] == true and anscheck[i] == false) check = false;
    if(check) break;

    int start;
    for(start = 0; start < 100; start++) if(exist[start] == true and anscheck[start] == false) break;

    for(int i = 0; i < 100; i++) {
      if(exist[i] == true and WCC[i] == WCC[start]) {
        anscheck[i] = true;
        result += char(i + 'A');
        result += " ";
      }
    }
    result += "\n";
  }
  if(result.back() == '\n') result.pop_back();
  return result;
}

///////////      End of Implementation      /////////////
///////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions for task4  */

int Graph::FindSCC(int x)
{
  SCCstack[SCCstackSize++] = x;
  int ret = id;
  nodeID[x] = id++;

  for(int i = 0; i < count; i++) {
    if(edge[x][i] == 1 and nodeID[i] == 0) {
      ret = min(ret, FindSCC(i));
    }
    else if(edge[x][i] == 1 and !finished[i]) {
      ret = min(ret, nodeID[i]);
    }
  }

  if(ret == nodeID[x]) {
    while(true) {
      int top = SCCstack[--SCCstackSize];
      SCCParent[top] = SCCParent[x];
      finished[top] = true;
      if(top == x) break;
    }
  }
  return ret;
}


int Graph::FindWCC(int x)
{
  int WCCstack[100] = {};
  int WCCstackSize = 0;

  WCCstack[WCCstackSize++] = x;
  finished[x] = true;

  while(WCCstackSize > 0) {
    int cur = WCCstack[--WCCstackSize];
    WCC[cur] = x;
    for(int i = 0; i < 100; i++) {
      if(exist[i] == 1 and edge[cur][i] == 1 and !finished[i]) {
        WCCstack[WCCstackSize++] = i;
        finished[i] = true;
      }
    }
  }
  return 0;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int i, j;
  int A = (int)nodeA[0] - 65;
  int B = (int)nodeB[0] - 65;
  for (i = 0; i < count; i++) {
    if (node_num[i] == A)
      break;
  }
  if (i == count) {
    node_num[count] = A;
    count++;
  }
  for (j = 0; j < count; j++) {
    if (node_num[j] == B)
      break;
  }
  if (j == count) {
    node_num[count] = B;
    count++;
  }
  directGraph[i][j] = weight;
  exist[i] = 1;
  exist[j] = 1;

  return 0;
}
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////

std::string Graph::dijkstra(std::string source, int budget,
                            std::ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string answer = "";
  int source_int = source[0] - 'A';
  int s_index;
  int dist[26] = {};

  for(s_index = 0; s_index < count; s_index ++) {
    if(node_num[s_index] == source_int) {
      break;
    }
  }
  const int INTMAX = 2147483647;
  for(int i = 0; i < 26; i++) {
    dist[i] = INTMAX;
  }
  dist[s_index] = 0;
  int visited[26] = {};

  while(true) {
    int minv = INTMAX, now = -1;
    for(int i = 0; i < count; i++) {
      if(!visited[i] and dist[i] < minv) {
        minv = dist[i];
        now = i;
      }
    }
    if(now == -1) break;
    visited[now] = 1;
    for(int next = 0; next < count; next++) {
      if(!visited[next] and directGraph[now][next] != 0) {
        dist[next] = min(dist[next], dist[now] + directGraph[now][next]);
      }
    }
  }

  for(int i = 0; i < 26; i++) {
    for(int j = 0; j < count; j++) {
      if(i == node_num[j]) {
        if(dist[j] > budget) continue;
        if(dist[j] == 0) continue;
        answer += char(i + 'A');
        answer += " ";
        answer += to_string(dist[j]);
        answer += "\n";
      }
    }
  }
  if(answer == "") return "\n";
  else fout << answer;


  // For last line, variables
  int queue[1000] = {};
  string path[1000] = {};
  int visit[1000][100] = {};
  int distance[1000] = {};
  int queue_size = 0;

  string max_path = "";
  int max_distance = 0;

  // First push
  queue[queue_size] = s_index;
  path[queue_size] = char(node_num[s_index] + 'A');
  distance[queue_size] = 0;
  visit[queue_size][s_index] = 1;
  queue_size++;

  while(queue_size > 0) {
    // Get now
    int now = queue[0];
    string now_path = path[0];
    int now_visit[100] = {};
    int now_distance = distance[0];
    for(int i = 0; i < 100; i++) {
      now_visit[i] = visit[0][i];
    }
    // Pop
    for(int i = 0; i < queue_size - 1; i++) {
      queue[i] = queue[i + 1];
      path[i] = path[i + 1];
      distance[i] = distance[i + 1];
      for(int j = 0; j < 100; j++) {
        visit[i][j] = visit[i + 1][j];
      }
    }
    queue_size--;

    // Calculate
    for(int i = 0; i < count; i++) {
      if(directGraph[now][i] != 0 and now_visit[i] == 0) {
        queue[queue_size] = i;
        path[queue_size] = now_path + " " + char(node_num[i] + 'A');
        distance[queue_size] = now_distance + directGraph[now][i];

        // If you find the better path, update
        if(distance[queue_size] <= budget) {
          if(max_path.size() == path[queue_size].size()) {
            if(max_path > path[queue_size]) {
              max_path = path[queue_size];
              max_distance = distance[queue_size];
            }
          } else if(max_path.size() < path[queue_size].size()) {
            max_path = path[queue_size];
            max_distance = distance[queue_size];
          }
        }
        
        for(int j = 0; j < 100; j++) {
          visit[queue_size][j] = now_visit[j];
        }
        visit[queue_size][i] = 1;
        queue_size++;
      }
    }
  }
  
  fout << max_path << " " << max_distance << "\n";
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return "ERROR";
}



int Graph::kruskalMST(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  // parent setting for union-find
  for(int i = 0; i < 26; i++) {
    parent[i] = i;
  }
  // sort edges
  applyTypeEdges();
  SortEdges();
  int sum = 0;

  for(int i = 0; i < numEdges; i++) {
    int x = Rootof(edges[i].nodeA);
    int y = Rootof(edges[i].nodeB);
    // if the edge is necessary
    if(edges[i].necessary == 1) {
      answer[numans++] = edges[i];
      sum += edges[i].weight;
      Union(x, y);
    }
    // if x and y have different root ( = not connected yet)
    else if(x != y) {
      sum += edges[i].weight;
      answer[numans++] = edges[i];
      // fout << char(node_num[edges[i].nodeA] + 'A') << " " << char(node_num[edges[i].nodeB] + 'A') << " " << edges[i].weight << "\n";
      Union(x, y);
    }

    // check if all nodes are connected
    int root = Rootof(0);
    bool allconnected = true;
    for(int i = 1; i < count; i++) {
      if(Rootof(i) != root) {
        allconnected = false;
        break;
      }
    }
    // if all nodes are connected, break
    if(allconnected) break;
  }
  SortAnsEdges();
  for(int i = 0; i < numans; i++) {
    fout << char(node_num[answer[i].nodeA] + 'A') << " " << char(node_num[answer[i].nodeB] + 'A') << " " << answer[i].weight << "\n";
  }
  return sum;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
