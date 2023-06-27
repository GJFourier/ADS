#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

using namespace std;

// 计算多项式的某一项
double computeTerm(double x, int power) {
    return pow(x, power);
}

// 并行计算多项式的一部分
void computePolynomial(vector<double>& coefficients, double x, int start, int end, vector<double>& results) {
    for (int i = start; i <= end; i++) {
        double term = coefficients[i] * computeTerm(x, i);
        results[i] = term;
    }
}

// 并行计算多项式
vector<double> parallelComputePolynomial(vector<double>& coefficients, double x) {
    int degree = coefficients.size() - 1;
    vector<double> results(degree + 1);

    // 获取可用的线程数
    int numThreads = thread::hardware_concurrency();
    vector<thread> threads(numThreads);

    // 平均划分多项式的系数，分配给每个线程进行计算
    int step = (degree + 1) / numThreads;
    int start = 0;
    int end = step - 1;

    for (int i = 0; i < numThreads; i++) {
        // 最后一个线程处理剩余的项
        if (i == numThreads - 1) {
            end = degree;
        }

        threads[i] = thread(computePolynomial, ref(coefficients), x, start, end, ref(results));

        start += step;
        end += step;
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    return results;
}

// 测试
int main() {
    vector<double> coefficients = {1, 2, 3, 4, 5};  // 多项式系数
    double x = 3;  // 输入值

    // 并行
    vector<double> results1 = parallelComputePolynomial(coefficients, x);

    // 串行
    vector<double> results2;
    results2.resize(coefficients.size());
    computePolynomial(coefficients, x, 0, coefficients.size(), results2);

    // 打印计算结果
    cout << "Parallel: ";
    for (int i = 0; i < results1.size(); i++) {
        cout << results1[i] << " ";
    }
    cout << endl;

    cout << "Serial: ";
    for (int i = 0; i < results2.size(); i++) {
        cout << results2[i] << " ";
    }
    cout << endl;

    return 0;
}
//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <thread>
//#include <mutex>
//
//using namespace std;
//
//// 计算多项式的某一项
//double computeTerm(double x, int power) {
//    return pow(x, power);
//}
//
//// 并行计算多项式的一部分
//void computePolynomial(vector<double>& coefficients, double x, int start, int end, vector<double>& results, mutex& mtx) {
//    for (int i = start; i <= end; i++) {
//        double term = coefficients[i] * computeTerm(x, i);
//
//        lock_guard<mutex> lock(mtx);  // 互斥锁保护共享数据
//        results[i] = term;
//    }
//}
//
//// 并行计算多项式
//vector<double> parallelComputePolynomial(vector<double>& coefficients, double x) {
//    int degree = coefficients.size() - 1;
//    vector<double> results(degree + 1);
//
//    int numThreads = thread::hardware_concurrency();
//    vector<thread> threads(numThreads);
//    mutex mtx;  // 互斥锁
//
//    int step = (degree + 1) / numThreads;
//    int start = 0;
//    int end = step - 1;
//
//    for (int i = 0; i < numThreads; i++) {
//        if (i == numThreads - 1) {
//            end = degree;
//        }
//
//        threads[i] = thread(computePolynomial, ref(coefficients), x, start, end, ref(results), ref(mtx));
//
//        start += step;
//        end += step;
//    }
//
//    for (auto& t : threads) {
//        t.join();
//    }
//
//    return results;
//}

//// 测试
//int main() {
//    vector<double> coefficients = {1, 2, 3, 4, 5};  // 多项式系数
//    double x = 3;  // 输入值
//
//    vector<double> results1 = parallelComputePolynomial(coefficients, x);
//
//    vector<double> results2;
//    results2.resize(coefficients.size());
//
//    mutex mtx;  // 互斥锁
//    computePolynomial(coefficients, x, 0, coefficients.size() - 1, results2, mtx);  // 修正结束索引
//
//    cout << "Parallel: ";
//    for (int i = 0; i < results1.size(); i++) {
//        cout << results1[i] << " ";
//    }
//    cout << endl;
//
//    cout << "Serial: ";
//    for (int i = 0; i < results2.size(); i++) {
//        cout << results2[i] << " ";
//    }
//    cout << endl;
//
//    return 0;
//}
