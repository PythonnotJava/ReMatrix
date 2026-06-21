//
// Created by A Luck Boy on 2023/4/24.
//
#include "rematrix.h"

Vector::Vector() {
    this->length = 1;
    this->data = new Element[1];
    this->data[0] = 0.;
}

Vector::Vector(Element* _data, int _length) {
    this->length = _length;
    this->data = new Element[_length]();
    for (int i = 0; i < length; i++) {
        this->data[i] = _data[i];
    }
}

// [BugFix #1] 析构函数必须释放 data，否则内存泄漏
Vector::~Vector() {
    delete[] data;
}

Vector::Vector(const Vector &other) {
    this->length = other.length;
    data = new Element[length];
    for (int i = 0; i < length; i++) {
        data[i] = other.data[i];
    }
}

// [BugFix #2] 赋值运算符深拷贝，防止浅拷贝导致 double-free / 数据串改
Vector& Vector::operator=(const Vector &other) {
    if (this == &other) return *this;
    delete[] data;
    this->length = other.length;
    data = new Element[length];
    for (int i = 0; i < length; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

Vector Vector::expand(int index, double k) {
    if (index < 0 || index > length-1){
        error_models(9);
        exit(EXIT_FAILURE);
    }
    auto _data = new Element [length];
    for (int i=0;i<length;i++){ _data[i] = data[i];}
    _data[index] = _data[index] * k;
    auto vec = Vector(_data, length);
    delete[] _data;
    return vec;
}

Vector * Vector::transpose() {
    auto* vecs = new Vector[length];
    for (int i = 0; i < length; i++) {
        Vector temp = Vector();
        temp.data[0] = data[i];
        vecs[i] = temp;
    }
    return vecs;
}

bool Vector::isEqual(Vector &other) const {
    if (other.length == this->length){
        for (int i=0;i< this->length;i++){
            if (this->data[i] != other.data[i]) return false;
        }
        return true;
    }
    return false;
}

// [BugFix #3] 原实现使用默认构造 Vector()（只分配1个元素）再写入length个元素 → 越界
Vector Vector::multi(Element k) {
    auto _data = new Element[length];
    for (int i = 0; i < length; i++) {
        _data[i] = data[i] * k;
    }
    auto vec = Vector(_data, length);
    delete[] _data;
    return vec;
}

Vector Vector::add(Vector &other) {
    if (other.length != this->length){
        error_models(8);
        exit(EXIT_FAILURE);
    }
    auto vec_data = new Element[this->length];
    for (int i=0;i<length;i++){
        vec_data[i] = this->data[i] + other.data[i];
    }
    auto vec = Vector(vec_data, length);
    delete[] vec_data;
    return vec;
}

bool Vector::isZero() const {
    int _count = 0;
    for(int i=0;i<length;i++) {if(data[i] == 0) ++_count; }
    return _count == length;
}

Vector Vector::unit() {
    if (isZero()) { error_models(0);exit(EXIT_FAILURE); }
    auto datas = new Element[length];
    for (int i=0;i<length;i++){ datas[i] = this->data[i]* this->data[i];}
    Element mod = pow(sums(datas, length), .5);
    delete[] datas;
    auto _dat = new Element [length];
    for (int i=0;i<length;i++){
        _dat[i] = this->data[i] / mod;
    }
    auto vec = Vector(_dat, length);
    delete[] _dat;
    return vec;
}

Element Vector::inner(Vector &other) const{
    if (this->length != other.length) { error_models(8);exit(EXIT_FAILURE); }
    Element e = 0.;
    for (int i=0;i<length;i++){
        e += this->data[i] * other.data[i];
    }
    return e;
}

Vector transpose2(Vector *vec, int row){
    auto data = new Element[row];
    for (int _row=0;_row<row;_row++){
        data[_row] = vec[_row].data[0];
    }
    auto _vec = Vector(data, row);
    delete[] data;
    return _vec;
}

void Vector::printVec(int len ,bool ifself, int round) {
    if (ifself) { cout << "\t\033[1;32m[ "; }
    else {cout << "\n\t\033[1;32m[ "; }
    for (int i = 0; i < len - 1; i++) {
        cout << fixed << setprecision(round)<< data[i] << "  ";
    }
    cout << fixed << setprecision(round)<< data[len - 1] << " ";
    cout << fixed << setprecision(ROUND);
    cout << "\033[1;32m]";
}

void printVecC(Vector* vecs, int length, int round){
    cout << "\t\033[1;32m[ ";
    for (int i = 0; i < length; i++) {
        cout << "[ " << fixed << setprecision(round)<< vecs[i].data[0] << " \033[1;32m] ";
    }
    cout << fixed << setprecision(ROUND);
    cout << "\033[1;32m]";
}

Vector Vector::splice(Vector &other, bool pos) {
    auto _data = new Element[this->length + other.length];
    if (pos){
        for (int i=0;i< this->length;i++) _data[i] = this->data[i];
        for (int i=0;i< other.length;i++) _data[i+ this->length] = other.data[i];
    }
    else{
        for (int i=0;i< other.length;i++) _data[i] = other.data[i];
        for (int i=0;i< this->length;i++) _data[i+other.length] = this->data[i];
    }
    auto vec = Vector(_data, this->length+other.length);
    delete[] _data;
    return vec;
}

int getReverseOrderNumber(Vector & vec) {
    int _count = 0;
    for (int i=0;i< vec.length-1;i++){
        for (int j=i+1;j<vec.length;j++){ if(vec.data[i] > vec.data[j]) ++_count;  }  }
    return _count;
}

// The core codes of the Matrix
Matrix::Matrix(Vector * vectors, int _row, int _column){
    this->shape =  {_row, _column};
    this->_row = _row;
    this->_column = _column;
    for (int row=0;row<this->_row;row++) {
        this->_vecs[row] = vectors[row];
        this->_vecs[row].length = _column;
    }
    this->spc = {false, false, false, false, false, false};
}

Matrix::Matrix(const Matrix &other) {
    this->_row = other._row;
    this->_column = other._column;
    for (int i=0;i< this->_row;i++)
    {
        this->_vecs[i] = other._vecs[i];
        this->_vecs[i].length = other._vecs[i].length;
    }
    this->shape.row = other.shape.row;
    this->shape.column = other.shape.column;
    this->spc.digUp = other.spc.digUp;
    this->spc.digDown = other.spc.digDown;
    this->spc.triDown = other.spc.triDown;
    this->spc.triUp = other.spc.triUp;
    this->spc.unit = other.spc.unit;
    this->spc.symmetry = other.spc.symmetry;
}

Matrix::~Matrix() = default;

void Matrix::printMatrix(int round) {
    cout << "\t============当前矩阵============";
    for (int vec=0;vec< this->_row;vec++){
        this->_vecs[vec].printVec(this->_column, false, round);
    }
    cout << "\n\t===============================";
}

bool Matrix::isSquare() const { return _row == _column; }

Matrix Matrix::E() {
    if (!isSquare()) { error_models(4); exit(EXIT_FAILURE); }
    auto vecs = new Vector[this->_row];
    for (int i=0;i< this->_column;i++){
        auto e_vector = new Element[_row];
        for (int j=0;j!=_row;j++){
            e_vector[j] = 0;
        }
        e_vector[i] = 1;
        vecs[i] = Vector(e_vector, _row);
        delete[] e_vector;
    }
    auto e = Matrix(vecs, _row, _row);
    e.spc = {true, true, true, false, true, true};
    return e;
}

Matrix Matrix::transpose() {
    if (this->spc.unit) { return copy_mat(*this);}
    if (this->spc.symmetry) {return copy_mat(*this); }
    auto vecs = new Vector[this->_column];
    for (int i=0;i< this->_column;i++){
        auto data = new Element[this->_column];
        for (int dat=0;dat< this->_column;dat++){
            data[dat] = this->_vecs[dat].data[i];
        }
        vecs[i] = Vector(data, this->_row);
        delete[] data;
    }
    return Matrix(vecs, this->_column, this->_row);
}

bool Matrix::isDig(bool if_main) {
    if (!isSquare()) { error_models(4);exit(EXIT_FAILURE) ;}
    if (if_main){
        if (this->spc.unit) {
            this->spc.digUp = true;
            return true;
        }
        if (this->spc.symmetry) {
            this->spc.digUp = true;
            return true;
        }
        for (int i=0;i< this->_row;i++){
            for (int j=0;j< this->_column;j++){
                if (i!=j) {
                    if ( this->_vecs[i].data[j] != 0) return false;
                }
            }
        }
        this->spc.digUp = true;
        return true;
    }
    else{
        for (int i=0;i< this->_row;i++){
            for (int j=0;j< this->_column;j++){
                if (i != this->_row-j-1){
                    if (this->_vecs[i].data[j] != 0) return false;
                }
            }
        }
    }
    this->spc.digDown = true;
    return true;
}

bool Matrix::isSymmetric() {
    if(!isSquare()) { error_models(4);exit(EXIT_FAILURE) ;}
    if (this->spc.unit) {
        this->spc.symmetry = true;
        return true;
    }
    for (int i=0;i< this->_row;i++){
        for (int j=0;j< this->_column;j++)
        {
            if (this->_vecs[i].data[j] != this->_vecs[j].data[i]) return false;
        }
    }
    this->spc.symmetry = true;
    return true;
}

// [BugFix #4] 修复两处 bug:
//   a) 边界检查 "row > this->_column-1" 应为 "col > this->_column-1"
//   b) 构造子矩阵的 Vector 长度应为 this->_column-1 而非 this->_column（否则越界读取）
Matrix Matrix::getRemainder(int row, int col) {
    if (this->_row <= 1 || this->_column <= 1) { error_models(6);exit(EXIT_FAILURE); }
    if ((row < 0 || row > this->_row-1) || (col < 0 || col > this->_column-1))
    {
        error_models(6);
        exit(EXIT_FAILURE);
    }
    auto vecs = new Vector[this->_row-1];
    int index = 0;
    for (int r=0;r< this->_row;r++){
        int index2 = 0;
        if (r != row){
            auto data = new Element[this->_column-1];
            for (int c=0;c< this->_column;c++){
                if (c != col) {
                    data[index2] = this->_vecs[r].data[c];
                    index2++;
                }
            }
            auto temp = Vector(data, this->_column - 1);
            delete[] data;
            vecs[index] = temp;
            index++;
        }
    }
    return Matrix(vecs, _row-1, _column-1);
}

Matrix Matrix::multi(Element k) {
    auto vecs = new Vector[this->_row];
    for (int i=0;i< this->_row;i++)
    {
        vecs[i] = this->_vecs[i].multi(k);
    }
    return Matrix(vecs, _row, _column);
}

Matrix Matrix::operator * (Element k) { return multi(k); }

Matrix Matrix::add(Matrix &other) {
    if (other._column == this->_column && other._row == this->_row){
        auto vecs = new Vector[this->_row];
        for (int i=0;i< this->_row;i++){
            vecs[i] = this->_vecs[i].add(other._vecs[i]);
        }
        return Matrix(vecs, this->_row, this->_column);
    } else{
        error_models(1);
        exit(EXIT_FAILURE);
    }
}

Matrix Matrix::operator+( Matrix &other) {return add(other);}

Matrix Matrix::splice(Matrix &other, Splice _splice) {
    // 如果左右拼接
    if (_splice.if_lr){
        if (this->_row != other._row) { error_models(2); exit(EXIT_FAILURE); }
        auto vesc = new Vector[this->_row];
        // 放other于右侧
        if (_splice.other_lr){
            for (int i=0;i< this->_row;i++){ vesc[i] = this->_vecs[i].splice(other._vecs[i]); }
        }
        else { for (int i=0;i< this->_row;i++)vesc[i] = other._vecs[i].splice(this->_vecs[i]);}
        return Matrix(vesc, this->_row, this->_column+ other._column);
    }
    // 如果上下拼接
    else
    {
        if (this->_column != other._column) { error_models(3);exit(EXIT_FAILURE);}
        auto vesc = new Vector[this->_row+other._row];
        // 放other于下面
        if (_splice.other_lr) {
            for(int r=0;r< this->_row;r++) vesc[r] = this->_vecs[r];
            for(int r=0;r< other._row;r++) vesc[r+ this->_row] = other._vecs[r];
        }
        else{
            for(int r=0;r< other._row;r++) vesc[r] = other._vecs[r];
            for(int r=0;r< this->_row;r++) vesc[r+ other._row] = this->_vecs[r];
        }
        return Matrix(vesc, this->_row+ other._row, this->_column);
    }
}

Matrix Matrix::operator^(Matrix &other) {  return innerMulti(other);}

bool Matrix::isEqual(Matrix &other) {
    if (other._row == this->_row && other._column == this->_column){
        for (int i=0;i< this->_row;i++){
            if (!this->_vecs[i].isEqual(other._vecs[i])) return false;
        }
        this->spc.symmetry = other.spc.symmetry = (this->spc.symmetry || other.spc.symmetry);
        this->spc.digUp = other.spc.digUp = (this->spc.digUp || other.spc.digUp);
        this->spc.digDown = other.spc.digDown = (this->spc.digDown || other.spc.digDown);
        this->spc.triDown = other.spc.triDown = (this->spc.triDown || other.spc.triDown);
        this->spc.triUp = other.spc.triUp = (this->spc.triUp || other.spc.triUp);
        this->spc.unit = other.spc.unit = (this->spc.unit || other.spc.unit);
        return true;
    }
    return false;
}

bool Matrix::operator==(Matrix &other) { return isEqual(other);}

// [BugFix #5] 下三角判断的 else 分支误写 spc.triUp = true，应为 spc.triDown = true
bool Matrix::ifTriMatrix(bool if_up)  {
    if (!isSquare()) { error_models(4);exit(EXIT_FAILURE); }
    if (this->spc.unit){
        this->spc.triUp = true;
        this->spc.triDown = true;
        return true;
    }
    if (if_up){
        for (int i=1;i< this->_row;i++) {
            for (int j = 0; j < i; j++) {
                if (this->_vecs[i].data[j] != 0)return false;
            }
        }
        this->spc.triUp = true;
        return true;
    }
    else{
        for (int i=0;i< this->_row;++i){
            for (int j=i+1;j< this->_row;j++){
                if(this->_vecs[i].data[j] != 0)return false;
            }
        }
        this->spc.triDown = true;   // ← 修复: 原为 triUp
        return true;
    }
}

void Matrix::getElementaryTransposeReSize(int lr, double k, bool if_line) {
    if (if_line){
        if(lr < 0 || lr > this->_row-1){
            error_models(6);
            exit(EXIT_FAILURE);
        }
        this->_vecs[lr] = this->_vecs[lr].multi(k);
    }
    else
    {
        if(lr <0  || lr > this->_column-1){
            error_models(6);
            exit(EXIT_FAILURE);
        }
        for (int j=0;j< this->_row;j++){
            this->_vecs[j] = this->_vecs[j].expand(lr, k);
        }
    }
}

void Matrix::getElementaryTransposeExchange(int lr1, int lr2, bool if_line) {
    if (if_line){
        if (lr1 < 0 || lr2 < 0|| lr1 > this->_row-1||lr2 > this->_row-1){
            error_models(6) ;
            exit(EXIT_FAILURE);
        }
        auto temp = this->_vecs[lr1];
        this->_vecs[lr1] = this->_vecs[lr2];
        this->_vecs[lr2] = temp;
    } else{
        if(lr1 < 0||lr2 < 0|| lr1 > this->_column-1 || lr2 > this->_column-1){
            error_models(6) ;
            exit(EXIT_FAILURE);
        }
        for (int j=0;j< this->_row;j++){
            auto temp = this->_vecs[j].data[lr1];
            this->_vecs[j].data[lr1] = this->_vecs[j].data[lr2];
            this->_vecs[j].data[lr2] = temp;
        }
    }
}

void Matrix::getElementaryTransposAdd(int lr1, int lr2, double k, bool if_line) {
    if (if_line){
        if (lr2 <0 || lr1 < 0 || lr1 > this->_row-1 || lr2 > this->_row-1){
            error_models(6) ;
            exit(EXIT_FAILURE);
        }
        auto _vec = this->_vecs[lr2].multi(k);
        this->_vecs[lr1] = this->_vecs[lr1].add(_vec);
    } else{
        if (lr2 <0 || lr1 < 0 || lr1 > this->_column-1 || lr2 > this->_column-1){
            error_models(6) ;
            exit(EXIT_FAILURE);
        }
        for (int j=0;j< this->_row;j++){
            this->_vecs[j].data[lr1] = this->_vecs[j].data[lr1] + this->_vecs[j].data[lr2] * k;
        }
    }
}

// [优化] 行列式计算
// 保留对已知特殊矩阵（单位阵、三角阵、对角阵）的 O(1) 快速路径
// 一般情况改为高斯消元（带列主元），O(n³) 替代原 O(n!) 递归代数余子式
Element Matrix::det(){
    if (!isSquare()) { error_models(4);exit(EXIT_FAILURE); }
    if (this->spc.unit) {return 1;}
    elif (this->spc.triUp || this->spc.triDown || this->spc.digUp) {
        Element _sum = 1;
        for (int i=0;i< this->_row;i++)
        {
            _sum *= this->_vecs[i].data[i] ;
        }return _sum;
    }
    elif(this->spc.digDown){
        // [BugFix #6] 用整数运算计算符号，避免 pow(-1, 浮点数) 产生 NaN
        Element _sum = 1;
        for (int i=0;i< this->_row;i++)
        {
            _sum *= this->_vecs[i].data[this->_column-i-1] ;
        }
        int n = this->_row;
        int sign = ((n * (n - 1) / 2) % 2 == 0) ? 1 : -1;
        return _sum * sign;
    }
    // 一般情况: 高斯消元法（带部分列主元），O(n³)
    else{
        int n = this->_row;
        // 创建工作矩阵（栈上分配，n <= MAXCOUNT = 10）
        Element mat[MAXCOUNT][MAXCOUNT];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = this->_vecs[i].data[j];
            }
        }

        Element det_sign = 1;

        for (int col = 0; col < n; col++) {
            // 部分列主元: 选当前列中绝对值最大的行
            int max_row = col;
            Element max_val = fabs(mat[col][col]);
            for (int row = col + 1; row < n; row++) {
                if (fabs(mat[row][col]) > max_val) {
                    max_val = fabs(mat[row][col]);
                    max_row = row;
                }
            }

            // 主元为零 → 奇异矩阵，行列式为 0
            if (max_val < EPSILON) {
                return 0;
            }

            // 交换行（记录符号变化）
            if (max_row != col) {
                for (int j = 0; j < n; j++) {
                    Element temp = mat[col][j];
                    mat[col][j] = mat[max_row][j];
                    mat[max_row][j] = temp;
                }
                det_sign *= -1;
            }

            // 消元: 将当前列 col 下方元素消为 0
            for (int row = col + 1; row < n; row++) {
                Element factor = mat[row][col] / mat[col][col];
                for (int j = col; j < n; j++) {
                    mat[row][j] -= factor * mat[col][j];
                }
            }
        }

        // 行列式 = 符号 × 对角元素乘积
        Element result = det_sign;
        for (int i = 0; i < n; i++) {
            result *= mat[i][i];
        }
        return result;
    }
}

