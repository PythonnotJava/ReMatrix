#pragma once
//
// Created by A Luck Boy on 2023/4/24.
//

#ifndef _GLIBCXX_REMATRIX
#define _GLIBCXX_REMATRIX 1
#endif

#ifdef _GLIBCXX_IOSTREAM
#else
    #include <iostream>
#endif

#ifdef _GLIBCXX_CMATH
#else
    #include <cmath>
#endif

#ifdef _GLIBCXX_IOMANIP
#else
    #include <iomanip>
#endif

#ifdef _GLIBCXX_AUXILIARY
#else
#include "auxiliary.h"
#endif

#ifdef Element
#else
#define Element double
#endif

// 定义每个向量最大允许长度
#ifndef MAXLEN
#define MAXLEN 10
#endif

// 定义允许向量最大个数
#ifndef MAXCOUNT
#define MAXCOUNT 10
#endif

using namespace std;

// 换行
#ifndef NEWLINE
#define NEWLINE cout<<endl;
#endif

#ifndef T_ERROR
#define T_ERROR cout << "测试失败，此处代码有误！";
#endif

#ifndef CHECKSUC
#define CHECKSUC cout<< "成功地验证，是你想的那样！";
#endif

#ifndef CHECKNOT
#define CHECKNOT cout <<"确实不是你想的那样！";
#endif

#ifndef elif
#define elif else if
#endif

#ifndef END_SUCCESSFULLY
#define END_SUCCESSFULLY cout << "已成功退出运算！"<< endl;return 0;
#endif

// 输出小数的精确格式
#ifndef ROUND
#define ROUND 0
#endif

// 优先创建向量类，有向量类可以更方便组成矩阵
// Let's create Vector class firstly, so that we can make it easier to form matrices.

// 我希望传入的行/列向量是这样的，假如我想构造一个如下矩阵
/* 1 2 3 4 5
 * 0 9 9 0 1
 * 1 0 0 0 0
 * */
// 传入的默认是行向量（因为线性代数这本书大部分基于行向量讲解）
// 对于上面的矩阵，你可以这样传入三个行向量对象
// {1, 2, 3, 4, 5}, {0, 9, 9, 0, 1}, {1, 0, 0, 0, 0}

// 实质是一个行向量，但是内置了转置方法，可以获取对应的列向量
class Vector {
public:
    Element* data;
    int length;
    // 根据构造函数传入数据
    // Pass in data according to the constructor function
    // 第一个构造函数不建议使用，是为了转置矩阵
    Vector();
    explicit Vector(Element* _data, int _length = MAXLEN);
    ~Vector();

    // 打印测试行向量数据
    void printVec(int len=MAXLEN, bool ifself= true, int round=ROUND);

    // 获取转置列向量
    Vector* transpose();

    // 拷贝函数
    Vector(const Vector& other);

    // 判断两个向量是否一样
    bool isEqual(Vector & other) const;

    // k倍
    Vector multi(Element k);

    // 向量相加
    Vector add(Vector & other);

    // 行向量拼接，pos=true说明other拼到右侧
    Vector splice(Vector & other, bool pos= true);

    // 向量的某个索引位置数扩大k倍
    Vector expand(int index, Element k);

    // 获取单位化向量
    Vector unit();

    // 是否是零向量
    bool isZero() const;

    // 获取转置行向量
    friend Vector transpose2(Vector *vec, int row);

    // 两个向量做乘积，前者是行向量，
    // 后者是列向量（程序里面传入的还是行向量，请视为列向量），得到值，即向量内积
    Element inner(Vector & other) const;
    // 把向量逆序数元素组成的，求取逆序数
    // 考虑矩阵中逆序元素组不可能存在两个元素相同的情况，不考虑其他用途了
    // 另外，值得注意的是  我的这个向量传入的是索引，每个数比对应实际值少一，但丝毫不影响，具体不解释了
    // 虽然内置的data是Element类型（目前是double类的别名），
    // 但是会转换到整型且服务对象是索引，所以必定是整型间操作
    friend int getReverseOrderNumber(Vector & vec);
};

// 打印测试列向量数据
// 这是一个独立于类的方法，前提是你有一个列向量
void printVecC(Vector* vecs, int length, int round=ROUND);

// 矩阵的形状，row表示行数、column表示列数
typedef struct _Shape{
    int row;
    int column;
}Shape;

// 拼接矩阵传入对象
typedef struct _Splice{
    // if_lr表示是否左右拼接，如果为true，左右拼接，否则上下拼接
    bool if_lr;
    // 如果other_lr为true，other放在根据上面bool值决定放在右侧或者下面，反之
    bool other_lr;
} Splice;

// Special结构体
// 用于记录这是一个特殊的矩阵，比如说对角阵、三角阵、在一些难乎其难的计算上
// 但是前提是，该矩阵已经被你调用了如判断是不是方阵、对角阵等等等方法才会触发记录，否则默认全都不是
// 比如说行列式计算，如果我们提前知道这是一个上三角矩阵、我们可以一步计算出（即O(1)复杂度）行列式值
// 知道一个矩阵是对角矩阵，那它必定是三角矩阵等等
typedef struct _Special{
    // 是否上三角矩阵
    bool triUp;
    // 是否下三角矩阵
    bool triDown;
    // 是否主对角线矩阵
    bool digUp;
    // 是否副对角线矩阵
    bool digDown;
    // 是否是单位矩阵
    bool unit;
    // 是否是对称矩阵
    bool symmetry;
} Special;

