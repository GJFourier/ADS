#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<fstream>
#include<string>

const int DATA_SIZE1 = 100;
const int SAMPLE_SIZE1 = 40;
const int DATA_SIZE2 = 1000;
const int SAMPLE_SIZE2 = 400;
const int DATA_SIZE3 = 10000;
const int SAMPLE_SIZE3 = 4000;
const int DATA_SIZE4 = 100000;
const int SAMPLE_SIZE4 = 40000;
const int DATA_SIZE5 = 1000000;
const int SAMPLE_SIZE5 = 400000;
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
            left = NULL;
            right = NULL;
        }
};

template <typename T>
class AVL{
    public:
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
            cout<<endl;
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
            if(head==NULL) return ;
            inorderUtil(head->left);
            cout<<head->key<<" "<<head->height<<'\n';
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



template <typename T>
class BST{
    // TODO: finish BST according to AVL
    public:
        node<T> * root = NULL;
        int num;
        ~BST(){
            clear(root);
        }
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
        void insertUtil(node<T>* &head, T x){
            if(head == NULL){
                head = new node<T>(x);
                return;
            }
            if(head->key > x) {
                insertUtil(head->left, x);
                head->height = max(height(head->left), height(head->right)) + 1;
            }
            if(head->key < x) {
                insertUtil(head->right, x);
                head->height = max(height(head->left), height(head->right)) + 1;
            }
        }
        void removeUtil(node<T>* &head, T x){
            if(head == NULL)
                return;
            if(head->key > x){
                removeUtil(head->left, x);
                head->height = max(height(head->left), height(head->right)) + 1;
            }
            else if(head->key < x){
                removeUtil(head->right, x);
                head->height = max(height(head->left), height(head->right)) + 1;
            }
            else if(head->left != NULL && head->right != NULL){
                node<T> *p = head->left;
                while(p->right != NULL){
                    p = p->right;
                }
                head->key = p->key;
                removeUtil(head->left, p->key);
                head->height = max(height(head->left), height(head->right)) + 1;
            }
            else{
                node<T> *p = head;
                if(head->left != NULL)
                    head = head->left;
                else
                    head = head->right;
                delete p;
            }
        }
        void inorderUtil(node<T> * head){
            if(head==NULL) return ;
            inorderUtil(head->left);
            cout<<head->key<<" "<<head->height<<'\n';
            inorderUtil(head->right);
        }
        node<T> * searchUtil(node<T> * head, T x){
            if(head == NULL) return NULL;
            T k = head->key;
            if(k == x) return head;
            if(k > x) return searchUtil(head->left, x);
            if(k < x) return searchUtil(head->right, x);
        }
};

void run(int data_size, int sample_size, string data_filename, string sample_filename){
    AVL<int> avl;
    BST<int> bst;
    LARGE_INTEGER t1, t2, tc;
    int *data = new int[data_size], *sample = new int[sample_size];
    double time;
    for(int i = 0;i < data_size;++i){
        int a = rand();
        data[i] = a;
        avl.insert(a);
        bst.insert(a);
    }
    cout << "data size:" << data_size << ' ' << "sample size:" << sample_size << '\n';
    cout << "height:" << '\n' << "avl:" << avl.root->height << '\n';
    cout << "bst:" << bst.root->height << '\n';

    cout <<"time:" << '\n';
    for(int i = 0;i < sample_size;++i){
        sample[i] = data[rand() % sample_size];
    }

    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 0;i < sample_size;++i){
        node<int>* p = avl.search(sample[i]);
    }
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    cout << "avl:" << time << "ms\n";

    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 0;i < sample_size;++i){
        node<int>* p = bst.search(sample[i]);
    }
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    cout << "bst:" << time << "ms\n";
    cout << '\n';
    ofstream oFile;
    oFile.open(data_filename);
    for(int i = 0;i < data_size;++i){
        oFile << data[i] <<endl;
    }
    oFile.close();
    oFile.open(sample_filename);
    for(int i = 0;i < sample_size;++i){
        oFile << sample[i] <<endl;
    }
    oFile.close();
    delete []data;
    delete []sample;
}


int main(){
    srand(time(0));
    run(DATA_SIZE1, SAMPLE_SIZE1, "data1.txt", "sample1.txt");
    run(DATA_SIZE2, SAMPLE_SIZE2, "data2.txt", "sample2.txt");
    run(DATA_SIZE3, SAMPLE_SIZE3, "data3.txt", "sample3.txt");
    run(DATA_SIZE4, SAMPLE_SIZE4, "data4.txt", "sample4.txt");
    run(DATA_SIZE5, SAMPLE_SIZE5, "data5.txt", "sample5.txt");
    // Design your program
}
