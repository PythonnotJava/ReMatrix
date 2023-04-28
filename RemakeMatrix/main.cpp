//
// Created by A Luck Boy on 2023/4/24.
//

#include "rematrix.h"

int main() {
    Element data[5] = { 1.2, 1.4, 6., 0.4, .5 };
    Vector vec = Vector(data, 5);
    vec.printVec(5, true, 1);
    NEWLINE

    Vector vec_5 = vec.multi(-5);
    vec_5.printVec(5);
    NEWLINE
    
    Vector copy_vector = vec;
    copy_vector.printVec(5);
    NEWLINE

    Vector* vecs = vec.transpose();
    printVecC(vecs, 5);
    NEWLINE

    // 把列向量转置回来试试
    Vector trans_row_vec = transpose2(vecs, 5);
    trans_row_vec.printVec(5);
    NEWLINE

    // 判断trans_row_vec与vec是否相同
    if (trans_row_vec.isEqual(vec)) {CHECKSUC}
    else {T_ERROR}
    NEWLINE
    Element data1[5] = {1, 2, 3, 4, 5};
    Element data2[5] = {2, 3, 4, 5, 6};
    Element data3[5] = {1, 1, 1, 1, 1};
    Element data4[5] = {.5, .2, .3, .4, .8};
    Element data5[5] = {7, 0, 0, 0, 0};
    Vector vec1 = Vector(data1, 5);
    Vector vec2 = Vector(data2, 5);
    Vector vec3 = Vector(data3, 5);
    Vector vec4 = Vector(data4, 5);
    Vector vec5 = Vector(data5, 5);
    Vector vecs1[5] = {vec1, vec2, vec3, vec4, vec5};
    Matrix mat1 = Matrix(vecs1, 5, 5);
    mat1.printMatrix();
    NEWLINE

    if (mat1.isSquare()) { CHECKSUC}
    else { T_ERROR }
    NEWLINE

    Matrix e_mat1 = mat1.E();
    e_mat1.printMatrix();
    NEWLINE

    Vector vecs2[5] = {vec1, vec2, vec3, vec5};
    auto mat2 = Matrix(vecs2, 4, 5);
    mat2.printMatrix();
    NEWLINE

    // 转置矩阵
    mat2.transpose().printMatrix();
    NEWLINE

    // 判断是不是主对角矩阵
    if (e_mat1.isDig()){ CHECKSUC}
    else{ T_ERROR }
    NEWLINE

    // 创建一个副对角矩阵
    Element data6[3] = {0, 0, 7};
    Element data7[3] = {0, 3, 0};
    Element data8[3] = {0, 0, 0};
    Vector vec6 = Vector(data6, 3);
    Vector vec7 = Vector(data7, 3);
    Vector vec8 = Vector(data8, 3);
    Vector vecs3[3] = {vec6, vec7, vec8};
    Matrix mat3 = Matrix(vecs3, 3, 3);
    mat3.printMatrix();
    NEWLINE

    // 判断是不是主对角矩阵
    if (mat3.isDig()){T_ERROR}
    else{ CHECKSUC }
    NEWLINE

    // 判断是不是副对角矩阵
    if (mat3.isDig(false)){CHECKSUC}
    else{ T_ERROR }
    NEWLINE

// 判断单位阵是不是对称矩阵（怎么可能不是）
    if (e_mat1.isSymmetric()) {CHECKSUC }
    else {T_ERROR}
    NEWLINE

    // 判断下面的mat4是不是对称矩阵
    Element data9[5] = {3, 4, 6, 9, 0};
    Element data10[5] = {4, 5, 9, 9, 9};
    Element data11[5] = {5, 6, 0, 9, 8};
    Vector vec9 = Vector(data9, 5);
    Vector vec10 = Vector(data10, 5);
    Vector vec11 = Vector(data11, 5);
    Vector vecs4[5] = {vec1, vec2, vec9, vec10, vec11};
    auto mat4 = Matrix(vecs4, 5, 5);
    mat4.printMatrix()  ;
    NEWLINE

    if (mat4.isSymmetric()) { CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // mat3不是
    mat3.printMatrix();
    NEWLINE

    if (!mat3.isSymmetric()) {CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // 创造一个非方阵mat5测试
    Vector vecs5[5] = {vec1, vec2, vec11};
    auto mat5 = Matrix(vecs5, 3, 5);
    mat5.printMatrix();
    NEWLINE

    mat5.getRemainder(1, 1).printMatrix();
    NEWLINE

    // -3倍的mat5得到mat6
    auto mat6 = mat5.multi(-3);
    mat6.printMatrix();
    NEWLINE

    // -3倍的mat5得到mat7
    auto mat7 = mat5 * -3;
    mat7.printMatrix();
    NEWLINE

    // mat3余子矩阵M13
    mat3.getRemainder(0, 2).printMatrix();
    NEWLINE
    // mat4的余子矩阵M33
    mat4.getRemainder(2, 2).printMatrix();
    NEWLINE

    // mat7与mat5相加
    mat7.printMatrix();
    NEWLINE

    mat5.printMatrix();
    NEWLINE

    (mat7+mat5).printMatrix();
    NEWLINE

    auto mat8 = mat7+mat5;
    // 把mat8拼接到mat5右侧
    mat8.splice(mat5, {true, false}).printMatrix();
    NEWLINE
    // 把mat8拼接到mat5下侧
    mat8.splice(mat5, {false, false}).printMatrix();
    NEWLINE
    // 把mat8拼接到mat5左侧
    mat8.splice(mat5, {true, true}).printMatrix();
    NEWLINE
    // 把mat8拼接到mat5上侧
    mat8.splice(mat5, {false, true}).printMatrix();
    NEWLINE

    // 判断mat9是不是和mat5相同
    auto mat9 = Matrix(vecs5, 3, 5);
    if (mat5 == mat9) { CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // 逆序数
    Element data12[6] = {2, 3, 1, 5, 4, 6};
    Vector vec12 = Vector(data12, 6);
    vec12.printVec(6);
    NEWLINE

    cout << "getReverseOrderNumber: " << getReverseOrderNumber(vec12);
    NEWLINE

    // 判断单位阵是不是上三角矩阵
    if(e_mat1.ifTriMatrix(true)){CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // 判断单位阵是不是下三角矩阵
    if (e_mat1.ifTriMatrix(false)){CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // 创建一个新的mat10（矩阵）
    Element data13[5] = {1, 4, 0, 8, 5};
    Element data14[5] = {7, 4,2, 0, 9};
    Element data15[5] = {0, 0, 0, 1, 0};
    Element data16[5] = {6, 5, 3, 2, 2};
    Element data17[5] = {5, 4, 8, 7, 2};
    Vector vec13 = Vector(data13, 5);
    Vector vec14 = Vector(data14, 5);
    Vector vec15 = Vector(data15, 5);
    Vector vec16 = Vector(data16, 5);
    Vector vec17 = Vector(data17, 5);
    Vector vecs6[5] = {vec13, vec14, vec15, vec16, vec17};
    auto mat10 = Matrix(vecs6, 5, 5);
    mat10.printMatrix();
    NEWLINE

    // 对mat10进行第二行5倍的初等变换
    auto mat11 = mat10;
    mat10.getElementaryTransposeReSize(1, 5, true);
    mat10.printMatrix();
    NEWLINE

    // 再对mat10进行第三列-2倍的初等变换
    mat10.getElementaryTransposeReSize(2, -2, false);
    mat10.printMatrix();
    NEWLINE

    // 继续对mat10进行 2 3行对换
    mat10.getElementaryTransposeExchange(1, 2, true);
    mat10.printMatrix();
    NEWLINE

    // 1 5列对换
    mat10.getElementaryTransposeExchange(0, 4, false);
    mat10.printMatrix();
    NEWLINE

    // 把第3行的2.3倍加到第2行
    mat10.getElementaryTransposAdd(1, 2, 2.3, true);
    mat10.printMatrix();
    NEWLINE

    // 把第一列的-2倍加到第五列
    mat10.getElementaryTransposAdd(4, 0, -2, false);
    mat10.printMatrix();
    NEWLINE

    mat11.printMatrix();
    NEWLINE

    auto mat12 = mat11.getRemainder(0, 0).getRemainder(0, 0);
    mat12.printMatrix();
    NEWLINE

    // 计算行列式值
    mat12.printMatrix();
    NEWLINE
    cout << mat12.det() << endl;

    e_mat1.printMatrix();
    NEWLINE
    cout << e_mat1.det() << endl;

    mat11.printMatrix();
    NEWLINE
    cout << mat11.det() << endl;

    // 创建2个奇异矩阵
    Element data18[4] = {1, 2, 3, 4};
    Element data19[4] = {5, 6, 7, 8};
    Element data20[4] = {9, 10, 11, 12};
    Element data21[4] = {13, 14, 15, 16};
    Element data22[4] = {};
    Vector vec18 = Vector(data18, 4);
    Vector vec19 = Vector(data19, 4);
    Vector vec20 = Vector(data20, 4);
    Vector vec21 = Vector(data21, 4);
    Vector vec22 = Vector(data22, 4);
    Vector vecs7[4] = {vec18, vec19, vec20, vec21};
    Vector vecs8[4] = {vec18, vec19, vec20, vec22};
    auto mat13 = Matrix(vecs7, 4, 4);
    auto mat14 = Matrix(vecs8, 4, 4);
    mat13.printMatrix();
    NEWLINE
    mat14.printMatrix();
    NEWLINE

    if (mat13.isSingularMat() && mat14.isSingularMat()) {CHECKSUC}
    else {T_ERROR}
    NEWLINE

    mat11.printMatrix();
    NEWLINE

    // 两种方式求取mat11的伴随矩阵
    auto mat15 = mat11.getAccompany();
    mat15.printMatrix();
    NEWLINE

    mat11.getAccompanyT().printMatrix();
    NEWLINE

    // mat11与mat11的矩阵内积验证是不是有AA* = |A|E
    // det(mat11) == 994
    (mat15 ^ mat11).printMatrix();
    NEWLINE

    (mat11 ^ mat15).printMatrix();
    NEWLINE

    // mat11的逆矩阵
    auto mat16 = mat11.inv();
    mat16.printMatrix();
    NEWLINE

    // 验证AA_1 == E
    (mat16 ^ mat11).printMatrix();
    NEWLINE

    vec11.printVec(5);
    NEWLINE

    // 单位化向量11
    vec11.unit().printVec(5, true, 4);
    NEWLINE

    // 单位阵的迹
    cout << "Trace is : " << e_mat1.trace()  <<endl;

    Vector(data1).printVec();
    NEWLINE

    mat10.printMatrix();
    NEWLINE

    auto copy_mat1 = mat10;
    mat10.getElementaryTransposeReSize(0, 10, true);
    mat10.printMatrix();
    NEWLINE

    copy_mat1.printMatrix();
    NEWLINE

    // 5倍的单位矩阵
    (e_mat1 * 5).printMatrix();
    NEWLINE

    // 伴随矩阵
    auto adj = (e_mat1 * 5).getAccompany();
    adj.printMatrix();
    NEWLINE

    // 记录adj是主对角线矩阵
    adj.isDig();
    adj.getAccompany().printMatrix();
    NEWLINE

    // 判断是不是正交矩阵
    // get 1 == true
    cout << e_mat1.isOrthogon() << endl;

    e_mat1.norm().printMatrix();
    NEWLINE

    e_mat1.norm(true).printMatrix();
    NEWLINE

    mat11.printMatrix();
    NEWLINE

    mat11.norm(true).printMatrix(5);
    NEWLINE

    mat11.norm(false).printMatrix(5);
    NEWLINE

    END_SUCCESSFULLY
}