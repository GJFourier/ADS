#include <iostream>
#include "skiplist.h"
#define e 2.718281828
void run(int size, double pro){
    int *data = new int[size];
    Skiplist sl(pro);
    for(int i = 0;i < size;++i){
        int a = rand() % 2000;
        data[i] = a;
        sl.insert(a, a);
    }
    std::cout << '\n';
    sl.output();
    long times = 0;
    for(int i = 0;i < 10000;++i){
        int label = rand() % size;
        int n = sl.find(data[label]);
        times += n;
    }
    times = times / 10000;
    std::cout << "size:" << size << ' ' << "probability:" << pro * 100 << '%' << '\n' << "search_length:" << times << '\n';
    delete []data;
}

int main() {
    int size[5] = {50, 100, 200, 500, 1000};
    double probability[4] = {double(1)/2, double(1)/e, double(1)/4, double(1)/8};
    for(int i = 0;i < 5;++i){
        for(int j = 0;j < 4;++j){
            run(size[i], probability[j]);
        }
    }
    return 0;
}
