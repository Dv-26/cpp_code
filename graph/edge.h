#ifndef EDGE_H
#define EDGE_H

#include <stdexcept>

template<typename T>
class edge{

    private:
        int v_;
        int w_;
        T wight_;

    public:
        edge(int w, int v, T wight) : w_(w), v_(v), wight_(wight) {}
        T weight() { return wight_; }
        int either() { return v_; }
        const int other(int v) const{
            if(v == v_) return w_;
            else if( v == w_ ) return v_;
            else throw std::invalid_argument("Parameter must be non-negative"); //参数无效
        }
};

#endif
