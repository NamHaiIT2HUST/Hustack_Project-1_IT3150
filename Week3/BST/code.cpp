#include <bits/stdc++.h>
using namespace std;

// Cấu trúc 1 node trong cây BST
struct Node {
    int val;
    Node *left, *right;
    Node(int v) {
        val = v;
        left = right = nullptr;
    }
};

// Hàm chèn một giá trị vào BST
Node* insert(Node* root, int k) {
    if (root == nullptr) return new Node(k);  // nếu cây rỗng -> tạo node mới
    if (k < root->val)                        // nhỏ hơn -> chèn sang trái
        root->left = insert(root->left, k);
    else if (k > root->val)                   // lớn hơn -> chèn sang phải
        root->right = insert(root->right, k);
    // nếu bằng thì bỏ qua
    return root;
}

// Duyệt cây theo thứ tự PreOrder (gốc → trái → phải)
void preorder(Node* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = nullptr;
    string cmd;
    int k;

    // Đọc từng dòng lệnh đến khi gặp dấu #
    while (cin >> cmd) {
        if (cmd == "#") break;
        cin >> k;
        root = insert(root, k);
    }

    // In ra kết quả duyệt PreOrder
    preorder(root);
    return 0;
}
