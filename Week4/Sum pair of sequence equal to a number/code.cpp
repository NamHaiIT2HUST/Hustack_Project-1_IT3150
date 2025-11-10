#include <bits/stdc++.h>
using namespace std;

/*
  Bài toán (tóm tắt):
  ------------------
  Cho dãy a1, a2, ..., an (các phần tử đôi một khác nhau) và một số nguyên dương M.
  Hãy đếm số Q các cặp (i, j) sao cho 1 <= i < j <= n và ai + aj = M.

  Ràng buộc:
    - 1 <= n, M <= 1 000 000
    - Các ai đôi một khác nhau (theo đề bài).
    - Kết quả Q có thể lớn, dùng kiểu long long để chứa.

  Ý tưởng & hướng giải (chi tiết):
  -------------------------------
  Ta cần đếm số cặp (i, j) với ai + aj = M.
  Một phương pháp nhanh (O(n) thời gian, O(n) bộ nhớ) là:
    - Duyệt qua mảng từ trái sang phải.
    - Với phần tử hiện tại x = a[i], ta cần tìm các phần tử trước đó có giá trị need = M - x.
    - Nếu need đã xuất hiện trước đó (ta lưu các phần tử đã gặp vào một tập `seen`),
      thì mỗi lần thấy need tương ứng với một cặp (previous_index, i).
    - Vì các phần tử là đôi một khác nhau, mỗi giá trị need chỉ có thể xuất hiện tối đa 1 lần.
    - Sau khi kiểm tra, thêm x vào `seen`.
  Cách làm này đảm bảo không đếm trùng (luôn i > previous_index) nên thỏa yêu cầu 1 <= i < j.
  Ta lưu ý dùng `unordered_set` để tra nhanh (O(1) trung bình).
  Độ phức tạp:
    - Thời gian: O(n) trung bình (do thao tác trên unordered_set)
    - Bộ nhớ: O(n)

  Lưu ý:
    - Nếu dữ liệu không đảm bảo các phần tử khác nhau, cách này vẫn hoạt động nếu
      ta thay `unordered_set` bằng `unordered_map<value, count>` để xử lý tần suất;
      nhưng theo đề bài, các phần tử đôi một khác nhau nên dùng set là đủ.
    - Kết quả được lưu trong `long long` để tránh tràn khi n lớn.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long M; // M có thể tới 1e6, long long an toàn hơn
    if (!(cin >> n >> M)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // seen: lưu các giá trị đã xuất hiện (các a[k] với k < i)
    unordered_set<long long> seen;
    seen.reserve(n * 2);            // reserve để giảm rehash, tăng tốc
    seen.max_load_factor(0.7f);

    long long Q = 0; // biến đếm số cặp, dùng long long

    for (int i = 0; i < n; ++i) {
        long long x = a[i];
        long long need = M - x;

        // Nếu need đã thấy trước đó => tồn tại index j < i với a[j] = need
        if (seen.find(need) != seen.end()) {
            ++Q;
        }

        // Thêm giá trị hiện tại vào tập đã thấy để phục vụ các phần tử sau
        seen.insert(x);
    }

    cout << Q << '\n';
    return 0;
}
