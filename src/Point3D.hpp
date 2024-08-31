/*************************************************************************
【文件名】                 Point3D.hpp
【功能模块和目的】         Point3D类(继承自Vector3D类）声明，头文件
【开发者及日期】           李想 2024/8/1
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef POINT3D_HPP
#define POINT3D_HPP
#include "Vector3D.hpp"


/*************************************************************************
【类名】             Point3D
【功能】             Vector3D的派生类，操作三维空间中的点
【接口说明】         公有继承Vector3D类，得到Vector3D类的所有接口
                    必备隐性行为：
                    默认构造函数 Point3D(double x = 0, double y = 0, double z = 0);
                    析构函数 virtual ~Point3D();
                    拷贝构造函数 Point3D(const Point3D& p);
                    赋值构造函数 Point3D& operator=(const Point3D& p);

                    Getters:
                    重载减法运算符，两点相减产生一个三维向量
                        Vector3D operator-(const Point3D& other) const;
                    求两点之间的距离
                        double Distance(const Point3D& other) const;
                    静态函数，求两点之间的距离
                        static double Distance(const Point3D& p1, const Point3D& p2);
                    删除基类中不适用于点的操作：
                    删除重载加法运算符
                    删除重载减法运算符（向量版）
                    删除重载星号乘法运算符为向量点乘
                    删除重载乘法运算符为标量乘法
                    删除重载除法运算符为标量除法
                    删除重载^运算符为向量叉乘
                    删除求三维向量的0范数
                    删除求三维向量的1范数
                    删除求三维向量的2范数
                    删除求三维向量的无穷范数
                    删除求三维向量的P范数
                    删除求三维向量的模
                    删除求三维向量的长度
                    删除求三维向量的方向
                    删除求三维向量的单位向量
                    删除求三维向量的叉乘
                    删除求三维向量的点乘
                    删除求三维向量的夹角

【开发者及日期】     李想 2024/8/1
【更改记录】         （若修改过则必需注明）
*************************************************************************/

class Point3D : public Vector3D{
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //默认构造函数
    Point3D(double X = 0, double Y = 0, double Z = 0);
    //析构函数
    virtual ~Point3D();
    //拷贝构造函数
    Point3D(const Point3D& OtherPoint);
    //赋值构造函数
    Point3D& operator=(const Point3D& OtherPoint);
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //重载减法运算符，两点相减产生一个三维向量
    Vector3D operator-(const Point3D& other) const;
    //求两点之间的距离
    double Distance(const Point3D& other) const;
    //静态函数，求两点之间的距离
    static double Distance(const Point3D& Point1, const Point3D& Point2);
    //------------------------------------------------------------------
    //删除基类中不适用于点的操作
    //------------------------------------------------------------------
    //删除重载加法运算符
    Vector3D operator+(const Vector3D& AVector) const = delete;
    //删除重载减法运算符
    Vector3D operator-(const Vector3D& AVector) const = delete;
    //删除重载星号乘法运算符为向量点乘
    double operator*(const Vector3D& AVector) const = delete;
    //删除重载乘法运算符为标量乘法
    Vector3D operator*(double Scalar) const = delete;
    //删除重载除法运算符为标量除法
    Vector3D operator/(double Scalar) const = delete;
    //删除重载^运算符为向量叉乘
    Vector3D operator^(const Vector3D& AVector) const = delete;
    //删除求三维向量的0范数
    double Norm0() const = delete;
    //删除求三维向量的1范数
    double Norm1() const = delete;
    //删除求三维向量的2范数
    double Norm2() const = delete;
    //删除求三维向量的无穷范数
    double NormInf() const = delete;
    //删除求三维向量的P范数
    double NormP(double p) const = delete;
    //删除求三维向量的模
    double Norm() const = delete;
    //删除求三维向量的长度
    double Length() const = delete;
    //删除求三维向量的方向
    Vector3D Direction() const = delete;
    //删除求三维向量的单位向量
    Vector3D Unit() const = delete;
    //删除求三维向量的叉乘
    Vector3D CrossProduct(const Vector3D& AVector) const = delete;
    //删除求三维向量的点乘
    double DotProduct(const Vector3D& AVector) const = delete;
    //删除求三维向量的夹角
    double Angle(const Vector3D& AVector) const = delete;
};

#endif //POINT3D_HPP