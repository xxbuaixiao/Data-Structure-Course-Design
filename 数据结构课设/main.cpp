/*
 * main.cpp - 数据结构课程设计主程序
 *
 * 功能说明：
 *   提供统一的主菜单入口，集成六大数据结构模块：
 *   1. 单链表（含通讯录应用）
 *   2. 栈（含表达式求值应用）
 *   3. 数组/矩阵（含矩阵乘法）
 *   4. 二叉树（含Huffman编码）
 *   5. 图（含DFS/BFS/拓扑排序/Kruskal/Dijkstra/关键路径）
 *   6. 退出系统
 *
 * 每个模块对应一个子菜单函数，用户通过主菜单选择进入。
 */

#include <iostream>
#include "LinkedList.h"
#include "ContactList.h"
#include "Stack.h"
#include "Array.h"
#include "BinaryTree.h"
#include "Graph.h"

using namespace std;

// 单链表子菜单
// 提供链表的基本操作：创建、插入、删除、查找、显示
// 同时集成通讯录功能作为链表应用
void linkedListMenu() {
    LinkedList<int> list;
    int choice;

    do {
        cout << "\n=== 单链子菜单 ===" << endl;
        cout << "1. 创建链表" << endl;
        cout << "2. 插入元素" << endl;
        cout << "3. 删除元素" << endl;
        cout << "4. 查找元素" << endl;
        cout << "5. 显示链表" << endl;
        cout << "6. 通讯录功能" << endl;
        cout << "7. 返回主菜单" << endl;
        cout << "请输入选择: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            list.create();
            break;
        }
        case 2: {
            int pos, val;
            cout << "请输入插入位置: ";
            cin >> pos;
            cout << "请输入插入值: ";
            cin >> val;
            list.insert(pos-1, val);
            break;
        }
        case 3: {
            int pos;
            cout << "请输入删除位置: ";
            cin >> pos;
            list.remove(pos-1);
            break;
        }
        case 4: {
            int val;
            cout << "请输入要查找的值: ";
            cin >> val;
            int index = list.find(val);
            if (index != -1) {
                cout << "找到元素，位置为: " << index+1 << endl;
            }
            else {
                cout << "未找到元素！" << endl;
            }
            break;
        }
        case 5: {
            list.display();
            break;
        }
        case 6: {
            ContactList contactList;
            contactList.menu();
            break;
        }
        case 7: {
            cout << "返回主菜单..." << endl;
            break;
        }
        default: {
            cout << "无效选择！" << endl;
        }
        }
    } while (choice != 7);
}

// 栈子菜单 
// 提供栈的基本操作：进栈、出栈、取栈顶、显示
// 集成表达式求值功能（中缀转后缀表达式计算）
void stackMenu() {
    Stack<int> stack;
    int choice;

    do {
        cout << "\n=== 栈子菜单 ===" << endl;
        cout << "1. 进栈" << endl;
        cout << "2. 出栈" << endl;
        cout << "3. 取栈顶" << endl;
        cout << "4. 显示栈" << endl;
        cout << "5. 表达式求值" << endl;
        cout << "6. 返回主菜单" << endl;
        cout << "请输入选择: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int val;
            cout << "请输入进栈值: ";
            cin >> val;
            stack.push(val);
            break;
        }
        case 2: {
            int val;
            if (stack.pop(val)) {
                cout << "出栈元素: " << val << endl;
            }
            break;
        }
        case 3: {
            int val;
            if (stack.getTop(val)) {
                cout << "栈顶元素: " << val << endl;
            }
            break;
        }
        case 4: {
            stack.display();
            break;
        }
        case 5: {
            string expression;
            cout << "请输入中缀表达式（仅支持+、-、*、/和括号）: ";
            cin >> expression;
            bool a=true;
            double result = ExpressionEvaluator::evaluateExpression(expression,a);
            if (a)
            {
                cout << "计算结果: " << result << endl;
            }
            break;
        }
        case 6: {
            cout << "返回主菜单..." << endl;
            break;
        }
        default: {
            cout << "无效选择！" << endl;
        }
        }
    } while (choice != 6);
}

// 数组/矩阵子菜单 
// 提供矩阵的基本操作：创建、显示、矩阵乘法
void arrayMenu() {
    Matrix mat1, mat2;
    int choice;

    do {
        cout << "\n=== 数组/矩阵子菜单 ===" << endl;
        cout << "1. 创建矩阵1" << endl;
        cout << "2. 创建矩阵2" << endl;
        cout << "3. 显示矩阵1" << endl;
        cout << "4. 显示矩阵2" << endl;
        cout << "5. 矩阵乘法（矩阵1 * 矩阵2）" << endl;
        cout << "6. 返回主菜单" << endl;
        cout << "请输入选择: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            mat1.create();
            break;
        }
        case 2: {
            mat2.create();
            break;
        }
        case 3: {
            mat1.display();
            break;
        }
        case 4: {
            mat2.display();
            break;
        }
        case 5: {
            mat1.multiply(mat2);
            break;
        }
        case 6: {
            cout << "返回主菜单..." << endl;
            break;
        }
        default: {
            cout << "无效选择！" << endl;
        }
        }
    } while (choice != 6);
}

