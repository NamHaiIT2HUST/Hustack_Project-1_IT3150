#include <bits/stdc++.h>
using namespace std;

/*
  Đếm số nghiệm của Sudoku 9x9 cho bảng nhập (0 = ô trống).
  Chiến lược:
    - rows[r], cols[c], boxes[b] là bitmask 9 bit, bit d-1 = 1 nghĩa là số (d) đã xuất hiện.
    - empties: danh sách các ô trống (r,c).
    - Backtracking với heuristic MRV: tại mỗi bước chọn ô trống có ít lựa chọn nhất.
*/

using ull = unsigned long long;

// global data
int grid[9][9];            // lưu bảng (0 = trống)
int rowsMask[9];           // rowsMask[r]: bit i =1 nếu số (i+1) đã có trong hàng r
int colsMask[9];           // colsMask[c]: tương tự cho cột
int boxesMask[9];          // boxesMask[b]: tương tự cho khối 3x3
vector<pair<int,int>> empties; // danh sách ô trống (r,c)
const int FULL = (1 << 9) - 1; // mask 9 bit tất cả 1 (bits 0..8 tương ứng số 1..9)

ull solutions = 0; // biến đếm nghiệm (dùng unsigned long long)

/* Hàm tiện: trả index box (0..8) từ vị trí (r,c) */
inline int boxIndex(int r, int c) {
    return (r / 3) * 3 + (c / 3);
}

/*
  Hàm đệ quy dfs:
    filled = số ô trống đã điền (we keep empties arranged so that positions [0..filled-1] are already set)
    empties.size() = total empty cells
*/
void dfs(int filled) {
    int m = (int)empties.size();
    if (filled == m) {
        // đã điền hết -> tìm được 1 nghiệm
        ++solutions;
        return;
    }

    // MRV: tìm ô (index từ filled..m-1) có số lượng lựa chọn nhỏ nhất
    int bestIdx = -1;
    int bestCount = 10; // số lựa chọn tối thiểu (1..9), khởi để >9
    for (int i = filled; i < m; ++i) {
        int r = empties[i].first;
        int c = empties[i].second;
        int b = boxIndex(r, c);
        int availMask = ~(rowsMask[r] | colsMask[c] | boxesMask[b]) & FULL; // các bit cho phép
        int cnt = __builtin_popcount(availMask);
        if (cnt == 0) {
            // Ô này không có lựa chọn -> nhánh vô nghiệm, prune ngay
            return;
        }
        if (cnt < bestCount) {
            bestCount = cnt;
            bestIdx = i;
            if (bestCount == 1) break; // không thể tốt hơn, dừng tìm
        }
    }

    // hoán đổi vị trí bestIdx về vị trí 'filled' để xử lý
    swap(empties[filled], empties[bestIdx]);
    int r = empties[filled].first;
    int c = empties[filled].second;
    int b = boxIndex(r, c);
    int availMask = ~(rowsMask[r] | colsMask[c] | boxesMask[b]) & FULL;

    // duyệt từng lựa chọn (bit) trong availMask
    while (availMask) {
        int pick = availMask & -availMask; // lấy lowest set bit
        int d = __builtin_ctz(pick);       // d in [0..8], tương ứng số = d+1

        // đặt số d+1 vào ô (r,c)
        rowsMask[r] |= (1 << d);
        colsMask[c] |= (1 << d);
        boxesMask[b] |= (1 << d);
        grid[r][c] = d + 1;

        // đệ quy tiếp cho ô tiếp theo
        dfs(filled + 1);

        // backtrack: bỏ đánh dấu và trả lại ô trống
        rowsMask[r] &= ~(1 << d);
        colsMask[c] &= ~(1 << d);
        boxesMask[b] &= ~(1 << d);
        grid[r][c] = 0;

        // loại bỏ bit đã thử khỏi availMask
        availMask &= (availMask - 1);
    }

    // khôi phục: đổi lại vị trí trong empties để trạng thái trước khi gọi hàm không thay đổi
    swap(empties[filled], empties[bestIdx]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // đọc bảng 9x9 (các dòng có 9 số 0..9)
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (!(cin >> grid[r][c])) return 0; // nếu input kết thúc bất thường
        }
    }

    // khởi tạo masks và danh sách empties
    for (int i = 0; i < 9; ++i) {
        rowsMask[i] = 0;
        colsMask[i] = 0;
        boxesMask[i] = 0;
    }
    empties.clear();

    // điền các số đã có vào masks; nếu có mâu thuẫn (trùng số trong hàng/cột/box) -> 0 nghiệm
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            int v = grid[r][c];
            if (v == 0) {
                empties.emplace_back(r, c);
            } else {
                if (v < 1 || v > 9) {
                    cout << 0 << '\n';
                    return 0;
                }
                int d = v - 1;
                int b = boxIndex(r, c);
                int bit = 1 << d;
                // kiểm tra trùng số
                if ((rowsMask[r] & bit) || (colsMask[c] & bit) || (boxesMask[b] & bit)) {
                    // mâu thuẫn: cùng số xuất hiện nhiều lần → không có nghiệm
                    cout << 0 << '\n';
                    return 0;
                }
                rowsMask[r] |= bit;
                colsMask[c] |= bit;
                boxesMask[b] |= bit;
            }
        }
    }

    // gọi backtracking bắt đầu với filled = 0
    dfs(0);

    // in ra số nghiệm
    cout << solutions << '\n';
    return 0;
}
