//
// Created by A Luck Boy on 2023/4/26.
//
// 辅助函数库，一些简单的实现
#ifndef _GLIBCXX_AUXILIARY
#define _GLIBCXX_AUXILIARY 1
#endif

#ifndef Element
    typedef double Element;
#endif

// 求整数x的非零y次幂，不考虑bug
Element power(int x, int y);

// 矩阵操作报错模式
// 0 "零向量不能被单位化！\n"
// 1 "矩阵间形状不一致！\n";
// 2 "矩阵的行数不一致！\n";
// 3 "矩阵的列数不一致！\n";
// 4 "请保证是n阶方阵！\n";
// 5 "请确保矩阵可逆（非奇异矩阵 或者说 矩阵的秩不为0）！\n";
// 6 "请勿传入不在矩阵行（列）索引范围的数！\n"
// 7 "不满足矩阵内积条件（前者列数等于后者行数）！\n"
// 8 "向量的长度不一样！\n"
// 9 "索引不在向量索引范围内！\n"
// 10 "奇异矩阵没有逆矩阵！\n"
void error_models(int model);

// 交换两个数组的数据
void swap_array(Element *arr1, Element *arr2, int len);

// 求和
Element sums(Element * data, int len);