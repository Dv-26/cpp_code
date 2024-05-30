#include<iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void tranNode(ListNode* head){
    ListNode* p = (head->next)->next;
    (head->next)->next = p->next;
    p->next = head->next;
    head->next = p;
}

void ListInsert(ListNode *head,int x){
    ListNode *p = head;
    while(p->next != nullptr){
        p = p->next;
    }
    p->next = new ListNode(x);
}

void printlist(ListNode *head){
    while(head->next != nullptr){
        cout << head->val << "->" ;
        head = head->next;
    }
    cout << head->val << endl;
}

ListNode* fun(ListNode *head,int n){
    ListNode *dummy  = new ListNode(0);
    dummy->next = head;
    ListNode *i,*j;
    i = dummy;
    j = dummy;
    // for(int count=0;count < n;count++){
    //     i = i->next;
    // }
    // while(i->next != nullptr){
    //     i = i->next;
    //     j = j->next;
    // }
    int counter = 0;
    while(i->next != nullptr){
        i = i->next;
        if(counter < n)
            counter++;
        else
            j = j->next;
    }
    ListNode *temp = j->next;
    j->next = temp->next;
    delete temp;
    ListNode *NewHead = dummy->next;
    delete dummy;
    return NewHead;
}

int main(void){
    ListNode *head = new ListNode(0);
    ListInsert(head ,1);
    ListInsert(head ,2);
    ListInsert(head ,3);
    ListInsert(head ,4);
    printlist(head);
    // head = fun(head,5);
    tranNode(head);
    printlist(head);
    return 0;
}

