#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // B1: Tạo mảng 1..n
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = i + 1;

    // B2: In hoán vị đầu tiên
    do {
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << "\n";
    } while (next_permutation(a.begin(), a.end())); // Sinh hoán vị kế tiếp
    //hàm có sẵn trong thư viện thuật toán, đổi dần hoán vị các phần tử trong vector cho đến khi về lại hoán vị ban đầu

    return 0;
}
