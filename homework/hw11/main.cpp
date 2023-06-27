#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#define SIZE (100000)
static const int TOTAL = 10000;

namespace cuckoo {
    template <typename T>
    inline void swap(T* a, T* b){
        assert(a != NULL && b != NULL);
        T tmp = *a;
        *a = *b;
        *b = tmp;
    }
    typedef int KeyType;

    class Cuckoo {
    protected:
        std::mutex mtx;
        int size;
        KeyType *T;

        int hash1(const KeyType& key);
        int hash2(const KeyType& key);
        KeyType get1(const KeyType& key);
        KeyType get2(const KeyType& key);
        void bt_evict(const KeyType& key, int which, int pre_pos, int num);

    public:
        Cuckoo();
        ~Cuckoo();
        KeyType get(const KeyType& key);
        void put(const KeyType& key);
        void put_p(const KeyType &key);
        void rehash();
        void putInNewTable(KeyType* table, const KeyType& key);
        void output();
        void reset();
    };
}

using namespace cuckoo;

Cuckoo::Cuckoo() {
    T = new KeyType [SIZE];
    size = SIZE;
    memset(T, 0, sizeof(KeyType) * SIZE);
}

Cuckoo::~Cuckoo() {

}

int Cuckoo::hash1(const KeyType& key) {
    assert(size != 0);
    int half_siz = size / 2;
    return key%half_siz;
}

int Cuckoo::hash2(const KeyType& key) {
    assert(size != 0);
    int half_siz = size / 2;
    return key%half_siz + half_siz;
}

KeyType Cuckoo::get1(const KeyType& key) {
    int pos = hash1(key);
    if (T[pos] == key)
        return key;
    return 0;
}

KeyType Cuckoo::get2(const KeyType& key) {
    int pos = hash2(key);
    if (T[pos] == key)
        return key;
    return 0;
}

void Cuckoo::bt_evict(const KeyType& key, int which, int pre_pos, int num) {
    if(num > 2 * size){
        rehash();
        //TODO:rehash
    }
    int idx = (which == 0)?hash1(key):hash2(key);
    // basic case: find a empty pos for the last evicted element
    if(T[idx] == 0){
        printf("evicted key %d from %d to %d\n", key, pre_pos, idx);
        T[idx] = key;
        return;
    }
    printf("evicted key %d from %d to %d\n", key, pre_pos, idx);
    KeyType cur = T[idx];
    // first evict latter elements
    bt_evict(cur, 1 - which, idx, num + 1);
    T[idx] = key;
}

KeyType Cuckoo::get(const KeyType& key) {
    assert(key != 0);
    KeyType result;
    result = get1(key);
    if (result != 0)
        return result;
    result = get2(key);
    return result;
}

void Cuckoo::put(const KeyType& key) {
    if(key == 0){
        std::cout << "invalid key\n";
        return;
    }
    KeyType result = get(key);
    if (result != 0){
        std::cout << "duplicate key, put fail\n";
        return;
    }
    int pos1 = hash1(key);
    if (T[pos1] == 0) {
        T[pos1] = key;
        return;
    }
    int pos2 = hash2(key);
    if (T[pos2] == 0) {
        T[pos2] = key;
        return;
    }
    bt_evict(key, 0, -1, 0);
}

void Cuckoo::put_p(const KeyType &key) {
    if(key == 0){
        printf("invalid key\n");
        return;
    }
    if(get(key) != 0){
        printf("duplicate key, put fail\n");
        return;
    }
    // basic way
    if(T[hash1(key)] == 0){
        T[hash1(key)] = key;
    }
    else if(T[hash2(key)] == 0){
        T[hash2(key)] = key;
    }
    else{
        std::unique_lock<std::mutex> lck(mtx);
        KeyType evicted = key;
        int which = 0;
        int idx = hash1(evicted);
        int pre_pos = -1;
        int num = 0;
        while(T[idx] != 0){
            swap(&evicted, &T[idx]);
            pre_pos = idx;
            if(num > 2 * size){
                rehash();
                //TODO:rehash
            }
            which = 1 - which;
            idx = (which == 0)?hash1(evicted):hash2(evicted);
            ++num;
        }
        T[idx] = evicted;
    }
}
void Cuckoo::rehash() {
    int newSize = size * 2;  // 哈希表容量扩大为原来的两倍
    auto* newTable = new KeyType[newSize];  // 创建新的哈希表

    // 初始化新哈希表
    memset(newTable, 0, sizeof(KeyType) * newSize);

    // 重新哈希旧哈希表中的元素
    for (int i = 0; i < size; i++) {
        if (T[i] != 0) {
            putInNewTable(newTable, T[i]);  // 将旧哈希表中的元素插入到新哈希表中
        }
    }

    delete[] T;  // 释放旧哈希表的内存
    T = newTable;  // 将新哈希表指针指向新的内存区域
    size = newSize;  // 更新哈希表的容量
}

void Cuckoo::putInNewTable(KeyType* table, const KeyType& key) {
    int pos1 = hash1(key);  // 根据哈希函数1计算插入位置
    if (table[pos1] == 0) {
        table[pos1] = key;  // 如果插入位置为空，则直接插入元素
        return;
    }

    int pos2 = hash2(key);  // 根据哈希函数2计算插入位置
    if (table[pos2] == 0) {
        table[pos2] = key;  // 如果插入位置为空，则直接插入元素
        return;
    }

    // 如果两个位置都被占用，则需要进行重哈希操作
    // 选择一个位置进行替换，并将被替换的元素继续插入新哈希表中
    bt_evict(key, 0, -1, 0);
}

void Cuckoo::output() {
    for(int i=0;i < size;++i){
        if(T[i] != 0)
            std::cout << T[i] << '\n';
    }
}

void Cuckoo::reset() {
    memset(T, 0, sizeof(KeyType) * size);
}

int main(){
    Cuckoo test;
    LARGE_INTEGER t1, t2, tc;
    double time;
    // 串行
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 1; i <= TOTAL; ++i) {
        test.put(i);
    }
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    std::cout << time << "ms\n";
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 1; i <= TOTAL; ++i) {
        test.get(i);
    }
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    std::cout << time << "ms\n";
    // 并行
    test.reset();
    std::vector<std::thread> threads;
    threads.clear();
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 1; i <= TOTAL; ++i){
        threads.emplace_back([&](int thread_id){
            test.put_p(thread_id);
        }, i);
    }
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    std::cout << time << "ms\n";
    for(int i = 0; i < TOTAL; ++i){
        threads[i].join();
    }
    threads.clear();
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 1; i <= TOTAL; ++i){
        threads.emplace_back([&](int thread_id){
            test.get(thread_id);
        }, i);
    }
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    std::cout << time << "ms\n";
    for(int i = 0; i < TOTAL; ++i){
        threads[i].join();
    }
    return 0;
    // single-thread to put [1, TOTAL]
}
