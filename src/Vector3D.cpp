/*************************************************************************
【文件名】                 Vector3D.cpp
【功能模块和目的】         Vector3D类的实现
【开发者及日期】           李想 2024/7/31
【更改记录】               李想 2024/8/2 修改了流插入格式为(x, y, z)
                        李想 2024/8/3 添加求法向量的Normal()方法，增加注释
*************************************************************************/

#include "Vector3D.hpp"
#include <cmath>//acos
#include <algorithm>//max
#include <climits>//INT_MAX
#include <sstream>//ostringstream
#include <iostream>



/*************************************************************************
【函数名称】       Vector3D::Vector3D
【函数功能】        带参数和默认值的构造函数
【参数】            输入参数 double x x坐标
                    输入参数 double y y坐标
                    输入参数 double z z坐标
【返回值】         无
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D::Vector3D(double X, double Y, double Z) : X(X), Y(Y), Z(Z){
    //初始化三维向量
}

/*************************************************************************
【函数名称】       Vector3D::~Vector3D
【函数功能】        析构函数
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D::~Vector3D() {
    //析构函数
}

/*************************************************************************
【函数名称】       Vector3D::Vector3D
【函数功能】        拷贝构造函数
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         无
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D::Vector3D(const Vector3D& AVec) : X(AVec.X), Y(AVec.Y), Z(AVec.Z){
        //拷贝构造函数
}

/*************************************************************************
【函数名称】       Vector3D::operator=
【函数功能】        重载赋值运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         Vector3D& 三维向量的引用
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D& Vector3D::operator=(const Vector3D& AVector){
    if (this != &AVector) {
        X = AVector.X;
        Y = AVector.Y;
        Z = AVector.Z;
    }
    return *this;
}

/*************************************************************************
【函数名称】       Vector3D::operator[]
【函数功能】        重载下标运算符
【参数】            输入参数 size_t Index 下标
【返回值】         double 三维向量的某个元素
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector3D::operator[](size_t Index) const{
    if (Index == 0) {
        return X;
    } else if (Index == 1) {
        return Y;
    } else {
        return Z;
    }
}

/*************************************************************************
【函数名称】       Vector3D::IsVertical
【函数功能】        检查向量是否垂直
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         bool 是否垂直的判断结果
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Vector3D::IsVertical(const Vector3D& AVector) const{
    return DotProduct(AVector) == 0;
}

/*************************************************************************
【函数名称】       Vector3D::IsParallel
【函数功能】        检查向量是否平行
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         bool 是否平行的判断结果
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Vector3D::IsParallel(const Vector3D& AVector) const{
    return CrossProduct(AVector).Norm() == 0;
}
/*************************************************************************
【函数名称】       Vector3D::operator+
【函数功能】        重载加法运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         Vector3D 两个三维向量的和
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Vector3D::operator+(const Vector3D& AVector) const{
    return Vector3D(X + AVector.X, Y + AVector.Y, Z + AVector.Z);
}

/*************************************************************************
【函数名称】       Vector3D::operator-
【函数功能】        重载减法运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         Vector3D 两个三维向量的差
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Vector3D::operator-(const Vector3D& AVector) const{
    return Vector3D(X - AVector.X, 
                    Y - AVector.Y, 
                    Z - AVector.Z);
}

/*************************************************************************
【函数名称】       Vector3D::operator*
【函数功能】        重载星号乘法运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         double 两个三维向量的点乘结果
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector3D::operator*(const Vector3D& AVector) const{
    return DotProduct(AVector);
}

/*************************************************************************
【函数名称】       Vector3D::operator*
【函数功能】        重载乘法运算符
【参数】            输入参数 double scalar 标量
【返回值】         Vector3D 三维向量与标量的乘积
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Vector3D::operator*(double scalar) const{
    return Vector3D(X * scalar, Y * scalar, Z * scalar);
}
/*************************************************************************
【函数名称】       Vector3D::operator/
【函数功能】        重载除法运算符
【参数】            输入参数 double scalar 标量
【返回值】         Vector3D 三维向量与标量的除法结果
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Vector3D::operator/(double scalar) const{
    return Vector3D(X / scalar, Y / scalar, Z / scalar);
}

/*************************************************************************
【函数名称】       Vector3D::operator^
【函数功能】        重载^运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         Vector3D 两个三维向量的叉乘结果
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Vector3D::operator^(const Vector3D& AVector) const{
    return CrossProduct(AVector);
}

/*************************************************************************
【函数名称】       Vector3D::operator==
【函数功能】        重载==运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         bool 两个三维向量是否相等的判断结果
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Vector3D::operator==(const Vector3D& AVector) const{
    //由于数据类型是double，所以不能直接比较是否相等
    return fabs(X - AVector.X) < EPS 
        && fabs(Y - AVector.Y) < EPS 
        && fabs(Z - AVector.Z) < EPS;
}

/*************************************************************************
【函数名称】       Vector3D::operator!=
【函数功能】        重载!=运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         bool 两个三维向量是否不等的判断结果
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Vector3D::operator!=(const Vector3D& AVector) const{
    return !(*this == AVector);
}


/*************************************************************************
【函数名称】       Vector3D::Norm0
【函数功能】        求三维向量的0范数
【参数】            无
【返回值】         double 三维向量的0范数
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector3D::Norm0() const{
    return X != 0 ? 1 : 0 + Y != 0 ? 1 : 0 + Z != 0 ? 1 : 0;
}

/*************************************************************************
【函数名称】       Vector3D::Norm1
【函数功能】        求三维向量的1范数
【参数】            无
【返回值】         double 三维向量的1范数
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

double Vector3D::Norm1() const{
    return fabs(X) + fabs(Y) + fabs(Z);
}

/*************************************************************************
【函数名称】       Vector3D::Norm2
【函数功能】        求三维向量的2范数
【参数】            无
【返回值】         double 三维向量的2范数
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

double Vector3D::Norm2() const{
    return sqrt(X * X + Y * Y + Z * Z);
}

/*************************************************************************
【函数名称】       Vector3D::NormInf
【函数功能】        求三维向量的无穷范数
【参数】            无
【返回值】         double 三维向量的无穷范数
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

double Vector3D::NormInf() const{
    return std::max(std::max(fabs(X), fabs(Y)), fabs(Z));
}

/*************************************************************************
【函数名称】       Vector3D::NormP
【函数功能】        求三维向量的p范数
【参数】            输入参数 double p 范数的阶数
【返回值】         double 三维向量的p范数
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

double Vector3D::NormP(double p) const{
    if (p == 0) {
        return Norm0();
    } else if (p == 1) {
        return Norm1();
    } else if (p == 2) {
        return Norm2();
    } else if (p == INT_MAX) {
        return NormInf();
    } else {
        return pow(pow(fabs(X), p) 
            + pow(fabs(Y), p) + pow(fabs(Z), p), 1.0 / p);
    }
}

/*************************************************************************
【函数名称】       Vector3D::Norm
【函数功能】        求三维向量的2范数
【参数】            无
【返回值】         double 三维向量的2范数，即长度
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

double Vector3D::Norm() const{
    return Norm2();
}

/*************************************************************************
【函数名称】       Vector3D::Length
【函数功能】        求三维向量的2范数
【参数】            无
【返回值】         double 三维向量的2范数，即长度，与Norm()功能相同
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

double Vector3D::Length() const{
    return Norm2();
}

/*************************************************************************
【函数名称】       Vector3D::Direction
【函数功能】        求三维向量的单位方向
【参数】            无
【返回值】         Vector3D 三维向量的单位方向（即该向量除以长度的结果）
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Vector3D Vector3D::Direction() const{
    return *this / Norm();
}

/*************************************************************************
【函数名称】       Vector3D::Unit
【函数功能】       求三维向量的单位向量
【参数】            无
【返回值】         Vector3D 三维向量的单位向量（即该向量除以长度的结果）
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Vector3D Vector3D::Unit() const{
    return *this / Norm();
}
/*************************************************************************
【函数名称】       Vector3D::Normal
【函数功能】       求三维向量的法向量
【参数】            无
【返回值】         Vector3D 三维向量的法向量
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Vector3D Vector3D::Normal() const{
    return Vector3D(Y, -X, 0);
}

/*************************************************************************
【函数名称】       Vector3D::CrossProduct
【函数功能】       求三维向量的叉乘
【参数】            无
【返回值】         Vector3D 两个三维向量的叉乘结果
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Vector3D::CrossProduct(const Vector3D& AVector) const{
    return Vector3D(
        Y * AVector.Z - Z * AVector.Y,
        Z * AVector.X - X * AVector.Z,
        X * AVector.Y - Y * AVector.X);
}

/*************************************************************************
【函数名称】       Vector3D::DotProduct
【函数功能】       求三维向量的点乘
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         double 两个三维向量的点乘结果
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector3D::DotProduct(const Vector3D& AVector) const{
    return X * AVector.X + Y * AVector.Y + Z * AVector.Z;
}

/*************************************************************************
【函数名称】       Vector3D::Angle
【函数功能】       求三维向量的夹角
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         double 两个三维向量的夹角的弧度值
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Vector3D::Angle(const Vector3D& AVector) const{
    return acos(DotProduct(AVector) / (Norm() * AVector.Norm()));
}

/*************************************************************************
【函数名称】       Vector3D::ToString
【函数功能】       转换为字符串
【参数】            无
【返回值】         std::string 三维向量的字符串形式，如"(1, 2, 3)"
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

std::string Vector3D::ToString() const{
    return "(" + std::to_string(X) + ", " 
        + std::to_string(Y) + ", " + std::to_string(Z) + ")";
}

/*************************************************************************
【函数名称】       Vector3D::operator+=
【函数功能】        重载+=运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         Vector3D& 三维向量的引用
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D& Vector3D::operator+=(const Vector3D& AVector){
    X += AVector.X;
    Y += AVector.Y;
    Z += AVector.Z;
    return *this;
}


/*************************************************************************
【函数名称】       Vector3D::operator-=
【函数功能】        重载-=运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         Vector3D& 三维向量的引用
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D& Vector3D::operator-=(const Vector3D& AVector){
    X -= AVector.X;
    Y -= AVector.Y;
    Z -= AVector.Z;
    return *this;
}

/*************************************************************************
【函数名称】       Vector3D::operator*=
【函数功能】        重载*=运算符
【参数】            输入参数 const Vector3D& v 三维向量
【返回值】         Vector3D& 三维向量的引用
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D& Vector3D::operator*=(const Vector3D& AVector){
    X *= AVector.X;
    Y *= AVector.Y;
    Z *= AVector.Z;
    return *this;
}

/*************************************************************************
【函数名称】       operator>>
【函数功能】        重载流提取运算符
【参数】            输入输出流对象 std::istream& Stream 输入输出流对象
                    输入参数 Vector3D& v 三维向量
【返回值】         std::istream& 输入输出流对象
【开发者及日期】   李想 2024/7/31
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::istream& operator>>(std::istream& Stream, Vector3D& AVector){
    Stream >> AVector.X >> AVector.Y >> AVector.Z;
    return Stream;
}

/*************************************************************************
【函数名称】       operator<<
【函数功能】        重载流插入运算符
【参数】            输入输出流对象 std::ostream& Stream 输入输出流对象
                    输入参数 const Vector3D& v 三维向量
【返回值】         std::ostream& 输入输出流对象
【开发者及日期】   李想 2024/7/31
【更改记录】       李想 2024/8/2 修改了输出格式为(x, y, z)
*************************************************************************/
std::ostream& operator<<(std::ostream& Stream, const Vector3D& AVector){
    Stream << "(" << AVector.X << ", " 
        << AVector.Y << ", " << AVector.Z << ")";
    return Stream;
}



