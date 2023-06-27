#include "kvstore.h"
#include <string>
#include <utility>

bool sort_string(const std::string& s1, const std::string& s2){
    std::string numberStr;
    int num1, num2;
    size_t tablePos = s1.find("SSTable");
    if (tablePos != std::string::npos) {
        // 从 "Table" 的下一个位置开始查找 "."
        size_t dotPos = s1.find('.', tablePos + 7);
        if (dotPos != std::string::npos) {
            // 从 "Table" 之后、"." 之前的位置开始提取数字部分
            size_t start = tablePos + 7;
            size_t length = dotPos - start;
            numberStr = s1.substr(start, length);
        }
    }
    num1 = std::stoi(numberStr);

    tablePos = s2.find("SSTable");
    if (tablePos != std::string::npos) {
        // 从 "Table" 的下一个位置开始查找 "."
        size_t dotPos = s2.find('.', tablePos + 7);
        if (dotPos != std::string::npos) {
            // 从 "Table" 之后、"." 之前的位置开始提取数字部分
            size_t start = tablePos + 7;
            size_t length = dotPos - start;
            numberStr = s2.substr(start, length);
        }
    }
    num1 = std::stoi(numberStr);
    return num1 < num2;
}
KVStore::KVStore(const std::string &dir): KVStoreAPI(dir)
{
    dataDirectory = dir;
    timeStamp = 1;
    if(!utils::dirExists(dir))
        utils::mkdir(dir.c_str());
    readConfig(std::string("default.conf"));
    if(directoryType.find(0) == directoryType.end()){
        directoryType[0] = std::pair<uint64_t , Mode>(2, Tiering);
    }
    load();
    if(!caches.empty())
        timeStamp += (caches.rbegin())->header.timeStamp;
}

KVStore::~KVStore()
{
//    if(memTable.size() != 0) {
//        SSTable ssTable(memTable, timeStamp, dataDirectory);
//        ssTable.store();
//        std::vector<std::string> files;
//        if(utils::scanDir(dataDirectory + "/level-0", files) > directoryType[0].first)
//            compaction(0, 1);
//    }
}

/**
 * Insert/Update the key-value pair.
 * No return values for simplicity.
 */
void KVStore::put(uint64_t key, const std::string &s)
{
    std::string pre_s = memTable.find(key);
    memTable.insert(key, s);
    if(ifTrans()){
        memTable.deleteNode(key);
        if(!pre_s.empty()){
            memTable.insert(key, pre_s);
        }
        toSSTable();
        memTable.clear();
        put(key, s);
    }
}
/**
 * Returns the (string) value of the given key.
 * An empty string indicates not found.
 */
std::string KVStore::get(uint64_t key)
{
    std::string result;
    result = memTable.find(key);
    if(result.empty()){
        result = findInSSTable(key);
    }
    if(result == "~DELETED~")
        return "";
	return result;
}
/**
 * Delete the given key-value pair if it exists.
 * Returns false iff the key is not found.
 */
bool KVStore::del(uint64_t key)
{
    std::string data = get(key);
    if(data.empty())
	    return false;
    else{
        put(key, "~DELETED~");
        return true;
    }
}

/**
 * This resets the kvstore. All key-value pairs should be removed,
 * including memtable and all sstables files.
 */
void KVStore::reset()
{
    memTable.clear();
    uint64_t num = caches.size();
    uint64_t level = 0;
    while (num > 0){
        std::vector<std::string> files;
        std::string directory = dataDirectory + "/level-" + std::to_string(level);
        uint64_t fileNum = utils::scanDir(directory, files);
        for(const std::string& file:files){
            utils::rmfile(file.c_str());
        }
        utils::rmdir(directory.c_str());
        ++level;
        num -= fileNum;
    }
    caches.clear();
}

/**
 * Return a list including all the key-value pair between key1 and key2.
 * keys in the list should be in an ascending order.
 * An empty string indicates not found.
 */
void KVStore::scan(uint64_t key1, uint64_t key2, std::list<std::pair<uint64_t, std::string> > &list)
{
    for(uint64_t i = key1;i <= key2;++i){
        std::string s = get(i);
        if(!s.empty()){
            list.emplace_back(i, s);
        }
    }
}

bool KVStore::ifTrans() {
    if (32 + 10240 + memTable.size() * 12 + memTable.dSize() > MEM_TABLE_MAX)
        return true;
    else
        return false;
}

