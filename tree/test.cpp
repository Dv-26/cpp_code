#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

using T = int;

class TreeNode {
   public:
    TreeNode() : children_(2, nullptr) {}
    TreeNode(const T &x) : data_(x), children_(2, nullptr) {}

    int Show(vector<vector<string>> &pic, int dep) const;
    void Insert(const shared_ptr<TreeNode> &data_ptr);
    bool Erase(const T &x, shared_ptr<TreeNode> &pre_ptr);

   private:
    inline shared_ptr<TreeNode> &left() { return children_.at(0); }
    inline shared_ptr<TreeNode> &right() { return children_.at(1); }
    inline const shared_ptr<TreeNode> &left() const { return children_.at(0); }
    inline const shared_ptr<TreeNode> &right() const { return children_.at(1); }

   public:
    T data_;
    vector<shared_ptr<TreeNode>> children_;
};

class Tree {
   public:
    void Show() const {
        vector<vector<string>> ret;
        root_->Show(ret, 0);
        for (auto p = ret.rbegin(); p != ret.rend(); ++p) {
            for (auto &q : *p) cout << q;
            puts("");
        }
    }
    void Insert(const T &x) {
        if (nullptr == root_)
            root_ = make_shared<TreeNode>(x);
        else
            root_->Insert(make_shared<TreeNode>(x));
    }
    bool Erase(const T &x) { return root_->Erase(x, root_); }

   private:
    shared_ptr<TreeNode> root_;
};

int main() {
    Tree root;
    root.Insert(52);
    root.Insert(2);
    root.Insert(102);
    root.Insert(1);
    root.Insert(100);
    root.Insert(98);
    root.Insert(90);
    root.Insert(101);
    root.Insert(1024);
    root.Show();
}

void TreeNode::Insert(const shared_ptr<TreeNode> &data_ptr) {
    auto &next_ptr = data_ptr->data_ < data_ ? left() : right();
    if (nullptr == next_ptr)
        next_ptr = data_ptr;
    else
        next_ptr->Insert(data_ptr);
}

int TreeNode::Show(vector<vector<string>> &pic, int dep) const {
    int start = pic.size(), sl, sr, ret;
    int this_string_length = to_string(data_).size();
    string line;
    for (int i = 0; i < this_string_length; ++i) line += "─";
    // gain
    if (nullptr != left()) {
        sl = left()->Show(pic, dep + 1);
    } else {
        pic.push_back(vector<string>{"", "null"});
        sl = pic.size() - 1;
    }
    pic.push_back(vector<string>{"", to_string(data_)});
    ret = pic.size() - 1;
    if (nullptr != right()) {
        sr = right()->Show(pic, dep + 1);
    } else {
        pic.push_back(vector<string>{"", "null"});
        sr = pic.size() - 1;
    }
    // al
    for (int i = start; i <= sl - 1; ++i) pic[i][0] = string(this_string_length + 1, ' ') + pic[i][0];
    pic[sl][0] = "└" + line + pic[sl][0];
    for (int i = sl + 1; i <= sr - 1; ++i) pic[i][0] = "│" + string(this_string_length, ' ') + pic[i][0];
    pic[ret][0] = "";
    pic[sr][0] = "┌" + line + pic[sr][0];
    for (int i = sr + 1; i < pic.size(); ++i) pic[i][0] = string(this_string_length + 1, ' ') + pic[i][0];

    return ret;
}

bool TreeNode::Erase(const T &x, shared_ptr<TreeNode> &pre_ptr) {
    if (x != data_) {
        auto &next_ptr = x < data_ ? left() : right();
        if (nullptr == next_ptr) return false;
        return next_ptr->Erase(x, next_ptr);
    }
    // x == data_
    if (nullptr == left() && nullptr == right()) {
        pre_ptr = nullptr;
        return true;
    }
    if (nullptr == left() || nullptr == right()) {
        pre_ptr = children_.at(nullptr != right());
        return true;
    }
    // both not null
    if (nullptr == right()->left()) {
        right()->left() = this->left();
        pre_ptr = right();
        return true;
    }
    if (nullptr == left()->right()) {
        left()->right() = this->right();
        pre_ptr = left();
        return true;
    }
    // find the min node in right
    auto &min_node_pre = right();
    while (nullptr != min_node_pre->left()->left()) min_node_pre = min_node_pre->left();
    min_node_pre->left()->left() = this->left();
    pre_ptr = this->right();
    return true;
}



