#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>
std::vector<int> rank;
class Graph {
public:
    struct Line{
        int node;
        int lower;
        int upper;
        int T;
        int step;
        Line(int a=0, int b=0, int c=0, int d=0){
            node = a;
            lower = b;
            upper = c;
            step = d;
            if(d != 0)
                T = (c - b) / d;
        }
        int time(int t){
            if(T == 0)
                return lower;
            if(t / T % 2 == 0)
                return upper - step * (t % T);
            else
                return lower + step * (t % T);
        }
    };
    std::map<int, std::vector<Line>> adjacency_list;
    int time;
    int current_time;
    int start_time;
    int arrive_time;
    int min_time;
    int size;
    int step;
    Graph(){
        time = 0;
        current_time = 0;
        start_time = 0;
        arrive_time = 0;
        min_time = INT_MAX;
    }
    void add_vertex(int vertex) {
        adjacency_list[vertex] = {};
    }
    void add_edge(int from, Line to) {
        adjacency_list[from].push_back(to);
    }
    void solve(){
//        std::cout << 1 << '\n';
//        std::cout << adjacency_list.size() << '\n';
        while(time < min_time) {
//            std::cout << "time:" << time << '\n';
            std::vector<std::set<int>> timetable(size, std::set<int>{});
            timetable[0].insert(time);
            for (int j = 0;j < size;++j){
                int node = rank[j];
                for (auto t: timetable[node]) {
                    for (auto & k : adjacency_list[node]) {
                        current_time = t + k.time(t);
                        if (current_time < min_time)
                            timetable[k.node].insert(current_time);
                    }
                }
            }
            int min = INT_MAX;
            for(int t : timetable[size-1]){
                if (t < min)
                    min = t;
//                std::cout << t << ' ';
            }
//            std::cout << '\n';
            if(min < min_time){
                start_time = time;
                arrive_time = min;
                min_time = min;
            }
//            std::cout << "min:" << min << '\n';
            time += step;
        }
        std::cout << start_time << ' ' << arrive_time << '\n';
        time = 0;
    }
    void output(){
        for(const auto& pair:adjacency_list){
            const int a = pair.first;
            const std::vector<Line> b = pair.second;
            for(auto it : b){
                std::cout << a << "->" << it.node << ' ';
            }
            std::cout << '\n';
        }
    }
};

int main() {
    Graph graph;
    int N, M, K;
    std::cin >> N >> M >> K;
    graph.size = N;
    graph.step = K;
    int u, v, lower, upper, step;
    for(int i = 0;i < M;++i){
        std::cin >> u >> v >> lower >> upper >> step;
        if(graph.adjacency_list.find(u) == graph.adjacency_list.end())
            graph.add_vertex(u);
        graph.add_edge(u, Graph::Line(v, lower, upper, step));
    }
//    graph.output();
    std::queue<int> q;
    rank = decltype(rank)(N);
    std::vector<int> in_degree(N, 0);
    std::map<int, std::vector<Graph::Line>> list = graph.adjacency_list;
    for(int i = 0;i < N;++i){
        for(auto & j : list[i]){
            in_degree[j.node]++;
        }
    }
    for(int i=0;i < N;++i){
        if(in_degree[i] == 0){
            q.push(i);
        }
    }
    int n = 0;
    while (!q.empty()) {
        auto x = q.front();
        q.pop();
        for(auto line: list[x]){
            if(--in_degree[line.node] == 0)
                q.push((line.node));
        }
        rank[n++] = x;
    }
    graph.solve();
    return 0;
}
