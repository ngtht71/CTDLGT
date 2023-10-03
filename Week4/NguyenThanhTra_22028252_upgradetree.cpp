#include <iostream>
#include <vector>

using namespace std;

// Một Node trong cây
class Node {
    int data;
    Node* fatherNode;
    vector<Node*> children;
public:
    Node() {
        fatherNode = NULL;
        data = 0;
    }

    Node(int data){
        this->data = data;
        this->fatherNode = NULL;
    }

    friend class Tree;
};

class Tree {
    //Node* root;
    vector <Node*> node;
public:
    Tree() {
        for(int i = 0;i < node.size(); i++)
            node[i] = new Node();
    }

    vector <Node*> getNodeList() { return node; }

    Node* findNode (int data){
        for (int i = 0; i < node.size(); i++)
            if (node[i]->data == data) return (node[i]);
        return NULL;
    }

    // Hàm thêm một Node vào cây
    bool insert(int father, int data) {
        if (node.size() == 0) {
            Node* root = new Node(data);
            node.push_back(root);
        }

        Node* dad = findNode (father);
        if (dad == NULL) return false;

        vector<Node*> tmp = dad->children;  //xet cac con cua node cha
        for (int i = 0; i < tmp.size(); i++)
            if (tmp[i]->data == data) return false;

        Node* p = new Node(data);
        p->fatherNode = dad;

        //cap nhat vao vector
        node.push_back(p);
        (dad->children).push_back(p);

        return true;
    }

    // Hàm xoá một Node trên cây
    // Nếu không phải Node lá xoá Node đó và toàn bộ các Node con của nó
    // Hàm trả về số lượng Node đã xoá
    // Nếu Node data không tồn tại trả về 0 (zero)
    void deleteAllChildren (Node* root, int &count)
    {
        if (root == NULL) return;
        else count++;

        // Duyệt qua các node con của node hiện tại
        vector <Node*> p = root->children;
        for (int i = 0; i < p.size(); i++)
            deleteAllChildren(p[i], count);

        delete root;
    }

    int remove(int data){
        Node* found = findNode(data);
        if (found == NULL) return 0;

        Node* found_father = found->fatherNode;

        vector<Node*> p = found_father->children;
        for(int i = 0; i < p.size(); i++)
            if (p[i]->data == data) p.erase(p.begin() + i);

        int count = 0;
        deleteAllChildren(found, count);

        return count;
    }

    // Hàm in ra các Node theo thứ tự preorder
    void preorder(Node* root) {
        if (root->children.size() == 0) return;
        cout << root->data << " ";

        for (int i = 0; i < root->children.size(); i++)
            preorder(root->children[i]);
    }

    // Hàm in ra các Node theo thứ tự postorder
    void postorder(Node* root){
        if (root->children.size() == 0) return;
        for (int i = 0; i < root->children.size(); i++)
            postorder(root->children[i]);
        cout << root->data << ' ';  // goc
    }

    // Hàm kiểm tra cây nhị phân
    bool isBinaryTree() {
        for (int i = 0; i < node.size(); i++)
            if (node[i]->children.size() > 2) return false;

        return true;
    }

    // Hàm kiểm tra cây tìm kiếm nhị phân
    bool isBinarySearchTree() {
        if (!isBinaryTree()) return false;
        for (int i = 0; i < node.size(); i++) {
            vector <Node*> p = node[i]->children;
            if (p.size() == 2)
                if (p[0]->data > node[i]->data || p[1]->data < node[i]->data)
                    return false;
        }
        return true;
    }

    // Hàm kiểm tra cây max-heap
    bool isMaxHeapTree() {
        if (!isBinaryTree()) return false;

        for (int i = 0; i < node.size(); i++) {
            vector<Node*> p = node[i]->children;
            for (int j = 0; j < p.size(); j++)
                if (p[j]->data > node[i]->data) return false;
        }

        return true;
    }

    // Hàm in ra các Node theo thứ tự inorder nếu là cây nhị phân
    void printInorder(Node* root) {          // con trai - goc - con phai
        cout << root->data << " ";
        if (root->children.size() > 0) printInorder(root->children[0]);
        if (root->children.size() > 1) printInorder(root->children[1]);
    }

