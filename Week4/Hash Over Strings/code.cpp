#include <bits/stdc++.h>
using namespace std;

/*
🧩 ĐỀ BÀI
---------------------------------
Cho n chuỗi s[1…k] chỉ gồm ký tự thường ('a'..'z'), 
và một số nguyên dương m.

Cần tính mã băm (hash code) của từng chuỗi theo công thức:
    H(s) = (s[1]*256^(k-1) + s[2]*256^(k-2) + ... + s[k]*256^0) mod m

Trong đó s[i] là mã ASCII của ký tự thứ i trong chuỗi.

Yêu cầu: In ra H(s) của từng chuỗi.

---------------------------------
📥 INPUT
- Dòng 1: n và m (1 ≤ n, m ≤ 100000)
- n dòng tiếp theo: mỗi dòng là 1 chuỗi có độ dài ≤ 200

📤 OUTPUT
- Mỗi dòng in ra hash code của chuỗi tương ứng.

---------------------------------
🧠 HƯỚNG GIẢI
- Với mỗi chuỗi s:
    + Duyệt từ trái sang phải.
    + Tính giá trị băm theo quy tắc luỹ thừa 256 giảm dần.
      Tuy nhiên, ta không cần tính 256^(k-1) trước.
      Có thể dùng cách nhân dồn:
        hash = (hash * 256 + s[i]) % m
      => kết quả tương đương nhưng tránh tràn số.
- Lặp lại cho tất cả n chuỗi.

---------------------------------
⚙️ GIẢI THÍCH CODE
1️⃣ Đọc n và m
2️⃣ Với mỗi chuỗi s:
      khởi tạo hash = 0
      với từng ký tự c trong s:
          hash = (hash * 256 + int(c)) % m
      in ra hash
3️⃣ Độ phức tạp:
      Mỗi chuỗi O(k), tổng O(n*k) ≤ 100000 * 200 = 2×10⁷ (chạy được)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        long long h = 0;
        for (char c : s) {
            h = (h * 256 + int(c)) % m;
        }
        cout << h << "\n";
    }
}
