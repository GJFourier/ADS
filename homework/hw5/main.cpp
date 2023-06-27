#include <iostream>
#include <algorithm>
//#include <cstdlib>
//#include <ctime>
#include<windows.h>
#include <fstream>
#include "rbtree.h"
#include "avl_tree.h"
#include "skiplist.h"

int main() {

//    srand(time(nullptr));
    LARGE_INTEGER t1, t2, tc;
    double time;
    int size[5] = {50, 100, 500, 1000, 10000};
    int size_s[5] = {20, 40, 200, 400, 4000};
    int size_e[5] = {30, 60, 300, 600, 6000};
    int data[10000];
    // 插入
    for (int i = 0; i < 5; ++i) {
//        Skiplist skipList;
//        AVL<int> avl;
        RBTree::RedBlackTree RBtree;
        std::string s = "input" + std::to_string(i + 6) + ".txt";
        std::fstream File("../input/" + s);
//        std::cout << avl.total << '\n';

        for (int j = 0; j < size[i]; ++j) {
            int num;
            File >> num;
//            skipList.insert(num, num);
//            std::cout << num << '\n';
            RBtree.insert(num);
//            avl.insert(num);
            data[j] = num;
        }
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        for(int j = size_s[i];j < size_e[i];++j){
//            avl.search(data[j]);
//            skipList.find(data[j]);
            RBtree.find(data[j]);
        }
        QueryPerformanceCounter(&t2);
//        std::cout << avl.total << '\n';
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "size:" << size[i] << ' ' << "time:" << time << '\n';
        File.close();
    }

    // 查找
}

// 生成数据
//    for(int i = 0;i < 5;++i){
//        bool flag[100000] = {false};
//        std::string s = "input" + std::to_string(i + 1) + ".txt";
//        std::fstream File("../input/" + s);
//        for(int j = 0;j < size[i];++j){
//            int num = rand() % (5 * size[i]) + 1;
//            if(flag[num]){
//                --j;
//                continue;
//            }
//            flag[num] = true;
//            File << num << '\n';
//        }
//    }
//    for(int i = 0;i < 5;++i){
//        std::string s = "input" + std::to_string(i + 1) + ".txt";
//        std::fstream File("../input/" + s);
//        int * data = new int [size[i]];
//        int num;
//        for(int j = 0;j < size[i];++j){
//            File >> num;
//            data[j] = num;
//        }
//        File.close();
//        s = "input" + std::to_string(i + 6) + ".txt";
//        File.open("../input/" + s);
//        std::sort(data, data + size[i]);
//        for(int j = 0;j < size[i];++j){
//            File << data[j] << '\n';
//        }
//        File.close();
//    }
