// Leetcode 1584 连接所有点的最小费用
// points = [[0,0],[2,2],[3,10],[5,2],[7,0]] 求坐标轴上这几个点的最小生成树的路径和
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
            // 跟Dijkstra一样，但人家遇到终点直接可以break
            // 因为采用优先队列的方式，队列里会有重复，第一次接触的肯定是最优解，后面
            // 重复的都是大于最优解的，之际跳过，或者你用一个数组，对应节点存储dist
            // 每次存储比较取最小值，但是空间浪费太大了，不如这样好
            if(dist[cur.node] == 0) continue;
            dist[cur.node] = 0;
            ret += cur.dis;
            for(int i=0; i<n; ++i){
                if(dist[i] > graph[cur.node][i]){
                    dist[i] = graph[cur.node][i];
                    pq.push(Node({i, graph[cur.node][i]}));
                }
            }
        }
        return ret;
    }
};
