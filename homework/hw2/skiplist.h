//
// Created by G.J.Fourier on 2023/3/3.
//
#ifndef HW2_SKIPLIST_H
#define HW2_SKIPLIST_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Node{
private:
    int key;
    int data;
    int height;

public:
    std::vector<Node*> next;
    Node (int k = 0, int d = 0, int h = 1);
    void setHeight(int h);
    int getKey() const;
    int getData() const;
    int getHeight() const;
};
class Skiplist {
private:
    Node* head;
    int height;
    double pro;
    void setHeight(int h);
    int grow();
public:
    Skiplist(double probability = 0.5);
    ~Skiplist();
    void insert(int k, int d);
    int find(int k);
    void deleteNode(int k);
    void output();
};


#endif //HW2_SKIPLIST_H
