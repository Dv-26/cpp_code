#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <vector>
#include <stdexcept>

template<typename T>
struct chang{
    void operator()(T& a,const T& b){
        *a = b;
    }
};


template<typename T, typename Comparator = std::less<T>, typename Chang = chang<T>>
class PriorityQueue{
    private:
        std::vector<T> heap;
        Comparator comp;
        Chang chang;

        //返回给定索引的父结点
        int parent(int index){
            return (index - 1)/2;
        }

        //返回给定索引的左子结点
        int leftChild(int index){
            return 2 * index + 1;
        }

        //返回给定索引的右子结点
        int rightChild(int index){
            return 2 * index + 2;
        }

        //从给定索引向上调整堆，以维护堆的性质
        void heapifyUp(int index){
            while(index > 0 && comp(heap[parent(index)], heap[index])){
                std::swap(heap[index], heap[parent(index)]);
                index = parent(index);
            }
        }

        //从给定索引向下调整堆，以维护堆的性质
        void heapifyDown(int index){
            int largest = index;
            int leftchildIdx = leftChild(largest);
            int rightchildIdx = rightChild(largest);

            if(leftchildIdx < heap.size() && comp(heap[largest], heap[leftchildIdx]))
                largest = leftchildIdx;
            if(rightchildIdx < heap.size() && comp(heap[largest], heap[rightchildIdx]))
                largest = rightchildIdx;

            if(largest != index){
                std::swap(heap[index], heap[largest]);
                heapifyDown(largest);
            }
        }


    public:

        PriorityQueue() {}

        bool update(const T& value){
            for(int i=0; i<heap.size(); i++){
                if(heap[i] == value){
                    chang(&heap[i],value);
                    if(comp(heap[i], heap[parent(i)]))
                        heapifyDown(i);
                    else
                        heapifyUp(i);
                    return true;
                }
            }
            return false;
        }

        void push(const T& value){
            heap.push_back(value);
            heapifyUp(heap.size()-1);
        }
    
        void pop(void){
            if(heap.empty())
                throw std::out_of_range("优先队列没有元素");
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);
        }


        T top(void){
            if(heap.empty())
                throw std::out_of_range("优先队列没有元素");
            return heap[0];
        }

        bool empty(){
            return heap.empty();
        }
        
        size_t size(){
            return heap.size();
        }
};

#endif