// [BugFix #7] 使用 EPSILON 进行浮点比较，避免因精度问题误判
bool Matrix::isSingularMat() { return fabs(det()) < EPSILON;}

Matrix Matrix::Zero(){
    auto _like_this = copy_mat(*this);
    // 这一步可以防止spc被继承之和，参与一些检测方法引发歧义
    _like_this.spc = {false, false, false, false, false, false};
    return _like_this * 0;
}

Matrix Matrix::getAccompany() {
    if (!isSquare()){ error_models(4); exit(EXIT_FAILURE); }
    if (isSingularMat()) { error_models(10);exit(EXIT_FAILURE);}
    elif (this->spc.unit) {return copy_mat(*this);}
    elif (this->spc.digUp){
        auto _mat = Zero();
        Element multi_value = 1;
        for (int i=0;i< this->_row;i++) multi_value *= this->_vecs[i].data[i];
        for (int i=0;i< this->_row;i++){
            _mat._vecs[i].data[i] = multi_value / this->_vecs[i].data[i];
        }
        _mat.spc.digUp = true;
        _mat.spc.symmetry = true;
        return _mat;
    }
    else
    {
        auto vecs = new Vector[this->_row];
        for (int row=0;row< this->_row;row++){
            auto _data = new Element [this->_column];
            for(int col=0;col< this->_column;col++){
                Element k = power(-1, row+col);
                auto A_ij = getRemainder(col, row).det() * k;
                _data[col] = A_ij;
            }
            auto vec = Vector(_data);
            delete[] _data;
            vecs[row] = vec;
        }
        return Matrix(vecs, this->_row, this->_column);
    }
}

