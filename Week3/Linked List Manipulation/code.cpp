#include <bits/stdc++.h>
using namespace std;

/*
  Ý tưởng tổng quát:
  - Dùng danh sách liên kết đơn (Node { val, next }).
  - Khởi tạo danh sách từ dãy a1..an bằng cách thêm lần lượt vào cuối.
  - Với mỗi lệnh:
      + addfirst k   : thêm node mới có khóa k vào đầu nếu k chưa tồn tại
      + addlast k    : thêm node mới có khóa k vào cuối nếu k chưa tồn tại
      + addafter u v : nếu v tồn tại và u chưa tồn tại -> chèn u ngay sau v
      + addbefore u v: nếu v tồn tại và u chưa tồn tại -> chèn u ngay trước v
      + remove k     : nếu k tồn tại -> xóa node có khóa k
      + reverse      : đảo ngược danh sách (không cấp phát node mới)
  - Sau khi xử lý xong tất cả lệnh (đến khi gặp "#"), in tuần tự các giá trị trong danh sách.
  
  Lưu ý:
  - Hàm exists(head, k) chạy O(n) để kiểm tra tồn tại; mỗi thao tác có thể O(n).
  - Độ phức tạp tổng phụ thuộc vào số lệnh và kích thước danh sách; với n ≤ 1000 bài này rất ổn.
*/

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

// Kiểm tra xem giá trị k đã có trong danh sách chưa (duyệt từ head).
// Trả về true nếu tồn tại, false nếu không.
bool exists(Node* head, int k) {
    while (head) {
        if (head->val == k) return true;
        head = head->next;
    }
    return false;
}

// Thêm node có giá trị k vào đầu danh sách.
// Trả về head mới (đã thay đổi).
Node* addFirst(Node* head, int k) {
    Node* p = new Node(k);
    p->next = head;
    return p;
}

// Thêm node có giá trị k vào cuối danh sách.
// Nếu head == nullptr (danh sách rỗng) thì trả về node mới làm head.
Node* addLast(Node* head, int k) {
    if (!head) return new Node(k);
    Node* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = new Node(k);
    return head;
}

// Thêm node có giá trị u vào ngay sau node đầu tiên có giá trị v.
// Giả thiết: caller đã đảm bảo v tồn tại và u chưa tồn tại.
// Nếu không tìm thấy v thì không làm gì và trả về head.
Node* addAfter(Node* head, int u, int v) {
    Node* cur = head;
    while (cur && cur->val != v) cur = cur->next;
    if (cur) {
        Node* p = new Node(u);
        p->next = cur->next;
        cur->next = p;
    }
    return head;
}

// Thêm node có giá trị u vào ngay trước node đầu tiên có giá trị v.
// Xử lý đặc biệt khi v nằm ở head (phải đổi head).
// Nếu không tìm thấy v thì không làm gì.
Node* addBefore(Node* head, int u, int v) {
    if (!head) return head;
    if (head->val == v) return addFirst(head, u); // nếu v là head, thêm vào trước -> thành head mới
    Node* cur = head;
    // tìm node cur sao cho cur->next có giá trị v
    while (cur->next && cur->next->val != v) cur = cur->next;
    if (cur->next) {
        Node* p = new Node(u);
        p->next = cur->next;
        cur->next = p;
    }
    return head;
}

// Xóa node có giá trị k (nếu tồn tại) và trả về head mới.
// Nếu xóa head, trả về head tiếp theo.
// Nếu không tìm thấy k thì trả về head không đổi.
// Giải phóng bộ nhớ của node bị xóa bằng delete.
Node* removeNode(Node* head, int k) {
    if (!head) return head;
    if (head->val == k) {
        Node* tmp = head->next;
        delete head;
        return tmp;
    }
    Node* cur = head;
    while (cur->next && cur->next->val != k) cur = cur->next;
    if (cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
    }
    return head;
}

// Đảo ngược danh sách liên kết đơn bằng cách thay đổi các con trỏ next,
// không cấp phát hay giải phóng node mới.
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev; // prev là head mới sau khi đảo
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0; // nếu không có input, thoát

    Node* head = nullptr;

    // Khởi tạo danh sách từ dãy a1..an bằng cách addLast lần lượt.
    // (Có thể giả sử dãy ban đầu có các khóa không trùng nhau theo đề bài,
    //  nếu đề có khác biệt thì cần kiểm tra exists trước khi add).
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        head = addLast(head, x);
    }

    // Đọc và xử lý lần lượt các lệnh đến khi gặp "#"
    // Mỗi lệnh: một chuỗi (tên lệnh) rồi các tham số (nếu có)
    string cmd;
    while (cin >> cmd && cmd != "#") {
        if (cmd == "addfirst") {
            int k; cin >> k;
            if (!exists(head, k)) head = addFirst(head, k);
        } else if (cmd == "addlast") {
            int k; cin >> k;
            if (!exists(head, k)) head = addLast(head, k);
        } else if (cmd == "addafter") {
            int u, v; cin >> u >> v;
            // chèn u sau v nếu v tồn tại và u chưa tồn tại
            if (!exists(head, u) && exists(head, v)) head = addAfter(head, u, v);
        } else if (cmd == "addbefore") {
            int u, v; cin >> u >> v;
            // chèn u trước v nếu v tồn tại và u chưa tồn tại
            if (!exists(head, u) && exists(head, v)) head = addBefore(head, u, v);
        } else if (cmd == "remove") {
            int k; cin >> k;
            if (exists(head, k)) head = removeNode(head, k);
        } else if (cmd == "reverse") {
            head = reverseList(head);
        } else {
            // nếu là lệnh không rõ, có thể bỏ qua phần còn lại của dòng (an toàn)
            // nhưng theo đề thì chỉ có lệnh ở trên và '#' kết thúc.
        }
    }

    // In danh sách kết quả
    for (Node* cur = head; cur; cur = cur->next)
        cout << cur->val << (cur->next ? " " : "");

    // (Tuỳ nhu cầu, có thể giải phóng toàn bộ node còn lại trước khi thoát.
    //  Ở các bài tập lập trình nhỏ thường không cần.)
    return 0;
}
