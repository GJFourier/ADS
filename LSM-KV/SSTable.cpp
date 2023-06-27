//
// Created by G.J.Fourier on 2023/5/9.
//

#include "SSTable.h"

SSTable::SSTable(SkipList &memTable, uint64_t timeStamp, std::string dir) {
    std::string fN = "SSTable" + std::to_string(timeStamp) + ".sst";
    directory = std::move(dir);
    this->fileName = std::move(fN);
    header = Header(timeStamp, memTable.size(), memTable.minKey(), memTable.maxKey());
    data = "";
    uint32_t offset = 0;
    SkipList::Node* p = memTable.head;
    for(uint64_t i = 0;i < memTable.size();++i){
        p = p->next[0];
        uint64_t key = p->key;
        std::string s = p->data;
        bloomFilter.insert(key);
        index.emplace_back(key, offset);
        offset += s.size();
        data += s;
    }
}

void SSTable::store(std::string level) {
    std::string dirPath = directory + "/" + level;
    if(!utils::dirExists(dirPath))
        utils::mkdir(dirPath.c_str());
    std::fstream file;
    file.open(dirPath + "/" + fileName, std::ios::out|std::ios::binary|std::ios::trunc);
    if (!file) {
        std::cout << "Failed to open/create the file:\"" << fileName << '\"' << std::endl;
        return;
    }
    file.write((char *)(&header), sizeof(header));
    bool *bloomFilter1 = new bool [10240 * 8];
    bloomFilter.copy(bloomFilter1);
    for(uint64_t i = 0;i < 10240 * 8;i += 8){
        uint8_t c = 0;
        for(uint64_t j = 0;j < 8;++j){
            c |= uint8_t(bloomFilter1[i + j]) << (7 - j);
        }
        file.write((char *)(&c), 1);
    }
    delete []bloomFilter1;
    for(Index p:index){
        file.write((char*)(&(p.key)), 8);
        file.write((char*)(&(p.offset)), 4);
    }
    file.write(data.c_str(), data.size());
    file.close();
}

std::string SSTable::getFileName() {
    return fileName;
}

uint64_t SSTable::getTimeStamp() {
    return header.timeStamp;
}

uint64_t SSTable::getKeyNum() {
    return header.keyNum;
}

uint64_t SSTable::getMinKey() {
    return header.minkey;
}

uint64_t SSTable::getMaxKey() {
    return header.maxKey;
}

std::string SSTable::find(uint64_t key) {
    for(int i = 0;i < header.keyNum;++i){
        if(index[i].key == key){
            uint32_t offset1 = index[i].offset;
            std::string b;
            if(i == header.keyNum - 1)
                b = data.substr(offset1);
            else{
                uint32_t offset2 = index[i + 1].offset;
                b = data.substr(offset1, offset2 - offset1 + 1);
            }
            return b;
        }
    }
    return "";
}

SSTable::~SSTable() {
}
