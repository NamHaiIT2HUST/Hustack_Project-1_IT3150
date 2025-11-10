#include <bits/stdc++.h>
using namespace std;

/*
  🧩 ĐỀ BÀI:
  Cho một chuỗi chỉ gồm các ký tự ngoặc: (, ), [, ], {, }.
  Hãy kiểm tra xem chuỗi này có phải là một "biểu thức ngoặc đúng" hay không.
  
  - "Đúng" nghĩa là:
      + Mỗi ngoặc mở đều có ngoặc đóng tương ứng đúng loại và đúng thứ tự.
      + Các ngoặc lồng nhau hợp lệ (ví dụ: ({[]}) là đúng, nhưng ([)] là sai).

  ✅ Ví dụ:
    ([]{()}()[])  → đúng  (output: 1)
    ([]{()]()[])  → sai   (output: 0)

  🔢 Input:
    Một dòng chứa chuỗi ngoặc, độ dài ≤ 10^6.

  🧾 Output:
    In 1 nếu chuỗi ngoặc đúng, ngược lại in 0.

  💡 Ý tưởng giải:
    - Dùng ngăn xếp (stack<char>) để kiểm tra tính hợp lệ của chuỗi ngoặc.
    - Duyệt từng ký tự trong chuỗi:
        + Nếu là ngoặc mở: đẩy vào stack.
        + Nếu là ngoặc đóng:
            → kiểm tra xem stack có rỗng không.
            → nếu không rỗng, lấy phần tử trên cùng (top) và so sánh xem có khớp kiểu không.
            → nếu không khớp hoặc stack rỗng → sai ngay (in 0).
    - Sau khi duyệt hết chuỗi:
        + Nếu stack rỗng → đúng (in 1)
        + Nếu vẫn còn phần tử trong stack → sai (in 0)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    stack<char> st; // ngăn xếp lưu các ngoặc mở

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            // Gặp ngoặc mở -> đẩy vào stack
            st.push(c);
        } else {
            // Gặp ngoặc đóng -> kiểm tra stack
            if (st.empty()) {
                cout << 0;
                return 0;
            }

            char top = st.top();
            st.pop();

            // Kiểm tra cặp ngoặc có khớp không
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                cout << 0;
                return 0;
            }
        }
    }

    // Sau khi duyệt hết, nếu stack còn phần tử => sai
    if (!st.empty()) cout << 0;
    else cout << 1;

    return 0;
}
