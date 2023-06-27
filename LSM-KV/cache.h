//
// Created by G.J.Fourier on 2023/5/11.
//

#ifndef LSMTREE_CACHE_H
#define LSMTREE_CACHE_H

#include <string>
#include <vector>
#include <set>
#include <cstring>
#include "skipList.h"
#include "bloomFilter.h"
#include "MurmurHash3.h"

struct Header{
    uint64_t timeStamp;
    uint64_t keyNum;
    uint64_t minkey;
    uint64_t maxKey;
    Header(uint64_t t = 0, uint64_t kN = 0, uint64_t minK = 0, uint64_t maxK = 0):timeStamp(t), keyNum(kN), minkey(minK), maxKey(maxK){}
};
struct Index{
    uint64_t key;
    uint32_t offset;
    Index(uint64_t k = 0, uint32_t off = 0):key(k), offset(off){}
    bool operator<(const Index& other) const {
        return key < other.key;
    }
    bool operator>(const Index& other) const {
        return key > other.key;
    }
};
class Cache {
public:
    std::string filename;
    uint64_t level;
    bool *bloomFilter;
    std::set<Index> index;
    Header header;

    Cache(SkipList &memTable, uint64_t timeStamp, uint64_t level = 0);

    Cache() {bloomFilter = new bool[10240 * 8];}

    Cache(const Cache &cache);

    Cache(std::string filename, uint64_t level, Header header, const bool* bloomFilter, std::set<Index> index);

    ~Cache();

    uint64_t inCache(uint64_t key) const;
    bool operator<(const Cache& other) const {
        return header.timeStamp < other.header.timeStamp;
    }
    bool operator>(const Cache& other) const {
        return header.timeStamp > other.header.timeStamp;
    }
};


#endif //LSMTREE_CACHE_H
