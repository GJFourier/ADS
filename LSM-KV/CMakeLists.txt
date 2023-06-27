cmake_minimum_required(VERSION 3.24)
project(LSMTree)

set(CMAKE_CXX_STANDARD 17)

#add_executable(LSMTree main.cpp kvstore.h kvstore.cc MurmurHash3.h skipList.h skipList.cpp bloomFilter.cpp bloomFilter.h SSTable.cpp SSTable.h utils.h cache.cpp cache.h)
add_executable(LSMTree correctness.cc kvstore.h kvstore.cc MurmurHash3.h skipList.h skipList.cpp bloomFilter.cpp bloomFilter.h SSTable.cpp SSTable.h utils.h cache.cpp cache.h)
#add_executable(LSMTree persistence.cc kvstore.h kvstore.cc MurmurHash3.h skipList.h skipList.cpp bloomFilter.cpp bloomFilter.h SSTable.cpp SSTable.h utils.h cache.cpp cache.h)

