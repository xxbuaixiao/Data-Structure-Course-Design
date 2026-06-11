#include "LinkedList.h"

    template <typename T>
    LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

    template <typename T>
    LinkedList<T>::~LinkedList() {
        clear();
    }

    // 清空链表：释放所有节点内存，重置头指针和长度
    template <typename T>
    void LinkedList<T>::clear() {
        Node<T>* current = head;  
        while (current != nullptr) {
            Node<T>* temp = current;  
            current = current->next; 
            delete temp;             
        }
        head = nullptr;  
        size = 0;        
    }

    // 创建链表：先清空原有数据，再手动输入元素创建新链表
    template <typename T>
    void LinkedList<T>::create() {
        clear();  
        int n;
        cout << "请输入链表元素个数: ";
        cin >> n;
        //确保输入正确
        while (1) {
            if (n <= 0 || !cin) {
                cin.clear();
                cin.ignore(10000, '\n');        //清空缓冲区里的垃圾字符
                system("cls");
                cout << "元素输入不合法,重新输入" << endl;
                cin >> n;
            }
            else
            {
                break;
            }
        }

        cout << "请输入" << n << "个元素: ";
        for (int i = 0; i < n; i++) {
            T val;
            cin >> val;          // 输入元素值
            insert(i, val);      // 依次插入到链表尾部
        }
        cout << "链表创建成功！" << endl;
    }

    // 在指定位置 pos 插入元素 val
    template <typename T>
    void LinkedList<T>::insert(int pos, const T& val) {
        // 判断插入位置是否合法
        if (pos < 0 || pos > size) {
            cout << "插入位置无效！" << endl;
            return;
        }

        Node<T>* newNode = new Node<T>(val);  // 创建新节点

        if (pos == 0) {       
            newNode->next = head;
            head = newNode;
        }
        else {                
            Node<T>* current = head;
            for (int i = 0; i < pos - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++; 
        cout << "插入成功！" << endl;
    }

    // 删除指定位置 pos 的元素
    template <typename T>
    void LinkedList<T>::remove(int pos) {
        // 判断删除位置是否合法
        if (isEmpty() || pos < 0 || pos >= size) {
            cout << "删除位置无效！" << endl;
            return;
        }

        Node<T>* temp;
        if (pos == 0) {       
            temp = head;
            head = head->next;
        }
        else {               
            Node<T>* current = head;
            for (int i = 0; i < pos - 1; i++) {
                current = current->next;
            }
            temp = current->next;
            current->next = temp->next;
        }
        delete temp;   
        size--;        
        cout << "删除成功！" << endl;
    }

    // 查找元素 val，找到返回下标，找不到返回 -1
    template <typename T>
    int LinkedList<T>::find(const T& val) {
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == val) {
                return index;  
            }
            current = current->next;
            index++;
        }
        return -1; 
    }

    // 遍历输出链表所有元素
    template <typename T>
    void LinkedList<T>::display() {
        if (isEmpty()) {
            cout << "链表为空！" << endl;
            return;
        }

        Node<T>* current = head;
        cout << "链表元素: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // 获取链表当前元素个数
    template <typename T>
    int LinkedList<T>::getSize() const {
        return size;
    }

    // 判断链表是否为空
    template <typename T>
    bool LinkedList<T>::isEmpty() const {
        return head == nullptr;
    }

    // 显式实例化模板，支持 int 类型（解决模板分离编译问题）
    template class LinkedList<int>;