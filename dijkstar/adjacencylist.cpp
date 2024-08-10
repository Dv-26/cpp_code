#include <iostream>
#include <vector>
#include <climits>
#include "../priorityqueue/PriorityQueue.h"
#include <list>

struct edge{
    int dest;   //目标节点
    int weight; //权重

    edge(int d,int w = 1) : dest(d), weight(w) {}

    bool operator==(const edge& other) const{
        return dest == other.dest;
    }
};

struct MyComparator{
    bool operator()(edge& a, edge& b) const{
        return a.weight > b.weight;
    }
};

struct Chang{
    void operator()(edge* a,edge b){
        a->weight = b.weight;
    }
};

class graph{
    private:
        int v;
        std::vector<std::list<edge>> adjlist;

        int printway_recur(int src, int dest, std::vector<edge>& way){
            if(src != dest){
                int node = printway_recur(src, way[dest].dest, way);
                std::cout << node << " -> ";
            }
            return dest;
        }

        void printway(int src, int dest, std::vector<edge>& way){
            std::cout << "路线为: ";
            printway_recur(src, dest, way);
            std::cout << dest << std::endl;
        }

    public:
        graph(int v) : v(v), adjlist(v) {}

        void addedge(int src, int dest, int weight = 1){
            adjlist[src].push_back(edge(dest, weight));
            adjlist[dest].push_back(edge(src, weight));
        }

        int findedge(int src, int dest){
            for(auto p = adjlist[src].begin(); p != adjlist[src].end(); p++){
                if(p->dest == dest)
                    return p->weight;
            }
            return 0;
        }

        int dijkstar(int src, int dest){

            if(src == dest)
                return 0;

            PriorityQueue<edge, MyComparator, Chang> queue;
            std::vector<bool> hash(v,false);
            std::vector<edge> dis(v,edge(-1,INT_MAX));
            dis[src].dest = 0;
            dis[src].weight = 0;
            hash[src] = true;
            queue.push(edge(src,0));

            while(!queue.empty()){
                int n = queue.top().dest;
                if(n == dest){
                    printway(src, dest, dis);
                    return dis[dest].weight;
                }
                queue.pop();
                for(auto p=adjlist[n].begin(); p != adjlist[n].end(); p++){
                    if(dis[n].weight + p->weight < dis[p->dest].weight){
                        dis[p->dest].weight = dis[n].weight + p->weight;
                        dis[p->dest].dest = n;
                        queue.update(edge(p->dest, dis[p->dest].weight));
                    }
                    if(hash[p->dest] == false){
                        hash[p->dest] = true;
                        queue.push(*p);
                    }
                }
            }
            return -1;
        }
};

int main(){
    graph g(6);
    g.addedge(0,1,3);
    g.addedge(0,3,2);
    g.addedge(0,4,7);
    g.addedge(1,4,1);
    g.addedge(1,3,4);
    g.addedge(1,2,3);
    g.addedge(2,3,2);
    g.addedge(3,5,1);
    g.addedge(4,5,3);

    int x,y;
    std::cout << "请输入起点：";
    std::cin >> x;
    std::cout << "请输入终点：";
    std::cin >> y;
    

    int waylength = g.dijkstar(x,y);
    std::cout << "路程为："<< waylength << std::endl;

    return 0;
}

