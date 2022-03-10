struct Node{ // 用来在优先队列里用
    int node;
    int dis;
    bool operator>(const Node& ano) const {
        return this->dis > ano.dis;
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size(); // 节点数
        vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; ++i){ // 建图
            for (int j = 0; j < i; ++j){
                graph[i][j] = abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]);
                graph[j][i] = graph[i][j];
            }
        }  
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        vector<int> dist(n, INT_MAX);
        pq.push(Node({0, 0})); // 从0开始， 0到0的距离是0
        int ret = 0;
        while(!pq.empty()){
            Node cur = pq.top(); pq.pop();
            if(dist[cur.node] == 0) continue;
            dist[cur.node] = 0;
            ret += cur.dis;
            for(int i=0; i<n; ++i){
                if(graph[cur.node][i] < INT_MAX && dist[i] > graph[cur.node][i]){
                    dist[i] = graph[cur.node][i];
                    pq.push(Node({i, graph[cur.node][i]}));
                }
            }
        }
        return ret;
    }
};
