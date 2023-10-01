#include <iostream>
#include <vector>
#include<fstream>

using namespace std;

const int MAXN = 1e5+5;
vector<int> adj[MAXN];
int startTime[MAXN], endTime[MAXN], timer = 0;

void dfs(int node) {
    startTime[node] = ++timer;

    for (auto child : adj[node]) {
        dfs(child);
    }

    endTime[node] = timer;
}

int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");

    int N, Q;
    fin >> N >> Q;
    vector<int> parent(N + 1);

    for (int i = 2; i <= N; i++) {
        fin >> parent[i];
        adj[parent[i]].push_back(i);
    }

    dfs(1);

    while (Q--) {
        int D, E;
        fin >> D >> E;

        int endExpeditionTime = startTime[D] + E;
        if (endExpeditionTime > endTime[D]) {
            fout << "-1\n";
        } else {
            for (int i = 1; i <= N; i++) {
                if (startTime[i] == endExpeditionTime) {
                    fout << i << "\n";
                    break;
                }
            }
        }
    }

    return 0;
}
