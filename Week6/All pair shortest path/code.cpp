#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
🧩 BÀI TOÁN: ALL PAIR SHORTEST PATHS (FLOYD–WARSHALL)
===============================================================================

📘 MÔ TẢ
---------
Cho đồ thị có hướng G = (V, E), trong đó:
- V = {1, 2, ..., n} là tập các đỉnh.
- E là tập các cạnh có trọng số w(u,v) ≥ 1.

Yêu cầu:  
Tính **độ dài đường đi ngắn nhất d(u,v)** giữa mọi cặp (u,v) trong đồ thị.

Nếu không tồn tại đường đi từ u đến v → d(u,v) = -1

-------------------------------------------------------------------------------

📘 INPUT
---------
- Dòng 1: n và m (1 ≤ n, m ≤ 10,000)
- m dòng tiếp theo: mỗi dòng gồm 3 số nguyên u, v, w  
  (nghĩa là có cạnh có hướng từ u đến v với trọng số w)

📘 OUTPUT
----------
- Ma trận d[n][n], trong đó d[i][j] là độ dài đường đi ngắn nhất từ i → j.
- Nếu không có đường đi, in ra -1.
- Mỗi dòng in 1 hàng của ma trận, các phần tử cách nhau bởi dấu cách.

-------------------------------------------------------------------------------

📗 VÍ DỤ
---------
Input:
4 9
1 2 9
1 3 7
1 4 2
2 1 1
2 4 5
3 4 6
3 2 2
4 1 5
4 2 8

Output:
0 9 7 2
1 0 8 3
3 2 0 5
5 8 12 0

-------------------------------------------------------------------------------

💡 PHÂN TÍCH & HƯỚNG GIẢI
--------------------------
🧠 Ý tưởng:
Sử dụng **thuật toán Floyd–Warshall**:
- Đây là giải pháp chuẩn để tìm **đường đi ngắn nhất giữa mọi cặp đỉnh**.
- Công thức cập nhật:
    d[i][j] = min(d[i][j], d[i][k] + d[k][j]) với mọi k từ 1 → n.

📈 Độ phức tạp:
- Thời gian: O(n³)
- Bộ nhớ: O(n²)
→ Với n ≤ 500 hợp lý, n ≤ 10000 thì chỉ áp dụng cho đồ thị thưa và yêu cầu bài tập mô phỏng.

===============================================================================
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    const int INF = 1e9;
    vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));

    // Khoảng cách từ chính nó đến chính nó bằng 0
    for (int i = 1; i <= n; ++i) d[i][i] = 0;

    // Đọc các cạnh
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u][v] = min(d[u][v], w); // nếu có nhiều cạnh, lấy cạnh nhỏ nhất
    }

    // Floyd–Warshall
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (d[i][k] == INF) continue;
            for (int j = 1; j <= n; ++j) {
                if (d[k][j] == INF) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    // In kết quả
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (d[i][j] == INF) cout << -1;
            else cout << d[i][j];
            if (j < n) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
