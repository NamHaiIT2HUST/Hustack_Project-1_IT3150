#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
🔍 PHÂN TÍCH ĐỀ BÀI:
    ---------------------------------------
    - Mỗi dòng dữ liệu thể hiện 1 đơn hàng:
        <CustomerID> <ProductID> <Price> <ShopID> <TimePoint>

    - Sau khối dữ liệu đầu (các đơn hàng), có một dòng "#"
      => tiếp theo là khối truy vấn (query).

    - Có 5 loại truy vấn:
        1️⃣ ?total_number_orders
             → số lượng đơn hàng (dòng dữ liệu đầu vào)
        2️⃣ ?total_revenue
             → tổng doanh thu của toàn bộ hệ thống
        3️⃣ ?revenue_of_shop <ShopID>
             → tổng doanh thu của shop đó
        4️⃣ ?total_consume_of_customer_shop <CustomerID> <ShopID>
             → tổng số tiền khách đó mua ở shop đó
        5️⃣ ?total_revenue_in_period <from_time> <to_time>
             → tổng doanh thu trong khoảng thời gian [from, to]

    ---------------------------------------
    🔢 ĐẦU VÀO:
        - Khối 1: Các đơn hàng
            VD: C001 P001 10 SHOP001 10:30:10
        - Dòng "#" ngăn cách
        - Khối 2: Các truy vấn
        - Dòng "#" kết thúc

    ✅ Phân tích & hướng giải
    --------------------------
    - Bài toán quản lý và truy vấn doanh thu bán hàng.
    - Các truy vấn cần được trả lời nhanh → dùng map/unordered_map + prefix sum.

    - Các truy vấn dạng:
        ?total_number_orders
        ?total_revenue
        ?revenue_of_shop <ShopID>
        ?total_consume_of_customer_shop <CustomerID> <ShopID>
        ?total_revenue_in_period <from_time> <to_time>

    ⚡ Cách tối ưu phần truy vấn theo thời gian:
        - Sắp xếp danh sách (time, price) theo thời gian.
        - Tạo prefix_sum[i] = tổng doanh thu đến thời điểm i.
        - Khi query, chỉ cần dùng lower_bound + upper_bound và trừ 2 giá trị prefix.
        → Mỗi truy vấn O(log N) thay vì O(N)
*/

struct Order {
    string customer, product, shop;
    int price, timeInSeconds;
};

unordered_map<string, ll> revenue_of_shop;
map<pair<string, string>, ll> customer_shop_revenue;
vector<pair<int, int>> time_revenue;
vector<ll> prefix_sum;
vector<Order> orders;
ll total_revenue = 0;

// ✅ Chuyển "HH:MM:SS" → giây để dễ so sánh
int convertTime(const string &t) {
    int h = stoi(t.substr(0, 2));
    int m = stoi(t.substr(3, 2));
    int s = stoi(t.substr(6, 2));
    return h * 3600 + m * 60 + s;
}

// ✅ Đọc danh sách đơn hàng
void readOrders() {
    string line;
    while (getline(cin, line)) {
        if (line == "#") break;
        if (line.empty()) continue;

        stringstream ss(line);
        string customer, product, shop, time_str;
        int price;
        ss >> customer >> product >> price >> shop >> time_str;

        int timeSec = convertTime(time_str);

        orders.push_back({customer, product, shop, price, timeSec});
        total_revenue += price;
        revenue_of_shop[shop] += price;
        customer_shop_revenue[{customer, shop}] += price;
        time_revenue.push_back({timeSec, price});
    }

    sort(time_revenue.begin(), time_revenue.end());

    // ✅ Tiền xử lý prefix sum cho phần truy vấn theo thời gian
    prefix_sum.resize(time_revenue.size() + 1, 0);
    for (int i = 0; i < (int)time_revenue.size(); ++i)
        prefix_sum[i + 1] = prefix_sum[i] + time_revenue[i].second;
}

// ✅ Tính tổng doanh thu trong khoảng thời gian [from, to]
ll revenueInPeriod(int fromSec, int toSec) {
    auto l = lower_bound(time_revenue.begin(), time_revenue.end(), make_pair(fromSec, 0));
    auto r = upper_bound(time_revenue.begin(), time_revenue.end(), make_pair(toSec, INT_MAX));

    int leftIdx = l - time_revenue.begin();
    int rightIdx = r - time_revenue.begin();

    return prefix_sum[rightIdx] - prefix_sum[leftIdx];
}

// ✅ Xử lý từng truy vấn
void processQuery(const string &queryLine) {
    stringstream ss(queryLine);
    string query;
    ss >> query;

    if (query == "?total_number_orders") {
        cout << orders.size() << "\n";
    }
    else if (query == "?total_revenue") {
        cout << total_revenue << "\n";
    }
    else if (query == "?revenue_of_shop") {
        string shop;
        ss >> shop;
        cout << revenue_of_shop[shop] << "\n";
    }
    else if (query == "?total_consume_of_customer_shop") {
        string customer, shop;
        ss >> customer >> shop;
        cout << customer_shop_revenue[{customer, shop}] << "\n";
    }
    else if (query == "?total_revenue_in_period") {
        string from_t, to_t;
        ss >> from_t >> to_t;
        int fromSec = convertTime(from_t);
        int toSec = convertTime(to_t);
        cout << revenueInPeriod(fromSec, toSec) << "\n";
    }
}

// ✅ Đọc và xử lý tất cả truy vấn
void handleQueries() {
    string line;
    while (getline(cin, line)) {
        if (line == "#") break;
        if (line.empty()) continue;
        processQuery(line);
    }
}

// ✅ MAIN
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readOrders();     // đọc toàn bộ đơn hàng
    handleQueries();  // xử lý tất cả truy vấn

    return 0;
}
