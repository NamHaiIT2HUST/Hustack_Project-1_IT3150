#include <bits/stdc++.h>
using namespace std;

/*
BÀI: Analyze Code Submission of a Programming Contest
-----------------------------------------------------
MỖI DÒNG SUBMISSION:
<UserID> <ProblemID> <TimePoint> <Status> <Point>

YÊU CẦU:
1. ?total_number_submissions
2. ?number_error_submision
3. ?number_error_submision_of_user <UserID>
4. ?total_point_of_user <UserID>
5. ?number_submission_period <from_time_point> <to_time_point>

CÁCH GIẢI:
- Lưu tổng số submissions
- Lưu số submission ERR
- Lưu số ERR theo user
- Lưu max point của mỗi (user, problem)
- Lưu tất cả time_points (chuyển sang giây) để đếm submissions trong khoảng

TRUY VẤN:
- Các truy vấn đơn giản trả về ngay
- Khoảng thời gian: dùng binary search trên mảng đã sort
*/

// Hàm chuyển HH:MM:SS → số giây
int timeToSec(const string &t) {
    int h, m, s;
    sscanf(t.c_str(), "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- Khai báo dữ liệu ---
    long long total_submissions = 0;
    long long total_error = 0;
    unordered_map<string, int> err_by_user;
    unordered_map<string, unordered_map<string, int>> max_point;
    vector<int> times; // lưu timepoints (dạng giây)

    // --- Đọc block 1 (submission data) ---
    string line;
    while (getline(cin, line)) {
        if (line == "#") break;
        if (line.empty()) continue;
        string user, prob, time_str, status;
        int point;
        stringstream ss(line);
        ss >> user >> prob >> time_str >> status >> point;

        total_submissions++;
        times.push_back(timeToSec(time_str));

        if (status == "ERR") {
            total_error++;
            err_by_user[user]++;
        }

        // lưu điểm tối đa cho mỗi user-problem
        int &best = max_point[user][prob];
        if (point > best) best = point;
    }

    // sort thời gian để xử lý binary search
    sort(times.begin(), times.end());

    // --- Đọc block 2 (queries) ---
    while (getline(cin, line)) {
        if (line == "#") break;
        if (line.empty()) continue;

        stringstream ss(line);
        string q;
        ss >> q;

        if (q == "?total_number_submissions") {
            cout << total_submissions << "\n";
        }
        else if (q == "?number_error_submision") {
            cout << total_error << "\n";
        }
        else if (q == "?number_error_submision_of_user") {
            string user; ss >> user;
            cout << err_by_user[user] << "\n";
        }
        else if (q == "?total_point_of_user") {
            string user; ss >> user;
            long long total = 0;
            if (max_point.count(user)) {
                for (auto &p : max_point[user]) total += p.second;
            }
            cout << total << "\n";
        }
        else if (q == "?number_submission_period") {
            string t1, t2;
            ss >> t1 >> t2;
            int a = timeToSec(t1), b = timeToSec(t2);
            auto itL = lower_bound(times.begin(), times.end(), a);
            auto itR = upper_bound(times.begin(), times.end(), b);
            cout << (itR - itL) << "\n";
        }
    }

    return 0;
}
