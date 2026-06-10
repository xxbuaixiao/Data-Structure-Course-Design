/*
 * BinaryTree.cpp - 二叉树与 Huffman 树实现
 *
 * 功能说明：
 *   1. BinaryTree 类：二叉树的创建、遍历、统计等操作
 *      - 支持先序、中序、后序三种递归遍历
 *      - 统计叶子节点数、计算树深度
 *      - 查找指定节点的双亲/兄弟节点
 *   2. HuffmanTree 类：Huffman 编码树的构建和编码生成
 *      - 根据字符频率构建 Huffman 树
 *      - 生成并输出各字符的 Huffman 编码
 */

#include "BinaryTree.h"

// ==================== BinaryTree 类 ====================

// 构造函数：初始化根节点为空
BinaryTree::BinaryTree() : root(nullptr) {}

// 析构函数：递归销毁整棵树，释放所有节点
BinaryTree::~BinaryTree() {
    destroy(root);
}

// 递归销毁子树：后序遍历方式释放所有节点内存
void BinaryTree::destroy(BTNode* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// 先序方式递归创建二叉树
// 用户输入节点值，输入 '#' 表示空节点
// 返回：新创建的子树根节点
BTNode* BinaryTree::createTree() {
    char ch;
    cout << "请输入节点值（输入'#'表示空节点）: ";
    cin >> ch;
    if (ch == '#') {
        return nullptr;
    }
    BTNode* node = new BTNode(ch);
    cout << "输入 " << ch << " 的左子树:" << endl;
    node->left = createTree();
    cout << "输入 " << ch << " 的右子树:" << endl;
    node->right = createTree();
    return node;
}

// 设置根节点：先销毁旧树，再设置新根
void BinaryTree::setRoot(BTNode* node) {
    destroy(root);
    root = node;
}

// ==================== 遍历算法 ====================

// 先序遍历（递归）：根 → 左子树 → 右子树
void BinaryTree::preOrder(BTNode* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

void BinaryTree::preOrderTraversal() {
    cout << "先序遍历: ";
    preOrder(root);
    cout << endl;
}

// 中序遍历（递归）：左子树 → 根 → 右子树
void BinaryTree::inOrder(BTNode* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
}

void BinaryTree::inOrderTraversal() {
    cout << "中序遍历: ";
    inOrder(root);
    cout << endl;
}

// 后序遍历（递归）：左子树 → 右子树 → 根
void BinaryTree::postOrder(BTNode* node) {
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }
}

void BinaryTree::postOrderTraversal() {
    cout << "后序遍历: ";
    postOrder(root);
    cout << endl;
}

// ==================== 统计与计算 ====================

// 递归统计叶子节点数：左右子树均为空的节点为叶子
int BinaryTree::countLeaves(BTNode* node) {
    if (node == nullptr) {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }
    return countLeaves(node->left) + countLeaves(node->right);
}

int BinaryTree::leafCount() {
    return countLeaves(root);
}

// 递归计算树的深度：max(左深度, 右深度) + 1
int BinaryTree::getDepth(BTNode* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftDepth = getDepth(node->left);
    int rightDepth = getDepth(node->right);
    return max(leftDepth, rightDepth) + 1;
}

int BinaryTree::treeDepth() {
    return getDepth(root);
}

// ==================== 查找功能 ====================

// 递归查找指定值的节点，返回节点指针（找不到返回 nullptr）
BTNode* BinaryTree::findNode(BTNode* node, char val) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->data == val) {
        return node;
    }
    BTNode* left = findNode(node->left, val);
    if (left != nullptr) {
        return left;
    }
    return findNode(node->right, val);
}

// 递归查找指定值节点的双亲节点
BTNode* BinaryTree::findParent(BTNode* node, char val) {
    if (node == nullptr) {
        return nullptr;
    }
    if ((node->left != nullptr && node->left->data == val) ||
        (node->right != nullptr && node->right->data == val)) {
        return node;
    }
    BTNode* left = findParent(node->left, val);
    if (left != nullptr) {
        return left;
    }
    return findParent(node->right, val);
}

// 外部接口：查找值为 val 的节点的双亲值
// 返回双亲的 data，若无双亲或根节点返回 '\0'
char BinaryTree::findParentValue(char val) {
    if (root == nullptr || root->data == val) {
        return '\0';
    }
    BTNode* parent = findParent(root, val);
    return parent != nullptr ? parent->data : '\0';
}

// 外部接口：查找值为 val 的节点的兄弟节点值
// 先找到双亲，再返回双亲的另一个孩子
char BinaryTree::findSibling(char val) {
    if (root == nullptr || root->data == val) {
        return '\0';
    }
    BTNode* parent = findParent(root, val);
    if (parent == nullptr) {
        return '\0';
    }
    if (parent->left != nullptr && parent->left->data == val) {
        return parent->right != nullptr ? parent->right->data : '\0';
    }
    return parent->left != nullptr ? parent->left->data : '\0';
}

// ==================== HuffmanTree 类 ====================

// 构造函数：初始化根节点为空
HuffmanTree::HuffmanTree() : root(nullptr) {}

// 析构函数：递归销毁整棵树
HuffmanTree::~HuffmanTree() {
    destroy(root);
}

// 递归销毁 Huffman 子树
void HuffmanTree::destroy(HuffmanNode* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// Huffman 树构建算法：
// 1. 将所有字符节点按频率放入最小优先队列
// 2. 每次取出频率最小的两个节点，合并为新节点（频率=两子节点频率之和）
// 3. 新节点入队，重复直到队列只剩一个节点，即为 Huffman 树的根
void HuffmanTree::buildTree(const map<char, int>& frequencies) {
    // 最小堆优先队列：按频率升序排列
    priority_queue<pair<int, HuffmanNode*>, vector<pair<int, HuffmanNode*>>, greater<pair<int, HuffmanNode*>>> pq;

    // 步骤1：所有字符作为叶子节点入队
    for (const auto& pair : frequencies) {
        pq.push({ pair.second, new HuffmanNode(pair.first, pair.second) });
    }

    // 步骤2-3：反复合并最小的两个节点
    while (pq.size() > 1) {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();

        // 创建新内部节点，频率为两子节点之和
        HuffmanNode* newNode = new HuffmanNode('\0', left.first + right.first);
        newNode->left = left.second;
        newNode->right = right.second;
        pq.push({ newNode->weight, newNode });
    }

    root = pq.top().second;
}

// 递归生成 Huffman 编码：
// 从根节点出发，左分支追加 '0'，右分支追加 '1'
// 到达叶子节点（data != '\0'）时记录编码
void HuffmanTree::generateCodes(HuffmanNode* node, string code, map<char, string>& codes) {
    if (node == nullptr) {
        return;
    }
    if (node->data != '\0') {
        codes[node->data] = code;
        return;
    }
    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

// 获取所有字符的 Huffman 编码表
map<char, string> HuffmanTree::getCodes() {
    map<char, string> codes;
    generateCodes(root, "", codes);
    return codes;
}

// 打印 Huffman 编码表
void HuffmanTree::printCodes() {
    map<char, string> codes = getCodes();
    cout << "\n=== Huffman编码表 ===" << endl;
    for (const auto& pair : codes) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
}