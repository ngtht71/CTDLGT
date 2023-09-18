#include <iostream>

using namespace std;

struct Node{
    Node* next;
    Node* prev;
    int value;
};

void print (Node* head)
{
    Node* p = head;
    while (p != NULL)
    {
        cout << p->value << ' ';
        p = p->next;
    }
    cout << endl;
}

Node* add (Node* head, int val){
    Node* p = head;

    Node* tmp = new Node;
    tmp->value = val;

    if (head == NULL){
        tmp->next = NULL;
        tmp->prev = NULL;
        head = tmp;
        return head;
    }
    while (p->next != NULL)
        p = p->next;

    p->next = tmp;
    tmp->prev = p;
    tmp->next = NULL;

    return head;
}

int count_triplets(Node* head, int n){
    Node* p = head;
    int trip_sum = 0, count = 0;

    p = p->next;
    //p chay tu 1 -> n-1
    for (int i = 2; i < n; i++){
        int a, b, c;
        a = p->prev->value;
        b = p->value;
        c = p->next->value;
        if (a+b+c == 0) count++;
        p = p->next;
    }
    return count;
}

int main (){
    int n; cin >> n;
    Node* head = NULL;
    for (int i = 0; i < n; i++)
    {
        int val; cin >> val;
        head = add(head, val);
    }
    //print(head);
    cout << count_triplets(head, n);

    return 0;
}