void KVStore::toSSTable() {
    SSTable ssTable(memTable, timeStamp, dataDirectory);
    ssTable.store();
    std::vector<std::string> files;
    caches.insert(Cache(memTable, timeStamp));
//    if(utils::scanDir(dataDirectory + "/level-0", files) > directoryType[0].first) {
//        compaction(0, 1);
//    }
    ++timeStamp;
}

std::string KVStore::findInSSTable(uint64_t key) {
    for(auto it = caches.rbegin(); it != caches.rend(); ++it){
        uint64_t offset;
        if((offset = it->inCache(key)) != 0){
            uint32_t offset1 = offset >> 32;
            uint32_t offset2 = (offset << 32) >> 32;
            uint32_t size = offset2 - offset1;
            std::fstream file;
            file.open(dataDirectory + "/level-" + std::to_string(it->level) + "/SSTable" + std::to_string(it->header.timeStamp) + ".sst", std::ios::in | std::ios::binary);
            if(!file)
                std::cout << "open failed" << '\n';
            offset1 += 32 + 10240 + 12 * it->header.keyNum;
            file.seekg(offset1, std::ios::beg);
            std::string data;
            if(offset2 != 0){
                data.resize(size);
                file.read(data.data(), size);
            }
            else{
                file.seekg( 0, std::ios::end );
                std::streampos tail = file.tellg();
                file.seekg(offset1, std::ios::beg);
                std::streampos start = file.tellg();
                size = tail - start;
                data.resize(size);
                file.read(data.data(), size);
            }
            file.close();
            return data;
        }
    }
    return "";
}

void KVStore::readConfig(const std::string& configName) {
    std::fstream file;
    file.open(configName, std::ios::in);
    if(!file)
        std::cerr << "Open failed!" << '\n';
    std::istringstream iss;
    uint64_t level = 0, num = 0;
    std::string line, mode;
    Mode m;
    while (std::getline(file, line)) {
        iss.clear();
        iss.str(line);
        iss >> level >> num >> mode;
        if (mode == "Tiering")
            m = Tiering;
        else
            m = Leveling;
        directoryType[level] = std::pair<uint64_t , Mode>(num, m);
    }
    file.close();
}

void KVStore::load() {
    std::fstream f;
    std::vector<std::string> levels;
    utils::scanDir(dataDirectory, levels);
    for(std::string &level : levels){
        size_t pos = level.find('-');
        uint64_t levelNum;
        if (pos != std::string::npos && pos < level.length() - 1){
            std::string num = level.substr(pos + 1);
            levelNum = std::stoull(num);
        } else {
            std::cout << "No '-' character found or it's the last character." << std::endl;
        }
        std::vector<std::string> files;
        utils::scanDir(dataDirectory + "/" + level, files);
        for(std::string & file : files){
            std::string filename = dataDirectory;
            filename += "/";
            filename += level;
            filename += "/";
            filename += file;
            f.open(filename, std::ios::in | std::ios::binary);
            if(!f)
                std::cerr << "Open failed!" << '\n';
            uint64_t _timeStamp, keyNum, minKey, maxKey;
            f.read((char *) &_timeStamp, 8);
            f.read((char *) &keyNum, 8);
            f.read((char *) &minKey, 8);
            f.read((char *) &maxKey, 8);
            Header h(_timeStamp, keyNum, minKey, maxKey);
            bool *bloomFilter = new bool [10240 * 8];
            for(long long i = 0;i < 10240 * 8;i += 8){
                char c;
                f.read(&c, 1);
                for(int j = 0;j < 8;++j)
                    bloomFilter[i + j] = (c >> (7 - j)) | 1;
            }
            std::set<Index> index;
            for(uint64_t i = 0;i < keyNum;++i){
                uint64_t key;
                uint32_t offset;
                f.read((char *) &key, 8);
                f.read((char *) &offset, 4);
                index.insert(Index(key, offset));
            }
            caches.insert(Cache(filename, levelNum, h, bloomFilter, index));
            delete []bloomFilter;
            f.close();
        }
    }
}

