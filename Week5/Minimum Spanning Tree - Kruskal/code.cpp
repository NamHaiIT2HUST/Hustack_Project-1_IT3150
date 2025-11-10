#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
🧩 BÀI TOÁN: Minimum Spanning Tree (Cây khung nhỏ nhất - MST)
===============================================================================

📘 MÔ TẢ
---------
Cho đồ thị vô hướng liên thông G = (V, E):
- V = {1, 2, ..., N} là tập các đỉnh
- E là tập các cạnh (u, v) với trọng số w(u, v)

Yêu cầu: Tìm **cây khung nhỏ nhất** (Minimum Spanning Tree — MST)  
và in ra **tổng trọng số nhỏ nhất** của cây khung đó.

Cây khung nhỏ nhất là cây con của đồ thị:
- Nối tất cả các đỉnh lại (liên thông)
- Không chứa chu trình
- Có tổng trọng số cạnh nhỏ nhất.

-------------------------------------------------------------------------------

📘 INPUT
---------
- Dòng 1: N và M (1 ≤ N, M ≤ 10^5)
- M dòng tiếp theo: mỗi dòng chứa 3 số nguyên `u v w`
  → nghĩa là có cạnh (u, v) với trọng số w.

📘 OUTPUT
----------
- Một số nguyên: tổng trọng số nhỏ nhất của cây khung.

-------------------------------------------------------------------------------

📗 VÍ DỤ
---------
Input:
5 8
1 2 1
1 3 4
1 5 1
2 4 2
2 5 1
3 4 3
3 5 3
4 5 2

Output:
7

Cây khung nhỏ nhất chọn các cạnh:
(1,2)=1, (1,5)=1, (2,4)=2, (3,4)=3  → Tổng = 7

-------------------------------------------------------------------------------

💡 PHÂN TÍCH & HƯỚNG GIẢI
--------------------------
Có hai thuật toán phổ biến để tìm cây khung nhỏ nhất:
1️⃣ **Kruskal’s Algorithm** (ưu tiên sắp xếp cạnh)
2️⃣ **Prim’s Algorithm** (ưu tiên mở rộng theo đỉnh)

Ở đây ta dùng **Kruskal** vì cài đặt đơn giản và hiệu quả O(M log M).

📘 Bước làm:
1. Đọc danh sách các cạnh (u, v, w)
2. Sắp xếp các cạnh theo trọng số tăng dần
3. Dùng **Union-Find (DSU)** để nối các thành phần:
   - Nếu 2 đỉnh thuộc 2 tập khác nhau → chọn cạnh đó, cộng trọng số.
   - Nếu cùng tập → bỏ qua (tránh tạo chu trình).
4. Khi đã chọn đủ (N-1) cạnh → dừng.

Độ phức tạp:
- Sắp xếp: O(M log M)
- Union-Find: gần như O(M α(N)) ≈ O(M)

===============================================================================
*/

struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n + 1);
        rank.assign(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    struct Edge { int u, v, w; };
    vector<Edge> edges(M);

    for (int i = 0; i < M; ++i)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    // B1: sắp xếp cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    DSU dsu(N);
    long long totalWeight = 0;
    int edgesUsed = 0;

    // B2: Duyệt qua các cạnh
    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            totalWeight += e.w;
            edgesUsed++;
            if (edgesUsed == N - 1) break;
        }
    }

    cout << totalWeight << "\n";
    return 0;
}