Matrix Matrix::getAccompanyT() {
    if (!isSquare()){ error_models(4); exit(EXIT_FAILURE); }
    if (isSingularMat()) { error_models(10);exit(EXIT_FAILURE);}
    elif (this->spc.unit) {return copy_mat(*this);}
    elif (this->spc.digUp){
        auto _mat = Zero();
        Element multi_value = 1;
        for (int i=0;i< this->_row;i++) multi_value *= this->_vecs[i].data[i];
        for (int i=0;i< this->_row;i++){
            _mat._vecs[i].data[i] = multi_value / this->_vecs[i].data[i];
        }
        _mat.spc.digUp = true;
        _mat.spc.symmetry = true;
        return _mat;
    }
    else{
        auto vecs = new Vector[this->_row];
        for (int i=0;i< this->_row;i++){
            auto _data = new Element [this->_row];
            for (int j=0;j< this->_row;j++){
                _data[j] = getRemainder(i, j).det() * power(-1, i+j);
            }
            vecs[i] = Vector(_data, _column);
            delete[] _data;
        }
        return Matrix(vecs, _row, _row).transpose();
    }
}

Matrix Matrix::innerMulti(Matrix & other) {
    if (this->_column != other._row) {
        error_models(7);
        exit(EXIT_FAILURE);
    }
    if (other.spc.unit) { return copy_mat(*this); }
    auto auxiliaryMartrix = other.transpose();
    auto vecs = new Vector[this->_row];
    for (int i=0;i< this->_row;i++){
        auto _data = new Element[other._column];
        for (int j=0;j<other._column;j++){
            _data[j] = this->_vecs[i].inner(auxiliaryMartrix._vecs[j]);
        }
        vecs[i] = Vector(_data, other._column);
        delete[] _data;
    }
    return Matrix(vecs, this->_row, other._column);
}

