#include <iostream>
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

template<typename T>
class Tree {
    public:
        void Show() const{
            vector<vector<string>> ret;
            root_->Show(ret, 0);
            for(auto p = ret.rbegin(); p != ret.rend(); p++){
                for(auto &q : *p) std::cout << q;
                puts("");
            }
        }

        void Insert(const T &x){
            if(root_ != nullptr) root_->Insert(make_shared<TreeNode<T>>(x)); 
            else root_ = make_shared<TreeNode<T>>(x);
        }

        bool Erase(const T &x){
            return root_->Erase(x, root_);
        }

    private:
        shared_ptr<TreeNode<T>> root_;
};
 

template <typename T>
int TreeNode<T>::Show(vector<vector<string>> &pic, int dep) const{
    int start = pic.size(),sl,sr,ret;
    int this_string_lenght = to_string(data_).size();
    string line;
    for(int i=0; i<this_string_lenght; i++) line += "─";

    if(left() == nullptr){
        pic.push_back(vector<string>{"", "null"});
        sl = pic.size() - 1; 
    } else {
        sl = left()->Show(pic, dep+1);
    }
    pic.push_back(vector<string>{"", to_string(data_)});
    ret = pic.size() - 1;
    if(right() == nullptr){
        pic.push_back(vector<string>{"", "null"});
        sr = pic.size() - 1;
    } else {
        sr = right()->Show(pic, dep+1);
    }

    for(int i = start; i < sl; i++) pic[i][0] = string(this_string_lenght + 1, ' ') + pic[i][0];
    pic[sl][0] = "└" + line + pic[sl][0];
    for(int i = sl + 1; i < sr; i++)   pic[i][0] = "│" + string(this_string_lenght, ' ') + pic[i][0];
    pic[ret][0] = "";
    pic[sr][0] = "┌" + line + pic[sr][0];
    for(int i = sr + 1; i < pic.size(); i++) pic[i][0] = string(this_string_lenght + 1, ' ') + pic[i][0];

    return ret;
}

template <typename T>
void TreeNode<T>::Insert(const shared_ptr<TreeNode<T>> &data_ptr){
    auto &next_ptr = (data_ < data_ptr->data_)? left() : right();
    if(next_ptr == nullptr)
        next_ptr = data_ptr;
    else
        next_ptr->Insert(data_ptr);
}

template <typename T>
bool TreeNode<T>::Erase(const T &x, shared_ptr<TreeNode<T>> &pre_ptr){
    if(data_ != x){
        auto &next_ptr = (x < data_)? right() : left();
        if(next_ptr == nullptr) return false;
        return next_ptr->Erase(x, next_ptr);
    }        

    if(right() == nullptr && left() == nullptr){
        pre_ptr = nullptr;
        return true;
    }

    if(right() == nullptr || left() == nullptr){
        pre_ptr = children_.at(left() == nullptr);
        return true;
    }

    if(right()->left() == nullptr){
        right()->left() = left();
        pre_ptr = right();
        return true;
    }

    if(left()->right() == nullptr){
        left()->right() = right();
        pre_ptr = left();
        return true;
    }

    auto &min_node_ptr = right();
    while(min_node_ptr->left()->left() != nullptr) min_node_ptr = min_node_ptr->left(); 
    min_node_ptr->left() = left();
    pre_ptr = right();
    return true;
}

int main(){
    Tree<int> root;
    string str;
    root.Insert(10);
    root.Insert(2);
    root.Insert(20);
    root.Insert(15);
    root.Show();
    root.Erase(15);
    root.Show();
}
