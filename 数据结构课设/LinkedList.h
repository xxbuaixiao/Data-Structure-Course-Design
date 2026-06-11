/*
 * LinkedList.h - 单链表模块头文件
 *
 * 功能说明：
 *  定义泛型单链表模板类 LinkedList<T>，支持任意数据类型 T，提供：
 *   创建链表（手动输入数据）
 *   在指定位置插入节点
 *   删除指定位置节点
 *   按值查找节点位置
 *   遍历显示链表
 *   清空链表
 *   获取链表大小 / 判空
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

// ==================== Node 结构体模板 ====================
// 链表节点结构体模板
// T 是泛型参数，可以存储 int、string、自定义结构体等任意类型数据
template <typename T>
struct Node {
    T data;             // 节点存储的数据
    Node<T>* next;      // 指向下一个节点的指针

    // 节点构造函数：用 val 初始化数据域，next 默认置空
    Node(const T& val) : data(val), next(nullptr) {}
};

// ==================== LinkedList 类模板 ====================
// 泛型单链表类，支持增删查显等基本操作
// 内部通过头指针 head 和 size 计数管理链表状态
template <typename T>
class LinkedList {
private:
    Node<T>* head;  // 链表头指针（带头结点），头结点不存储有效数据
    int size;       // 链表当前节点个数（不含头结点）

public:
    // 构造函数：创建带头结点的空链表，head 指向头结点，size = 0
    LinkedList();

    // 析构函数：调用 clear() 释放链表所有节点内存，防止内存泄漏
    ~LinkedList();

    // 创建链表：提示用户输入节点个数及每个节点的值，依次插入链表尾部
    void create();

    // 插入节点：在指定位置 pos（从1开始）插入值为 val 的新节点
    // pos 越界时输出错误提示
    void insert(int pos, const T& val);

    // 删除节点：删除指定位置 pos（从1开始）的节点
    // pos 越界时输出错误提示
    void remove(int pos);

    // 查找节点：查找值为 val 的节点，返回其位置下标（从1开始）
    // 找不到则返回 -1
    int find(const T& val);

    // 遍历显示：按顺序打印链表所有节点的数据
    void display();

    // 清空链表：释放除头结点外的所有节点内存，size 归零
    void clear();

    // 获取链表当前节点个数（不含头结点）
    int getSize() const;

    // 判断链表是否为空（size == 0）
    bool isEmpty() const;
};

#endif
