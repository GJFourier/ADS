//
// Created by G.J.Fourier on 2023/3/3.
//
#include "Skiplist.h"


Node::Node(int k, int d, int h) {
    key = k;
    data = d;
    height = h;
    for (int i = 0; i < h; ++i) {
        next.push_back(nullptr);
    }
}
int Node::getData() const {
    return data;
}

int Node::getHeight() const {
    return height;
}

int Node::getKey() const {
    return key;
}

void Node::setHeight(int h) {
    height = h;
}


Skiplist::Skiplist(double probability) {
    head = new Node(-1, -1, 1);
    height = 1;
    pro = probability;
    srand(time(nullptr));
}

void Skiplist::insert(int k, int d) {
    int h = grow();
    Node* r = new Node(k, d, h);
    Node *p = head, *q = p;
    if(h > height){
        for(int i = height;i < h;++i){
            head->next.push_back(nullptr);
        }
        setHeight(h);
    }
    while(h > 0){
        while(p != nullptr && p->getKey() < k){
            q = p;
            p = p->next[h - 1];
        }
        if(p == nullptr){
            r->next[h - 1] = q->next[h - 1];
            q->next[h - 1] = r;
            --h;
            if(h > 0){
                p = q->next[h - 1];
            }
        }
        else {
            if(p->getKey() == k){
                deleteNode(k);
            }
            r->next[h - 1] = q->next[h - 1];
            q->next[h - 1] = r;
            --h;
            if(h > 0){
                p = q->next[h - 1];
            }
        }
    }
    h = height;
    while(h > 0 && head->next[h - 1] == nullptr){
        --h;
        head->next.pop_back();
    }
    if(h > 0){
        setHeight(h);
    }
    else{
        setHeight(1);
        head->next.push_back(nullptr);
    }
}

int Skiplist::find(int k) {
    Node *p = head, *q = p;
    int h = p->getHeight();
    int n = 1;
    while(h > 0){
        while(p != nullptr && p->getKey() < k){
            ++n;
            q = p;
            p = p->next[h - 1];
        }
        if(p == nullptr){
            --h;
            ++n;
            p = q->next[h - 1];
        }
        else {
            if(p->getKey() == k){
                return n;
            }
            --h;
            ++n;
            if(h > 0){
                p = q->next[h - 1];
            }
        }
    }
    --n;
    return n;
}

void Skiplist::setHeight(int h) {
    height = h;
    head->setHeight(h);
}

int Skiplist::grow() {
    int n = 1;
    while(rand() < RAND_MAX * pro){
        ++n;
    }
    return n;
}

void Skiplist::deleteNode(int k) {
    Node *p = head, *q = p;
    int h = head->getHeight();
    while(h > 0){
        while(p != nullptr && p->getKey() < k){
            q = p;
            p = p->next[h - 1];
        }
        if(p != nullptr && p->getKey() == k){
            q->next[h - 1] = p->next[h - 1];
        }
        --h;
        if(h > 0){
            p = q->next[h - 1];
        }
    }
    if(p != nullptr && p->getKey() == k)
        delete p;
}

void Skiplist::output() {
    int h = height;
    std::cout << "height:" << h << '\n';
    Node *p;
    while(h > 0){
        p = head->next[h - 1];
        while(p != nullptr){
            std::cout << p->getKey() << " ";
            p = p->next[h - 1];
        }
        std::cout << '\n';
        --h;
    }
}

Skiplist::~Skiplist() {
    Node *p = head, *q = p;
    while(p != nullptr){
        q = p;
        p = p->next[0];
        delete q;
    }
}
