#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include<map>
#include<mutex>
#include<condition_variable>
#include <unistd.h>
#include <windows.h>

using namespace std;

int n = 10;
int m = 30;

struct Edge {
    int src, dest, weight;
    Edge(int a, int b , int c){
        src = a;
        dest = b;
        weight = c;
    }
};
class UnionFind {
    std::vector<int> parent;
    std::vector<int> rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        // 初始化每个节点的父节点为自身
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // 查找节点的根节点
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // 合并两个集合
    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};
class edge{
public:
    edge() {}
    edge(int a,int b,int c)
            :v1(a),v2(b),w(c),next(NULL) {}
    int v1,v2;
    int w,tid;
    edge* next;
};
class vertex {
public:
    vertex(int v)
            :vid(v),next(NULL) {}
    int vid;
    edge* next;
};

const int thread_num = 16;//线程数量
vector<vertex> graph;//图邻接表
vector<edge> mst;//结果集
vector<thread> subthreads;//线程向量
multimap<int,edge> edge_queue;//全局队列
mutex mut;//互斥锁
mutex mut2, mut3;
condition_variable cond_v[thread_num];//条件变量
bool isfinished = false;

// 生成无向联通图
vector<vector<int>> generateConnectedGraph(int n, int m , vector<Edge> &edges) {
    vector<vector<int>> graph(n, vector<int>(n, 0));  // 邻接矩阵表示图
    srand(time(0));  // 设置随机数种子

    // 创建连通图
    for (int i = 1; i < n; i++) {
        int j = rand() % i;  // 随机选择一个已存在的节点
        int weight = rand() % 10 + 1;  // 随机生成边的权重（1到10之间的整数）
        graph[i][j] = graph[j][i] = weight;  // 添加边及其权重
        edges.emplace_back(i, j ,weight);
    }

    // 添加额外的边，直到达到m条边
    int edgeCount = n - 1;
    while (edgeCount < m) {
        int u = rand() % n;  // 随机选择一个节点
        int v = rand() % n;  // 随机选择另一个节点

        if (u != v && graph[u][v] == 0) {  // 确保节点不同且边不存在
            int weight = rand() % 10 + 1;  // 随机生成边的权重（1到10之间的整数）
            graph[u][v] = graph[v][u] = weight;  // 添加边及其权重
            edges.emplace_back(u, v ,weight);
            edgeCount++;
        }
    }

    return graph;
}
// 将图信息输出到文本文件
void writeGraphToFile(const vector<vector<int>>& graph, int n, int m) {
    // string filename = "graph_info.txt";  // 输出文件名

    string filename = to_string(n)+"_"+to_string(m)+".txt";
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Failed to create file: " << filename << endl;
        return;
    }

    // 写入顶点数和边数
    outFile << n << " " << m << endl;

    // 写入边的信息
    for (int i = 0; i < graph.size(); i++) {
        for (int j = i + 1; j < graph[i].size(); j++) {
            if (graph[i][j] > 0) {
                outFile << i << " " << j << " " << graph[i][j] << endl;
            }
        }
    }

    outFile.close();
}
// 比较函数
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}
// 串行算法
void kruskalMST(vector<Edge> edges, int numVertices) {
    LARGE_INTEGER t1, t2, tc;
    double time;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind uf(numVertices);

    vector<Edge> mst;  // 最小生成树的边集合
    int mstWeight = 0;      // 最小生成树的总权重


    for (const auto& edge : edges) {
        int src = edge.src;
        int dest = edge.dest;
        int weight = edge.weight;

        // 如果加入这条边不会形成环，则加入最小生成树
        if (uf.find(src) != uf.find(dest)) {
            mst.push_back(edge);
            mstWeight += weight;
            uf.merge(src, dest);
        }
    }
    // 结束计时
    QueryPerformanceCounter(&t2);
    // 计算执行时间

    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    cout << "Execution time:" << time << "ms\n";

//    // 输出最小生成树的边及总权重
//    cout << "Minimum Spanning Tree Edges:" << endl;
//    for (const auto& edge : mst) {
//        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << endl;
//    }
//    cout << '\n';
}

void output() {
    for (int i = 0; i < mst.size(); i++)
        cout << mst[i].v1 << " -- " << mst[i].v2 << " : " << mst[i].w << endl;
}

void construct(){
    std::ifstream inFile(to_string(n) + "_" + to_string(m) + ".txt");
    int v_num,a_num;
    inFile >> v_num >> a_num;
    for (int i = 0; i < v_num; i++)
        graph.push_back(vertex(i));
    for (int i = 0; i < a_num; i++){
        edge *temp1 = new edge(), *temp2;
        // cin >> temp1->v1 >> temp1->v2 >> temp1->w;
        inFile >> temp1->v1 >> temp1->v2 >> temp1->w;
        // cout << temp1->v1 << temp1->v2 << temp1->w;
        temp2 = new edge(*temp1);
        temp1->next = graph[temp1->v1 ].next;
        graph[temp1->v1 ].next = temp1;
        temp2->next = graph[temp2->v2 ].next;
        graph[temp2->v2 ].next = temp2;
    }
}

