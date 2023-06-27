//
// Created by G.J.Fourier on 2023/5/9.
//

#include "bloomFilter.h"
BloomFilter::BloomFilter(uint32_t s) {
    hashTableSize = s * 8;
    hashTable = new bool[hashTableSize];
    for(int i = 0;i < s;++i){
        hashTable[i] = false;
    }
}

BloomFilter::~BloomFilter() {
    delete []hashTable;
}

void BloomFilter::insert(uint64_t data) {
    uint32_t hash[4] = {0};
    MurmurHash3_x64_128(&data, sizeof(data), 1, hash);
    for(uint32_t i : hash){
        hashTable[i % hashTableSize] = true;
    }
}

bool BloomFilter::find(uint64_t data) {
    uint32_t hash[4] = {0};
    MurmurHash3_x64_128(&data, sizeof(data), 1, hash);
    for(uint32_t i : hash){
        if(!hashTable[i % hashTableSize])
            return false;
    }
    return true;
}

void BloomFilter::clear() {
    for(int i = 0;i < hashTableSize;++i){
        hashTable[i] = false;
    }
}

void BloomFilter::copy(bool *array) {
    for(int i = 0;i < hashTableSize;++i){
        array[i] = hashTable[i];
    }
}
