#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int task_data[MAXN], dp[MAXN];

int min_context_switches(int node) {
    if (dp[node] != -1) {
        return dp[node];
    }
    dp[node] = 0;
    int same_data = 0;
    for (auto &it : adj[node]) {
        dp[node] = max(dp[node], min_context_switches(it));
        if (task_data[node] != task_data[it]) {
            same_data = max(same_data, dp[it] + 1);
        }
    }
    dp[node] = max(dp[node], same_data);
    return dp[node];
}

int main() {
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");

    int N, M;
    fin >> N >> M;

    for (int i = 1; i <= N; i++) {
        fin >> task_data[i];
    }

    int u, v;
    for (int i = 1; i <= M; i++) {
        fin >> u >> v;
        adj[u].push_back(v);
    }
    memset(dp, -1, sizeof(dp));
    int min_switches = 0;
    for (int i = 1; i <= N; i++) {
        min_switches = max(min_switches, min_context_switches(i));
    }

    fout << min_switches;
    return 0;
}
