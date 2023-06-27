//
// Created by G.J.Fourier on 2023/5/7.
//

#include "skipList.h"

SkipList::Node::Node(uint64_t k, std::string d, uint32_t h) {
    key = k;
    data = d;
    height = h;
    for (int i = 0; i < h; ++i) {
        next.push_back(nullptr);
    }
}

uint64_t SkipList::Node::getKey() {
    return key;
}

std::string SkipList::Node::getData() {
    return data;
}

uint32_t SkipList::Node::getHeight() {
    return height;
}

uint32_t SkipList::grow() {
    int n = 1;
    while(rand() < RAND_MAX * pro){
        ++n;
    }
    return n;
}

SkipList::SkipList(double probability) {
    head = new Node(0, "", 1);
    height = 1;
    listSize = 0;
    dataSize = 0;
    pro = probability;
    srand(time(nullptr));
}

SkipList::~SkipList() {
    Node *p = head, *q = p;
    while(p != nullptr){
        q = p;
        p = p->next[0];
        delete q;
    }
}

void SkipList::insert(uint64_t k, std::string d) {
    if(!find(k).empty()) {
        deleteNode(k);
    }
    uint32_t h = grow();
    Node* r = new Node(k, d, h);
    Node *p = head, *q = p;
    if(h > height){
        for(uint32_t i = height;i < h;++i){
            head->next.push_back(nullptr);
        }
        height = h;
        head->height = h;
    }
    while(h > 0){
        p = q->next[h - 1];
        while(p != nullptr && p->getKey() < k){
            q = p;
            p = p->next[h - 1];
        }
        r->next[h - 1] = q->next[h - 1];
        q->next[h - 1] = r;
        --h;
    }
    ++listSize;
    dataSize += d.size();
}

std::string SkipList::find(uint64_t k) {
    Node *p = head, *q = p;
    uint32_t h = height;
    while (h > 0){
        p = q->next[h - 1];
        while (p != nullptr && p->getKey() < k){
            q = p;
            p = p->next[h - 1];
        }
        if(p == nullptr || p->getKey() > k){
            --h;
        }
        else{
            return p->getData();
        }
    }
    return "";
}

void SkipList::deleteNode(uint64_t k) {
    Node *p = head, *q = p;
    uint32_t h = height;
    while(h > 0){
        p = q->next[h - 1];
        while(p != nullptr && p->getKey() < k){
            q = p;
            p = p->next[h - 1];
        }
        if(p != nullptr && p->getKey() == k){
            q->next[h - 1] = p->next[h - 1];
        }
        --h;
    }
    if(p != nullptr && p->getKey() == k){
        --listSize;
        dataSize -= p->getData().size();
        delete p;
        adjustHeight();
    }
}

void SkipList::output() {
    uint32_t h = height;
    std::cout << "height:" << h << '\n';
    Node *p;
    while(h > 0){
        p = head->next[h - 1];
        std::cout << "head-->";
        while(p != nullptr){
            std::cout << p->getKey() << "-->";
            p = p->next[h - 1];
        }
        std::cout << "tail\n";
        --h;
    }
}

void SkipList::adjustHeight() {
    uint32_t h = height;
    while(h > 0 && head->next[h - 1] == nullptr){
        head->next.pop_back();
        --h;
    }
    if(h > 0){
        height = h;
        head->height = h;
    }
    else{
        height = 1;
        head->height = 1;
        head->next.push_back(nullptr);
    }
}

uint64_t SkipList::size() {
    return listSize;
}

void SkipList::clear() {
    Node* p = head->next[0], *q;
    while(p != nullptr){
        q = p;
        p = p->next[0];
        delete q;
    }
    head->next.clear();
    head->next.push_back(nullptr);
    head->height = 1;
    height = 1;
    listSize = 0;
    dataSize = 0;
}

uint64_t SkipList::dSize() {
    return dataSize;
}

uint64_t SkipList::maxKey() {
    Node* p = head;
    while (p->next[0] != nullptr)
        p = p->next[0];
    return p->getKey();
}

uint64_t SkipList::minKey() {
    return head->next[0]->getKey();
}

SkipList::Node SkipList::operator[](uint32_t index) {
    if(index > listSize - 1)
        return {};
    Node* p = head->next[0];
    for(int i = 0;i < index;++i){
        p = p->next[0];
    }
    return {p->getKey(), p->getData()};
}
