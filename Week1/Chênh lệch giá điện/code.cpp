#include <bits/stdc++.h>  // Thư viện gom hầu hết các thư viện chuẩn của C++
using namespace std;

// ✅ Hàm tính tiền điện theo BIỂU GIÁ 6 BẬC
double calc6(int kwh) {
    // Giới hạn kWh cho từng bậc giá
    int limit[] = {50, 50, 100, 100, 100, INT_MAX};
    // Đơn giá tương ứng của từng bậc (đồng/kWh)
    double price[] = {1728, 1786, 2074, 2612, 2919, 3015};

    double cost = 0;  // Tổng tiền chưa có VAT

    // Lặp qua 6 bậc, tính số điện tiêu thụ trong mỗi bậc
    for (int i = 0; i < 6 && kwh > 0; i++) {
        // Lấy số kWh thực tế dùng trong bậc này (không vượt quá limit[i])
        int used = min(kwh, limit[i]);

        // Cộng tiền cho phần điện đã dùng ở bậc này
        cost += used * price[i];

        // Trừ số kWh đã tính ra khỏi tổng còn lại
        kwh -= used;
    }

    return cost;  // Trả về tổng tiền chưa có VAT
}

// ✅ Hàm tính tiền điện theo BIỂU GIÁ 5 BẬC
double calc5(int kwh) {
    // Giới hạn kWh cho từng bậc
    int limit[] = {100, 100, 200, 300, INT_MAX};
    // Đơn giá tương ứng cho từng bậc
    double price[] = {1728, 2074, 2612, 3111, 3457};

    double cost = 0;  // Tổng tiền chưa có VAT

    // Lặp qua 5 bậc
    for (int i = 0; i < 5 && kwh > 0; i++) {
        // Số điện dùng trong bậc này (nếu kwh ít hơn limit thì chỉ tính phần đó)
        int used = min(kwh, limit[i]);

        // Tính tiền cho số điện của bậc này
        cost += used * price[i];

        // Trừ ra phần điện đã tính
        kwh -= used;
    }

    return cost;  // Trả về tổng tiền chưa có VAT
}

int main() {
    int kwh;  // Số điện tiêu thụ (kWh)
    cin >> kwh;  // Nhập từ bàn phím

    // Tính tiền điện theo hai biểu giá, đã bao gồm 10% VAT
    double cost6 = calc6(kwh) * 1.1;  // Biểu giá 6 bậc
    double cost5 = calc5(kwh) * 1.1;  // Biểu giá 5 bậc

    // Tính chênh lệch giữa hai biểu giá
    double diff = cost5 - cost6;

    // In kết quả với 2 chữ số sau dấu phẩy
    cout << fixed << setprecision(2) << diff;

    return 0;  // Kết thúc chương trình
}
