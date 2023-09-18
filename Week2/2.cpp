#include <iostream>
#include <sstream>

using namespace std;

struct Node{
    Node* next;
    int value;
};

void print (Node* head)
{
    Node* p = head;
    while (p != NULL){
        cout << p->value << " ";
        p = p->next;
    }
}

Node* createNode (int val)
{
    Node* p = new Node;
    p->value = val;
    p->next = NULL;
    return p;
}

Node* insert (Node* head, int x, int pos)
{
    Node* p = head;
    if (head == NULL && pos != 0) return head;
    Node* tmp = createNode(x);

    if (pos == 0){
        tmp->next = head;
        head = tmp;
        return head;
    }

    // tro p den trc node pos
    for (int i = 1; i < pos; i++)
        p = p->next;

    tmp->next = p->next;
    p->next = tmp;
    return head;
}

Node* deleteNode (Node* head, int pos){
    if (head == NULL) return head;

    if (pos == 0) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return head;
    }

    Node* p = head;
    for (int i = 1; i < pos; i++)
        p = p->next;

    Node* tmp = p->next;
    p->next = p->next->next;
    delete tmp;
    return head;
}

int main(){
    int n;
    cin >> n;

    Node* head = new Node;

    for (int i = 0; i < n; i++){
        int pos, x;
        string operation;

        cin >> operation;
        if (operation == "insert"){
            cin >> pos >> x;
            head = insert(head, x, pos);
        }

        else if (operation == "delete"){
            cin >> pos;
            head = deleteNode(head, pos);
        }
    }

    print(head);
    return 0;
}
