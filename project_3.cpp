/***********************************************
************CSCI-311-PROJECT-3-V-1011***********
************************************************
*******CODE-CHECKER-STARTING-ALIGNMENT**********
************************************************
*************CONTROL-NUMBER-XA-73***************
************************************************
**REPORT-GENERATION-MODE-AUTO_SYNC-EXCEPTION-2**
************************************************
*****************DATETIME-SYS*******************
************************************************/

//G1_EXCEPTION: Only produce your code as directed in Section A, B, C, and D1_EXCEPTION.
//G2_EXCEPTION: Do not write anything at the other places in this file.
//D1_EXCEPTION: Put you names here (on this line): Jake Baartman

/***********************************************
*************SECTION-A-HEADERS******************
************************************************/
//SECTION_A_START: put your header files here using the include directive.
//G3_EXCEPTION: You can also declare using standard namespace if you like, but do
//not use any global variable or method.

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <memory>
#include <algorithm>

using namespace std; // use standard namespace for convenience

//SECTION_A_END: Section A ends here.
/***********************************************
*************SECTION-A-HEADERS-END**************
************************************************/

/***********************************************
*************SECTION-B-CLASSES******************
************************************************/
//SECTION_B_START: put all your classes definitions here.

struct Node {
  int id;
  bool hasChargingStation;
  int distance; // shortest distance to this node
  int remainingCharge; // remaining charge when reaching this node
  vector<int> path; // path taken to reach this node

    // comparison operator for min-heap
  bool operator<(const Node& other) const {
      return distance > other.distance; // prioritize shorter distances
  }
};

struct Edge {
  int u, v, weight; // edge connects u to v with a weight
};

class Graph {
public:
  vector<shared_ptr<Node>> nodes; // list of nodes in the graph
  vector<vector<pair<int, int>>> adjList; // adjacency list with weights
  int maxCharge; // max battery charge capacity

  Graph(int n) : adjList(n) {} // initialize graph with n nodes

  void addNode(int id, bool hasChargingStation) {
    auto node = make_shared<Node>();
    node->id = id;
    node->hasChargingStation = hasChargingStation;
    node->distance = INT_MAX; // set initial distance to infinity
    node->remainingCharge = 0; // no charge initially
    nodes.push_back(node); // add node to graph
  }

  void addEdge(int u, int v, int weight) {
    adjList[u].push_back(make_pair(v, weight)); // add edge u->v
    adjList[v].push_back(make_pair(u, weight)); // add edge v->u
  }

  void findShortestPath(int start, int end, int maxCharge, int initialCharge) {
    this->maxCharge = maxCharge;

    // reset all nodes before starting the search
    for(auto& node : nodes) {
      node->distance = INT_MAX;
      node->remainingCharge = 0;
      node->path.clear();
    }

      // priority queue for dijkstra's algorithm
      priority_queue<Node> pq;
      nodes[start]->distance = 0; // starting node distance is 0
      nodes[start]->remainingCharge = initialCharge; // set initial charge
      nodes[start]->path.push_back(start); // path starts with the node itself
      pq.push(*nodes[start]); // add starting node to the queue

      while(!pq.empty()) {
        auto current = pq.top(); // get the closest node
        pq.pop();

        if(current.id == end) { // reached destination
          printPath(current.path, current.distance);
          return;
        }

        // check all neighbors of the current node
        for(size_t i = 0; i < adjList[current.id].size(); i++) {
          int neighbor = adjList[current.id][i].first; // neighbor node
          int weight = adjList[current.id][i].second; // edge weight

          if (weight > current.remainingCharge) continue; // not enough charge to travel

          int newDistance = current.distance + weight; // calculate new distance
          int newCharge = current.remainingCharge - weight; // calculate remaining charge

          if(nodes[neighbor]->hasChargingStation) {
            newCharge = maxCharge; // recharge at charging station
          }

          // update neighbor node if a shorter path is found
          if(newDistance < nodes[neighbor]->distance) {
            nodes[neighbor]->distance = newDistance;
            nodes[neighbor]->remainingCharge = newCharge;
            nodes[neighbor]->path = current.path; // update path
            nodes[neighbor]->path.push_back(neighbor);

            pq.push(*nodes[neighbor]); // add neighbor to the queue

          }
        }
      }

      // no suitable path found
      cout << "No suitable path from " << start << " to " << end << " exists" << endl;
  }

  void printPath(const vector<int>& path, int distance) {
    cout << "Verify Path: 1\n" << distance << ": ";
    for(size_t i = 0; i < path.size(); i++) {
      cout << path[i] << " "; // print each node in the path
    }
    cout << endl;
  }
};

//SECTION_B_END: Section B ends here.
/***********************************************
*************SECTION-B-CLASSES-END**************
************************************************/
/***********************************************
*************SECTION-C-MAIN-FUNCTION************
************************************************/
//SECTION_C_START: write your main function here.

bool verifyPath(Graph& G, const vector<int>& path, int initialCharge, int maxCharge) {
  int charge = initialCharge;
  for(size_t i = 0; i + 1 < path.size(); i++) {
    int u = path[i];
    int v = path[i + 1];

    bool edgeFound = false; // flag to check if edge exists
    int weight = -1;

    // find the edge between u and v
    for(size_t j = 0; j < G.adjList[u].size(); j++) {
      if(G.adjList[u][j].first == v) {
        weight = G.adjList[u][j].second;
        edgeFound = true;
        break;
      }
    }

    if (!edgeFound || weight == -1) return false; // invalid path

    if (weight > charge) return false; // not enough charge for this edge

    charge -= weight; // reduce charge after traveling the edge
    if (G.nodes[v]->hasChargingStation) {
      charge = maxCharge; // recharge at charging station
    }
  }
  return true; // path is valid
}

int main() {
  int n, m, maxCharge, initialCharge;
  cin >> n >> m >> maxCharge >> initialCharge; // input graph details

  int start, end;
  cin >> start >> end; // input start and end nodes

  Graph graph(n); // create graph with n nodes

    // input node details
  for(int i = 0; i < n; ++i) {
    int id, hasChargingStation;
    cin >> id >> hasChargingStation;
    graph.addNode(id, hasChargingStation);
  }

    // input edges
  for(int i = 0; i < m; ++i) {
    int u, v, weight;
    cin >> u >> v >> weight;
    graph.addEdge(u, v, weight);
  }

  // find and print the shortest path
  graph.findShortestPath(start, end, maxCharge, initialCharge);

   return 0;
}

//SECTION_C_END: Section C ends here.
/***********************************************
************SECTION-C-MAIN-FUNCTION-END*********
************************************************/
