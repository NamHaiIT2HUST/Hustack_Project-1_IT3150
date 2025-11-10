#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Bài: DUYỆT BFS TRÊN ĐỒ THỊ VÔ HƯỚNG (Breadth-First Search)
===============================================================================

🧩 MÔ TẢ ĐỀ BÀI
---------------
Cho một đồ thị vô hướng G = (V, E) với:
- V = {1, 2, ..., n} là tập các đỉnh.
- E là tập các cạnh (m cạnh).

Yêu cầu: 
Thực hiện duyệt đồ thị bằng **thuật toán BFS (Breadth-First Search)**  
và in ra **thứ tự các đỉnh được thăm**.

🎯 Lưu ý:
- Khi có nhiều đỉnh kề cần duyệt, ta **chọn đỉnh nhỏ hơn trước** (tức là duyệt theo thứ tự tăng dần).
- Đồ thị có thể **không liên thông** ⇒ phải chạy BFS cho tất cả các thành phần.

-------------------------------------------------------------------------------

📘 INPUT
- Dòng 1: hai số nguyên `n` và `m` — số đỉnh và số cạnh.
- m dòng tiếp theo: mỗi dòng chứa hai số `u` và `v` — một cạnh nối giữa u và v.

📘 OUTPUT
- In ra dãy các đỉnh theo thứ tự được duyệt bằng BFS (cách nhau bởi dấu cách).

-------------------------------------------------------------------------------

📗 VÍ DỤ
Input:
6 7
2 4
1 3
3 4
5 6
1 2
3 5
2 3

Output:
1 2 3 4 5 6

-------------------------------------------------------------------------------

🔍 PHÂN TÍCH & HƯỚNG GIẢI
--------------------------
1️⃣ **Ý tưởng chính**
- Dùng thuật toán BFS (Breadth-First Search — duyệt theo chiều rộng).
- Vì đồ thị vô hướng, mỗi cạnh (u, v) được lưu cả hai chiều.
- Khi có nhiều đỉnh kề cần duyệt, ta **sắp xếp danh sách kề** theo thứ tự tăng dần.

2️⃣ **Thuật toán tổng quát**
- Dùng mảng `visited[n+1]` để đánh dấu đỉnh đã thăm.
- Duyệt lần lượt các đỉnh từ 1 → n:
  + Nếu đỉnh chưa thăm, chạy BFS bắt đầu từ đó.
  + Duyệt các đỉnh kề theo thứ tự tăng dần.
  + Mỗi khi gặp đỉnh mới → đưa vào hàng đợi (queue).
- Ghi lại thứ tự thăm đỉnh để in ra.

3️⃣ **Độ phức tạp**
- O(n + m) cho BFS, cộng thêm O(m log m) do sắp xếp danh sách kề.

===============================================================================
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1); // danh sách kề

    // đọc các cạnh
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // sắp xếp danh sách kề để duyệt theo thứ tự tăng dần
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<bool> visited(n + 1, false);
    vector<int> result;

    // duyệt qua tất cả các thành phần liên thông
    for (int start = 1; start <= n; ++start) {
        if (!visited[start]) {
            queue<int> q;
            q.push(start);
            visited[start] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                result.push_back(u);

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    // in kết quả BFS
    for (size_t i = 0; i < result.size(); ++i) {
        if (i) cout << ' ';
        cout << result[i];
    }
    cout << '\n';

    return 0;
}
