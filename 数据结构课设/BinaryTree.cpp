#include "BinaryTree.h"

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    destroy(root);
}

void BinaryTree::destroy(BTNode* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

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

void BinaryTree::setRoot(BTNode* node) {
    destroy(root);
    root = node;
}

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

char BinaryTree::findParentValue(char val) {
    if (root == nullptr || root->data == val) {
        return '\0';
    }
    BTNode* parent = findParent(root, val);
    return parent != nullptr ? parent->data : '\0';
}

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

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {
    destroy(root);
}

void HuffmanTree::destroy(HuffmanNode* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

void HuffmanTree::buildTree(const map<char, int>& frequencies) {
    priority_queue<pair<int, HuffmanNode*>, vector<pair<int, HuffmanNode*>>, greater<pair<int, HuffmanNode*>>> pq;

    for (const auto& pair : frequencies) {
        pq.push({ pair.second, new HuffmanNode(pair.first, pair.second) });
    }

    while (pq.size() > 1) {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left.first + right.first);
        newNode->left = left.second;
        newNode->right = right.second;
        pq.push({ newNode->weight, newNode });
    }

    root = pq.top().second;
}

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

map<char, string> HuffmanTree::getCodes() {
    map<char, string> codes;
    generateCodes(root, "", codes);
    return codes;
}

void HuffmanTree::printCodes() {
    map<char, string> codes = getCodes();
    cout << "\n=== Huffman编码表 ===" << endl;
    for (const auto& pair : codes) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
}