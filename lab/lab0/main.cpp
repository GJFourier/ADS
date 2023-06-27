#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "windows.h"

#include "SparseMatrix.h"

const int num_case = 4;
std::string grade_cases[num_case];

//void compare_res(std::string test_case) {
//  std::ifstream stu, ans;
//  std::stringstream errstring;
//  std::string s_stu, s_ans;
//  int lineno = 0;
//
//  std::string name = "output/" + test_case + ".yourans";
//  stu.open(name, std::ios::in);
//  if (!stu.is_open()) {
//    throw std::runtime_error("Failed to open file: " + name);
//  }
//
//  name = "output/" + test_case + ".ans";
//  ans.open(name, std::ios::in);
//  if (!ans.is_open()) {
//    throw std::runtime_error("Failed to open file: " + name);
//  }
//
//  while (getline(stu, s_stu) && getline(ans, s_ans)) {
//    lineno++;
//    if (s_stu != s_ans) {
//      errstring << "line " << lineno << " mismatch: " << s_stu << "(stu) vs. "
//                << s_ans << "(ans)" << std::endl;
//      throw std::runtime_error(errstring.str());
//    }
//  }
//  if(getline(stu, s_stu)){
//      if(s_stu!=""){
//          errstring << "row num mis match";
//          throw std::runtime_error(errstring.str());
//      }
//  }
//  if(std::getline(ans, s_ans)){
//      errstring << "输出内容缺行" << s_ans;
//      throw std::runtime_error(errstring.str());
//  }
//
//  stu.close();
//  ans.close();
//}
//
//void grade_test(std::string test_case) {
//  SparseMatrix left = SparseMatrix("input/" + test_case + ".left");
//  SparseMatrix right = SparseMatrix("input/" + test_case + ".right");
//  SparseMatrix ans = left * right;
//  ans.to_file("output/" + test_case + ".yourans");
//
//  try {
//    compare_res(test_case);
//  } catch (std::exception &e) {
//    throw std::runtime_error("Failed to pass " + test_case + ":\n\t" +
//                             e.what());
//  }
//}

void test(int n,double e){
    int **mat_nor1 = new int*[n];
    int **mat_nor2 = new int*[n];
    int **mat_nor3 = new int*[n];
    LARGE_INTEGER t1, t2, tc;
    double time;
    for(int i = 0;i < n;++i){
        mat_nor1[i] = new int[n];
        mat_nor2[i] = new int[n];
        mat_nor3[i] = new int[n];
        for(int j = 0;j < n;++j){
            mat_nor1[i][j] = 0;
            mat_nor2[i][j] = 0;
            mat_nor3[i][j] = 0;
        }
    }
    SparseMatrix mat_spa1, mat_spa2, mat_spa3;
    mat_spa1.setRow(n);
    mat_spa1.setCol(n);
    mat_spa2.setRow(n);
    mat_spa2.setCol(n);
    if(e < 0.5){
        for(int i = 0;i < e * n * n;++i){
            int x = rand() % n;
            int y = rand() % n;
            int data = (rand() % 20) + 1;
            if(mat_nor1[x][y] == 0){
                mat_nor1[x][y] = data;
                mat_spa1.insert(x, y, data);
            }
            else {
                --i;
            }
        }
        for(int i = 0;i < e * n * n;++i){
            int x = rand() % n;
            int y = rand() % n;
            int data = (rand() % 20) + 1;
            if(mat_nor2[x][y] == 0){
                mat_nor2[x][y] = data;
                mat_spa2.insert(x, y, data);
            }
            else{
                --i;
            }
        }
    }
    else{
        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                mat_nor1[i][j] = rand() % 20 + 1;
                mat_nor2[i][j] = rand() % 20 + 1;
            }
        }
        for(int i = 0;i < n * n - e * n * n;++i){
            int x = rand() % n;
            int y = rand() % n;
            if(mat_nor1[x][y] != 0){
                mat_nor1[x][y] = 0;
            }
            else{
                --i;
            }
        }
        for(int i = 0;i < n * n - e * n * n;++i){
            int x = rand() % n;
            int y = rand() % n;
            if(mat_nor2[x][y] != 0){
                mat_nor2[x][y] = 0;
            }
            else{
                --i;
            }
        }
        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                if(mat_nor1[i][j] != 0){
                    mat_spa1.insert(i, j, mat_nor1[i][j]);
                }
                if(mat_nor2[i][j] != 0){
                    mat_spa2.insert(i, j, mat_nor2[i][j]);
                }
            }
        }
    }

    std::cout << "size:" << n << ' ' << "sparseness:" << e << '\n';
    // 普通矩阵乘法
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 0;i < n;++i){
        for(int j = 0;j < n;++j){
            for(int k = 0;k < n;++k){
                mat_nor3[i][j] += mat_nor1[i][k] * mat_nor2[k][j];
            }
        }
    }
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    std::cout << "time:" << '\n' << "nor:" << time << "ms" << '\n';

    // 稀疏矩阵乘法
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    mat_spa3 = mat_spa1 * mat_spa2;
    QueryPerformanceCounter(&t2);
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    std::cout << "spa:" << time << "ms" << '\n';
//    for(int i = 0;i < n;++i){
//        for(int j=0;j < n;++j){
//            std::cout << mat_nor3[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
    std::cout << "size:" << '\n' << "nor:" << n * n * sizeof(int) << "bytes" << '\n';
    std::cout << "spa:" << 3 * mat_spa3.num * sizeof(int) << "bytes" << '\n';
    std::cout << '\n';
    std::string str = "size " + std::to_string(n) + " " + "sparseness " + std::to_string(e) + ".txt";
    mat_spa3.to_file(str);
    for(int i = 0;i < n;++i){
        delete []mat_nor1[i];
    }
    delete []mat_nor1;
    for(int i = 0;i < n;++i){
        delete []mat_nor2[i];
    }
    delete []mat_nor2;
    for(int i = 0;i < n;++i){
        delete []mat_nor3[i];
    }
    delete []mat_nor3;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int size[6] = {10, 25, 50, 100, 200, 500};
    double e[7] = {0.01, 0.05, 0.1, 0.2, 0.5, 0.75, 1};
    for(int i = 0;i < 6;++i){
        for(int j = 0;j < 7;++j){
            test(size[i], e[j]);
        }
    }
//  for (int i = 0; i < num_case; i++) {
//    grade_cases[i] = "test" + std::to_string(i + 1);
//  }
//  try {
//    if (argc == 2) {
//      grade_test(argv[1]);
//    } else if (argc == 1) {
//      for (auto test_case : grade_cases) {
//        grade_test(test_case);
//      }
//    } else {
//      throw std::runtime_error("[usage]: ./sparsematrix [test_case_name]");
//    }
//  } catch (std::exception &e) {
//    std::cerr << e.what() << std::endl;
//    return 1;
//  }
//
//  std::cout << "Congratulations! You've passed all test(s)." << std::endl;
//  return 0;
}