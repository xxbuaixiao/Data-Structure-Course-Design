/*
 * ContactList.h - 通讯录模块头文件
 *
 * 功能说明：
 *   以单链表为底层数据结构实现通讯录管理，支持：
 *   - 添加联系人（姓名 + 电话）
 *   - 按姓名删除联系人
 *   - 按姓名查找联系人
 *   - 显示所有联系人
 *   - 交互式菜单操作
 *
 * 应用场景：
 *   作为单链表的实际应用案例，演示链表在信息管理中的使用
 */

#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <iostream>
#include <string>

using namespace std;

// ==================== Contact 结构体 ====================
// 联系人信息，包含姓名和电话号码
struct Contact {
    string name;   // 联系人姓名
    string phone;  // 联系人电话号码
};

// ==================== ContactNode 结构体 ====================
// 通讯录链表节点，存储一个联系人及其后继指针
struct ContactNode {
    Contact data;        // 联系人信息
    ContactNode* next;   // 指向下一个节点的指针

    // 节点构造函数：用联系人信息初始化节点，next 默认为空
    ContactNode(const Contact& val) : data(val), next(nullptr) {}
};

// ==================== ContactList 类 ====================
// 基于单链表的通讯录管理类
// 通过头指针管理联系人节点链表，支持增删查显等操作
class ContactList {
private:
    ContactNode* head;  // 链表头指针，指向第一个联系人节点
    int size;           // 当前联系人数量

public:
    // 构造函数：初始化空通讯录
    ContactList();

    // 析构函数：释放所有联系人节点内存
    ~ContactList();

    // 添加联系人：将新联系人 c 插入链表尾部
    void addContact(const Contact& c);

    // 删除联系人：按姓名查找并删除对应的联系人节点
    void deleteContact(const string& name);

    // 查找联系人：按姓名查找联系人并显示其信息
    void searchContact(const string& name);

    // 显示所有联系人：遍历链表并打印每个联系人的姓名和电话
    void displayContacts();

    // 通讯录菜单：提供交互式操作界面，循环处理用户选择
    void menu();
};

#endif
