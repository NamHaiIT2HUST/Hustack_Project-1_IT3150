#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
🧩 ĐỀ BÀI
---------------------------------
Cho dãy số nguyên A1, A2, ..., An.
Với mỗi phần tử Ai, kiểm tra xem trước đó (với j < i)
đã có phần tử Aj nào bằng Ai hay chưa.

Nếu có → in 1  
Nếu chưa → in 0

Ví dụ:
Input:
5
1 4 3 1 4

Output:
0
0
0
1
1


🧠 HƯỚNG GIẢI
---------------------------------
- Duyệt dãy từ trái sang phải.
- Dùng một tập hợp (set) để lưu lại các phần tử đã gặp.
- Với mỗi Ai:
    + Nếu Ai đã có trong set → in 1
    + Nếu chưa có → in 0 và thêm Ai vào set
- Dùng set vì có thể kiểm tra và chèn nhanh (O(log n)).


⚙️ GIẢI THÍCH CODE
---------------------------------
1️⃣ Đọc n và mảng a
2️⃣ Khởi tạo set<ll> s để lưu các giá trị đã thấy
3️⃣ Với mỗi phần tử:
    - Nếu s.count(a[i]) == true → in 1
    - Ngược lại in 0 và s.insert(a[i])
4️⃣ Độ phức tạp: O(n log n)


✅ KẾT LUẬN
---------------------------------
- Ý tưởng: kiểm tra trùng lặp bằng set
- Đơn giản, gọn, chạy nhanh, đúng yêu cầu
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    set<ll> s;  
    for (int i = 0; i < n; i++) {
        if (s.count(a[i])) cout << 1 << "\n";
        else {
            cout << 0 << "\n";
            s.insert(a[i]);
        }
    }
}
