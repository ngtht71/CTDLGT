#include <iostream>
#include <queue>

using namespace std;

class Stack{
private:
    queue<int> q1, q2;

public:
    void print(){
        queue<int> tmp = q1;
        cout << "Top to first: ";
        while (!tmp.empty()){
            cout << tmp.front() << " ";
            tmp.pop();
        }
        cout << endl;
    }

    bool isEmpty(){
        return q1.empty();
    }
    //<------------
    // q1 1 2 3
    // q2 4
    //q2 4 1 2 3
    void push(int x){
        q2.push(x);
        while (!q1.empty()){
            int first = q1.front();
            q2.push(first);
            q1.pop();
        }
        swap (q1, q2);
    }

    //khi su dung push thi phan tu cuoi dc them vao se dung dau
    //chi can pop front queue1 tuong duong voi pop phan tu vua them vao
    int pop(){
        if (q1.empty()) swap (q1, q2);

        int first = q1.front();
        q1.pop();
        return first;
    }
    int top(){
        if (isEmpty()){
            cout << "Stack is empty." << endl;
            exit(0);
        }
        return q1.front();
    }
};

int main(){
    Stack myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    myStack.print();    // 3 2 1

    cout << myStack.pop() << endl;  // 3

    myStack.pop();     // 2
    myStack.push(5);
    myStack.print();    // 5 1
    return 0;
}
