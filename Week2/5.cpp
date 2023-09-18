#include <iostream>

using namespace std;

class Stack{
private:
    int* a;
    int size;
    int top;

public:
    Stack(int n){
        this->size = n;
        a = new int [n];
        top = -1;
    }
    ~Stack(){
        delete[] a;
    }
    bool isFull(){
        return top == size-1;
    }
    bool isEmpty(){
        return top == -1;
    }

    void push(int x){
        if (isFull()) return;
        a[++top] = x;
    }
    void pop(){
        if (isEmpty()) return;
        top--;
    }
    void print(){
        for (int i = 0; i <= top; i++)
            cout << a[i] << ' ';
        cout << endl;
    }
};

int main(){
    int n; cin >> n;
    Stack new_stack(n);
    for (int i = 0; i < n; i++){
        string operation;
        cin >> operation;
        if (operation == "push"){
            int x;
            cin >> x;
            new_stack.push(x);
        }
        else if (operation == "pop")
            new_stack.pop();
    }
    new_stack.print();
    return 0;
}
