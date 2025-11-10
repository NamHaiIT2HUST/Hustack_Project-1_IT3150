#include <bits/stdc++.h>
using namespace std;

int n;

// Hàm đệ quy sinh chuỗi nhị phân không có "11"
void generate(string s) {
    // Nếu chuỗi đủ độ dài n → in ra
    if (s.size() == n) {
        cout << s << "\n";
        return;
    }

    // Luôn có thể thêm '0'
    generate(s + "0");

    // Chỉ được thêm '1' nếu chuỗi rỗng hoặc ký tự cuối ≠ '1'
    if (s.empty() || s.back() != '1')
        generate(s + "1");
}

int main() {
    cin >> n;
    generate(""); // Bắt đầu với chuỗi rỗng
    return 0;
}
