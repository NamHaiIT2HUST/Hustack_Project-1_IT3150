#include <bits/stdc++.h>
using namespace std;

//fixed in dạng thập phân với n số sau dấu phẩy
//setprecision(2) lấy 2 chữ số có nghĩa sau dấu phẩy, lấy trong thư viện iomanip



int main() {
    double a, b, c;
    cin >> a >> b >> c;

    const double EPS = 1e-9;  //so sánh với 10^-9

    //nếu a đủ nhỏ coi như = 0
    if (fabs(a) < EPS) { 
        if (fabs(b) < EPS) {
            cout << "NO SOLUTION";
        } else {
            double x = -c / b;
            cout << fixed << setprecision(2) << x;
        }

    } else {
        double d = b*b - 4*a*c;
        if (d < -EPS) {
            cout << "NO SOLUTION";
        } else if (fabs(d) < EPS) {
            double x = -b / (2*a);
            cout << fixed << setprecision(2) << x;
        } else {
            double x1 = (-b - sqrt(d)) / (2*a);
            double x2 = (-b + sqrt(d)) / (2*a);
            if (x1 > x2) swap(x1, x2);
            cout << fixed << setprecision(2) << x1 << " " << x2;
        }
    }
    return 0;
}
