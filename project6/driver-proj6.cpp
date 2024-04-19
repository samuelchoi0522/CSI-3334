#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

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
int main() {
    map<string, int> nameToIndex;
    vector<bool> serverExists;
    vector<int> delayTimes;
    string from, to;
    int delay, totalMinTime, numVertices, verticeCount = 0;
    stringstream inpSS;

    cin >> numVertices;

    for (int i = 0; i < numVertices; i++) {
        cin >> from >> to >> delay;
        inpSS << from << " " << to << " " << delay << endl;

        if (nameToIndex.find(from) == nameToIndex.end()) {
            int index = nameToIndex.size();
            nameToIndex[from] = index;
            serverExists.push_back(from.size() >= 7 && from.substr(from.size() - 7) == "_server");
        }

        if (nameToIndex.find(to) == nameToIndex.end()) {
            int index = nameToIndex.size();
            nameToIndex[to] = index;
            serverExists.push_back(to.size() >= 7 && to.substr(to.size() - 7) == "_server");
        }
    }

    Graph g(nameToIndex.size());

    for (int i = 0; i < numVertices; i++) {
        inpSS >> from >> to >> delay;
        g.addEdge(nameToIndex[from], nameToIndex[to], delay);
    }

    delayTimes.resize(serverExists.size(), g.INFINITE_COST);
    totalMinTime = g.INFINITE_COST;

    for (int i = 0; i < serverExists.size(); i++) {
        if (serverExists[i]) {
            vector<int> numDelays = g.dijkstra(i);
            int serverDelay = 0;
            bool validServer = true;

            for (int j = 0; j < numDelays.size(); j++) {
                if (numDelays[j] == g.INFINITE_COST) {
                    validServer = false;
                    break;
                }
                serverDelay += numDelays[j];
            }

            if (validServer) {
                delayTimes[i] = serverDelay;
                totalMinTime = min(totalMinTime, serverDelay);
            }
        }
    }

    if (totalMinTime == g.INFINITE_COST) {
        cout << "no server can serve the whole network" << endl;
    } else {
        cout << "total delay: " << totalMinTime << endl;
        for (map<string, int>::iterator it = nameToIndex.begin(); it != nameToIndex.end(); ++it) {
            if (serverExists[it->second] && delayTimes[it->second] == totalMinTime) {
                cout << it->first << endl;
            }
        }
    }

    return 0;
}
