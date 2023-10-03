#include <iostream>

using namespace std;

class Node {
    int data;
    Node* fatherNode;
    Node* firstChild;
    Node* next;
public:
    Node() {
        data = 0;
        fatherNode = NULL;
        firstChild = NULL;
        next = NULL;
    }

    Node(int data){
        this->data = data;
        this->fatherNode = NULL;
        this->firstChild = NULL;
        this->next = NULL;
    }
    friend class Tree;
};

class Tree{
    Node* root;
public:
    Tree() {
        root = NULL;
    }

    Node* getRoot(){ return root; }

    Node* findNode (int data){      // ok
        if (root == NULL) return NULL;

        Node* p = root;
        while (p != NULL) {
            if (p->data == data) return p;
            //duyet cac con trai cua c
            while (p->firstChild != NULL){
                p = p->firstChild;
                if (p->data == data) return p;
            }
            if (p->next != NULL) {
                p = p->next;
                if (p->data == data) return p;
            }
            //leaf node
            if (p->firstChild == NULL && p->fatherNode != NULL)
            {
                while (p->next == NULL) p = p->fatherNode;
                p = p->next;
            }
        }
        return NULL;
    }

     bool insert(int father, int data) {    //ok
        if (root == NULL) root = new Node(father);

        Node* dad = findNode(father);
        if (dad == NULL) return false;

        Node* p = new Node(data);
        p->fatherNode = dad;

        Node* fchild = dad->firstChild;
        if (fchild == NULL) dad->firstChild = p;
        else{
            //node cha co con = data
            if (fchild->data == data) return false;
            while (fchild->next != NULL){
                if (fchild->data == data) return false;
                fchild = fchild->next;
            }
            //check node con cuoi
            if (fchild->data == data) return false;
            fchild->next = p;  //chen node moi vao cuoi dsach node con
        }
        return true;
    }

    void deleteAllChildren (Node* root, int &count)
    {
        if (root == NULL) return;
        else count++;

        // Duyệt qua các node con của node hiện tại
        Node* p = root->firstChild;
        while (p != NULL) {
            // Lưu lại node anh chị em bên phải của node hiện tại
            Node* pnext = p->next;
            deleteAllChildren (p, count);
            delete p;

            // Chuyển sang node anh chị em bên phải đã lưu
            p = pnext;
        }
    }

    int remove (int data)      //ok
    {
        if (root == NULL) return 0;

        Node* target = findNode (data);
        if (target == NULL) return 0;

        //node can xoa la con 1
        if (target->fatherNode != NULL && target->fatherNode->firstChild == target)
            target->fatherNode->firstChild = target->next;
        else {      //node xoa la con giua
            Node* tmp = target->fatherNode->firstChild;
            while (tmp->next != target) tmp = tmp->next;
            tmp->next = target->next;
        }
        int count = 0;
        deleteAllChildren (target, count);

        // Nếu node đích là node gốc, gán NULL cho nó
        if (target == root) {
            root = NULL;
            return count;
        }

        delete target;
        return count;
    }

    void preorder(Node* root){         // goc - con trai - con phai
        if (root == NULL) return;
        cout << root->data << " ";
        preorder(root->firstChild);
        preorder(root->next);
    }

    void postorder(Node* root) {       // con trai - con phai - goc
        if (root == NULL) return;
        //postorder(root->firstChild);    //duyet cho con trai

        Node* p = root->firstChild;
        // duyet con phai
        while (p != NULL){
            postorder(p);
            p = p->next;
        }
        //if (root->firstChild != NULL) postorder(root->firstChild->next);
        cout << root->data << " ";      //goc
    }

    int numChild (Node* dad) {      //ok
        Node* p = dad->firstChild;
        int count = 0;
        while (p != NULL) {
            p = p->next;
            count++;
        }
        return count;
    }

    // kiem tra cay nhi phan
    bool isBinaryTree(Node* root) {
        if (root == NULL) return false;
        if (numChild(root) > 2) return false;

        // de quy kiem tra cac con cua node hien tai
        Node* p = root->firstChild;
        while (p != NULL) {
            // Nếu một trong các node con không phải là cây nhị phân, trả về false
            if (!isBinaryTree(p)) return false;

            // Chuyển sang node anh chị em bên phải
            p = p->next;
        }
        return true;
    }

    bool isBinaryNode(Node* p) {
        if (numChild(p) > 2) return false;
        if (numChild(p) == 2)
            if (p->data > p->firstChild->data && p->data < p->firstChild->next->data)
                return true;
        return true;
    }

    //kiem tra cay tim kiem nhi phan
    bool isBinarySearchTree(Node* root) {
        if (root == NULL) return false;
        if (!isBinaryTree(root)) return false;
        if (!isBinaryNode(root)) return false;

        Node* p = root->firstChild;
        while (p != NULL)
        {
            if (!isBinaryNode(p)) return false;
            if(!isBinarySearchTree(p)) return false;

            p = p->next;
        }
        return true;
    }

    void inorder(Node* root) {          // con trai - goc - con phai
        if (!isBinaryTree(root)) return;
        inorder(root->firstChild);
        cout << root->data << " ";
        if (root->firstChild != NULL) inorder(root->firstChild->next);
    }

