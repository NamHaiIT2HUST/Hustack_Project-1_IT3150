#include <bits/stdc++.h>
using namespace std;

/*
    💡 ĐỀ BÀI
    ----------------------------------------------------
    Cho một mạng dòng chảy G = (V, E) là đồ thị có hướng và có trọng số.
    Mỗi cạnh (u, v) có một giá trị c(u, v) thể hiện **dung lượng (capacity)** của nó.
    Cho hai đỉnh đặc biệt:
        - s: nguồn (source)
        - t: đích (sink)
    Hãy tìm **giá trị dòng chảy cực đại (maximum flow)** có thể đi từ s → t.

    ⚙️ DỮ LIỆU VÀ KẾT QUẢ
    ----------------------------------------------------
    Input:
        Dòng 1: N M — số đỉnh và số cạnh (1 ≤ N ≤ 10^4, 1 ≤ M ≤ 10^6)
        Dòng 2: s t — đỉnh nguồn và đỉnh đích
        M dòng tiếp: u v c — cạnh có hướng từ u → v, dung lượng là c
    Output:
        Dòng chảy cực đại từ s đến t.

    🧠 HƯỚNG GIẢI (THUẬT TOÁN DINIC)
    ----------------------------------------------------
    Vì N ≤ 10^4 và M ≤ 10^6 → dùng **thuật toán Dinic** là tối ưu:
        - Nhanh hơn Ford–Fulkerson và Edmonds–Karp.
        - Dùng BFS để xây dựng “mức độ” (level graph).
        - Dùng DFS để đẩy dòng chảy trong mạng theo các đường hợp lệ.
    
    💧 Ý TƯỞNG CƠ BẢN CỦA DINIC
    ----------------------------------------------------
    1️⃣ **Level graph (BFS)**: 
        - Gán mỗi đỉnh một “mức độ” (distance từ s).
        - Chỉ cho phép đi theo các cạnh có khả năng đẩy thêm dòng (capacity > 0)
          và đi từ đỉnh cấp thấp → cấp cao hơn.

    2️⃣ **Blocking Flow (DFS)**:
        - Dựa trên đồ thị mức, thực hiện DFS để đẩy dòng từ s → t.
        - Mỗi khi một đường đầy, quay lại tìm đường khác.

    3️⃣ **Lặp lại**:
        - Khi không thể xây thêm đồ thị mức → dừng.
        - Tổng dòng đã đẩy chính là dòng cực đại.

    ⚙️ CÁC BIẾN TRONG CODE
    ----------------------------------------------------
    - `adj[u]`: lưu danh sách các cạnh đi ra từ đỉnh `u` (dưới dạng chỉ số cạnh).
    - `edges`: mảng chứa các cạnh (mỗi cạnh gồm: from, to, capacity, flow).
    - `level[u]`: lưu cấp độ của mỗi đỉnh trong đồ thị mức.
    - `ptr[u]`: lưu chỉ số duyệt cạnh trong DFS (tránh duyệt lại cạnh cũ).
    - `INF`: giá trị vô cực để biểu diễn dòng cực đại có thể đẩy được.

    ⚡ ĐỘ PHỨC TẠP
    ----------------------------------------------------
    - Thời gian: O(min(V^(2/3), E^(1/2)) * E) — đủ nhanh cho 10^6 cạnh.
    - Bộ nhớ: O(V + E)

    🧩 GIẢI THÍCH KẾT QUẢ
    ----------------------------------------------------
    - Sau khi thuật toán kết thúc, tổng dòng từ `s` đến `t`
      chính là dòng chảy cực đại trong mạng.
*/

struct Edge {
    int v;          // đỉnh kề
    long long cap;  // dung lượng
    int rev;        // chỉ số cạnh ngược trong danh sách kề của v
};

struct Dinic {
    int n, s, t;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;
    const long long INF = 1e18; // "vô cực"

    Dinic(int n, int s, int t): n(n), s(s), t(t) {
        adj.assign(n + 1, {});
        level.resize(n + 1);
        ptr.resize(n + 1);
    }

    // thêm cạnh (u → v) với dung lượng cap, và cạnh ngược (v → u) dung lượng 0
    void add_edge(int u, int v, long long cap) {
        Edge a{v, cap, (int)adj[v].size()};
        Edge b{u, 0, (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    // BFS để xây dựng đồ thị mức
    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap > 0 && level[e.v] == -1) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[t] != -1;
    }

    // DFS đẩy dòng chảy từ đỉnh u đến t
    long long dfs(int u, long long pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int &cid = ptr[u]; cid < (int)adj[u].size(); ++cid) {
            Edge &e = adj[u][cid];
            if (level[e.v] == level[u] + 1 && e.cap > 0) {
                long long tr = dfs(e.v, min(pushed, e.cap));
                if (tr == 0) continue;
                e.cap -= tr;
                adj[e.v][e.rev].cap += tr;
                return tr;
            }
        }
        return 0;
    }

    // thuật toán Dinic chính
    long long maxflow() {
        long long flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;

    Dinic dinic(n, s, t);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        dinic.add_edge(u, v, c);
    }

    cout << dinic.maxflow() << "\n";
    return 0;
}
