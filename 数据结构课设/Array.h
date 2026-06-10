/*
 * Array.h - 数组/矩阵模块头文件
 *
 * 功能说明：
 *   定义 Matrix 类，实现二维矩阵的存储与基本运算：
 *   - 动态创建矩阵（用户输入行列及元素）
 *   - 显示矩阵
 *   - 矩阵乘法
 *   - 获取/设置指定位置的元素
 */

#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

using namespace std;

class Matrix {
private:
    int** data;   // 指向二维数组的二级指针，存储矩阵元素
    int rows;     
    int cols;     

public:
    Matrix();
    Matrix(int r, int c);
    ~Matrix();

    // 创建矩阵：提示用户输入行数、列数和各元素的值
    void create();

    // 显示矩阵：按行列格式打印矩阵所有元素
    void display() const;

    // 矩阵乘法：当前矩阵 * other，显示结果矩阵
    void multiply(const Matrix& other) const;

    // 获取矩阵行数
    int getRows() const;

    // 获取矩阵列数
    int getCols() const;

    // 获取第 i 行第 j 列的元素值（行列从0开始）
    int getElement(int i, int j) const;

    // 设置第 i 行第 j 列的元素值为 val（行列从0开始）
    void setElement(int i, int j, int val);
};

#endif
