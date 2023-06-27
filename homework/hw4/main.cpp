#include <iostream>
#include <cstdlib>
#include <ctime>
#include<windows.h>

#include "SplayTree.h"
using namespace std;

template <typename T>
class node{
public:
    T key;
    int height;
    node * left;
    node * right;
    node(T k){
        height = 1;
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class AVL{
public:
    ~AVL(){
        clear(root);
    }
    void clear(node<T>* &p){
        if(p == nullptr)
            return;
        clear(p->left);
        clear(p->right);
        delete p;
        p = nullptr;
    }
    node<T> * root = nullptr;
    int num;
    void insert(T x){
        insertUtil(root, x);
    }

    void remove(T x){
        removeUtil(root, x);
    }

    node<T> * search(T x){
        return searchUtil(root,x);
    }

    void inorder(){
        inorderUtil(root);
        cout<<endl;
    }
private:
    int height(node<T> * head){
        if(head==nullptr) return 0;
        return head->height;
    }

    node<T> * rightRotation(node<T> * head){
        node<T> * newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node<T> * leftRotation(node<T> * head){
        node<T> * newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    // Traverse and print AVL tree
    void inorderUtil(node<T> * head){
        if(head==nullptr) return ;
        inorderUtil(head->left);
        cout<<head->key<<" "<<head->height<<'\n';
        inorderUtil(head->right);
    }

    void insertUtil(node<T> * &head, T x){
        // TODO: finish insertUtil
        if(head == nullptr) {
            head = new node<T>(x);
            return;
        }
        if(head->key > x){
            insertUtil(head->left, x);
            head->height = max(height(head->left), height(head->right)) + 1;
            if(height(head->left) - height(head->right) == 2){
                if(head->left->key > x){
                    head = rightRotation(head);
                }
                else if(head->left->key < x){
                    head->left = leftRotation(head->left);
                    head = rightRotation(head);
                }
            }
        }
        if(head->key < x) {
            insertUtil(head->right, x);
            head->height = max(height(head->left), height(head->right)) + 1;
            if (height(head->right) - height(head->left) == 2) {
                if (head->right->key< x) {
                    head = leftRotation(head);
                } else if (head->right->key > x) {
                    head->right = rightRotation(head->right);
                    head = leftRotation(head);
                }
            }
        }
    }

    bool removeUtil(node<T> * &head, T x){
        // TODO: finish removeUtil
        bool stop = false;
        int subtree;
        if(head == nullptr){
            return true;
        }
        if(head->key > x){
            stop = removeUtil(head->left, x);
            head->height = max(height(head->left), height(head->right)) + 1;
            subtree = 1;
        }
        else if(head->key < x){
            stop = removeUtil(head->right, x);
            head->height = max(height(head->left), height(head->right)) + 1;
            subtree = 2;
        }
        else if(head->left != nullptr && head->right != nullptr){
            node<T> *p = head->left;
            while(p->right != nullptr){
                p = p->right;
            }
            head->key = p->key;
            stop = removeUtil(head->left, p->key);
            head->height = max(height(head->left), height(head->right)) + 1;
            subtree = 1;
        }
        else{
            node<T> *p = head;
            if(head->left != nullptr)
                head = head->left;
            else
                head = head->right;
            delete p;
            return false;
        }
        if(stop)
            return true;
        int bf;
        switch(subtree){
            case 1:
                bf = height(head->left) - height(head->right) + 1;
                if(bf == 0)
                    return true;
                if(bf == 1)
                    return false;
                if(bf == -1){
                    int bfr = height(head->right->left) - height(head->right->right);
                    switch(bfr){
                        case 0:
                            head = leftRotation(head);
                            return true;
                        case -1:
                            head = leftRotation(head);
                            return false;
                        case 1:
                            head->right = rightRotation(head->right);
                            head = leftRotation(head);
                            return false;
                    }
                }
            case 2:
                bf = height(head->right) - height(head->left) + 1;
                if(bf == 0)
                    return true;
                if(bf == 1)
                    return false;
                if(bf == -1){
                    int bfr = height(head->left->right) - height(head->left->left);
                    switch(bfr){
                        case 0:
                            head = rightRotation(head);
                            return true;
                        case -1:
                            head = rightRotation(head);
                            return false;
                        case 1:
                            head->left = leftRotation(head->left);
                            head = rightRotation(head);
                            return false;
                    }
                }
        }
        return true;
    }

    node<T> * searchUtil(node<T> * head, T x){
        if(head == nullptr) return nullptr;
        T k = head->key;
        if(k == x) return head;
        if(k > x) return searchUtil(head->left, x);
        if(k < x) return searchUtil(head->right, x);
    }
};

int main()
{
    srand(time(nullptr));
    int n[4] = {1000, 2000, 5000, 10000};
    double ratio[9] = {0.0001, 0.0005, 0.001, 0.005, 0.01, 0.10, 0.25, 0.45, 0.65};
    LARGE_INTEGER t1, t2, tc;
    int time;
    SplayTree<int, int> spl;
    AVL<int> avl;
    for(int i = 0;i < 4;++i){
        for(int j = 0;j < n[i];++j){
            spl.insert(j+1, j+1);
            avl.insert(j+1);
        }
        for(int j = 0;j < 9;++j){
            int k = n[i] * ratio[j];
            int init = rand() % (n[i] + 1);
            cout << "m:" << 100 * n[i] << ' ' << "n:" << n[i] << ' ' << "k:" << k << '\n';

            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);
            for(int l = 0;l < 100 * n[i];++l) {
                for (int o = 0; o < k; ++o) {
                    avl.search((init + o) % (n[i] + 1));
                }
            }
            QueryPerformanceCounter(&t2);
            time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
            cout << "avl:" << time << "ms\n";

            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);
            for(int l = 0;l < 100 * n[i];++l) {
                for (int o = 0; o < k; ++o) {
                    spl.search((init + o) % (n[i] + 1));
                }
            }
            QueryPerformanceCounter(&t2);
            time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
            cout << "spl:" << time << "ms\n";
        }
        avl.clear(avl.root);
        spl.deleteAll();
    }
}
