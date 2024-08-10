#include "edge.h"
#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

template<typename T>
class EdgeWeightedGraph{
    public:

        int V(){ return V_; }
        int E(){ return E_; }

        void addedge(edge<T> e);
        vector<int> adj(int v);
        vector<edge<T>> edges();
        
    private:
        int V_;//点的数量
        int E_;//边的数量
        unordered_map<int, list<edge<T>>> adj_;
};

template<typename T>
void EdgeWeightedGraph<T>::addedge(edge<T> e){
    int v = e.either();
    int w = e.other(v);
    if(v == w){
        throw std::invalid_argument("Parameter must be non-negative"); //参数无效
    }
    else{
        adj_[v].push_back(e);
        adj_[w].push_back(e);
    }
}

template<typename T>
vector<edge<T>> EdgeWeightedGraph<T>::edges(){
    vector<edge<T>> edges;
    for(const auto& pair : adj_){
        for(const auto& edge : pair.second){
            if(edge.other(pair.first) > pair.first)
                edges.push_back(edge);
        }
    }
    return edges;
}

template<typename T>
vector<int> EdgeWeightedGraph<T>::adj(int v){
    vector<int> nodes;
    for(auto &p = adj_[v].begin(); p != adj_[v].end(); p++){
        nodes.push_back(p.other(v));
    }
    return nodes;
}

int main(){

    EdgeWeightedGraph<double> graph;

    graph.addedge(edge<double>(1,2,8));
    graph.addedge(edge<double>(1,3,8));
    graph.addedge(edge<double>(1,4,2));
    graph.addedge(edge<double>(1,5,8));

    vector<edge<double>> edges = graph.edges();
    for(auto p = edges.begin(); p != edges.end(); p++){
        cout << p->either() << "-" << p->other(p->either()) << endl; 
    }

    return 0;
}

