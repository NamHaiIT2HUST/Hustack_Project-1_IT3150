#include <bits/stdc++.h>
using namespace std;

// Hằng số MOD = 10^9 + 7 (số nguyên tố lớn, thường dùng để lấy dư tránh tràn số)
const int MOD = 1e9 + 7;

int main() {
    int k, n;
    cin >> k >> n; // Đọc vào hai số nguyên dương k và n

    // Tạo bảng 2 chiều C có kích thước (n+1) x (k+1)
    // C[i][j] sẽ lưu giá trị C(i, j): số cách chọn j phần tử từ i phần tử
    // Khởi tạo tất cả phần tử = 0
    vector<vector<long long>> C(n + 1, vector<long long>(k + 1, 0));

    // Duyệt i từ 0 đến n (số phần tử tổng)
    for (int i = 0; i <= n; i++) {
        // Với mỗi i, chỉ cần xét j từ 0 đến min(i, k)
        // (vì không thể chọn nhiều hơn i phần tử)
        for (int j = 0; j <= min(i, k); j++) {

            // Nếu j == 0: chọn 0 phần tử từ i phần tử → chỉ có 1 cách (không chọn gì)
            // Nếu j == i: chọn toàn bộ i phần tử → cũng chỉ có 1 cách
            if (j == 0 || j == i)
                C[i][j] = 1;

            // Ngược lại, áp dụng công thức Pascal:
            // C(i, j) = C(i-1, j-1) + C(i-1, j)
            // (chọn phần tử thứ i hoặc không chọn nó)
            else
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD; // Lấy modulo để tránh tràn số
        }
    }

    // Sau khi điền xong bảng, kết quả cần tìm là C[n][k]
    cout << C[n][k];

    return 0; // Kết thúc chương trình
}
