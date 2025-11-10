#include <bits/stdc++.h>
using namespace std;

int main() {
    stack<int> st;   // Tạo một stack rỗng để lưu các số nguyên
    string cmd;      // Chuỗi để đọc lệnh nhập vào

    // Đọc từng lệnh cho đến khi gặp ký tự kết thúc "#"
    while (cin >> cmd && cmd != "#") {

        // Nếu lệnh là "PUSH"
        if (cmd == "PUSH") {
            int v;       // giá trị cần đẩy vào stack
            cin >> v;    // đọc giá trị sau lệnh PUSH
            st.push(v);  // thêm phần tử v vào đỉnh stack
        }

        // Nếu lệnh là "POP"
        else if (cmd == "POP") {
            // Nếu stack rỗng thì không có gì để lấy ra
            if (st.empty()) {
                cout << "NULL\n";  // in ra NULL
            }
            // Nếu stack có phần tử
            else {
                cout << st.top() << "\n"; // In phần tử ở đỉnh stack
                st.pop();                 // Xóa phần tử đó ra khỏi stack
            }
        }
    }

    return 0; // Kết thúc chương trình
}
