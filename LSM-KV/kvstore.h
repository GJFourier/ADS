#pragma once

#include "kvstore_api.h"
#include "skipList.h"
#include "bloomFilter.h"
#include "SSTable.h"
#include "cache.h"
#include "utils.h"
#include <map>

#define MEM_TABLE_MAX (1024 * 1024 * 2)

class KVStore : public KVStoreAPI {
	// You can add your implementation here
private:
    enum Mode{
        Tiering,
        Leveling
    };
    std::string dataDirectory;
    SkipList memTable;
    uint64_t timeStamp;
    std::multiset<Cache> caches;
    std::map<uint64_t, std::pair<uint64_t, Mode>> directoryType;

public:
	KVStore(const std::string &dir);

	~KVStore();

	void put(uint64_t key, const std::string &s) override;

	std::string get(uint64_t key) override;

	bool del(uint64_t key) override;

	void reset() override;

	void scan(uint64_t key1, uint64_t key2, std::list<std::pair<uint64_t, std::string> > &list) override;

    bool ifTrans();

    void toSSTable();

    std::string findInSSTable(uint64_t key);

    void readConfig(const std::string& configName);

    void load();

    void compaction(uint64_t level1, uint64_t level2);
};
