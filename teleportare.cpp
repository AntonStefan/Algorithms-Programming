#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const long long INF = 1e18;
int N, M, K;
vector<pair<int, int>> G[MAXN], teleports[MAXN];
long long dist[MAXN][9];

struct State {
    int node;
    long long time;
    bool operator<(const State& other) const {
        return time > other.time;
    }
};

long long solve() {
    for (int i=1; i<=N; i++)
        for (int j=0; j<9; j++)
            dist[i][j] = INF;
    dist[1][0] = 0;

    priority_queue<State> pq;
    pq.push({1, 0});
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        int node = current.node;
        long long time = current.time;
        if (time != dist[node][time % 8])
            continue;

        for (auto next : G[node]) {
            int nextNode = next.first;
            long long nextTime = time + next.second;
            if (dist[nextNode][nextTime % 8] > nextTime) {
                dist[nextNode][nextTime % 8] = nextTime;
                pq.push({nextNode, nextTime});
            }
        }

        for (auto next : teleports[node]) {
            int nextNode = next.first;
            long long nextTime = ((time + next.second - 1)
                                / next.second) * next.second + 1;
            if (dist[nextNode][nextTime % 8] > nextTime) {
                dist[nextNode][nextTime % 8] = nextTime;
                pq.push({nextNode, nextTime});
            }
        }
    }

    long long minDist = INF;
    for (int i=0; i<9; i++)
        minDist = min(minDist, dist[N][i]);
    return minDist;
}

int main() {
    ifstream fin("teleportare.in");
    ofstream fout("teleportare.out");
    fin >> N >> M >> K;
    for (int i=0; i<M; i++) {
        int x, y, t;
        fin >> x >> y >> t;
        G[x].push_back({y, t});
        G[y].push_back({x, t});
    }
    for (int i=0; i<K; i++) {
        int x, y, p;
        fin >> x >> y >> p;
        teleports[x].push_back({y, p});
        teleports[y].push_back({x, p});
    }
    fout << solve() << '\n';
    return 0;
}
