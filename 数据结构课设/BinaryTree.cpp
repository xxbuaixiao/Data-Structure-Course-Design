#include "BinaryTree.h"

// BinaryTree 类
BinaryTree::BinaryTree() : root(nullptr) {}
BinaryTree::~BinaryTree() {
    destroy(root);
}

// 递归销毁子树
void BinaryTree::destroy(BTNode* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// 先序方式递归创建二叉树
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

// 遍历
// 先序遍历
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

// 中序遍历
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

// 后序遍历
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

// 统计与计算
// 统计叶子节点数
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

// 递归计算树的深度
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

// 查找
// 指定值的节点
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

// 查找指定值双亲
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

// 查找双亲接口
char BinaryTree::findParentValue(char val) {
    if (root == nullptr || root->data == val) {
        return '\0';
    }
    BTNode* parent = findParent(root, val);
    return parent != nullptr ? parent->data : '\0';
}

// 找兄弟接口
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

// HuffmanTree
// 构造函数
HuffmanTree::HuffmanTree() : root(nullptr) {}

// 析构函数
HuffmanTree::~HuffmanTree() {
    destroy(root);
}

// 递归销毁
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
    priority_queue<pair<int, HuffmanNode*>, vector<pair<int, HuffmanNode*>>, greater<pair<int, HuffmanNode*>>> pq;

    // 字符作为叶子节点入队
    for (const auto& pair : frequencies) {
        pq.push({ pair.second, new HuffmanNode(pair.first, pair.second) });
    }

    // 反复合并最小的两个节点
    while (pq.size() > 1) {
        auto right = pq.top();
        pq.pop();
        auto left = pq.top();
        pq.pop();

        // 创建新内部节点，频率为两子节点之和
        HuffmanNode* newNode = new HuffmanNode('\0', left.first + right.first);
        newNode->left = left.second;
        newNode->right = right.second;
        pq.push({ newNode->weight, newNode });
    }

    root = pq.top().second;
}

// 递归生成 Huffman 编码
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