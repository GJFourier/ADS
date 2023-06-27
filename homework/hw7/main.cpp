#include <iostream>
#include <fstream>
#include <vector>
#include "windows.h"

template <typename T>
T quickSelect(std::vector<T> &data, int rank){
    for(int lo = 0, hi = data.size() - 1;lo < hi;){
        int i = lo, j = hi;
        T pivot = data[lo];
        while (i < j){
            while (i < j && pivot <= data[j])
                j--;
            data[i] = data[j];
            while (i < j && data[i] <= pivot)
                i++;
            data[j] = data[i];
        }
        data[i] = pivot;
        if (rank <= i)
            hi = i - 1;
        if(i <= rank)
            lo = i + 1;
    }
    return data[rank];
}

template <typename T>
T QlinearSelect(std::vector<T> &data, int rank, int start, int end, int Q){
//    std::cout << rank << " " << start << " " << end << " " << Q << '\n';
    if(end - start < Q){
        for(int i = start;i <= start + rank;++i){
            T min = data[i];
            int mnum = i;
            for(int j = i;j <= end;++j){
                if(data[j] < min) {
                    min = data[j];
                    mnum = j;
                }
            }
            data[mnum] = data[i];
            data[i] = min;
        }
        return data[start + rank];
    }
    std::vector<T> subdata;
    int i;
    for(i = 0;i * Q + Q - 1 <= end;++i){
        subdata.push_back(QlinearSelect(data, (Q - 1) / 2, i * Q, i * Q + Q - 1, Q));
    }
    if(i * Q <= end)
        subdata.push_back(QlinearSelect(data, (end - i * Q) / 2, i * Q, end, Q));
    T div = QlinearSelect(subdata, (subdata.size() - 1) / 2, 0, subdata.size() - 1, Q);
//    std:: cout << div << '\n';
    std::vector<T> less;
    std::vector<T> equal;
    std::vector<T> great;
    for(i = start;i <= end;++i){
        if(data[i] < div)
            less.push_back(data[i]);
        else if (data[i] > div)
            great.push_back(data[i]);
        else
            equal.push_back(data[i]);
    }
    if(rank < less.size())
        return QlinearSelect(less, rank, 0, less.size() - 1, Q);
    else if(rank < less.size() + equal.size())
        return div;
    else
        return QlinearSelect(great, rank - less.size(), 0, great.size() - 1, Q);
}

template <typename T>
T linearSelect(std::vector<T> &data, int rank, int Q){
    return QlinearSelect(data, rank, 0, data.size() - 1, Q);
}

int main() {
    LARGE_INTEGER t1, t2, tc;
    double time;
    int size[4] = {100, 500, 1000, 10000};
    int Q[5]= {3, 5, 8, 12, 20};
    int num;
    for(int i = 0;i < 4;++i){
        // ÂÒÐò
        std::cout << "size:" << size[i] << '\n';
        std::ifstream file(std::string("../input/") + std::to_string(i + 1));
        std::vector<int> data;
        for(int j = 0;j < size[i];++j){
            file >> num;
            data.push_back(num);
        }
        std::cout << "ÂÒÐò:" << '\n';
        std::cout << "quickSelect:" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        quickSelect(data, (size[i] - 1) * 1 / 4);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/4 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        quickSelect(data, (size[i] - 1) / 2);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/2 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        quickSelect(data, (size[i] - 1) * 3 / 4);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 3/4 " << time << "ms" << '\n';

        std::cout << "linearSelect:" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        linearSelect(data, (size[i] - 1) * 1 / 4, 5);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/4 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        linearSelect(data, (size[i] - 1) / 2, 5);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/2 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        linearSelect(data, (size[i] - 1) * 3 / 4, 5);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 3/4 " << time << "ms" << '\n';

        //

        file.open(std::string("../input/") + std::to_string(i + 5));
        for(int j = 0;j < size[i];++j){
            file >> num;
            data.push_back(num);
        }
        std::cout << "Ë³Ðò:" << '\n';
        std::cout << "quickSelect:" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        quickSelect(data, (size[i] - 1) * 1 / 4);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/4 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        quickSelect(data, (size[i] - 1) / 2);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/2 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        quickSelect(data, (size[i] - 1) * 3 / 4);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 3/4 " << time << "ms" << '\n';
        std::cout << "linearSelect:" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        linearSelect(data, (size[i] - 1) * 1 / 4, 5);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/4 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        linearSelect(data, (size[i] - 1) / 2, 5);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 1/2 " << time << "ms" << '\n';
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);
        linearSelect(data, (size[i] - 1) * 3 / 4, 5);
        QueryPerformanceCounter(&t2);
        time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
        std::cout << "rank: 3/4 " << time << "ms" << '\n';
    }

    std::cout << "linearSelect¶ÔQµÄ±È½Ï\n";
    for(int i = 0;i < 4;++i){
        // ÂÒÐò1 Ë³Ðò2
        std::ifstream file1(std::string("../input/") + std::to_string(i + 1));
        std::ifstream file2(std::string("../input/") + std::to_string(i + 5));
        std::vector<int> data1, data2;
        for(int j = 0;j < size[i];++j){
            file1 >> num;
            data1.push_back(num);
            file2 >> num;
            data2.push_back(num);
        }
        std::cout << "size: " << size[i] << '\n';
        for(int j = 0;j < 5;++j){
            std::cout << "Q:" << Q[j] << '\n';
            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);
            linearSelect(data1, (size[i] - 1) / 2, Q[j]);
            QueryPerformanceCounter(&t2);
            time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
            std::cout << "ÂÒÐò:" << time << "ms\n";
            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);
            linearSelect(data2, (size[i] - 1) / 2, Q[j]);
            QueryPerformanceCounter(&t2);
            time = 1e3 * (double) (t2.QuadPart - t1.QuadPart) / (double) tc.QuadPart;
            std::cout << "Ë³Ðò:" << time << "ms\n";
        }
    }
    return 0;
}
