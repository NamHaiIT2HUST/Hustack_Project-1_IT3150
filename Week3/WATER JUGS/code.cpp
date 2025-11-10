#include <bits/stdc++.h>
using namespace std;

/*
    ============================================
                🧩  BÀI: WATER JUGS
    ============================================

    🔹 ĐỀ BÀI:
    Có hai bình chứa nước có dung tích lần lượt là `a` lít và `b` lít.
    Có một nguồn nước vô hạn. Mục tiêu: đong được chính xác `c` lít
    nước trong **một trong hai bình**.

    Các thao tác cho phép (mỗi thao tác tính 1 bước):
      1️⃣ Đổ đầy bình A (A = a)
      2️⃣ Đổ đầy bình B (B = b)
      3️⃣ Đổ hết bình A (A = 0)
      4️⃣ Đổ hết bình B (B = 0)
      5️⃣ Chuyển nước từ A sang B cho đến khi:
          - A hết nước, hoặc
          - B đầy
      6️⃣ Chuyển nước từ B sang A cho đến khi:
          - B hết nước, hoặc
          - A đầy

    ➡️ Yêu cầu: In ra số bước **ít nhất** để có một trong hai bình chứa đúng `c` lít,
                 hoặc in `-1` nếu không thể.

    --------------------------------------------
    🔹 DỮ LIỆU VÀ KẾT QUẢ:
    Input:
        a b c   (1 <= a, b, c <= 900)
    Output:
        Số bước nhỏ nhất, hoặc -1 nếu vô nghiệm.

    Ví dụ:
        Input:
            6 8 4
        Output:
            4

    Giải thích:
        Các bước (ví dụ 1 cách):
        1. Đổ đầy B (0,8)
        2. Rót từ B → A (6,2)
        3. Đổ hết A (0,2)
        4. Rót từ B → A (2,0) => có 4 lít trong A hoặc B tùy trạng thái

    --------------------------------------------
    🔹 Ý TƯỞNG GIẢI QUYẾT:
    Bài toán này có thể coi là tìm **đường đi ngắn nhất** trên đồ thị trạng thái:

      ➤ Trạng thái = (x, y)
          - x: lượng nước trong bình A
          - y: lượng nước trong bình B
          - 0 ≤ x ≤ a, 0 ≤ y ≤ b

      ➤ Từ mỗi trạng thái, ta sinh ra tối đa 6 trạng thái mới
         tương ứng với các thao tác hợp lệ nêu trên.

      ➤ Mục tiêu:
         tìm đường đi ngắn nhất từ (0,0) đến bất kỳ trạng thái có:
             x == c hoặc y == c

      ➤ Dùng BFS (Breadth-First Search):
         vì mỗi bước có chi phí = 1 → BFS đảm bảo tìm được lời giải ngắn nhất.

    --------------------------------------------
    🔹 KIỂM TRA SỚM (CẮT NGUỒN):
      - Nếu c > max(a, b) → không thể chứa c lít trong một bình.
      - Nếu c không chia hết cho gcd(a, b) → không thể đo chính xác c lít
        (định lý Bézout về bài toán bình nước).

    --------------------------------------------
    🔹 ĐỘ PHỨC TẠP:
      - Tối đa (a+1)*(b+1) trạng thái ≈ 900*900 = 810.000
      - BFS qua được trong thời gian cho phép.
*/

int gcd_int(int x, int y) {
    // Tính ước chung lớn nhất (Euclid)
    while (y) {
        int t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;

    // 🔸 Kiểm tra điều kiện không thể đo được
    if (c > max(a, b)) {
        cout << -1 << '\n';
        return 0;
    }

    int g = gcd_int(a, b);
    if (c % g != 0) {
        cout << -1 << '\n';
        return 0;
    }

    // 🔸 visited[x][y] = đã thăm trạng thái (x nước trong A, y nước trong B)
    vector<vector<bool>> visited(a + 1, vector<bool>(b + 1, false));

    // Hàng đợi BFS: (x, y, steps)
    queue<tuple<int, int, int>> q;
    q.emplace(0, 0, 0);
    visited[0][0] = true;

    // 🔸 Bắt đầu BFS
    while (!q.empty()) {
        auto [x, y, steps] = q.front();
        q.pop();

        // Nếu một trong hai bình có đúng c lít → in ra số bước và kết thúc
        if (x == c || y == c) {
            cout << steps << '\n';
            return 0;
        }

        // =========================
        // Sinh các trạng thái mới
        // =========================

        // 1️⃣ Đổ đầy bình A
        if (!visited[a][y]) {
            visited[a][y] = true;
            q.emplace(a, y, steps + 1);
        }

        // 2️⃣ Đổ đầy bình B
        if (!visited[x][b]) {
            visited[x][b] = true;
            q.emplace(x, b, steps + 1);
        }

        // 3️⃣ Đổ hết bình A
        if (!visited[0][y]) {
            visited[0][y] = true;
            q.emplace(0, y, steps + 1);
        }

        // 4️⃣ Đổ hết bình B
        if (!visited[x][0]) {
            visited[x][0] = true;
            q.emplace(x, 0, steps + 1);
        }

        // 5️⃣ Rót từ A sang B
        {
            int transfer = min(x, b - y);   // lượng nước chuyển từ A sang B
            int nx = x - transfer;          // A giảm
            int ny = y + transfer;          // B tăng
            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.emplace(nx, ny, steps + 1);
            }
        }

        // 6️⃣ Rót từ B sang A
        {
            int transfer = min(y, a - x);   // lượng nước chuyển từ B sang A
            int nx = x + transfer;          // A tăng
            int ny = y - transfer;          // B giảm
            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.emplace(nx, ny, steps + 1);
            }
        }
    }

    // Nếu BFS kết thúc mà không đạt được c lít
    cout << -1 << '\n';
    return 0;
}
