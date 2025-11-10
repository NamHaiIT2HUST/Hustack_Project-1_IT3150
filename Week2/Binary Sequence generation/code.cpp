#include <bits/stdc++.h>
using namespace std;

int n;

// Hàm đệ quy sinh các chuỗi nhị phân độ dài n
void generate(string s) {
    if (s.size() == n) {       // Nếu chuỗi đủ độ dài n
        cout << s << "\n";     // In ra
        return;
    }

    generate(s + "0");         // Gắn thêm '0' và sinh tiếp
    generate(s + "1");         // Gắn thêm '1' và sinh tiếp
}

int main() {
    cin >> n;
    generate("");              // Gọi hàm bắt đầu từ chuỗi rỗng
    return 0;
}
