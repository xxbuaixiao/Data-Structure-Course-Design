#include "Graph.h"
#include "Graph.h" 

// 构造函数
Graph::Graph() : vertexCount(0), directed(false), weighted(false) {
    for (int i = 0; i < MAX_VERTEX; i++) {
        visited[i] = false;
        for (int j = 0; j < MAX_VERTEX; j++) {
            adjMatrix[i][j] = 0;
        }
    }
}

// 图的创建
// 参数：isDirected(是否有向), isWeighted(是否带权)
void Graph::createGraph(bool isDirected, bool isWeighted) {
    directed = isDirected;
    weighted = isWeighted;

    cout << "请输入顶点数: ";
    cin >> vertexCount;

    cout << "请输入边数: ";
    int edgeCount;
    cin >> edgeCount;

    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = 0; j < MAX_VERTEX; j++) {
            adjMatrix[i][j] = weighted ? INF : 0;
        }
        adjMatrix[i][i] = 0;
    }

    cout << "请输入每条边（格式：起点 终点 [权重]）:" << endl;
    for (int i = 0; i < edgeCount; i++) {
        int u, v, w = 1;
        cin >> u >> v;
        if (weighted) {
            cin >> w;
        }
        adjMatrix[u][v] = w;
        if (!directed) {
            adjMatrix[v][u] = w;
        }
    }
    cout << "图创建成功！" << endl;
}

// 显示邻接矩阵
void Graph::displayMatrix() const {
    cout << "邻接矩阵:" << endl;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (weighted && adjMatrix[i][j] == INF) {
                cout << "INF\t";
            }
            else {
                cout << adjMatrix[i][j] << "\t";
            }
        }
        cout << endl;
    }
}


// DFS 递归辅助函数：访问顶点 v，然后递归访问所有未访问的邻接顶点
void Graph::dfsUtil(int v) {
    visited[v] = true;
    cout << v << " ";

    for (int i = 0; i < vertexCount; i++) {
        if ((!weighted && adjMatrix[v][i] != 0) || (weighted && adjMatrix[v][i] != INF && adjMatrix[v][i] != 0)) {
            if (!visited[i]) {
                dfsUtil(i);
            }
        }
    }
}

// DFS 接口
void Graph::dfs() {
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
    cout << "DFS遍历结果: ";
    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            dfsUtil(i);
        }
    }
    cout << endl;
}

// 广度优先搜索，使用队列实现
void Graph::bfs() {
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }

    queue<int> q;
    cout << "BFS遍历结果: ";

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cout << v << " ";

                for (int j = 0; j < vertexCount; j++) {
                    if ((!weighted && adjMatrix[v][j] != 0) || (weighted && adjMatrix[v][j] != INF && adjMatrix[v][j] != 0)) {
                        if (!visited[j]) {
                            visited[j] = true;
                            q.push(j);
                        }
                    }
                }
            }
        }
    }
    cout << endl;
}

// 拓扑排序
void Graph::topologicalSortUtil(int v, stack<int>& st) {
    visited[v] = true;

    for (int i = 0; i < vertexCount; i++) {
        if (adjMatrix[v][i] != 0 && !visited[i]) {
            topologicalSortUtil(i, st);
        }
    }
    st.push(v);
}

// 拓扑排序接口
void Graph::topologicalSort() {
    if (!directed) {
        cout << "拓扑排序只适用于有向图！" << endl;
        return;
    }

    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }

    stack<int> st;

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, st);
        }
    }

    cout << "拓扑排序结果: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

// 并查集（Kruskal 辅助） 
// 查找：带路径压缩的查找根节点
int Graph::find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]);
}

