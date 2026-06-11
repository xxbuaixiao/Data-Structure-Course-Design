#include "Array.h"

// 默认构造函数
Matrix::Matrix() : data(nullptr), rows(0), cols(0) {}

// 带参数构造函数：分配 rows×cols 的二维数组并初始化为 0
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data = new int* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols]();
    }
}

// 析构函数
Matrix::~Matrix() {
    if (data != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete [] data[i];
        }
        delete[] data;
    }
}

// 创建矩阵:先释放旧数据，再创建
void Matrix::create() {
    if (data != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }

    cout << "请输入矩阵的行数: ";
    cin >> rows;
    cout << "请输入矩阵的列数: ";
    cin >> cols;

    data = new int* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols];
    }

    cout << "请输入矩阵元素（按行输入）:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "第" << i + 1 << "行: ";
        for (int j = 0; j < cols; j++) {
            cin >> data[i][j];
        }
    }
    cout << "矩阵创建成功！" << endl;
}

// 显示矩阵
void Matrix::display() const {
    if (data == nullptr) {
        cout << "矩阵为空！" << endl;
        return;
    }

    cout << "矩阵内容:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}

// 矩阵乘法
void  Matrix::multiply(const Matrix& other) const {
    if (cols != other.rows) {
        cout << "矩阵乘法失败：第一个矩阵的列数必须等于第二个矩阵的行数！" << endl;
        return ;
    }

    Matrix result(rows, other.cols);        //可是这句话执行完result就被删了

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    if (result.getRows() > 0) {
        cout << "乘法结果:" << endl;
        result.display();
    }


    return ;
}

// 获取行数
int Matrix::getRows() const {
    return rows;
}

// 获取列数
int Matrix::getCols() const {
    return cols;
}

// 获取指定位置元素，越界返回 0
int Matrix::getElement(int i, int j) const {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
        return data[i][j];
    }
    return 0;
}

// 设置指定位置元素，越界则忽略
void Matrix::setElement(int i, int j, int val) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
        data[i][j] = val;
    }
}