//
// Created by G.J.Fourier on 2023/3/9.
//

#include "BloomFilter.h"

BloomFilter::BloomFilter(int s, int m, int n) {
    size = s;
    data_num = m;
    hash_num = n;
    hash = new bool[size];
    fun = new std::hash<std::string>;
    for(int i = 0;i < s;++i){
        hash[i] = false;
    }
}

BloomFilter::~BloomFilter() {
    delete []hash;
}

void BloomFilter::insert(int data) {
    for(int i = 0;i < hash_num;++i){
        int label = fun->operator()(std::to_string(data) + std::to_string(i)) % size;
        hash[label] = true;
    }
}

bool BloomFilter::search(int data) {
    for(int i = 0;i < hash_num;++i){
        int label = fun->operator()(std::to_string(data) + std::to_string(i)) % size;
        if(!hash[label])
            return false;
    }
    return true;
}
