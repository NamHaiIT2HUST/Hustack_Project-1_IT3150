#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; 
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    string tmp; 
    cin >> tmp;
    cin.ignore();   

    string line;
    while (getline(cin, line)) {
        if (line == "***") break;
        stringstream ss(line);    //getline đọc từ bán phím mình gõ, stringstream đọc lại line thay vì phải đi cut chuỗi
        string cmd; ss >> cmd; 

        if (cmd == "find-max")
            cout << *max_element(a.begin(), a.end()) << "\n";
        else if (cmd == "find-min")
            cout << *min_element(a.begin(), a.end()) << "\n";
        else if (cmd == "sum")
            cout << accumulate(a.begin(), a.end(), 0) << "\n";
        else if (cmd == "find-max-segment") {
            int i, j; 
            ss >> i >> j;
            cout << *max_element(a.begin() + i - 1, a.begin() + j) << "\n";
        }
    }
}
