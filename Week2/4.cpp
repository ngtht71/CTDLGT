#include <iostream>

using namespace std;

class Queue {
private:
    int size;
    int* a;

    int head;
    int rear;

public:
    Queue(int n){
        this->size = n;
        a = new int[n];
        head = 0;
        rear = -1;
    }
    ~Queue{
        delete[] a;
    }

    bool isFull(){
        return rear == size-1;
    }
    bool isEmpty(){
        return head > rear;
    }
    void print(){
        for (int i = head; i <= rear; i++)
            cout << a[i] << " ";
        cout << endl;
    }

    void enqueue (int x){
        if (isFull()) return;
        a[++rear] = x;
    }
    // remove first
    void dequeue(){
        if (isEmpty()) return;
        head++;
    }
};

int main(){
    int n; cin >> n;
    Queue q(n);

    for (int i = 0; i < n; i++){
        string operation;
        int x;
        cin >> operation;
        if (operation == "enqueue"){
            cin >> x;
            q.enqueue(x);
        }
        else if (operation == "dequeue")
            q.dequeue();
    }
    q.print();
    return 0;
}
