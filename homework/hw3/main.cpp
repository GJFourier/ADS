#include <iostream>
#include "BloomFilter.h"

void run(int m, int n, int k){
    int num = 0;
    BloomFilter bloomFilter(m, n, k);
    for(int i = 0;i < n;++i){
        bloomFilter.insert(i);
    }
    for(int i = 0;i < n;++i){
        bool flag = bloomFilter.search(i + n);
        if(flag){
            ++num;
        }
    }
    std::cout << "m/n:" << m/n << ' ' << "k:" << k << '\n';
    std::cout << double(num) / double(n) << '\n';
}

int main() {
    int k[5] = {1, 2, 3, 4, 5};
    int m[4] = {10000, 15000, 20000, 25000};
    int n[4] = {5000, 5000, 5000, 5000};
    for(int i = 0;i < 5;++i){
        for(int j = 0;j < 4;++j){
            if(m[j]/n[j] >= k[i]) {
                run(m[j], n[j], k[i]);
            }
        }
    }
}