// [优化] 逆矩阵求解
// 保留特殊矩阵（单位阵、主/副对角阵）的 O(1)/O(n) 快速路径
// 一般情况改为高斯-约旦消元法，O(n³) 替代原伴随矩阵法 O(n⁵)
// [BugFix #8] 副对角线矩阵逆矩阵：修复索引错误（原来写入最后一列而非副对角线位置）
Matrix Matrix::inv() {
    if (!isSquare()) { error_models(4);exit(EXIT_FAILURE); }
    if(isSingularMat()){ error_models(10);exit(EXIT_FAILURE);}
    if (this->spc.unit) {return copy_mat(*this);}
    elif (this->spc.digUp){
        auto _zero = Zero();
        for (int i=0;i< this->_row;i++){
            _zero._vecs[i].data[i] = 1/ this->_vecs[i].data[i];
        }
        _zero.spc.digUp = true;
        _zero.spc.symmetry = true;
        return _zero;
    }
    elif(this->spc.digDown){
        // 副对角线矩阵的逆仍为副对角线矩阵
        // A^{-1}[i][n-1-i] = 1 / A[n-1-i][i]
        auto _zero = Zero();
        int n = this->_row;
        for (int i = 0; i < n; i++){
            _zero._vecs[i].data[n - 1 - i] = 1.0 / this->_vecs[n - 1 - i].data[i];
        }
        _zero.spc.digDown = true;
        return _zero;
    }
    else {
        // 高斯-约旦消元法求逆，O(n³)
        int n = this->_row;
        // 增广矩阵 [A | I]，宽度 2n
        Element aug[MAXCOUNT][MAXCOUNT * 2];

        // 初始化增广矩阵
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                aug[i][j] = this->_vecs[i].data[j];
            }
            for (int j = 0; j < n; j++) {
                aug[i][n + j] = (i == j) ? 1.0 : 0.0;
            }
        }

        // 高斯-约旦消元（带部分列主元）
        for (int col = 0; col < n; col++) {
            // 选主元
            int max_row = col;
            Element max_val = fabs(aug[col][col]);
            for (int row = col + 1; row < n; row++) {
                if (fabs(aug[row][col]) > max_val) {
                    max_val = fabs(aug[row][col]);
                    max_row = row;
                }
            }

            // 交换行
            if (max_row != col) {
                for (int j = 0; j < 2 * n; j++) {
                    Element temp = aug[col][j];
                    aug[col][j] = aug[max_row][j];
                    aug[max_row][j] = temp;
                }
            }

            // 主元归一化
            Element pivot = aug[col][col];
            for (int j = 0; j < 2 * n; j++) {
                aug[col][j] /= pivot;
            }

            // 消去当前列的其他所有行
            for (int row = 0; row < n; row++) {
                if (row != col) {
                    Element factor = aug[row][col];
                    for (int j = 0; j < 2 * n; j++) {
                        aug[row][j] -= factor * aug[col][j];
                    }
                }
            }
        }

        // 从增广矩阵右半部分提取逆矩阵
        auto vecs = new Vector[n];
        for (int i = 0; i < n; i++) {
            auto _data = new Element[n];
            for (int j = 0; j < n; j++) {
                _data[j] = aug[i][n + j];
            }
            vecs[i] = Vector(_data, n);
            delete[] _data;
        }
        return Matrix(vecs, n, n);
    }
}

Element Matrix::trace() const {
    // 矩阵的迹就没有必要使用spc特性简化了
    if (!isSquare()){ error_models(4);  exit(EXIT_FAILURE);}
    Element _sum = 0;
    for(int i=0;i< this->_row;i++)  { _sum += this->_vecs[i].data[i]; }
    return _sum;
}

bool Matrix::isOrthogon() {
    auto T = this->transpose();
    auto E = this->E();
    return (*this).innerMulti(T) == E;
}

Matrix Matrix::norm(bool if_line) {
    // 行单位化
    auto copy = copy_mat(*this);
    if(if_line){
        for (int i=0;i< this->_row;i++){
            copy._vecs[i] = copy._vecs[i].unit();
        }
    } else{
        copy = copy.transpose();
        for (int i=0;i< this->_column;i++){
            copy._vecs[i] = copy._vecs[i].unit();
        }
        copy = copy.transpose();
    }return copy;
}