    bool isHeapNode(Node* p) {
        if (p->firstChild == NULL) return true;
        Node* tmp = p->firstChild;  //check node con
        while (tmp != NULL) {
            if (tmp->data > p->data) return false;
            tmp = tmp->next;
        }
        return true;
    }

    // Hàm kiểm tra cây max-heap
    bool isMaxHeapTree() {
        Node* tmp = root;
        while (tmp != NULL) {
            while (tmp->firstChild != NULL) {
                tmp = tmp->firstChild;
                if (!(isHeapNode(tmp))) return false;
            }
            if (tmp->next != NULL) {
                tmp = tmp->next;
                if (!(isHeapNode(tmp))) return false;
            }
            if (tmp->firstChild == NULL) {
                while (tmp->next == NULL && tmp != root)
                    tmp = tmp->fatherNode;
                tmp = tmp->next;
            }
        }
        return true;
    }

    // Hàm trả về độ cao của cây
    int height() {
        if (root == NULL) return -1;
        Node* p = root;
        int high = 0, deep = 0;
        while (p != NULL) {
            while (p->firstChild != NULL) p = p->firstChild;
            deep = depth(p->data);
            if (deep > high) high = deep;
            if (p->next != NULL) p = p->next;

            if (p->firstChild == NULL) {
                while (p->next == NULL && p != root)
                    p = p->fatherNode;
                p = p->next;
            }
        }
        return high;
    }

    // Hàm trả về độ sâu của một Node
    int depth(int data) {
        Node* p = findNode (data);
        if (p == NULL) return -1;
        int deep = 0;
        while (p->fatherNode != NULL) {
            p = p->fatherNode;
            deep++;
        }
        return deep;
    }

    int nodeLeaves (Node* root)
    {
        if (root == NULL) return 0;
        if (root->firstChild == NULL) return 1;

        int leaf = 0;
        Node* p = root->firstChild;

        while (p != NULL) {
            leaf += nodeLeaves(p);
            p = p->next;
        }
        return leaf;
    }

    // Hàm đếm số lượng lá
    int numOfLeaves() {
       return nodeLeaves(root);
    }

    void miniFindMax (Node* temp, int& max){
        if (temp) {
            if (temp->data > max) max = temp->data;

            miniFindMax(temp->firstChild, max);
            miniFindMax(temp->next, max);
        }
    }
    // Hàm trả về Node có giá trị lớn nhất
    int findMax(){
        int maxx = root->data;
        miniFindMax(root, maxx);

        return maxx;
    }

    int maxChild(Node* root)
    {
        if (root == NULL) return 0;

        int maxCount = 0;
        int currentCount = numChild(root);

        Node* p = root->firstChild;
        while (p != NULL) {
            int temp = maxChild(p);
            if (temp > maxCount) maxCount = temp;
            p = p->next;
        }
        return max(maxCount, currentCount);
    }

    // Hàm trả về Node có nhiều con nhất
    int findMaxChild() {
        return maxChild(root);
    }

};

int main()
{
    Tree* tree = new Tree();
    int cha[] = {1, 1, 2, 2, 5, 7, 8, 8, 3, 6, 3};  //11
    int con[] = {2, 3, 4, 5, 7, 8, 9, 10, 6, 11, 12};   //11
    for (int i = 0; i < 11; i++) tree->insert(cha[i], con[i]);
    for (int i = 13; i < 20; i++) tree->insert(12, i);
    for (int i = 20; i <= 30; i++) tree->insert(i-3, i);

    tree->preorder(tree->getRoot());
    cout << endl;
    tree->postorder(tree->getRoot());
    cout << endl;
    cout << endl << "Is binary tree: " << tree->isBinaryTree(tree->getRoot()) << endl;

    cout << endl << tree->remove(8) << endl;
    tree->preorder(tree->getRoot());

    Node* p = tree->findNode(12);
    cout << "Number Children of Node: " << tree->numChild(p) << endl;

    cout << "Binary Search Tree functions" << endl;     // ok
    Tree* BST = new Tree();
    int pa[] = {10, 10, 5, 5, 20, 3, 8, 20, 25, 8, 25};
    int va[] = {5, 20, 3, 8, 13, 4, 6, 25, 21, 9, 27};
    for (int i = 0; i < 11; i++) BST->insert(pa[i], va[i]);
    BST->preorder(BST->getRoot());

    cout << endl << "Is binary tree: " << BST->isBinaryTree(BST->getRoot()) << endl;
    cout << "Is Binary Search Tree: " << BST->isBinarySearchTree(BST->getRoot()) << endl;
    BST->inorder(BST->getRoot());
    cout << endl;

    cout << "Heap Max Tree functions\n";
    Tree* heap = new Tree();
    for (int i = 0; i < 11; i++) heap->insert(20-cha[i], 20-con[i]);
    heap->preorder(heap->getRoot());
    cout << endl;

    cout << "Is Max Heap Tree: " << heap->isMaxHeapTree() << endl;
    cout << "Height of tree: " << heap->height() << endl;
    cout << "Depth of tree: " << heap->depth(12) << endl;
    cout << "Number of Leaves: "<< tree->numOfLeaves() << endl;
    cout << "Max Value: "<< BST->findMax() << endl;
    cout << "Max Child: "<< BST->findMaxChild() << endl;

    return 0;
}
