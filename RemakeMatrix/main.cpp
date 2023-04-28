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

    // ��������ת�û�������
    Vector trans_row_vec = transpose2(vecs, 5);
    trans_row_vec.printVec(5);
    NEWLINE

    // �ж�trans_row_vec��vec�Ƿ���ͬ
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

    // ת�þ���
    mat2.transpose().printMatrix();
    NEWLINE

    // �ж��ǲ������ԽǾ���
    if (e_mat1.isDig()){ CHECKSUC}
    else{ T_ERROR }
    NEWLINE

    // ����һ�����ԽǾ���
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

    // �ж��ǲ������ԽǾ���
    if (mat3.isDig()){T_ERROR}
    else{ CHECKSUC }
    NEWLINE

    // �ж��ǲ��Ǹ��ԽǾ���
    if (mat3.isDig(false)){CHECKSUC}
    else{ T_ERROR }
    NEWLINE

// �жϵ�λ���ǲ��ǶԳƾ�����ô���ܲ��ǣ�
    if (e_mat1.isSymmetric()) {CHECKSUC }
    else {T_ERROR}
    NEWLINE

    // �ж������mat4�ǲ��ǶԳƾ���
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

    // mat3����
    mat3.printMatrix();
    NEWLINE

    if (!mat3.isSymmetric()) {CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // ����һ���Ƿ���mat5����
    Vector vecs5[5] = {vec1, vec2, vec11};
    auto mat5 = Matrix(vecs5, 3, 5);
    mat5.printMatrix();
    NEWLINE

    mat5.getRemainder(1, 1).printMatrix();
    NEWLINE

    // -3����mat5�õ�mat6
    auto mat6 = mat5.multi(-3);
    mat6.printMatrix();
    NEWLINE

    // -3����mat5�õ�mat7
    auto mat7 = mat5 * -3;
    mat7.printMatrix();
    NEWLINE

    // mat3���Ӿ���M13
    mat3.getRemainder(0, 2).printMatrix();
    NEWLINE
    // mat4�����Ӿ���M33
    mat4.getRemainder(2, 2).printMatrix();
    NEWLINE

    // mat7��mat5���
    mat7.printMatrix();
    NEWLINE

    mat5.printMatrix();
    NEWLINE

    (mat7+mat5).printMatrix();
    NEWLINE

    auto mat8 = mat7+mat5;
    // ��mat8ƴ�ӵ�mat5�Ҳ�
    mat8.splice(mat5, {true, false}).printMatrix();
    NEWLINE
    // ��mat8ƴ�ӵ�mat5�²�
    mat8.splice(mat5, {false, false}).printMatrix();
    NEWLINE
    // ��mat8ƴ�ӵ�mat5���
    mat8.splice(mat5, {true, true}).printMatrix();
    NEWLINE
    // ��mat8ƴ�ӵ�mat5�ϲ�
    mat8.splice(mat5, {false, true}).printMatrix();
    NEWLINE

    // �ж�mat9�ǲ��Ǻ�mat5��ͬ
    auto mat9 = Matrix(vecs5, 3, 5);
    if (mat5 == mat9) { CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // ������
    Element data12[6] = {2, 3, 1, 5, 4, 6};
    Vector vec12 = Vector(data12, 6);
    vec12.printVec(6);
    NEWLINE

    cout << "getReverseOrderNumber: " << getReverseOrderNumber(vec12);
    NEWLINE

    // �жϵ�λ���ǲ��������Ǿ���
    if(e_mat1.ifTriMatrix(true)){CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // �жϵ�λ���ǲ��������Ǿ���
    if (e_mat1.ifTriMatrix(false)){CHECKSUC}
    else {T_ERROR}
    NEWLINE

    // ����һ���µ�mat10������
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

    // ��mat10���еڶ���5���ĳ��ȱ任
    auto mat11 = mat10;
    mat10.getElementaryTransposeReSize(1, 5, true);
    mat10.printMatrix();
    NEWLINE

    // �ٶ�mat10���е�����-2���ĳ��ȱ任
    mat10.getElementaryTransposeReSize(2, -2, false);
    mat10.printMatrix();
    NEWLINE

    // ������mat10���� 2 3�жԻ�
    mat10.getElementaryTransposeExchange(1, 2, true);
    mat10.printMatrix();
    NEWLINE

    // 1 5�жԻ�
    mat10.getElementaryTransposeExchange(0, 4, false);
    mat10.printMatrix();
    NEWLINE

    // �ѵ�3�е�2.3���ӵ���2��
    mat10.getElementaryTransposAdd(1, 2, 2.3, true);
    mat10.printMatrix();
    NEWLINE

    // �ѵ�һ�е�-2���ӵ�������
    mat10.getElementaryTransposAdd(4, 0, -2, false);
    mat10.printMatrix();
    NEWLINE

    mat11.printMatrix();
    NEWLINE

    auto mat12 = mat11.getRemainder(0, 0).getRemainder(0, 0);
    mat12.printMatrix();
    NEWLINE

    // ��������ʽֵ
    mat12.printMatrix();
    NEWLINE
    cout << mat12.det() << endl;

    e_mat1.printMatrix();
    NEWLINE
    cout << e_mat1.det() << endl;

    mat11.printMatrix();
    NEWLINE
    cout << mat11.det() << endl;

    // ����2���������
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

    // ���ַ�ʽ��ȡmat11�İ������
    auto mat15 = mat11.getAccompany();
    mat15.printMatrix();
    NEWLINE

    mat11.getAccompanyT().printMatrix();
    NEWLINE

    // mat11��mat11�ľ����ڻ���֤�ǲ�����AA* = |A|E
    // det(mat11) == 994
    (mat15 ^ mat11).printMatrix();
    NEWLINE

    (mat11 ^ mat15).printMatrix();
    NEWLINE

    // mat11�������
    auto mat16 = mat11.inv();
    mat16.printMatrix();
    NEWLINE

    // ��֤AA_1 == E
    (mat16 ^ mat11).printMatrix();
    NEWLINE

    vec11.printVec(5);
    NEWLINE

    // ��λ������11
    vec11.unit().printVec(5, true, 4);
    NEWLINE

    // ��λ��ļ�
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

    // 5���ĵ�λ����
    (e_mat1 * 5).printMatrix();
    NEWLINE

    // �������
    auto adj = (e_mat1 * 5).getAccompany();
    adj.printMatrix();
    NEWLINE

    // ��¼adj�����Խ��߾���
    adj.isDig();
    adj.getAccompany().printMatrix();
    NEWLINE

    // �ж��ǲ�����������
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