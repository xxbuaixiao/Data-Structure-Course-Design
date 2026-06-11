#include "Stack.h"

// 构造函数：初始化栈顶指针为 -1（表示空栈）
template <typename T>
Stack<T>::Stack() : top(-1) {}


template <typename T>
Stack<T>::~Stack() {}

// 进栈：先检查栈满，再将值放入 top+1 位置
template <typename T>
bool Stack<T>::push(const T& val) {
    if (isFull()) {
        cout << "栈已满！" << endl;
        return false;
    }
    data[++top] = val;
    return true;
}

// 出栈：先检查栈空，再返回 top 位置的元素并令 top 减 1
template <typename T>
bool Stack<T>::pop(T& val) {
    if (isEmpty()) {
        cout << "栈为空！" << endl;
        return false;
    }
    val = data[top--];
    return true;
}

// 取栈顶：只读取不弹出，栈空则返回 false
template <typename T>
bool Stack<T>::getTop(T& val) {
    if (isEmpty()) {
        cout << "栈为空！" << endl;
        return false;
    }
    val = data[top];
    return true;
}

template<typename T>
int Stack<T>::Top()
{
    return top;
}

// 判空：栈顶指针为 -1 则为空
template <typename T>
bool Stack<T>::isEmpty() const {
    return top == -1;
}

// 判满：栈顶指针达到最大容量-1 则为满
template <typename T>
bool Stack<T>::isFull() const {
    return top == MAX_SIZE - 1;
}

// 显示栈：从栈底到栈顶依次输出所有元素
template <typename T>
void Stack<T>::display() {
    if (isEmpty()) {
        cout << "栈为空！" << endl;
        return;
    }
    cout << "栈元素（从栈底到栈顶）: ";
    for (int i = 0; i <= top; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

//ExpressionEvaluator 类

// 运算符优先级：+/- 为 1，* / 为 2，其他为 0
int ExpressionEvaluator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 中缀转后缀：
string ExpressionEvaluator::infixToPostfix(const string& infix, bool& a) {
    Stack<char> opStack;
    string postfix;

    for (char c : infix) {
        if (isdigit(c) || c == '.') {
            postfix += c;
        }
        else if (c == '(') {
            opStack.push(c);
        }
        else if (c == ')') {
            char op;
            while (!opStack.isEmpty() && opStack.getTop(op) && op != '(') {
                opStack.pop(op);
                postfix += op;
            }
            //补充一个括号对应
            if (!opStack.isEmpty() && opStack.getTop(op) && op == '(') {
                opStack.pop(op); 
            }
            else {
                
                cout << "表达式错误：右括号没有匹配的左括号！" << endl;
                a = 0;
                return ""; 
            }
        }
        else {
            char topOp;
            while (!opStack.isEmpty() && opStack.getTop(topOp) && precedence(topOp) >= precedence(c)) {
                opStack.pop(topOp);
                postfix += topOp;
            }
            opStack.push(c);
        }
    }

    // 把栈里剩下的运算符弹出来
    char op;
    while (!opStack.isEmpty()) {
        opStack.getTop(op);
        if (op == '(') {
            cout << "错误：有未闭合的左括号！" << endl;
            a = 0;
            return "";
        }
        opStack.pop(op);
        postfix += op;
    }
    return postfix;
}

// 后缀求值：
double ExpressionEvaluator::evaluatePostfix(const string& postfix) {

    Stack<double> numStack;

    for (char c : postfix) {
        if (isdigit(c)) {
            numStack.push(c - '0');
        }
        else {
            double b, a;
            numStack.pop(b);
            numStack.pop(a);
            switch (c) {
            case '+': numStack.push(a + b); break;
            case '-': numStack.push(a - b); break;
            case '*': numStack.push(a * b); break;
            case '/':
                if (b == 0) {
                    cout << "错误：除数不能为零！" << endl;
                    return 0;
                }
                numStack.push(a / b);
                break;
            }
        }
    }

    double result;
    numStack.pop(result);
    return result;
}

// 表达式求值主函数：中缀 → 后缀 → 求值
double ExpressionEvaluator::evaluateExpression(const string& infix,bool& a) {
    string postfix = infixToPostfix(infix,a);
    if (a)
    {
        cout << "后缀表达式: " << postfix << endl;
        return evaluatePostfix(postfix);
    }
    else
    {
        return 0;
    }
   
   
}

// 显式实例化模板，确保链接器能找到这些类型的实现
template class Stack<int>;
template class Stack<char>;
template class Stack<double>;