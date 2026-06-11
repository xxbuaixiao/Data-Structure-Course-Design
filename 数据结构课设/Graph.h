#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

//常量
const int MAX_VERTEX = 50;  // 图的最大顶点数
const int INF = INT_MAX;    // 无穷大常量

// Graph
class Graph {
private:
    int vertexCount;                        // 当前图的顶点数
    int adjMatrix[MAX_VERTEX][MAX_VERTEX];  // 邻接矩阵，边权值
    bool directed;                          // 是否为有向
    bool weighted;                          // 是否为带权
    bool visited[MAX_VERTEX];               // 标记数组

    // DFS
    void dfsUtil(int v);

    // 拓扑排序
    void topologicalSortUtil(int v, stack<int>& st);

    // 找到 key 数组中未加入 MST 且权值最小的顶点
    int findMinKey(int key[], bool mstSet[]);

    // 并查集 - 查找：找到顶点 i 所属集合的根
    int find(int parent[], int i);

    // 并查集 - 合并：将 x 和 y 所在的集合合并（按秩优化）
    void Union(int parent[], int rank[], int x, int y);

public:
    // 构造函数
    Graph();

    // 创建图
    void createGraph(bool isDirected, bool isWeighted);

    // 显示邻接矩阵
    void displayMatrix() const;

    // 深度优先
    void dfs();

    // 广度优先
    void bfs();

    // 拓扑排序
    void topologicalSort();

    // Kruskal 最小生成树：输出无向网的最小生成树边集及总权值
    void kruskalMST();

    // Dijkstra 最短路径：从 start 顶点出发，计算到各顶点的最短路径
    void dijkstra(int start);

    // 关键路径：计算 AOE 网的关键路径并输出（仅限有向网）
    void criticalPath();
};

#endif
