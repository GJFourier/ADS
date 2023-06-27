//
// Created by G.J.Fourier on 2023/3/9.
//

#ifndef HW3_BLOOMFILTER_H
#define HW3_BLOOMFILTER_H
#include <iostream>

class BloomFilter {
private:
    bool *hash;
    int size;
    int data_num;
    int hash_num;
    std::hash<std::string> *fun;

public:
    BloomFilter(int s = 0, int m = 0, int n = 1);
    ~BloomFilter();
    void insert(int data);
    bool search(int data);

};


#endif //HW3_BLOOMFILTER_H
