#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// 二叉树节点，存储字符数据及左右孩子指针
struct BTNode {
    char data;       
    BTNode* left;    
    BTNode* right;   

    // 节点构造函数
    BTNode(char val) : data(val), left(nullptr), right(nullptr) {}
};


// Huffman 树节点，存储字符、权值及左右孩子指针
struct HuffmanNode {
    char data;          
    int weight;         
    HuffmanNode* left;  
    HuffmanNode* right; 

    // 节点构造函数
    HuffmanNode(char c, int w) : data(c), weight(w), left(nullptr), right(nullptr) {}
};


// 以 BTNode 为节点类型的二叉树，通过 root 管理
class BinaryTree {
private:
    BTNode* root;  // 根节点

    // 内部递归辅助函数
    // 销毁二叉树：后序遍历方式释放所有节点内存
    void destroy(BTNode* node);

    // 先序,中序,后序遍历
    void preOrder(BTNode* node);
    void inOrder(BTNode* node);
    void postOrder(BTNode* node);

    // 统计叶子节点数
    int countLeaves(BTNode* node);

    // 计算树深度
    int getDepth(BTNode* node);

    // 查找指定值双亲
    BTNode* findParent(BTNode* node, char val);

    // 查找指定值的节点
    BTNode* findNode(BTNode* node, char val);

public:
    // 构造函数
    BinaryTree();

    // 析构函数:调用destroy
    ~BinaryTree();

    // 创建二叉树
    BTNode* createTree();

    // 设置根节点
    void setRoot(BTNode* node);

    // 先序遍历接口
    void preOrderTraversal();

    // 中序遍历接口
    void inOrderTraversal();

    // 后序遍历接口
    void postOrderTraversal();

    // 统计叶子节点接口
    int leafCount();

    // 树深度接口
    int treeDepth();

    // 查找双亲：查找节点的双亲值，若节点为根或无此节点，返回 '\0'
    char findParentValue(char val);

    // 查找值节点的兄弟节点值
    char findSibling(char val);
};

// HuffmanTree
class HuffmanTree {
private:
    HuffmanNode* root;  
    void destroy(HuffmanNode* node);

    // 递归生成 Huffman 编码：从根出发，左分支编码 '0'，右分支编码 '1'
    // 到达叶子节点时将 (字符, 编码) 存入 codes 映射表
    void generateCodes(HuffmanNode* node, string code, map<char, string>& codes);

public:
    // 构造函数
    HuffmanTree();

    // 析构函数
    ~HuffmanTree();

    // 构建 Huffman 树
    void buildTree(const map<char, int>& frequencies);

    // 获取 Huffman 编码表：返回 字符 -> 二进制编码 的映射
    map<char, string> getCodes();

    // 打印 Huffman 编码：按格式输出所有字符及其对应的编码
    void printCodes();
};

#endif