void KVStore::compaction(uint64_t level1, uint64_t level2) {
    std::cout << "compaction " << level1 << ' ' << level2 << '\n';
    std::string level1_name = dataDirectory + "/level-" + std::to_string(level1);
    std::string level2_name = dataDirectory + "/level-" + std::to_string(level2);
    std::vector<std::string> level1_files;
    std::vector<std::string> level2_files;
    uint64_t fileNum1, fileNum2;
    std::fstream f;
    auto p = directoryType.find(level1);
    if(p == directoryType.end()){
        auto q = directoryType.find((level1 - 1));
        directoryType[level1] = std::pair<uint64_t, Mode>(q->second.first * 2, Leveling);
    }
    p = directoryType.find(level2);
    if(p == directoryType.end()){
        auto q = directoryType.find((level2 - 1));
        directoryType[level2] = std::pair<uint64_t, Mode>(q->second.first * 2, Leveling);
    }
    if(!utils::dirExists(level2_name)){
        utils::mkdir(level2_name.c_str());
    }
    fileNum1 = utils::scanDir(level1_name, level1_files);
    fileNum2 = utils::scanDir(level2_name, level2_files);
    struct Node{
        uint64_t time;
        std::string data;
        Node(uint64_t t, std::string d):time(t), data(std::move(d)){}
    };
    std::map<uint64_t, Node> temp;
    if(directoryType[level1].second == Tiering){
        for(const std::string& file : level1_files){
            std::string filename = level1_name;
            filename += "/";
            filename += file;
            f.open(filename, std::ios::in | std::ios::binary);
            if(!f){
                std::cerr << "Open failed!" << '\n';
            }
            uint64_t time, keyNum;
            f.read((char *)&time, 8);
            f.read((char *)&keyNum, 8);
            for(uint64_t i = 0;i < keyNum;++i){
                f.seekg(32 + 10240 + i * 12);
                uint64_t key;
                uint32_t offset1, offset2;
                std::string data;
                f.read((char *)&key, 8);
                f.read((char *)&offset1, 4);
                if(i != keyNum - 1){
                    f.seekg(32 + 10240 + (i + 1) * 12 + 8);
                    f.read((char *)&offset2, 4);
                    f.seekg(32 + 10240 + keyNum * 12 + offset1);
                    data.resize(offset2 - offset1);
                    f.read(data.data(), offset2 - offset1);
                }
                else{
                    f.seekg( 0, std::ios::end );
                    std::streampos tail = f.tellg();
                    f.seekg(32 + 10240 + keyNum * 12 + offset1, std::ios::beg);
                    std::streampos start = f.tellg();
                    uint32_t size = tail - start;
                    data.resize(size);
                    f.read(data.data(), size);
                }
                auto it = temp.find(key);
                if (it != temp.end()) {
                    if(it->second.time < time){
                        temp.erase(key);
                        temp.insert({key, Node(time, data)});
                    }
                }
                else {
                    temp.insert({key, Node(time, data)});
                }
            }
            f.close();
            utils::rmfile(filename.c_str());
        }
        for (auto it = caches.begin(); it != caches.end(); ) {
            if (it->level == level1) {
                it = caches.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    else{
        std::vector<std::string> remove_files;
        uint64_t fileNum = fileNum1 - directoryType[level1].first;
        std::sort(level1_files.begin(), level1_files.end(), sort_string);
        for(uint64_t i = 0;i < fileNum;++i){
            std::string filename = level1_name;
            filename += "/";
            filename += level1_files[i];
            remove_files.push_back(level1_files[i]);
            f.open(filename, std::ios::in | std::ios::binary);
            if(!f){
                std::cerr << "Open failed!" << '\n';
            }
            uint64_t time, keyNum;
            f.read((char *)&time, 8);
            f.read((char *)&keyNum, 8);
            for(uint64_t j = 0;j < keyNum;++j){
                f.seekg(32 + 10240 + j * 12);
                uint64_t key;
                uint32_t offset1, offset2;
                std::string data;
                f.read((char *)&key, 8);
                f.read((char *)&offset1, 4);
                if(i != keyNum - 1){
                    f.seekg(32 + 10240 + (j + 1) * 12 + 8);
                    f.read((char *)&offset2, 4);
                    f.seekg(32 + 10240 + keyNum * 12 + offset1);
                    data.resize(offset2 - offset1);
                    f.read(data.data(), offset2 - offset1);
                }
                else{
                    f.seekg( 0, std::ios::end );
                    std::streampos tail = f.tellg();
                    f.seekg(32 + 10240 + keyNum * 12 + offset1, std::ios::beg);
                    std::streampos start = f.tellg();
                    uint32_t size = tail - start;
                    data.resize(size);
                    f.read(data.data(), size);
                }
                auto it = temp.find(key);
                if (it != temp.end()) {
                    if(it->second.time < time){
                        temp.erase(key);
                        temp.insert({key, Node(time, data)});
                    }
                }
                else {
                    temp.insert({key, Node(time, data)});
                }
            }
            f.close();
            utils::rmfile(filename.c_str());
        }
        for (auto it = caches.begin(); it != caches.end(); ++it) {
            std::cout << it->level << ' ' << it->filename << '\n';
            if (it->level == level1) {
                for (auto remove_it = remove_files.begin(); remove_it != remove_files.end(); ++remove_it) {
                    if (it->filename == *remove_it) {
                        it = caches.erase(it);
                        remove_it = remove_files.erase(remove_it);
                        --it;
                        --remove_it;
                    }
                }
            }
        }
    }
    if(directoryType[level2].second == Leveling){
        std::vector<std::string> remove_files;
        uint64_t keyMax, keyMin;
        if (!temp.empty()) {
            keyMin = temp.begin()->first;
            keyMax = temp.rbegin()->first;
        }
        else{
            std::cerr << "temp is empty!" << '\n';
        }
        for(const std::string& file : level2_files){
            std::string filename = level2_name;
            filename += "/";
            filename += file;
            f.open(filename, std::ios::in | std::ios::binary);
            if(!f){
                std::cerr << "Open failed!" << '\n';
            }
            uint64_t time, keyNum, keymin, keymax;
            f.read((char *)&time, 8);
            f.read((char *)&keyNum, 8);
            f.read((char *)&keymin, 8);
            f.read((char *)&keymax, 8);
            if(!(keymax > keyMin && keymin < keyMax)){
                f.close();
                continue;
            }
            remove_files.push_back(file);
            for(uint64_t i = 0;i < keyNum;++i){
                f.seekg(32 + 10240 + i * 12);
                uint64_t key;
                uint32_t offset1, offset2;
                std::string data;
                f.read((char *)&key, 8);
                f.read((char *)&offset1, 4);
                if(i != keyNum - 1){
                    f.seekg(32 + 10240 + (i + 1) * 12 + 8);
                    f.read((char *)&offset2, 4);
                    f.seekg(32 + 10240 + keyNum * 12 + offset1);
                    data.resize(offset2 - offset1);
                    f.read(data.data(), offset2 - offset1);
                }
                else{
                    f.seekg( 0, std::ios::end );
                    std::streampos tail = f.tellg();
                    f.seekg(32 + 10240 + keyNum * 12 + offset1, std::ios::beg);
                    std::streampos start = f.tellg();
                    uint32_t size = tail - start;
                    data.resize(size);
                    f.read(data.data(), size);
                }
                auto it = temp.find(key);
                if (it != temp.end()) {
                    if(it->second.time < time){
                        temp.erase(key);
                        temp.insert({key, Node(time, data)});
                    }
                }
                else {
                    temp.insert({key, Node(time, data)});
                }
            }
            f.close();
            utils::rmfile(filename.c_str());
            for (auto it = caches.begin(); it != caches.end();++it) {
                if (it->level == level2) {
                    for (auto remove_it = remove_files.begin(); remove_it != remove_files.end(); ++remove_it) {
                        if (it->filename == *remove_it) {
                            it = caches.erase(it);
                            remove_it = remove_files.erase(remove_it);
                            --it;
                            --remove_it;
                        }
                    }
                }
            }
        }
    }
    uint64_t bytes = 32 + 10240;
    uint64_t maxTimeStamp = 0;
    SkipList store;
    for(auto & it : temp){
        uint64_t key = it.first;
        uint64_t time = it.second.time;
        std::string data = it.second.data;
        if(data == "~DELETED~" && level2 == directoryType.size())
            continue;
        if(bytes + 12 + data.size() > MEM_TABLE_MAX){
            SSTable ssTable(store, maxTimeStamp, dataDirectory);
            ssTable.store("level-" + std::to_string(level2));
            caches.insert(Cache(store, maxTimeStamp, level2));
            store.clear();
            bytes = 32 + 10240;
            maxTimeStamp = 0;
        }
        bytes += 12 + data.size();
        if(time > maxTimeStamp)
            maxTimeStamp = time;
        store.insert(key, data);
    }
    if(store.size() != 0){
        SSTable ssTable(store, maxTimeStamp, dataDirectory);
        ssTable.store("level-" + std::to_string(level2));
        caches.insert(Cache(store, maxTimeStamp, level2));
    }
    level2_files.clear();
    fileNum2 = utils::scanDir(level2_name, level2_files);
    if(fileNum2 > directoryType[level2].first){
        compaction(level2, level2 + 1);
    }
}

