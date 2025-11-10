#include <bits/stdc++.h>
using namespace std;

int main() {
    queue<int> q;     // Tạo một hàng đợi rỗng để lưu các số nguyên
    string cmd;       // Chuỗi chứa lệnh nhập từ bàn phím

    // Đọc lần lượt từng lệnh cho đến khi gặp ký tự #
    while (cin >> cmd && cmd != "#") {

        // Nếu lệnh là PUSH v
        if (cmd == "PUSH") {
            int v;       // giá trị cần thêm vào hàng đợi
            cin >> v;    // đọc giá trị sau lệnh PUSH
            q.push(v);   // thêm vào cuối hàng đợi
        }

        // Nếu lệnh là POP
        else if (cmd == "POP") {
            // Nếu hàng đợi đang rỗng
            if (q.empty()) {
                cout << "NULL\n";  // không có phần tử nào để lấy
            }
            // Nếu hàng đợi có phần tử
            else {
                cout << q.front() << "\n"; // in phần tử ở đầu hàng
                q.pop();                   // loại bỏ phần tử đầu hàng
            }
        }
    }

    return 0; // Kết thúc chương trình
}
