#include <bits/stdc++.h>
using namespace std;

struct Person {
    string id, birth, father, mother, region;
    bool alive;
};

unordered_map<string, Person> p;
map<string, int> born;
map<string, int> prefix;

int dfsAlive(const string &u, unordered_set<string> &vis) {
    if (!p.count(u) || vis.count(u)) return -1;
    vis.insert(u);
    int res = -1;
    auto &cur = p[u];
    if (cur.father != "0000000" && p.count(cur.father)) {
        if (p[cur.father].alive) res = max(res, 1);
        int tmp = dfsAlive(cur.father, vis);
        if (tmp >= 0) res = max(res, tmp + 1);
    }
    if (cur.mother != "0000000" && p.count(cur.mother)) {
        if (p[cur.mother].alive) res = max(res, 1);
        int tmp = dfsAlive(cur.mother, vis);
        if (tmp >= 0) res = max(res, tmp + 1);
    }
    return res;
}

pair<int,int> dfsMIS(int u, int parent, vector<vector<int>> &g, vector<char> &vis) {
    vis[u] = 1;
    int take = 1, notake = 0;
    for (int v : g[u]) {
        if (v == parent) continue;
        if (!vis[v]) {
            auto pr = dfsMIS(v, u, g, vis);
            take += pr.second;
            notake += max(pr.first, pr.second);
        } else {
            // if already visited (shouldn't happen in tree), still skip parent
        }
    }
    return {take, notake};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (true) {
        string id;
        if (!(cin >> id)) return 0;
        if (id == "*") break;
        string birth, father, mother, region;
        char alive;
        cin >> birth >> father >> mother >> alive >> region;
        p[id] = {id, birth, father, mother, region, alive == 'Y'};
        born[birth]++;
    }
    int acc = 0;
    for (auto &kv : born) {
        acc += kv.second;
        prefix[kv.first] = acc;
    }
    while (true) {
        string cmd;
        if (!(cin >> cmd)) break;
        if (cmd == "***") break;
        if (cmd == "NUMBER_PEOPLE") {
            cout << p.size() << "\n";
        } else if (cmd == "NUMBER_PEOPLE_BORN_AT") {
            string d; cin >> d;
            cout << (born.count(d) ? born[d] : 0) << "\n";
        } else if (cmd == "NUMBER_PEOPLE_BORN_BETWEEN") {
            string a,b; cin >> a >> b;
            auto itR = prefix.upper_bound(b);
            int sumR = (itR == prefix.begin()) ? 0 : prev(itR)->second;
            auto itL = prefix.lower_bound(a);
            int sumL = (itL == prefix.begin()) ? 0 : prev(itL)->second;
            cout << max(0, sumR - sumL) << "\n";
        } else if (cmd == "MOST_ALIVE_ANCESTOR") {
            string id; cin >> id;
            unordered_set<string> vis;
            int d = dfsAlive(id, vis);
            cout << max(0, d) << "\n";
        } else if (cmd == "MAX_UNRELATED_PEOPLE") {
            // build index
            vector<string> codes;
            codes.reserve(p.size());
            for (auto &kv : p) codes.push_back(kv.first);
            int N = codes.size();
            unordered_map<string,int> idx;
            idx.reserve(N*2);
            for (int i=0;i<N;++i) idx[codes[i]] = i;
            vector<vector<int>> g(N);
            for (auto &kv : p) {
                int u = idx[kv.first];
                auto &per = kv.second;
                if (per.father != "0000000" && p.count(per.father)) {
                    int v = idx[per.father];
                    g[u].push_back(v);
                    g[v].push_back(u);
                }
                if (per.mother != "0000000" && p.count(per.mother)) {
                    int v = idx[per.mother];
                    g[u].push_back(v);
                    g[v].push_back(u);
                }
            }
            vector<char> vis(N, 0);
            int total = 0;
            for (int i = 0; i < N; ++i) {
                if (!vis[i]) {
                    auto pr = dfsMIS(i, -1, g, vis);
                    total += max(pr.first, pr.second);
                }
            }
            cout << total << "\n";
        }
    }
    return 0;
}
