#include <bits/stdc++.h>
using namespace std;

/*
  Bài toán (tóm tắt):
  - Mỗi nút trên cây có một id (số nguyên) và các id là duy nhất.
  - Thực hiện một chuỗi hành động:
      MakeRoot u   : tạo (hoặc đặt) nút gốc có id = u
      Insert u v   : tạo mới nút u và chèn vào cuối danh sách con của nút v
                     (nếu nút v không tồn tại hoặc nút u đã tồn tại thì bỏ qua)
      PreOrder     : in dãy id theo duyệt tiền (root, children từ trái qua phải)
      InOrder      : định nghĩa duyệt giữa cho cây đa-nhiều-con:
                     - nếu nút không có con -> in chính nó
                     - nếu có ít nhất 1 con -> duyệt InOrder(child_1), in node,
                       sau đó duyệt InOrder(child_2), InOrder(child_3), ...
                     (tức là: child đầu -> node -> các child còn lại theo thứ tự)
      PostOrder    : duyệt hậu tự: duyệt tất cả con theo thứ tự, rồi in node.
  - Dữ liệu: mỗi dòng một lệnh, kết thúc bằng dòng "*" (một dấu sao).
  - Kết quả: với mỗi lệnh PreOrder/InOrder/PostOrder in ra 1 dòng kết quả
             chứa id các nút theo thứ tự duyệt, cách nhau bằng dấu cách.
  
  Ghi chú:
  - Nếu MakeRoot được gọi với id đã tồn tại: ta đặt node đó làm root (không tạo node mới).
  - Insert: chỉ tạo node u khi u chưa tồn tại và parent v tồn tại.
  - Danh sách con giữ thứ tự chèn; Insert chèn vào cuối danh sách con.
  - Nếu chưa có root mà có lệnh duyệt thì in dòng rỗng (tùy chọn).
*/

/* Cấu trúc Node dùng cho cây đa-nhiều-con */
struct Node {
    int id;                    // identifier của node
    vector<Node*> children;    // danh sách con theo thứ tự
    Node(int _id) : id(_id) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Bảng ánh xạ id -> con trỏ Node. Dùng unordered_map để truy xuất nhanh (O(1) trung bình).
    unordered_map<int, Node*> nodes;

    // Con trỏ root của cây (có thể null nếu chưa gọi MakeRoot)
    Node* root = nullptr;

    string line;
    // Đọc từng dòng lệnh cho đến khi gặp "*"
    while (true) {
        if (!std::getline(cin, line)) break; // nếu hết input thì thoát
        if (line.size() == 0) continue;      // bỏ qua dòng rỗng
        if (line == "*") break;              // kết thúc dữ liệu

        // Tách các token trong dòng
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        if (cmd.empty()) continue;

        if (cmd == "MakeRoot") {
            // Lấy id u
            int u; ss >> u;
            // Nếu node đã tồn tại thì đặt lại root
            if (nodes.find(u) != nodes.end()) {
                root = nodes[u];
            } else {
                // Tạo node mới, thêm vào map, đặt làm root
                Node* p = new Node(u);
                nodes[u] = p;
                root = p;
            }
        }
        else if (cmd == "Insert") {
            // Insert u v : tạo node u (nếu chưa có) và chèn vào cuối danh sách con của v
            int u, v; ss >> u >> v;
            // Điều kiện: nếu v tồn tại và u chưa tồn tại thì mới chèn
            if (nodes.find(v) == nodes.end()) {
                // parent v không tồn tại -> không làm gì
                continue;
            }
            if (nodes.find(u) != nodes.end()) {
                // node u đã tồn tại -> không làm gì
                continue;
            }
            // tạo node u và chèn vào cuối children của v
            Node* nu = new Node(u);
            nodes[u] = nu;
            nodes[v]->children.push_back(nu);
        }
        else if (cmd == "PreOrder") {
            // Duyệt tiền: node -> children (theo thứ tự)
            vector<int> out;
            // sử dụng stack/đệ quy. Dùng đệ quy dễ viết; kích thước cây không quá lớn thường.
            function<void(Node*)> preorder = [&](Node* p) {
                if (!p) return;
                out.push_back(p->id);
                for (Node* ch : p->children) preorder(ch);
            };
            preorder(root);
            // In kết quả (nếu root == nullptr thì out rỗng -> in dòng trống)
            for (size_t i = 0; i < out.size(); ++i) {
                if (i) cout << ' ';
                cout << out[i];
            }
            cout << '\n';
        }
        else if (cmd == "InOrder") {
            // Duyệt giữa cho cây đa-nhiều-con được định nghĩa như sau:
            // nếu node không có con -> in node
            // nếu node có >=1 con -> InOrder(child_1), in node, InOrder(child_2), InOrder(child_3), ...
            vector<int> out;
            function<void(Node*)> inorder = [&](Node* p) {
                if (!p) return;
                if (p->children.empty()) {
                    out.push_back(p->id);
                    return;
                }
                // có ít nhất một con
                inorder(p->children[0]);
                out.push_back(p->id);
                for (size_t i = 1; i < p->children.size(); ++i) inorder(p->children[i]);
            };
            inorder(root);
            for (size_t i = 0; i < out.size(); ++i) {
                if (i) cout << ' ';
                cout << out[i];
            }
            cout << '\n';
        }
        else if (cmd == "PostOrder") {
            // Duyệt hậu: children -> node
            vector<int> out;
            function<void(Node*)> postorder = [&](Node* p) {
                if (!p) return;
                for (Node* ch : p->children) postorder(ch);
                out.push_back(p->id);
            };
            postorder(root);
            for (size_t i = 0; i < out.size(); ++i) {
                if (i) cout << ' ';
                cout << out[i];
            }
            cout << '\n';
        }
        else {
            // Lệnh không nhận diện: bỏ qua (theo đề chỉ có các lệnh trên và dấu *)
            continue;
        }
    }

    // Giải phóng bộ nhớ (tùy chọn): xóa tất cả node được cấp phát
    for (auto &kv : nodes) delete kv.second;

    return 0;
}
