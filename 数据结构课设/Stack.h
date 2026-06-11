/*
 * Stack.h - 栈模块头文件
 *
 * 功能说明：
 *   定义泛型顺序栈模板类 Stack<T>，基于数组实现，支持任意数据类型 T，
 *   提供进栈、出栈、取栈顶、判空、判满、显示等基本操作。
 *   提供表达式求值功能：
 *   - 中缀表达式转后缀表达式（逆波兰式）
 *   - 后缀表达式求值
 *   - 完整的表达式计算流程
 *
 * 常量说明：
 *   MAX_SIZE = 100  顺序栈的最大容量
 */

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;
const int MAX_SIZE = 100;  

template <typename T>
class Stack {
private:
    T data[MAX_SIZE];  
    int top;           // -1 表示空栈

public:
    Stack();
    ~Stack();

    // 进栈成功 true，错误 false
    bool push(const T& val);

    // 出栈成功 true，错误 false
    bool pop(T& val);

    // 取栈顶成功 true，错误 false (不弹出)
    bool getTop(T& val);

    int Top();
    // 判空,判满
    bool isEmpty() const;
    bool isFull() const;

    // 显示栈
    void display();
};

//表达式求值
class ExpressionEvaluator {
public:
    // 返回运算符的优先级：* / 为 2，+ - 为 1，其他为 0
    static int precedence(char op);

    // 中缀表达式转后缀表达式（逆波兰式）
    // 利用栈处理运算符优先级和括号
    static string infixToPostfix(const string& infix, bool& a);

    // 后缀表达式求值：遍历后缀表达式，遇到数字压栈，遇到运算符弹出两个操作数计算
    static double evaluatePostfix(const string& postfix);

    // 完整的表达式求值：先中缀转后缀，再对后缀求值，返回计算结果
    static double evaluateExpression(const string& infix, bool& a);
};

#endif