// 合并：按秩合并两个集合，将高度较小的树合并到高度较大的树下
void Graph::Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    }
    else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    }
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// ==================== Kruskal 最小生成树 ====================
// 算法：将所有边按权重排序 → 依次取边，若不构成环则加入生成树
// 使用并查集判断是否构成环
void Graph::kruskalMST() {
    if (directed) {
        cout << "Kruskal算法适用于无向图！" << endl;
        return;
    }

    vector<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < vertexCount; i++) {
        for (int j = i + 1; j < vertexCount; j++) {
            if (adjMatrix[i][j] != 0 && adjMatrix[i][j] != INF) {
                edges.push_back({ adjMatrix[i][j], {i, j} });
            }
        }
    }

    sort(edges.begin(), edges.end());

    int parent[MAX_VERTEX], rank[MAX_VERTEX];
    for (int i = 0; i < vertexCount; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalWeight = 0;
    cout << "Kruskal最小生成树边:" << endl;

    for (const auto& edge : edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        int x = find(parent, u);
        int y = find(parent, v);

        if (x != y) {
            cout << "(" << u << ", " << v << ") 权重: " << w << endl;
            totalWeight += w;
            Union(parent, rank, x, y);
        }
    }

    cout << "最小生成树总权重: " << totalWeight << endl;
}

// ==================== Dijkstra 最短路径 ====================

// 找最小 key 值的顶点（未纳入已确定集合的顶点中距离最小的）
int Graph::findMinKey(int key[], bool mstSet[]) {
    int min = INF, minIndex = -1;

    for (int v = 0; v < vertexCount; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Dijkstra 最短路径算法：
// 从起点 start 出发，贪心选择距离最小且未确定的顶点
// 松弛操作：通过该顶点更新其他顶点的最短距离
void Graph::dijkstra(int start) {
    if (!weighted) {
        cout << "Dijkstra算法适用于带权图！" << endl;
        return;
    }

    int dist[MAX_VERTEX];
    bool visited[MAX_VERTEX];

    for (int i = 0; i < vertexCount; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int count = 0; count < vertexCount - 1; count++) {
        int u = findMinKey(dist, visited);
        visited[u] = true;

        for (int v = 0; v < vertexCount; v++) {
            if (!visited[v] && adjMatrix[u][v] != INF && dist[u] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }

    cout << "从顶点" << start << "到各顶点的最短路径:" << endl;
    for (int i = 0; i < vertexCount; i++) {
        if (dist[i] == INF) {
            cout << "到" << i << ": 不可达" << endl;
        }
        else {
            cout << "到" << i << ": " << dist[i] << endl;
        }
    }
}

// ==================== 关键路径（AOE 网） ====================
// 算法步骤：
// 1. 计算每个顶点的入度，通过拓扑排序获得拓扑序列
// 2. 正向计算 ve（事件最早发生时间）
// 3. 反向计算 vl（事件最迟发生时间）
// 4. 满足 ve[u] == vl[v] - w(u,v) 的边即为关键活动
void Graph::criticalPath() {
    if (!directed || !weighted) {
        cout << "关键路径算法适用于带权有向图！" << endl;
        return;
    }

    vector<int> inDegree(vertexCount, 0);
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (adjMatrix[i][j] != 0 && adjMatrix[i][j] != INF) {
                inDegree[j]++;
            }
        }
    }

    queue<int> q;
    vector<int> topoOrder;

    for (int i = 0; i < vertexCount; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != 0 && adjMatrix[u][v] != INF) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }

    vector<int> ve(vertexCount, 0);
    for (int u : topoOrder) {
        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != 0 && adjMatrix[u][v] != INF) {
                if (ve[v] < ve[u] + adjMatrix[u][v]) {
                    ve[v] = ve[u] + adjMatrix[u][v];
                }
            }
        }
    }

    vector<int> vl(vertexCount, ve[topoOrder.back()]);
    for (auto it = topoOrder.rbegin(); it != topoOrder.rend(); ++it) {
        int u = *it;
        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != 0 && adjMatrix[u][v] != INF) {
                if (vl[u] > vl[v] - adjMatrix[u][v]) {
                    vl[u] = vl[v] - adjMatrix[u][v];
                }
            }
        }
    }

    cout << "关键路径活动:" << endl;
    int maxTime = ve[topoOrder.back()];
    cout << "关键路径长度: " << maxTime << endl;
    cout << "关键活动: ";
    for (int u : topoOrder) {
        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != 0 && adjMatrix[u][v] != INF) {
                if (ve[u] == vl[v] - adjMatrix[u][v]) {
                    cout << "(" << u << "," << v << ") ";
                }
            }
        }
    }
    cout << endl;
}