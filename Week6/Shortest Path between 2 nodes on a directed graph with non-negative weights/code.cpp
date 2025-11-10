#include <bits/stdc++.h>
using namespace std;

/*
    💡 ĐỀ BÀI
    ----------------------------------------------------
    Cho đồ thị có hướng G = (V, E) với:
        - V = {1, 2, ..., n}
        - Mỗi cung (u, v) có trọng số không âm w(u, v)
    Yêu cầu: Tìm đường đi ngắn nhất từ đỉnh s đến đỉnh t.
    Nếu không có đường đi, in ra -1.

    ⚙️ DỮ LIỆU VÀ KẾT QUẢ
    ----------------------------------------------------
    Input:
        Dòng 1: n, m  (1 ≤ n ≤ 10^5)
        M dòng tiếp: u v w  (0 ≤ w ≤ 100000)
        Dòng cuối: s t
    Output:
        Độ dài đường đi ngắn nhất từ s đến t hoặc -1 nếu không tồn tại.

    🧠 HƯỚNG GIẢI (Dijkstra)
    ----------------------------------------------------
    - Vì trọng số cung không âm → dùng thuật toán Dijkstra.
    - Dijkstra dùng hàng đợi ưu tiên (min-heap) để chọn đỉnh có khoảng cách nhỏ nhất.
    - Bắt đầu từ s, lần lượt “nới lỏng” (relax) các cạnh ra khỏi các đỉnh đã thăm.
    - Khi lấy được t ra khỏi heap → khoảng cách hiện tại chính là ngắn nhất.

    🚀 CÁC BƯỚC TRIỂN KHAI
    ----------------------------------------------------
    1️⃣ Đọc n, m và các cạnh → xây danh sách kề adj[u].
    2️⃣ Đọc s, t.
    3️⃣ Khởi tạo:
        - dist[i] = INF (vô cực) cho mọi i
        - dist[s] = 0
        - priority_queue chứa (dist, node)
    4️⃣ Trong khi queue chưa rỗng:
        - Lấy node u có dist[u] nhỏ nhất.
        - Nếu u == t → dừng sớm (vì Dijkstra đảm bảo tối ưu).
        - Với mỗi cạnh (u → v, w):
              nếu dist[v] > dist[u] + w thì cập nhật dist[v].
    5️⃣ Nếu dist[t] = INF → in -1, ngược lại in dist[t].

    🧩 GIẢI THÍCH BIẾN INF
    ----------------------------------------------------
    - INF là “vô cực” (giá trị lớn hơn mọi đường đi có thể).
    - Chọn INF = 4e18 (4×10^18) để tránh tràn khi cộng các trọng số.
    - Dùng kiểu long long cho dist để lưu tổng trọng số lớn.

    ⚡ ĐỘ PHỨC TẠP
    ----------------------------------------------------
    - Thời gian: O(m log n)
    - Bộ nhớ: O(n + m)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<pair<int,int>>> adj(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }
    int s, t; cin >> s >> t;

    const long long INF = (long long)4e18; // giá trị “vô cực”
    vector<long long> dist(n+1, INF);
    dist[s] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        long long d = cur.first;
        int u = cur.second;
        if (d != dist[u]) continue;
        if (u == t) break;
        for (auto &e : adj[u]) {
            int v = e.first; long long w = e.second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[t] == INF) cout << -1 << '\n';
    else cout << dist[t] << '\n';
    return 0;
}
