#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

vector<vector<int>> graph, reversedGraph;
vector<bool> visited;
stack<int> nodesStack;
vector<int> SCC;

void DFS1(int node) {
    visited[node] = true;
    for (int nextNode : graph[node]) {
        if (!visited[nextNode]) {
            DFS1(nextNode);
        }
    }
    nodesStack.push(node);
}

void DFS2(int node, int comp) {
    SCC[node] = comp;
    for (int nextNode : reversedGraph[node]) {
        if (SCC[nextNode] == -1) {
            DFS2(nextNode, comp);
        }
    }
}

int main() {
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    int N, M, S;
    fin >> N >> M >> S;
    graph.resize(N + 1);
    reversedGraph.resize(N + 1);
    visited.resize(N + 1, false);
    SCC.resize(N + 1, -1);

    for (int i = 0; i < M; i++) {
        int x, y;
        fin >> x >> y;
        graph[x].push_back(y);
        reversedGraph[y].push_back(x);
    }

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            DFS1(i);
        }
    }

    int comp = 0;
    while (!nodesStack.empty()) {
        int node = nodesStack.top();
        nodesStack.pop();
        if (SCC[node] == -1) {
            DFS2(node, comp++);
        }
    }

    vector<int> incomingEdges(comp, 0);
    for (int i = 1; i <= N; i++) {
        for (int j : graph[i]) {
            if (SCC[i] != SCC[j]) {
                incomingEdges[SCC[j]]++;
            }
        }
    }

    int result = 0;
    for (int i = 0; i < comp; i++) {
        if (incomingEdges[i] == 0) {
            result++;
        }
    }

    if (incomingEdges[SCC[S]] > 0) {
         fout << result << '\n';
    } else {
    fout << result - 1<< '\n';
    }

    return 0;
}
