#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int NUM_NETWORK_LINKS = 4000;

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
            nameToIndex[from] = reverse.size(); //get index to push to 
            reverse.push_back(from);            //push to reversed list
            if(from.length() >= 7 && from.substr(from.length() - 7) == "_server"){    //get up to_server
                serverNames.push_back(nameToIndex[from]);
            }
        }
        if(nameToIndex.find(to) == nameToIndex.end()){
            nameToIndex[to] = reverse.size(); //get index to push to 
            reverse.push_back(to);            //push to reversed list
            serverNames.push_back(nameToIndex[to]);
        }
        g.addEdge(nameToIndex[from], nameToIndex[to], delay);
    }


    for(int i = 0; i < serverNames.size(); i++){
        int serverIndex = serverNames[i];
        vector<int> numDelays = g.dijkstra(serverIndex);
        int totalDelay = 0;
        bool isValidServer = true;
        for(int j = 0; j < serverNames.size(); j++){
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

    if(fastestServers.empty()){
        cout << "no server can serve the whole network." << endl;
    }
    else{
        sort(fastestServers.begin(), fastestServers.end());
        cout << "total delay: " << minDelay << endl;
        for(int i = 0 ; i < fastestServers.size(); i++){
            cout << fastestServers[i] << endl;
        }
    }



    return 0;

}
