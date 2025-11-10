#include <bits/stdc++.h>
using namespace std;

/*
📘 ĐỀ BÀI
---------------------------------
Một cơ sở dữ liệu chứa danh sách các chuỗi (khóa):
    k1, k2, ..., kn

Sau đó, có các thao tác cần thực hiện trên cơ sở dữ liệu:
    - find k   : tìm xem k có trong cơ sở dữ liệu hay không
                 → in 1 nếu có, 0 nếu không
    - insert k : chèn thêm k vào cơ sở dữ liệu
                 → in 1 nếu chèn thành công (k chưa tồn tại)
                 → in 0 nếu thất bại (k đã tồn tại)

Dữ liệu nhập:
- Khối 1: danh sách các chuỗi (mỗi dòng 1 chuỗi)
          kết thúc bằng dòng chứa dấu "*"
- Khối 2: danh sách các thao tác (find/insert), kết thúc bằng dòng "***"

Giới hạn:
- n ≤ 100000, số thao tác ≤ 100000
- Mỗi chuỗi dài ≤ 50 ký tự

---------------------------------
🎯 YÊU CẦU
- Với mỗi thao tác find/insert, in ra kết quả (0 hoặc 1).

---------------------------------
💡 HƯỚNG GIẢI
1️⃣ Dùng cấu trúc dữ liệu `set<string>` hoặc `unordered_set<string>` để lưu trữ tập khóa:
    - `insert`: O(log n) hoặc O(1) trung bình
    - `find`  : O(log n) hoặc O(1) trung bình

2️⃣ Quy trình:
    - Đọc các chuỗi vào set cho đến khi gặp "*"
    - Sau đó đọc từng lệnh cho đến "***":
        + Nếu là "find k": kiểm tra xem k có trong set không → in 1 hoặc 0
        + Nếu là "insert k": 
             - nếu chưa có → chèn và in 1
             - nếu có rồi → in 0

---------------------------------
⚙️ ĐỘ PHỨC TẠP
- O(n + q), với n là số chuỗi ban đầu và q là số thao tác.
- Bộ nhớ: O(n), vì chỉ lưu các chuỗi trong set.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_set<string> db;  // lưu các khóa duy nhất
    string s;

    // --- Đọc khối 1: danh sách ban đầu ---
    while (true) {
        if (!(cin >> s)) return 0;
        if (s == "*") break;
        db.insert(s);
    }

    // --- Đọc khối 2: thao tác find / insert ---
    string cmd, key;
    while (true) {
        cin >> cmd;
        if (cmd == "***") break;
        cin >> key;

        if (cmd == "find") {
            cout << (db.count(key) ? 1 : 0) << "\n";
        } 
        else if (cmd == "insert") {
            if (db.count(key)) cout << 0 << "\n";
            else {
                db.insert(key);
                cout << 1 << "\n";
            }
        }
    }

    return 0;
}
