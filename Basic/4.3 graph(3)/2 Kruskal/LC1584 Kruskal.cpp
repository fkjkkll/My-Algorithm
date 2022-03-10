class UFSet{
public:
    UFSet(int _n):count(_n), parent(_n, -1){}
    int getCount(){return count;}
    void unite(int a, int b){
        int f1 = find(a);
        int f2 = find(b);
        if(f1 == f2) return;
        if(parent[f1] < parent[f2]){
            parent[f1] += parent[f2];
            parent[f2] = f1;
        }else{
            parent[f2] += parent[f1];
            parent[f1] = f2;
        }
        -- count;
    }
    bool isConnected(int a, int b){
        return find(a) == find(b);
    }
    
private:
    int find(int pos){
        if(parent[pos] < 0) return pos;
        return parent[pos] = find(parent[pos]);
    }
    int count; // 连通集的个数
    vector<int> parent;
};

struct Edge{
    int from;
    int to;
    int weight;
    bool operator>(const Edge& ano) const {
        return this->weight > ano.weight;
    }
};

class Solution {
public:
    // 都不用建图，直接把边放进去就行了
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        UFSet ufs(n);
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        for(int i=0; i<n; ++i){
            for(int j=0; j<i; ++j){
                int weight = abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]);
                pq.push(Edge({i, j, weight}));
            }
        }
        int res = 0, cnt = 0;
        while(!pq.empty() && cnt<n-1){
            Edge cur = pq.top(); pq.pop();
            if(ufs.isConnected(cur.from, cur.to) == false){
                ufs.unite(cur.from, cur.to);
                res += cur.weight;
                ++cnt;
            }
        }
        return res;
    }
};