// 二叉树子菜单
// 提供二叉树的基本操作：创建（先序）、三种遍历、统计叶子数、计算深度、查找双亲/兄弟并且集成 Huffman 编码功能
void binaryTreeMenu() {
    BinaryTree tree;
    HuffmanTree huffman;
    int choice;

    do {
        cout << "\n=== 二叉树子菜单 ===" << endl;
        cout << "1. 创建二叉树（先序）" << endl;
        cout << "2. 先序遍历" << endl;
        cout << "3. 中序遍历" << endl;
        cout << "4. 后序遍历" << endl;
        cout << "5. 统计叶子数" << endl;
        cout << "6. 计算树深度" << endl;
        cout << "7. 查找双亲" << endl;
        cout << "8. 查找兄弟" << endl;
        cout << "9. Huffman编码" << endl;
        cout << "10. 返回主菜单" << endl;
        cout << "请输入选择: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            BTNode* root = tree.createTree();
            tree.setRoot(root);
            cout << "二叉树创建成功！" << endl;
            break;
        }
        case 2: {
            tree.preOrderTraversal();
            break;
        }
        case 3: {
            tree.inOrderTraversal();
            break;
        }
        case 4: {
            tree.postOrderTraversal();
            break;
        }
        case 5: {
            cout << "叶子节点数: " << tree.leafCount() << endl;
            break;
        }
        case 6: {
            cout << "树的深度: " << tree.treeDepth() << endl;
            break;
        }
        case 7: {
            char val;
            cout << "请输入要查找双亲的节点值: ";
            cin >> val;
            char parent = tree.findParentValue(val);
            if (parent != '\0') {
                cout << val << " 的双亲是: " << parent << endl;
            }
            else {
                cout << "未找到双亲或该节点是根节点！" << endl;
            }
            break;
        }
        case 8: {
            char val;
            cout << "请输入要查找兄弟的节点值: ";
            cin >> val;
            char sibling = tree.findSibling(val);
            if (sibling != '\0') {
                cout << val << " 的兄弟是: " << sibling << endl;
            }
            else {
                cout << "未找到兄弟！" << endl;
            }
            break;
        }
        case 9: {
            map<char, int> frequencies;
            int n;
            cout << "请输入字符个数: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                char c;
                int w;
                cout << "请输入字符和权重（如: a 5）: ";
                cin >> c >> w;
                frequencies[c] = w;
            }
            huffman.buildTree(frequencies);
            huffman.printCodes();
            break;
        }
        case 10: {
            cout << "返回主菜单..." << endl;
            break;
        }
        default: {
            cout << "无效选择！" << endl;
        }
        }
    } while (choice != 10);
}

// 图子菜单
void graphMenu() {
    Graph graph;
    int choice;

    do {
        cout << "\n=== 图子菜单 ===" << endl;
        cout << "1. 创建无向图" << endl;
        cout << "2. 创建有向图" << endl;
        cout << "3. 创建无向网(无向带权)" << endl;
        cout << "4. 创建有向网(有向带权)" << endl;
        cout << "5. 显示邻接矩阵" << endl;
        cout << "6. DFS遍历" << endl;
        cout << "7. BFS遍历" << endl;
        cout << "8. 拓扑排序" << endl;
        cout << "9. 最小生成树(Kruskal)" << endl;
        cout << "10. 最短路径(Dijkstra)" << endl;
        cout << "11. 关键路径" << endl;
        cout << "12. 返回主菜单" << endl;
        cout << "请输入选择: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            graph.createGraph(false, false);
            break;
        }
        case 2: {
            graph.createGraph(true, false);
            break;
        }
        case 3: {
            graph.createGraph(false, true);
            break;
        }
        case 4: {
            graph.createGraph(true, true);
            break;
        }
        case 5: {
            graph.displayMatrix();
            break;
        }
        case 6: {
            graph.dfs();
            break;
        }
        case 7: {
            graph.bfs();
            break;
        }
        case 8: {
            graph.topologicalSort();
            break;
        }
        case 9: {
            graph.kruskalMST();
            break;
        }
        case 10: {
            int start;
            cout << "请输入起始顶点: ";
            cin >> start;
            graph.dijkstra(start);
            break;
        }
        case 11: {
            graph.criticalPath();
            break;
        }
        case 12: {
            cout << "返回主菜单..." << endl;
            break;
        }
        default: {
            cout << "无效选择！" << endl;
        }
        }
    } while (choice != 12);
}

// 主菜单
void mainMenu() {
    int choice;

    do {
        cout << "\n========== 数据结构课程设计 ==========" << endl;
        cout << "1. 单链表" << endl;
        cout << "2. 栈" << endl;
        cout << "3. 数组(矩阵)" << endl;
        cout << "4. 二叉树" << endl;
        cout << "5. 图" << endl;
        cout << "6. 退出" << endl;
        cout << "======================================" << endl;
        cout << "请输入选择: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            linkedListMenu();
            break;
        }
        case 2: {
            stackMenu();
            break;
        }
        case 3: {
            arrayMenu();
            break;
        }
        case 4: {
            binaryTreeMenu();
            break;
        }
        case 5: {
            graphMenu();
            break;
        }
        case 6: {
            cout << "感谢使用数据结构课程设计！" << endl;
            break;
        }
        default: {
            cout << "无效选择，请重新输入！" << endl;
        }
        }
    } while (choice != 6);
}

// ==================== 程序入口 ====================
// 启动主菜单，进入交互式循环
int main() {
    mainMenu();
    return 0;
}