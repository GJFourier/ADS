#ifndef LSMKV_SKIPLIST_H
#define LSMKV_SKIPLIST_H
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
class SkipList {
private:
    friend class SSTable;
    friend class Cache;
    class Node{
        friend class SkipList;
        friend class SSTable;
        friend class Cache;
    private:
        uint64_t key;

        std::string data;

        uint32_t height;

        std::vector<Node*> next;
    public:
        Node (uint64_t k = 0, std::string d = "", uint32_t h = 1);
        uint64_t getKey();
        std::string getData();
        uint32_t getHeight();
    };
    Node* head;

    uint32_t height;

    double pro;

    uint64_t listSize;

    uint64_t dataSize;

    uint32_t grow();

    void adjustHeight();
public:
    SkipList(double probability = 0.5);

    ~SkipList();

    void insert(uint64_t k, std::string d);

    std::string find(uint64_t k);

    void deleteNode(uint64_t k);

    void output();

    uint64_t size();

    uint64_t dSize();

    void clear();

    uint64_t maxKey();

    uint64_t minKey();

    Node operator[](uint32_t index);
};
#endif //LSMKV_SKIPLIST_H

