/*************************************************************************
【文件名】                 Vector3D.hpp
【功能模块和目的】         Vector3D类声明，头文件
【开发者及日期】           李想 2024/7/31
【更改记录】               李想 2024/8/3 添加求法向量的Normal()方法，增加注释
*************************************************************************/


#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
#include <iostream>//istream, ostream
#include <cstddef>//size_t
#include <string>//string



/*************************************************************************
【类名】             Vector3D
【功能】             Vector3D类声明，操作三维向量
【接口说明】         必备隐性行为：
                    默认构造函数 Vector3D(double x = 0, double y = 0, double z = 0);
                    析构函数 virtual ~Vector3D();
					拷贝构造函数 Vector3D(const Vector3D& v);
					赋值构造函数 Vector3D& operator=(const Vector3D& v);

                    Getters:
                    元素只读访问 double operator[](size_t index) const;
                    重载加法运算符 Vector3D operator+(const Vector3D& v) const;
                    重载减法运算符 Vector3D operator-(const Vector3D& v) const;
                    重载星号乘法运算符为向量点乘 
                        double operator*(const Vector3D& v) const;
                    重载乘法运算符为标量乘法 
                        Vector3D operator*(double scalar) const;
                    重载除法运算符为标量除法
                        Vector3D operator/(double scalar) const;
                    重载^运算符为向量叉乘 
                        Vector3D operator^(const Vector3D& v) const;
                    重载==运算符 bool operator==(const Vector3D& v) const;
                    重载!=运算符 bool operator!=(const Vector3D& v) const;
                    求三维向量的0范数 double Norm0() const;
                    求三维向量的1范数 double Norm1() const;
                    求三维向量的2范数 double Norm2() const;
                    求三维向量的无穷范数 double NormInf() const;
                    求三维向量的P范数 double NormP(double p) const;
                    求三维向量的模 double Norm() const;
                    求三维向量的长度 double Length() const;
                    求三维向量的方向 Vector3D Direction() const;
                    求三维向量的单位向量 Vector3D Unit() const;
                    求三维向量的叉乘 
                        Vector3D CrossProduct(const Vector3D& v) const; 
                    求三维向量的点乘
                        double DotProduct(const Vector3D& v) const;
                    求三维向量的夹角 double Angle(const Vector3D& v) const;
                    转换为字符串std::string ToString() const;
                    对私有成员变量X常引用 const double& X {X};
                    对私有成员变量Y常引用 const double& Y {Y};
                    对私有成员变量Z常引用 const double& Z {Z};

                    Setters:
                    重载+=运算符 Vector3D& operator+=(const Vector3D& v);
                    重载-=运算符 Vector3D& operator-=(const Vector3D& v);
                    重载*=运算符 Vector3D& operator*=(const Vector3D& v);
                    重载流插入运算符 
                        friend std::istream&
                            operator>>(std::istream& is, Vector3D& v);
                    重载流提取运算符
                        friend std::ostream& 
                            operator<<(std::ostream& os, const Vector3D& v);  
                      


【开发者及日期】     李想 2024/7/31
【更改记录】         李想 2024/8/3 添加求法向量的Normal()方法，增加注释
*************************************************************************/

class Vector3D{
public:
    //------------------------------------------------------------------
    //公有成员变量，矢量坐标
    //------------------------------------------------------------------
    //由于没有读写规则，所以将所有成员变量设为公有
    double X;
    double Y;
    double Z;
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //默认构造函数
    Vector3D(double X = 0, double Y = 0, double Z = 0);
    //析构函数
    virtual ~Vector3D();
    //拷贝构造函数
    Vector3D(const Vector3D& AVector);
    //赋值构造函数
    Vector3D& operator=(const Vector3D& AVector);
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //元素只读访问
    double operator[](size_t Index) const;
    //检查向量是否垂直
    bool IsVertical(const Vector3D& AVector) const;
    //检查向量是否平行
    bool IsParallel(const Vector3D& AVector) const;
    //重载加法运算符
    Vector3D operator+(const Vector3D& AVector) const;
    //重载减法运算符
    Vector3D operator-(const Vector3D& AVector) const;
    //重载星号乘法运算符为向量点乘
    double operator*(const Vector3D& AVector) const;
    //重载乘法运算符为标量乘法
    Vector3D operator*(double Scalar) const;
    //重载除法运算符为标量除法
    Vector3D operator/(double Scalar) const;
    //重载^运算符为向量叉乘
    Vector3D operator^(const Vector3D& AVector) const;
    //重载==运算符
    bool operator==(const Vector3D& AVector) const;
    //重载!=运算符
    bool operator!=(const Vector3D& AVector) const;
    //求三维向量的0范数
    double Norm0() const;
    //求三维向量的1范数
    double Norm1() const;
    //求三维向量的2范数
    double Norm2() const;
    //求三维向量的无穷范数
    double NormInf() const;
    //求三维向量的P范数
    double NormP(double p) const;
    //求三维向量的模
    double Norm() const;
    //求三维向量的长度
    double Length() const;
    //求三维向量的方向
    Vector3D Direction() const;
    //求三维向量的单位向量
    Vector3D Unit() const;
    //求三维向量的法向量
    Vector3D Normal() const;
    //求三维向量的叉乘
    Vector3D CrossProduct(const Vector3D& AVector) const;
    //求三维向量的点乘
    double DotProduct(const Vector3D& AVector) const;
    //求三维向量的夹角
    double Angle(const Vector3D& AVector) const;
    //转换为字符串
    std::string ToString() const;
    //------------------------------------------------------------------
    //Setters:
    //------------------------------------------------------------------
    //重载+=运算符
    Vector3D& operator+=(const Vector3D& AVector);
    //重载-=运算符
    Vector3D& operator-=(const Vector3D& AVector);
    //重载*=运算符
    Vector3D& operator*=(const Vector3D& AVector);
    //------------------------------------------------------------------
    //友元函数
    //------------------------------------------------------------------
    //重载流插入运算符
    friend std::istream& operator>>(std::istream& Stream, Vector3D& AVector);
    //重载流提取运算符
    friend std::ostream& operator<<(
        std::ostream& Stream, 
        const Vector3D& AVector);
private:
    static constexpr double EPS = 1e-9; // 定义一个非常小的数值,用于比较
};

#endif // VECTOR3D_HPP