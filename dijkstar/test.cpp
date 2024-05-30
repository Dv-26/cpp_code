#include <iostream>
#include "person.h"
#include "PriorityQueue.h"

struct MyComparator{
    bool operator()(Person& a, Person& b) const{
        return a.age > b.age;
    }
};

struct Chang{
    void operator()(Person* a,Person b){
        a->age = b.age;
    }
};

int main(){

    PriorityQueue<Person,MyComparator,Chang> queue;

    queue.push(Person("a",4));
    queue.push(Person("b",3));
    queue.push(Person("c",1));
    queue.update(Person("a",0));

    while(!queue.empty()){
        std::cout << queue.top().name << "," << queue.top().age << " ";
        queue.pop();
    }

    return 0;
}

