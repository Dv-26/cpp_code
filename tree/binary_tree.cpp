#include <memory>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class TreeNode {
    public:
        TreeNode() : children_(2, nullptr) {}
        TreeNode(const T &x) : data_(x), children_(2, nullptr) {}

        int Show(vector<vector<string>> &pic, int dep) const;
        void Insert(const shared_ptr<TreeNode<T>> &data_ptr);
        bool Erase(const T &x, shared_ptr<TreeNode<T>> &pre_ptr);
        //删除指定值的节点

    private:
        inline shared_ptr<TreeNode<T>> &left() { return children_.at(0); }
        inline shared_ptr<TreeNode<T>> &right() { return children_.at(1); }

        inline const shared_ptr<TreeNode<T>> &left() const { return children_.at(0); }
        inline const shared_ptr<TreeNode<T>> &right() const { return children_.at(1); }

        T data_;
        vector<shared_ptr<TreeNode<T>>> children_;
};

template <typename T>
void TreeNode<T>::Insert(const shared_ptr<TreeNode<T>> &data_ptr){
    auto &next_ptr = (data_ptr->data_ < data_)? left():right();

    if(next_ptr == nullptr){
        next_ptr = data_ptr;
    }
    else
        next_ptr->Insert(data_ptr);
}

template <typename T>
bool TreeNode<T>::Erase(const T  &x, shared_ptr<TreeNode<T>> &pre_ptr){
    if(x != data_){
        auto &next_ptr = (x < data_)? left():right();
        if(next_ptr == nullptr) return false;
        return next_ptr->Erase(x, next_ptr);
    }

    if(left() == nullptr && right() == nullptr){
        pre_ptr = nullptr;
        return true;
    }
    if(left() == nullptr || right() == nullptr){
        pre_ptr = children_.at(left() == nullptr);
        return true;
    }

    if(right()->left() == nullptr){
        right()->left() = left();
        return true;
    }
    if(left()->right() == nullptr){
        left()->right() = right();
        return true;
    }

    auto &min_node_ptr = right();
    while(min_node_ptr->left()->left() != nullptr) min_node_ptr = min_node_ptr->left(); 
    min_node_ptr->left()->left() = left();
    pre_ptr = right();

}

template <typename T>
int TreeNode<T>::Show(vector<vector<string>> &pic, int dep) const{
    int this_string_length = to_string(data_).size(); 
    int stare = pic.size(), sl, sr, ret;

    if(left() != nullptr) {
        sl = left()->Show(pic, dep-1);
    } else {
        pic.push_back( vector<string>{' ', "null"} );
    }
}

template <typename T>
class Tree{
    public:
        void Show() const;
        void Insert(const T &x);
        bool Erase(const T &x);

    private:
        shared_ptr<TreeNode<T>> root_;
};



