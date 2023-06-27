//
// Created by G.J.Fourier on 2023/5/9.
//

#ifndef LSMTREE_BLOOMFILTER_H
#define LSMTREE_BLOOMFILTER_H


#include <functional>
#include <iostream>
#include "MurmurHash3.h"

class BloomFilter {
    bool *hashTable;
    uint32_t hashTableSize;
public:
    BloomFilter(uint32_t s = 10240);

    ~BloomFilter();

    void insert(uint64_t key);

    bool find(uint64_t key);

    void clear();

    void copy(bool *array);
};


#endif //LSMTREE_BLOOMFILTER_H
