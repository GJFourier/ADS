//
// Created by G.J.Fourier on 2023/5/9.
//

#ifndef LSMTREE_SSTABLE_H
#define LSMTREE_SSTABLE_H
#include <string>
#include "skipList.h"
#include "bloomFilter.h"
#include "utils.h"
#include <vector>
#include <fstream>
class SSTable {
private:
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
        Index(uint64_t k = 0, uint64_t off = 0):key(k), offset(off){};
    };
    std::string fileName;
    std::string directory;
    Header header;
    BloomFilter bloomFilter;
    std::vector<Index> index;
    std::string data;
public:
    SSTable(SkipList &memTable, uint64_t timeStamp, std::string dir);

    ~SSTable();

    void store(std::string level = "level-0");

    std::string getFileName();

    uint64_t getTimeStamp();

    uint64_t getKeyNum();

    uint64_t getMinKey();

    uint64_t getMaxKey();

    std::string find(uint64_t key);

};


#endif //LSMTREE_SSTABLE_H
