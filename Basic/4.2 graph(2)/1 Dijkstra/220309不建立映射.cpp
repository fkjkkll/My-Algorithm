// 春招实习：微软二面
// 输入： 起始城市A，终点城市F，城市中转 [(A, B, 10), (A, C, 12), (B, F, 50), (C, D, 20), (D, F, 10)]
// 最便宜路线 A->C->D->F, 42
struct node {
    string from;
    string to;
    int price;
};

struct lee { // 用来参与优先队列排序的
    string city;
    int dis;
    lee(string _city, int _dis=0):city(_city), dis(_dis) {}
    bool operator>(const lee& ano) const {
        return this->dis > ano.dis;
    }
};

void showPath(string city, unordered_map<string, string>& path) {
    if (city == "*") return;
    showPath(path[city], path);
    cout << " " << city;
}

void Djkstra(string start, string end, vector<node>& details) {
    unordered_map<string, vector<node>> graph;
    priority_queue<lee, vector<lee>, greater<lee>> pq;
    unordered_map<string, string> path;
    unordered_map<string, int> dist;
    for (auto& e : details) {
        graph[e.from].push_back(e);
        dist[e.from] = INT_MAX;
        dist[e.to] = INT_MAX;
        path[e.from] = "*";
        path[e.to] = "*";
    }
    dist[start] = 0;
    pq.push(lee(start, 0));
    while (!pq.empty()) {
        lee cur = pq.top(); pq.pop();
        if (cur.city == end)
            break;
        for (auto& e : graph[cur.city]) {
            if (dist[e.to] > cur.dis + e.price) {
                dist[e.to] = cur.dis + e.price;
                path[e.to] = e.from;
                pq.push(lee(e.to, dist[e.to]));
            }
        }
    }
    if (dist[end] == INT_MAX) {
        cout << "无法到达" << endl; return;
    }
    showPath(end, path);
    cout << " | 总共花费：" << dist[end] << endl;
}

int main(){
    vector<node> path = { {"A", "B", 1}, {"B", "C", 1}, {"B", "E", 4}, {"C", "E", 3}, {"A", "D", 4}, {"C", "D", 1}, {"D", "E", 1} };
    Djkstra("A", "E", path);
    return 0;
}
