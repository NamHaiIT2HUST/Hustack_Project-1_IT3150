#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
🧩 BÀI TOÁN: Depth First Search (DFS) - Duyệt đồ thị theo chiều sâu
===============================================================================

📘 MÔ TẢ
---------
Cho đồ thị vô hướng G = (V, E)
- V = {1, 2, ..., n} là tập các đỉnh
- E là tập các cạnh nối giữa các đỉnh u, v

Yêu cầu:  
Thực hiện **duyệt đồ thị theo chiều sâu (DFS)**,  
các đỉnh được thăm theo **thứ tự từ điển (lexicographic order)**  
và in ra **thứ tự các đỉnh được thăm**.

-------------------------------------------------------------------------------

📘 INPUT
---------
- Dòng 1: Hai số nguyên n và m (1 ≤ n, m ≤ 100000)
- m dòng tiếp theo: mỗi dòng có hai số u, v (1 ≤ u, v ≤ n)
  → nghĩa là có cạnh nối giữa u và v (đồ thị vô hướng).

📘 OUTPUT
----------
- Một dòng duy nhất chứa thứ tự các đỉnh được thăm trong DFS.

-------------------------------------------------------------------------------

📗 VÍ DỤ
---------
Input:
7 12
1 2
1 3
2 3
2 4
2 7
3 5
3 7
4 5
4 6
4 7
5 6
5 7

Output:
1 2 3 5 4 6 7

-------------------------------------------------------------------------------

💡 PHÂN TÍCH & HƯỚNG GIẢI
--------------------------
🧠 Ý tưởng:
1️⃣ Đọc dữ liệu → xây dựng **danh sách kề (adjacency list)**.
2️⃣ Vì cần **thứ tự từ điển**, ta **sắp xếp danh sách kề** của từng đỉnh.
3️⃣ Dùng **DFS (đệ quy)** để duyệt:
    - Bắt đầu từ đỉnh 1.
    - Mỗi khi thăm một đỉnh u, in ra u.
    - Duyệt các đỉnh kề của u theo thứ tự tăng dần (lexicographic order).

📈 Độ phức tạp:
- Thời gian: O(N + M log M) (do cần sắp xếp danh sách kề)
- Bộ nhớ: O(N + M)

===============================================================================
*/

const int MAX = 100000;
vector<int> adj[MAX + 1];
vector<bool> visited(MAX + 1);
vector<int> result;

void dfs(int u) {
    visited[u] = true;
    result.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v])
            dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Sắp xếp danh sách kề để đảm bảo duyệt theo thứ tự từ điển
    for (int i = 1; i <= n; ++i)
        sort(adj[i].begin(), adj[i].end());

    // Duyệt DFS từ đỉnh 1
    dfs(1);

    // In kết quả
    for (int i = 0; i < (int)result.size(); ++i) {
        cout << result[i];
        if (i < (int)result.size() - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
