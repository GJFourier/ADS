#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 定义一个Graph类，用于表示有向无环图
class Graph {
    
private:
    // 用一个vector来表示图的邻接表
    vector<vector<int>> adj_list;


public:
    // 构造函数，用于创建具有指定节点数的图
    Graph(int num_nodes) : adj_list(num_nodes) {}

    // 添加一条从u到v的有向边
    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
    }

    // 执行拓扑排序，并返回排序后的节点序列
    vector<int> topological_sort() {
        // 创建一个vector用于存储每个节点的入度数
        vector<int> in_degree(adj_list.size(), 0);

        // 统计每个节点的入度数
        for (int i = 0; i < adj_list.size(); i++) {
            for (int j = 0; j < adj_list[i].size(); j++) {
                in_degree[adj_list[i][j]]++;
            }
        }

        // TODO: 将入度数为0的节点加入队列q
        queue<int> q;
        for(int i=0;i < adj_list.size();++i){
            if(in_degree[i] == 0){
                q.push(i);
            }
        }
       
        // 创建一个vector用于存储排序后的节点序列
        vector<int> res;

        // 不断从队列中取出节点，并将其加入结果序列中
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            res.push_back(node);

            // TODO:将当前节点的所有邻居节点的入度数减1
            // 如果减1后邻居节点的入度数变为0，则将其加入队列
            for(int i=0;i<adj_list[node].size();++i){
                --in_degree[adj_list[node][i]];
                if(in_degree[adj_list[node][i]] == 0)
                    q.push(adj_list[node][i]);
            }
        }

        // 如果结果序列的长度小于节点数，则说明图中存在环
        // 返回一个空序列表示无法完成拓扑排序
        if (res.size() < adj_list.size()) {
            return vector<int>();
        }

        // 返回排序后的节点序列
        return res;
    }


};

// 示例代码，创建一个图并执行拓扑排序
int main() {
//    // 创建一个包含5个节点的图
//    Graph graph(5);
//
//    // 添加一些有向边
//    graph.add_edge(0, 1);
//    graph.add_edge(0, 2);
//    graph.add_edge(1, 3);
//    graph.add_edge(2, 3);
//    graph.add_edge(3, 4);
//    vector<int> result = graph.topological_sort();
//    for (int data:result) {
//        std::cout << data << ' ';
//    }
//    return 0;
    Graph graph(15);
    graph.add_edge(1, 5);
    graph.add_edge(1, 6);
    graph.add_edge(1, 12);
    graph.add_edge(2, 3);
    graph.add_edge(2, 5);
    graph.add_edge(2, 9);
    graph.add_edge(3, 6);
    graph.add_edge(3, 7);
    graph.add_edge(3, 10);
    graph.add_edge(4, 3);
    graph.add_edge(4, 7);
    graph.add_edge(4, 14);
    graph.add_edge(5, 8);
    graph.add_edge(6, 9);
    graph.add_edge(6, 13);
    graph.add_edge(7, 6);
    graph.add_edge(9, 8);
    graph.add_edge(10, 11);
    graph.add_edge(10, 12);
    graph.add_edge(11, 14);
    graph.add_edge(13, 10);
    vector<int> result = graph.topological_sort();
    for(int i = 1;i < 15;++i){
        std::cout << result[i] << ' ';
    }
}
