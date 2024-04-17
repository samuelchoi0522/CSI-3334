#include "graph-proj6.h"
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <list>
#include "arrayheap-student-proj6.h"

void Graph::addEdge(int from, int to, int cost){
    adjacencyList[from].push_back(Edge(to, cost));
}

vector<int> Graph::dijkstra(int source) const{
    vector<int> dist(adjacencyList.size(), INFINITE_COST);
    dist[source] = 0;

    ArrayHeap<pair<int,int> > pq;

    pq.insert(make_pair(0, source));

    while(pq.getNumItems() != 0){
        int u = pq.getMinItem().second;
        pq.removeMinItem();

        for(list<Edge>::const_iterator i = adjacencyList[u].begin(); 
        i != adjacencyList[u].end(); i++){
            int v = i->to;
            int weight = i->cost;

            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.insert(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}