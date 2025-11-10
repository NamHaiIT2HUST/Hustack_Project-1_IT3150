#include <bits/stdc++.h>
using namespace std;

/*
  ĐỀ BÀI (tóm tắt bằng tiếng Việt)
  ---------------------------------
  Cho các quan hệ child-parent (c, p) (c là con của p). Từ các quan hệ này
  xây thành một cây/ rừng quan hệ gia đình (mỗi mối quan hệ hướng từ parent -> child).
  Thực hiện các truy vấn:
    - "descendants <name>": trả về số lượng tất cả hậu duệ (con, cháu, chắt, ...) của <name>.
    - "generation <name>": trả về số "thế hệ" của hậu duệ, tức là độ sâu lớn nhất của
                          cây con xuất phát từ <name> (nếu không có con -> 0).
  Input gồm hai khối:
    - Khối 1: các dòng "<child> <parent>" (kết thúc bởi dòng "***")
    - Khối 2: các truy vấn dạng "<cmd> <name>" (kết thúc bởi dòng "***")
  Output: với mỗi truy vấn in kết quả tương ứng trên một dòng.
  Tổng số người <= 10^4.

  Ý TƯỞNG GIẢI QUYẾT
  ------------------
  - Xây một đồ thị hướng (forest) với cạnh parent -> child. Mỗi tên map thành một id số.
  - Với mỗi nút u, ta cần 2 thông tin:
      size[u] = số hậu duệ của u (không tính u)
      depth[u] = số thế hệ lớn nhất của hậu duệ (0 nếu u không có con; nếu có con, depth = 1 + max(depth(child)))
    Ta có thể tính hai giá trị trên bằng DFS (đệ qui) từ u xuống các con, dùng memoization
    để tránh tính lại nhiều lần (vì có thể nhiều truy vấn).
  - Với truy vấn:
      + descendants name -> in size[id(name)]
      + generation name   -> in depth[id(name)]
  - Nếu tên không tồn tại trong map (không xuất hiện trong dữ liệu quan hệ) -> kết quả là 0.

  Độ phức tạp:
  - Xây đồ thị O(M) với M = số cặp child-parent.
  - Mỗi nút được tính size và depth tối đa một lần nhờ memoization -> O(N) tổng cho việc tính.
  - Mỗi truy vấn O(1) sau khi tiền xử lý.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Map tên người -> id (0..)
    unordered_map<string,int> id;
    vector<string> names; // để có thể tra ngược lại nếu cần (không bắt buộc)
    auto getId = [&](const string &s) -> int {
        auto it = id.find(s);
        if (it != id.end()) return it->second;
        int nid = (int)names.size();
        names.push_back(s);
        id[s] = nid;
        return nid;
    };

    // Đọc khối child-parent tới "***"
    vector<pair<int,int>> edges; // parent -> child
    string line;
    while (true) {
        if (!std::getline(cin, line)) return 0; // hết input bất thường
        if (line == "***") break;
        if (line.size() == 0) continue; // bỏ qua dòng rỗng nếu có

        // tách hai token (child parent)
        stringstream ss(line);
        string child, parent;
        if (!(ss >> child >> parent)) continue; // nếu dòng không đúng định dạng thì bỏ qua
        int cid = getId(child);
        int pid = getId(parent);
        edges.emplace_back(pid, cid); // lưu parent -> child
    }

    int n = (int)names.size();
    // tạo danh sách con cho mỗi node
    vector<vector<int>> children(n);
    for (auto &e : edges) {
        int p = e.first, c = e.second;
        children[p].push_back(c);
    }

    // memo cho số hậu duệ và độ sâu
    vector<int> descendants(n, -1); // -1 = chưa tính; descendants[u] = số hậu duệ của u
    vector<int> generations(n, -1); // generations[u] = độ sâu lớn nhất của hậu duệ (0 nếu không có con)

    // Hàm DFS tính descendants[u] và generations[u] cùng lúc, có memo
    function<void(int)> dfs = [&](int u) {
        if (descendants[u] != -1 && generations[u] != -1) return; // đã tính
        int totalDesc = 0;
        int maxGen = 0;
        for (int v : children[u]) {
            // nếu chưa tính cho child v thì tính trước
            if (descendants[v] == -1 || generations[v] == -1) dfs(v);
            // descendants của u tăng thêm 1 (chính v) + descendants của v (tất cả hậu duệ của v)
            totalDesc += 1 + descendants[v];
            // generations là 1 + max generations của các con
            maxGen = max(maxGen, 1 + generations[v]);
        }
        descendants[u] = totalDesc;
        generations[u] = maxGen;
    };

    // Trả lời khối truy vấn
    while (true) {
        if (!getline(cin, line)) break;
        if (line == "***") break;
        if (line.size() == 0) continue;

        stringstream ss(line);
        string cmd, name;
        ss >> cmd >> name;
        if (cmd.empty()) continue;

        // Nếu tên chưa có trong map thì kết quả luôn 0
        if (id.find(name) == id.end()) {
            cout << 0 << '\n';
            continue;
        }
        int u = id[name];
        // tính nếu cần
        if (descendants[u] == -1 || generations[u] == -1) dfs(u);

        if (cmd == "descendants") {
            cout << descendants[u] << '\n';
        } else if (cmd == "generation") {
            cout << generations[u] << '\n';
        } else {
            // lệnh không hợp lệ theo đề bài, ta bỏ qua hoặc in 0
            cout << 0 << '\n';
        }
    }

    return 0;
}
