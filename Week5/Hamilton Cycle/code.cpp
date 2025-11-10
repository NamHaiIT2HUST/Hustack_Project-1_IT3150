#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
Tuần 5 - Chu trình Hamilton (Hamilton Cycle)
===============================================================================

🧩 MÔ TẢ BÀI TOÁN
-----------------
Cho một đồ thị vô hướng G = (V, E).  
Hãy kiểm tra xem đồ thị có **chu trình Hamilton** hay không.  
Chu trình Hamilton là một chu trình đi qua **tất cả các đỉnh đúng một lần**
và quay trở lại đỉnh ban đầu.

🎯 Yêu cầu:
- Nhập vào T (số lượng đồ thị cần kiểm tra).
- Với mỗi đồ thị:
  + Dòng đầu: n (số đỉnh), m (số cạnh)
  + m dòng tiếp theo: hai số u, v (cạnh nối giữa hai đỉnh u và v)
- Xuất ra:
  + 1 nếu đồ thị có chu trình Hamilton
  + 0 nếu không có

📘 Ví dụ:
Input:
2
5 5
1 2
1 3
2 4
2 5
3 5
7 13
1 3
1 5
1 7
2 4
2 5
2 6
3 4
3 5
3 7
4 6
4 7
5 7
6 7

Output:
0
1

===============================================================================

🔍 PHÂN TÍCH & HƯỚNG GIẢI
--------------------------
1️⃣ **Kiến thức cơ bản**
- Chu trình Hamilton đi qua mọi đỉnh đúng một lần, quay lại điểm xuất phát.
- Bài toán kiểm tra có chu trình Hamilton hay không là **NP-complete**  
  ⇒ Không có thuật toán nhanh cho mọi n (phải thử toàn bộ tổ hợp đỉnh).

2️⃣ **Hướng tiếp cận khả thi**
- Khi n nhỏ (≤ 20): có thể dùng **quy hoạch động với bitmask (DP Held-Karp)**  
  → Độ phức tạp O(n² × 2ⁿ)
- Khi n lớn hơn: không thể duyệt hết, nên chỉ dùng các **điều kiện nhanh** để kết luận.

3️⃣ **Các bước xử lý**
- Nếu n < 3 → chắc chắn KHÔNG có chu trình Hamilton → in 0.
- Nếu có đỉnh có bậc < 2 → cũng KHÔNG thể có chu trình → in 0.
- Nếu đồ thị thỏa **Định lý Dirac**:  
  (mọi đỉnh có bậc ≥ n/2) → chắc chắn CÓ chu trình Hamilton → in 1.
- Nếu n ≤ 20 → dùng **DP bitmask** để kiểm tra chính xác.
- Nếu n > 20 → không thể duyệt hết, in 0.

===============================================================================

🧠 Ý tưởng thuật toán DP Bitmask:
---------------------------------
- dp[mask][v] = true nếu có đường đi qua các đỉnh trong mask và kết thúc tại v.
- mask là tập các đỉnh đã đi qua (biểu diễn bằng bit).
- Bắt đầu từ từng đỉnh s: dp[1<<s][s] = true.
- Chuyển tiếp:
    Nếu dp[mask][v] = true và có cạnh (v, u) mà u chưa trong mask:
      dp[mask | (1<<u)][u] = true
- Kết thúc:
    Nếu tồn tại dp[(1<<n)-1][v] = true và có cạnh (v, s) (về lại đỉnh đầu s)
    ⇒ tồn tại chu trình Hamilton.

===============================================================================
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n);
        vector<vector<char>> edge(n, vector<char>(n, 0));

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            if (!edge[u][v]) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                edge[u][v] = edge[v][u] = 1;
            }
        }

        // 1️⃣ Loại nhanh: ít đỉnh hoặc đỉnh có bậc < 2
        if (n < 3) {
            cout << 0 << "\n";
            continue;
        }

        int min_deg = INT_MAX;
        for (int i = 0; i < n; ++i)
            min_deg = min(min_deg, (int)adj[i].size());
        if (min_deg < 2) {
            cout << 0 << "\n";
            continue;
        }

        // 2️⃣ Định lý Dirac
        if (min_deg >= n / 2) {
            cout << 1 << "\n";
            continue;
        }

        // 3️⃣ Nếu nhỏ, dùng DP Bitmask kiểm tra chính xác
        if (n <= 20) {
            int ALL = 1 << n;
            bool found = false;

            for (int s = 0; s < n && !found; ++s) {
                vector<vector<char>> dp(ALL, vector<char>(n, 0));
                dp[1 << s][s] = 1;

                for (int mask = 1; mask < ALL; ++mask) {
                    for (int v = 0; v < n; ++v) {
                        if (!dp[mask][v]) continue;
                        for (int u : adj[v]) {
                            if (mask & (1 << u)) continue;
                            dp[mask | (1 << u)][u] = 1;
                        }
                    }
                }

                int full = ALL - 1;
                for (int v = 0; v < n; ++v) {
                    if (v != s && dp[full][v] && edge[v][s]) {
                        found = true;
                        break;
                    }
                }
            }

            cout << (found ? 1 : 0) << "\n";
            continue;
        }

        // 4️⃣ Với n > 20: Không thể chạy DP, in 0
        cout << 0 << "\n";
    }

    return 0;
}
