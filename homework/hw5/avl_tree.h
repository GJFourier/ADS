#ifndef HW5_AVL_TREE_H
#define HW5_AVL_TREE_H
#include <iostream>

int max(int a,int b){
    return a > b ? a : b;
}
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
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class AVL{
public:
    long long total = 0;
    ~AVL(){
        clear(root);
    }
    node<T> * root = NULL;
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
        std::cout << '\n';
    }
private:
    void clear(node<T> *p){
        if(p == NULL)
            return;
        clear(p->left);
        clear(p->right);
        delete p;
    }
    int height(node<T> * head){
        if(head==NULL) return 0;
        return head->height;
    }

    node<T> * rightRotation(node<T> * head){
        ++total;
        node<T> * newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node<T> * leftRotation(node<T> * head){
        ++total;
        node<T> * newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    // Traverse and print AVL tree
    void inorderUtil(node<T> * head){
        if(head==NULL) return ;
        inorderUtil(head->left);
        std::cout<<head->key<<" "<<head->height<<'\n';
        inorderUtil(head->right);
    }

    void insertUtil(node<T> * &head, T x){
        // TODO: finish insertUtil
        if(head == NULL) {
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
        if(head == NULL){
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
        else if(head->left != NULL && head->right != NULL){
            node<T> *p = head->left;
            while(p->right != NULL){
                p = p->right;
            }
            head->key = p->key;
            stop = removeUtil(head->left, p->key);
            head->height = max(height(head->left), height(head->right)) + 1;
            subtree = 1;
        }
        else{
            node<T> *p = head;
            if(head->left != NULL)
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
        if(head == NULL) return NULL;
        T k = head->key;
        if(k == x) return head;
        if(k > x) return searchUtil(head->left, x);
        if(k < x) return searchUtil(head->right, x);
    }
};
#endif //HW5_AVL_TREE_H