    void inorder() {
        if (isBinaryTree()) printInorder(node[0]);
    }

    // Hàm trả về độ sâu của một Node
    int depth(int data) {
        Node* p = findNode(data);
        if (p == NULL) return -1;
        int deep = 0;
        while (p->fatherNode != NULL) {
            p = p->fatherNode;
            deep++;
        }
        return deep;
    }

    // Hàm trả về độ cao của cây
    int height() {
        int deep = 0, high = 0;
        for (int i = 0; i < node.size(); i++)
        if (node[i]->children.size() == 0) {
            deep = depth(node[i]->data);
            if (deep > high) high = deep;
        }
        return high;
    }


    // Hàm đếm số lượng lá
    int numOfLeaves() {
        int leaf = 0;
        for (int i = 0; i < node.size(); i++)
            if ((node[i]->children).size() == 0) leaf++;

        return leaf;
    }

    // Hàm trả về Node có giá trị lớn nhất
    int findMax(){
        int maxx = node[0]->data;
        for (int i = 1; i < node.size(); i++)
            if (node[i]->data > maxx) maxx = node[i]->data;

        return maxx;
    }

    // Hàm trả về Node có nhiều con nhất
    int findMaxChild() {
        int maxx = node[0]->children.size();
        for (int i = 1; i < node.size(); i++)
            if (node[i]->children.size() > maxx) maxx = node[i]->children.size();

        return maxx;
    }
};

int main(int argc, char const *argv[]) {
    Tree* tree = new Tree();
    int cha[] = {1, 1, 2, 2, 5, 7, 8, 8, 3, 6, 3};  //11
    int con[] = {2, 3, 4, 5, 7, 8, 9, 10, 6, 11, 12};   //11
    for (int i = 0; i < 11; i++) tree->insert(cha[i], con[i]);
    for (int i = 13; i < 20; i++) tree->insert(12, i);
    for (int i = 20; i <= 30; i++) tree->insert(i-3, i);

    Node* treeRoot = tree->getNodeList()[0];
    vector<Node*> treeNode = tree->getNodeList();

    tree->preorder(treeRoot);
    cout << endl;
    tree->postorder(treeRoot);
    cout << endl;
    cout << endl << "Is binary tree: " << tree->isBinaryTree() << endl;

    cout << endl << tree->remove(8) << endl;
    tree->preorder(treeRoot);

    Node* p = tree->findNode(12);
    cout << "Number Children of Node: " << treeNode.size() << endl;

    cout << "Binary Search Tree functions" << endl;     // ok
    Tree* BST = new Tree();
    int pa[] = {10, 10, 5, 5, 20, 3, 8, 20, 25, 8, 25};
    int va[] = {5, 20, 3, 8, 13, 4, 6, 25, 21, 9, 27};
    for (int i = 0; i < 11; i++) BST->insert(pa[i], va[i]);

    Node* BRoot = BST->getNodeList()[0];
    BST->preorder(BRoot);

    cout << endl << "Is binary tree: " << BST->isBinaryTree() << endl;
    cout << "Is Binary Search Tree: " << BST->isBinarySearchTree() << endl;
    BST->inorder();
    cout << endl;

    cout << "Heap Max Tree functions\n";
    Tree* heap = new Tree();
    for (int i = 0; i < 11; i++) heap->insert(20-cha[i], 20-con[i]);

    Node* heapRoot = heap->getNodeList()[0];
    heap->preorder(heapRoot);
    cout << endl;

    cout << "Is Max Heap Tree: " << heap->isMaxHeapTree() << endl;
    cout << "Height of tree: " << heap->height() << endl;
    cout << "Depth of tree: " << heap->depth(12) << endl;
    cout << "Number of Leaves: "<< tree->numOfLeaves() << endl;
    cout << "Max Value: "<< BST->findMax() << endl;
    cout << "Max Child: "<< BST->findMaxChild() << endl;

    return 0;
}

