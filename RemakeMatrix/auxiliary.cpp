//
// Created by A Luck Boy on 2023/4/26.
//
#include "auxiliary.h"
#include "rematrix.h"

Element power(int x, int y) { return (y == 0) ? 1 : (x * power(x, y-1)); }

void error_models(int model){
    switch (model) {
        case 0:
            cout << "零向量不能被单位化！\n";
            break;
        case 1:
            cout << "矩阵间形状不一致！\n";
            break;
        case 2:
            cout << "矩阵的行数不一致！\n";
            break;
        case 3:
            cout << "矩阵的列数不一致！\n";
            break;
        case 4:
            cout << "请保证是n阶方阵！\n";
            break;
        case 5:
            cout << "请确保矩阵可逆（非奇异矩阵 或者说 矩阵的秩不为0）！\n";
            break;
        case 6:
            cout << "请勿传入不在矩阵行（列）索引范围的数！\n";
            break;
        case 7:
            cout << "不满足矩阵内积条件（前者列数等于后者行数）！\n";
            break;
        case 8:
            cout << "向量的长度不一样！\n";
            break;
        case 9:
            cout << "索引不在向量索引范围内！\n";
            break;
        case 10:
            cout <<  "奇异矩阵没有逆矩阵！\n";
            break;
        default: cout << "匹配到错误的模式!\n";
            break;
    }
}

void swap_array(Element *arr1, Element *arr2, int len){
    auto temp = new Element [len];
    for (int i=0;i<len;i++){
        temp[i] = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = temp[i];
    }
    delete[] temp;
}

Element sums(Element * data, int len){
    Element _sum = 0;
    for (int i=0;i<len;i++) { _sum += data[i]; }
    return _sum;

}