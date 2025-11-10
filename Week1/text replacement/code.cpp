#include <bits/stdc++.h>   // Gộp toàn bộ các thư viện chuẩn
using namespace std;

int main() {
    string P1, P2, T;
    
    // Đọc 3 dòng từ input:
    // P1: chuỗi cần tìm
    // P2: chuỗi thay thế
    // T : chuỗi gốc (văn bản cần xử lý)
    getline(cin, P1);
    getline(cin, P2);
    getline(cin, T);
    
    size_t pos = 0;  // Biến lưu vị trí tìm thấy chuỗi con trong T
    
    // Vòng lặp tìm và thay thế P1 trong T

    //string::npos là một giá trị đặc biệt (của kiểu size_t) dùng để biểu thị rằng:
    //❌ Không tìm thấy (no position) trong chuỗi.
    while ((pos = T.find(P1, pos)) != string::npos) {
        // Nếu tìm thấy P1 trong T tại vị trí pos,
        // thì thay thế nó bằng P2
        T.replace(pos, P1.size(), P2);

        // Sau khi thay xong, dịch vị trí tìm kiếm sang sau phần thay thế
        pos += P2.size();
    }

    // In ra chuỗi T sau khi đã thay thế xong
    cout << T;
    return 0;
}
