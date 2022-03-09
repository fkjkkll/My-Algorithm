// 输入： 起始城市A，终点城市F，城市中转 [(A, B, 10), (A, C, 12), (B, F, 50), (C, D, 20), (D, F, 10)]
// 最便宜路线 A->C->D->F, 42
struct node {
    string from;
    string to;
    int price;
};

struct lee {
    int dis;
    int idx;
    bool operator>(const lee& ano) const {
        return this->dis > ano.dis;
    }
};

void showPath(int end, vector<int>& path, unordered_map<int, string>& i2s) {
    if (end == -1) return;
    showPath(path[end], path, i2s);
    cout << " " << i2s[end];
}

void Djkstra(string start, string end, vector<node>& details) {
    unordered_map<string, int> s2i;
    unordered_map<int, string> i2s;
    int cnt = 0;
    for (auto& e : details) { // 建立映射
        if (!s2i.count(e.from)) {
            s2i[e.from] = cnt;
            i2s[cnt] = e.from;
            ++cnt;
        }
        if (!s2i.count(e.to)) {
            s2i[e.to] = cnt;
            i2s[cnt] = e.to;
            ++cnt;
        }
    }
    vector<int> path(cnt, -1);
    vector<int> dist(cnt, INT_MAX);
    vector<vector<int>> graph(cnt, vector<int>(cnt, INT_MAX));
    priority_queue<lee, vector<lee>, greater<lee>> pq;
    for (auto& e : details) {
        graph[s2i[e.from]][s2i[e.to]] = e.price; // 单向图
    }
    dist[s2i[start]] = 0;
    pq.push(lee({ s2i[start], 0 }));
    while (!pq.empty()) {
        lee cur = pq.top(); pq.pop();
        for (int i = 0; i < cnt; ++i) {
            if (graph[cur.idx][i] != INT_MAX && dist[i] > cur.dis + graph[cur.idx][i]) {
                dist[i] = cur.dis + graph[cur.idx][i];
                path[i] = cur.idx;
                pq.push(lee({ dist[i], i }));
            }
        }
    }
    if (dist[s2i[end]] == INT_MAX)
        cout << "无法到达" << endl;
    else {
        showPath(s2i[end], path, i2s);
        cout << " | 总共花费：" << dist[s2i[end]] << endl;
    }
}

int main(){
    vector<node> path = { {"A", "B", 1}, {"B", "C", 1}, {"B", "E", 4}, {"C", "E", 3}, {"A", "D", 4}, {"C", "D", 1}, {"D", "E", 1} };
    Djkstra("A", "E", path);
    return 0;
}