void send_edge(multimap<int,edge>& m, int i) {
    if (!m.empty()) {
        edge_queue.insert(*(m.begin()));
        // cout << "thread "<<i<<" insert "<<m.begin()->second.v1 <<" "<<m.begin()->second.v2<<endl;
        // cout << edge_queue.size()<<endl;
        m.erase(m.begin());
    }
}
//线程函数，执行“部分算法”
void subthread_func(vector<vertex> v,int tid){
    // cout << "test"<<endl;
    multimap<int,edge> e;//用于排序
    // cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++){
        edge* temp = v[i].next;
        while (temp != NULL){
            temp->tid = tid;
            e.insert(pair<int,edge>(temp->w,*temp));
            temp = temp->next;
        }
    }
    //  cout <<tid<< " insert ok "<<e.size()<<endl;
    unique_lock<mutex> lk(mut);

    send_edge(e,tid);
    while (true){
        cond_v[tid].wait(lk);
        // cout << "wait" << endl;
        if (isfinished){
            return;
        }
        send_edge(e,tid);
    }
}

void partition() {
    vector<vertex> temp[thread_num];
    for (int i = 0; i < graph.size(); i++)
        temp[i % thread_num].push_back(graph[i]);
    for (int i = 0; i < thread_num; i++)
        subthreads.push_back(thread(subthread_func,temp[i],i));
}

void add_edge(edge e,map<int,int>& i,map<int,vector<int>>& rev_i){
    mst.push_back(e);
    // cout << "push " << e.v1 <<" "<<e.v2<<endl;
    int cid1 = i[e.v1],cid2 = i[e.v2];
    if (cid1 == -1 && cid2 == -1){
        int cid = rev_i.size() + 1;
        vector<int> temp;
        temp.push_back(e.v1);
        temp.push_back(e.v2);
        rev_i[cid] = temp;
        i[e.v1] = cid;
        i[e.v2] = cid;
    }
    else if (cid1 == -1){
        i[e.v1] = cid2;
        rev_i[cid2].push_back(e.v1);
    }
    else if (cid2 == -1){
        i[e.v2] = cid1;
        rev_i[cid1].push_back(e.v2);
    }
    else if (rev_i[cid1].size() <= rev_i[cid2].size()){
        for (int k = 0; k < rev_i[cid1].size(); k++){
            i[rev_i[cid1][k]] = cid2;
            rev_i[cid2].push_back(rev_i[cid1][k]);
        }
        rev_i.erase(cid1);
    }
    else{
        for (int k = 0; k < rev_i[cid2].size(); k++){
            i[rev_i[cid2][k]] = cid1;
            rev_i[cid1].push_back(rev_i[cid2][k]);
        }
        rev_i.erase(cid2);
    }
}

void kruskal(){
    LARGE_INTEGER t1, t2, tc;
    double time;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    map<int,int> index;
    map<int,vector<int>> rev_index;
    for (int i = 0; i < graph.size(); i++){
        index[i] = -1;
    }
    while (mst.size() < graph.size() - 1){
        unique_lock<mutex> lk(mut);
        // cout << "loop"<<endl;
        if (edge_queue.empty())
            // break;
        {
            // cout << "is empty" << endl;

            lk.unlock();
            for (int i = 0; i < thread_num; i++){
                cond_v[i].notify_all();
            }
            continue;
        }
        pair<int,edge> temp = *(edge_queue.begin());
        edge_queue.erase(edge_queue.begin());
        lk.unlock();
        cond_v[temp.second.tid].notify_all();

        if (index[temp.second.v1] != index[temp.second.v2] ||
            index[temp.second.v1] == -1)
            add_edge(temp.second,index,rev_index);
    }
    isfinished = true;
    for (int i = 0; i < thread_num; i++){
        cond_v[i].notify_all();
        subthreads[i].join();
    }
    QueryPerformanceCounter(&t2);
    // 计算执行时间
    time = 1e3 * (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;
    cout << "Execution time:" << time << "ms\n";
}

int main() {
    int point_num[3] = {2000, 5000, 10000};
    int edge_num[3] = {10000, 100000, 1000000};
    int i = 2;
    int j = 2;
    n = point_num[i];
    m = edge_num[j];
    cout << "num of point and edge:" << n << ' ' << m << '\n';
    vector<Edge> edges;
    vector<vector<int>> _graph = generateConnectedGraph(n, m, edges);
    writeGraphToFile(_graph, n, m);
    kruskalMST(edges, n);

    construct();//构造图的邻接表
    partition();//图的划分，创建并发进程，执行“部分算法”
    kruskal();//全局进程执行“仲裁算法”
//    output();//结果输出

    return 0;
}
