#include <iostream>
#include<future>
#include <mutex>

using namespace std;

int num_threads_max = 6;  // 使用6个线程来计算斐波那契数列
int num_threads = 1;
mutex mtx;
// 计算斐波那契数列第n项
int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if(num_threads >= num_threads_max)
        return fibonacci(n - 1) + fibonacci(n - 2);
    mtx.lock();
    num_threads += 2;
    mtx.unlock();
    int res = async(fibonacci,n - 1).get() + async(fibonacci,n - 2).get();
    mtx.lock();
    num_threads -= 2;
    mtx.unlock();
    return res;
}

int main() {
    int n = 30;  // 计算斐波那契数列的第n项
    // 分配任务给每个线程
    int res = async(fibonacci, n).get();
    cout << res;
    return 0;
}
