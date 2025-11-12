#include <bits/stdc++.h>
using namespace std;

/*
───────────────────────────── PHÂN TÍCH ĐỀ ─────────────────────────────

ĐỀ BÀI:
- Ta có dữ liệu giao dịch ngân hàng, mỗi dòng chứa:
    <from_account> <to_account> <money> <time_point> <atm>

  Trong đó:
  • from_account: tài khoản gửi (chuỗi độ dài 6–20)
  • to_account: tài khoản nhận (chuỗi độ dài 6–20)
  • money: số tiền giao dịch (1–10000)
  • time_point: thời gian giao dịch (HH:MM:SS)
  • atm: mã cây ATM (chuỗi độ dài 3–10)

- Một **chu trình giao dịch (transaction cycle)** độ dài k bắt đầu từ a1 là
  dãy các tài khoản **phân biệt**:
        a1 → a2 → a3 → … → ak → a1
  sao cho tồn tại giao dịch từ ai → ai+1 (và ak → a1).

CẦN XỬ LÝ 5 LOẠI TRUY VẤN:
1️⃣ ?number_transactions  
    → Tổng số giao dịch trong dữ liệu.

2️⃣ ?total_money_transaction  
    → Tổng số tiền của tất cả giao dịch.

3️⃣ ?list_sorted_accounts  
    → Danh sách tất cả các tài khoản (gửi + nhận), sắp xếp theo thứ tự tăng dần.

4️⃣ ?total_money_transaction_from <account>  
    → Tổng số tiền gửi đi từ tài khoản đó.

5️⃣ ?inspect_cycle <account> k  
    → Kiểm tra xem có **chu trình** độ dài k bắt đầu từ account đó không.
      Nếu có → in 1, ngược lại → in 0.

───────────────────────────── HƯỚNG GIẢI ─────────────────────────────

1️⃣ Đọc dữ liệu giao dịch:
    - Lưu toàn bộ các giao dịch (from, to, money).
    - Tính:
        • Tổng số giao dịch
        • Tổng tiền
        • Tổng tiền gửi từ từng account
        • Danh sách tất cả account
    - Xây dựng **đồ thị có hướng** `adj[from].push_back(to)` để phục vụ kiểm tra chu trình.

2️⃣ Truy vấn:
    - Với các truy vấn thống kê, chỉ cần dùng các map/unordered_map.
    - Với `?inspect_cycle`: dùng DFS giới hạn độ sâu k:
        • Xuất phát từ account gốc.
        • Không đi qua lại tài khoản đã thăm.
        • Khi độ sâu = k, kiểm tra xem có cạnh quay lại gốc hay không.
        • Nếu có → trả về 1.

3️⃣ Tối ưu:
    - Dừng sớm nếu tìm thấy chu trình.
    - Giới hạn độ sâu DFS = k (nhỏ hơn số lượng đỉnh).

───────────────────────────── CÀI ĐẶT ─────────────────────────────
*/
unordered_map<string, vector<string>> adj;
unordered_map<string, long long> total_from;
set<string> all_accounts;
long long total_transactions = 0;
long long total_money = 0;

bool found_cycle = false;

void dfs(const string &start, const string &current, int depth, int k, unordered_set<string> &visited) {
    if (found_cycle) return;
    if (depth == k) {
        for (auto &next : adj[current]) {
            if (next == start) {
                found_cycle = true;
                return;
            }
        }
        return;
    }
    for (auto &next : adj[current]) {
        if (!visited.count(next)) {
            visited.insert(next);
            dfs(start, next, depth + 1, k, visited);
            visited.erase(next);
        }
    }
}

bool has_cycle(const string &account, int k) {
    if (!adj.count(account)) return false;
    unordered_set<string> visited;
    visited.insert(account);
    found_cycle = false;
    dfs(account, account, 1, k, visited);
    return found_cycle;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line == "#") break;
        if (line.empty()) continue;
        string from, to, time_point, atm;
        long long money;
        stringstream ss(line);
        ss >> from >> to >> money >> time_point >> atm;
        adj[from].push_back(to);
        total_from[from] += money;
        total_money += money;
        total_transactions++;
        all_accounts.insert(from);
        all_accounts.insert(to);
    }

    while (getline(cin, line)) {
        if (line == "#") break;
        if (line.empty()) continue;
        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "?number_transactions") {
            cout << total_transactions << "\n";
        }
        else if (query == "?total_money_transaction") {
            cout << total_money << "\n";
        }
        else if (query == "?list_sorted_accounts") {
            bool first = true;
            for (auto &acc : all_accounts) {
                if (!first) cout << " ";
                cout << acc;
                first = false;
            }
            cout << "\n";
        }
        else if (query == "?total_money_transaction_from") {
            string acc;
            ss >> acc;
            cout << total_from[acc] << "\n";
        }
        else if (query == "?inspect_cycle") {
            string acc;
            int k;
            ss >> acc >> k;
            cout << (has_cycle(acc, k) ? 1 : 0) << "\n";
        }
    }

    return 0;
}
