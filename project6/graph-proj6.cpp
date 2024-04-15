#include "graph-proj6.h"
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <list>

void Graph::addEdge(int from, int to, int cost){
    adjacencyList[from].push_back(Edge(to, cost));
}

vector<int> Graph::dijkstra(int source) const{
    vector<int> priQueue;
}