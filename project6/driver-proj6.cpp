#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int NUM_NETWORK_LINKS = 4000;

/* main
 *  parameters:
 *      none
 *  return value:
 *      0 (indicating a successful run)
 *
 *  This function reads in a description of an existing network. Vertices
 *  are added to the graph and the server names are tracked. Then, the
 *  total delay for each server is calculated to find the fastest server.
 *  The shortest delay time is then output, or that no server can serve the
 *  entire network.
 */
int main(){
    Graph g(NUM_NETWORK_LINKS);
    map<string, int> nameToIndex;
    vector<string> reverse, fastestServers;
    vector<int> minDelays(reverse.size(), g.INFINITE_COST), serverNames;
    string from, to;
    int delay, numVertices, minDelay = g.INFINITE_COST;


    cin >> numVertices;
    

    for(int i = 0; i < numVertices; i++){
        cin >> from >> to >> delay;

        if(nameToIndex.find(from) == nameToIndex.end()){
            nameToIndex[from] = reverse.size();
            reverse.push_back(from);
            if(from.length() >= 7 && from.substr(from.length() - 7) == "_server"){
                serverNames.push_back(nameToIndex[from]);
            }
        }
        if(nameToIndex.find(to) == nameToIndex.end()){
            nameToIndex[to] = reverse.size();
            reverse.push_back(to);
            serverNames.push_back(nameToIndex[to]);
        }
        g.addEdge(nameToIndex[from], nameToIndex[to], delay);
    }

    int serversize = serverNames.size();

    for(int i = 0; i < serversize; i++){
        int serverIndex = serverNames[i];
        vector<int> numDelays = g.dijkstra(serverIndex);
        int totalDelay = 0;
        bool isValidServer = true;
        for(int j = 0; j < serversize; j++){
            if(numDelays[j] == g.INFINITE_COST){
                isValidServer = false;
                break;
            }
            totalDelay += numDelays[j];
        }

        if(isValidServer && totalDelay < minDelay){
            minDelay = totalDelay;
            fastestServers.clear();
            fastestServers.push_back(reverse[serverIndex]);
        }
        else if(isValidServer && totalDelay == minDelay){
            fastestServers.push_back(reverse[serverIndex]);
        }
    }

    int fastestserversize = fastestServers.size();

    if(fastestServers.empty()){
        cout << "no server can serve the whole network" << endl;
    }
    else{
        sort(fastestServers.begin(), fastestServers.end());
        cout << "total delay: " << minDelay << endl;
        for(int i = 0 ; i < fastestserversize; i++){
            if(fastestServers[i].length() >= 7 && 
            fastestServers[i].substr(fastestServers[i].length() - 7) == "_server"){
                cout << fastestServers[i] << endl;
            }
        }
    }



    return 0;

}
