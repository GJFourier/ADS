//
// Created by G.J.Fourier on 2023/5/11.
//

#include "cache.h"

#include <utility>
Cache::Cache(SkipList &memTable, uint64_t timeStamp, uint64_t level) {
    filename = "SSTable" + std::to_string(timeStamp) + ".sst";
    this->level = level;
    header = (Header(timeStamp, memTable.size(), memTable.minKey(), memTable.maxKey()));
    BloomFilter bloomFilter1;
    uint32_t offset = 0;
    SkipList::Node *p = memTable.head;
    for(int i = 0;i < header.keyNum;++i){
        p = p->next[0];
        uint64_t key = p->key;
        std::string data = p->data;
        bloomFilter1.insert(key);
        index.insert(Index(key, offset));
        offset += data.size();
    }
    bloomFilter = new bool[10240 * 8];
    bloomFilter1.copy(bloomFilter);
}
Cache::~Cache(){
    delete []bloomFilter;
}

Cache::Cache(const Cache &cache){
    this->header = cache.header;
    this->filename = cache.filename;
    this->level = cache.level;
    this->index = cache.index;
    this->bloomFilter = new bool[10240 * 8];
    for(int i = 0;i < 10240 * 8;++i){
        this->bloomFilter[i] = cache.bloomFilter[i];
    }
}

uint64_t Cache::inCache(uint64_t key) const {
    if(key < header.minkey || key > header.maxKey)
        return 0;
    uint32_t hash[4] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, hash);
    for(uint32_t h:hash){
        if(!bloomFilter[h % (10240 * 8)]){
            return 0;
        }
    }
    auto it = index.find(Index(key));
    if(it != index.end()){
        uint64_t offset = 0;
        uint32_t offset1 = it->offset;
        offset |= offset1;
        offset = offset << 32;
        auto next = index.upper_bound(Index(key));
        uint32_t offset2 = next == index.end() ? 0 : next->offset;
        offset |= offset2;
        return offset;
    }
    return 0;
}

Cache::Cache(std::string filename, uint64_t level, Header header, const bool *bloomFilter, std::set<Index> index) {
    this->filename = std::move(filename);
    this->level = level;
    this->header = header;
    this->bloomFilter = new bool [10240 * 8];
    for(uint64_t i = 0;i < 10240 * 8;++i){
        this->bloomFilter[i] = bloomFilter[i];
    }
    this->index = std::move(index);
}
