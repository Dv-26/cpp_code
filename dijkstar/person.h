#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>

class Person{
    public:    
        std::string name;
        int age;

        Person(std::string name,int age){
            this->name = name;
            this->age = age;
        }

        bool operator==(const Person& other) const {
            return name == other.name;
        }
};


#endif