// 仍要备注 ： 代码所涉及的知识点源于我对线性代数的浅薄理解
// 行向量为主序
class Matrix {
private:
    Vector _vecs[MAXCOUNT];
    int _row;
    int _column;
    Special spc;
public:
    // 形状
    Shape shape{};
    // vectors行向量组，注意，必须是行向量组
    // _column每个向量统一长度
    // _row表示传入的向量个数
    explicit Matrix(Vector * vectors, int _row, int _column);
    // 拷贝函数
    Matrix(const Matrix & other);
    ~Matrix();

    // 打印出直观可见的矩阵
    void printMatrix(int round=ROUND);
    // 判断是否是方阵
    bool isSquare() const;
    // 构造方阵同形状的单位矩阵，前提是方阵
    Matrix E();
    // 转置矩阵
    Matrix transpose();
    // 判断是不是对角阵，true表示判断是不是主对角阵，false表示判断是不是副对角阵，前提是对角阵
    bool isDig(bool if_main=true) ;
    // 判断是不是主对角线对称矩阵，前提是对角阵
    bool isSymmetric();
    // 判断两个矩阵是不是相同的矩阵
    bool isEqual(Matrix & other);
    bool operator ==(Matrix & other);
    // 矩阵拼接
    // A.splice(other, ...)
    // if_row=true表示A-other行方向拼接，反之
    // if_up为true，在行拼接时，A置于other左侧，反之；列拼接时，A置于other上面，反之
    Matrix splice(Matrix & other, Splice _splice={true, true});
    // 矩阵加（减）法，前提是形状一样
    Matrix add(Matrix & other);
    Matrix operator + (Matrix & other);

    // 数量与矩阵乘法
    Matrix multi(Element k);
    Matrix operator * (Element k);

    // 矩阵与矩阵乘法（矩阵内积）
    // A ^ other,A(mxn)的列必须与other(nxk)的行数相同，返回(mxk)的矩阵
    Matrix innerMulti(Matrix & other);
    Matrix operator ^ (Matrix & other);

    // 逆矩阵
    // 根据去掉的行列数获取矩阵的余子式矩阵
    // 请区别于行列式的余子式
    Matrix getRemainder(int row, int col);
    // 获取行列式的值，前提是这是一个方阵
    // 我的之前方法是使用代数余子式，一直递归到二阶余子式
    // 逆序排列法求值，和上面方法一样，都是超级耗时的工作，时间复杂度为O(n!)
    // 我有考虑化为三角矩阵法，但是这样虽然显著的降低了时间复杂度，但是需要考虑更多因素了
    // 因为传入的方阵不会太大，我决定使用代数余子式法
    Element det();
    // 判断矩阵是不是上（下）三角矩阵，传入if_up=true表示判断是不是上三角矩阵，反之
    // 前提是方阵
    bool ifTriMatrix(bool if_up=true) ;

    // 判断是不是奇异矩阵
    bool isSingularMat();

    // 矩阵的迹
    Element trace() const;
    // 伴随矩阵，前提是这是一个方阵
    // 第一种求伴随矩阵的方法
    Matrix getAccompany();
    // 第二种求伴随矩阵的方法
    Matrix getAccompanyT();
    // 求解逆矩阵
    // 根据 AA* = |A|E
    Matrix inv();
    // 获取同形状零矩阵
    Matrix Zero();
    // 矩阵的初等行（列）变换
    // lr表示行或列的索引
    // if_line=true说明行变换，否则列变换
    // 1.任一行（列）扩大非0倍，注意k最好不能为0，
    // 但是这个功能也可以作为指定一行全为0，所以不做0检测
    void getElementaryTransposeReSize(int lr, Element k, bool if_line= true);
    // 2.任两行（列）对换
    void getElementaryTransposeExchange(int lr1, int lr2, bool if_line=true);
    // 3.任一行（列）的k倍加到另一行
    // lr1是被加行，取lr2的值作为扩大值，但是不扩大lr2本身
    void getElementaryTransposAdd(int lr1, int lr2, double k, bool if_line= true);
    // 判断方阵是不是正交矩阵，即AA_T = E
    bool isOrthogon();
    // 矩阵的向量组单位化
    Matrix norm(bool if_line= false);
    /* 尚未实现的方法
    // 矩阵的秩
     int getRank() const;
    // 矩阵的特征值
     int * getEigenvalues() const;
    // 判断两个组成矩阵的两个向量组是否为等价向量组
     bool isEquivalentVectorSets(Matrix &other) const;
    // 组成矩阵的向量组是否线性无关
     bool isLinearlyIndependent() const;
     */
};

// 复制矩阵
static Matrix copy_mat(Matrix & other){
    auto copyMat = other;
    return copyMat;
}