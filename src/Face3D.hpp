/*************************************************************************
【文件名】                 Face3D.hpp
【功能模块和目的】         继承自Element3D的Face3D类声明，实现一个三维空间中的三角形，
                        该三角形由三个点构成，可以计算面积、周长、法向量等
【开发者及日期】           李想 2024/8/3
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef FACE3D_HPP
#define FACE3D_HPP
#include "Element3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <iostream>
#include <cstddef>
#include <cmath>
#include <initializer_list>
#include <vector>




/*************************************************************************
【类名】             Face3D
【功能】             继承自Element3D的Face3D类声明，实现一个三维空间中的三角形，
                    该三角形由三个点构成，可以计算面积、周长、法向量等
【接口说明】         公有继承Element3D类，得到Element3D类的所有接口
                    必备隐性行为：
                    带参构造函数 Face3D(std::initializer_list<Point3D> init);
                    析构函数 virtual ~Face3D();
                    拷贝构造函数 Face3D(const Face3D& Other);
                    赋值构造函数 Face3D& operator=(const Face3D& Other);
                    
                    Setters:
                    修改三角形的三个顶点 
                        void ModifyPoints(std::initializer_list<Point3D> init);
                    
                    Non-static getters:
                    求三角形的面积 double GetArea() const;
                    求三角形的周长 double GetLength() const;
                    求三角形的法向量 Vector3D GetNormal() const;
                    求三角形的重心 Point3D GetBarycenter() const;
                    求三角形的外心 Point3D GetCircumcenter() const;
                    求三角形的内心 Point3D GetIncenter() const;
                    求三角形的垂心 Point3D GetOrthocenter() const;
                    求三角形的费马点 Point3D GetFermatPoint() const;
                    重载流输出运算符 
                        friend std::ostream& 
                            operator<<(std::ostream& os, const Face3D& f);
                    
                    Static getters:
                    静态函数，求三角形的面积 
                        static double GetArea(
                        const Point3D& Point1, 
                        const Point3D& Point2, 
                        const Point3D& Point3);
                    静态函数，求三角形的周长
                        static double GetLength(
                        const Point3D& Point1, 
                        const Point3D& Point2, 
                        const Point3D& Point3);
                    静态函数，求三角形的法向量
                        static Vector3D GetNormal(
                        const Point3D& Point1, 
                        const Point3D& Point2, 
                        const Point3D& Point3);
                    静态函数，求三角形的重心
                        static Point3D GetBarycenter(
                        const Point3D& Point1, 
                        const Point3D& Point2, 
                        const Point3D& Point3);
                    静态函数，求三角形的外心
                        static Point3D GetCircumcenter(
                        const Point3D& Point1, 
                        const Point3D& Point2, 
                        const Point3D& Point3);
                    静态函数，求三角形的内心
                        static Point3D GetIncenter(
                        const Point3D& Point1, 
                        const Point3D& Point2, 
                        const Point3D& Point3);
                    静态函数，求三角形的垂心    
                        static Point3D GetOrthocenter(
                        const Point3D& Point1,
                         const Point3D& Point2, 
                         const Point3D& Point3);
                    静态函数，求三角形的费马点
                        static Point3D GetFermatPoint(
                        const Point3D& Point1, 
                        const Point3D& Point2, 
                        const Point3D& Point3);
【开发者及日期】       李想 2024/8/4
【更改记录】           （若修改过则必需注明）
*************************************************************************/

class Face3D : public Element3D<3> {
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //带参构造函数
    Face3D(std::initializer_list<Point3D> Init);
    //析构函数
    virtual ~Face3D();
    //拷贝构造函数
    Face3D(const Face3D& Other);
    //赋值构造函数
    Face3D& operator=(const Face3D& Other);
    //------------------------------------------------------------------
    //Non-static getters:
    //------------------------------------------------------------------
    //求三角形的面积
    double GetArea() const override;
    //求三角形的周长
    double GetLength() const override;
    //求三角形的法向量
    Vector3D Normal() const override;
    //求三角形的重心
    Point3D GetBarycenter() const;
    //求三角形的外心
    Point3D GetCircumcenter() const;
    //求三角形的内心
    Point3D GetIncenter() const;
    //求三角形的垂心
    Point3D GetOrthocenter() const;
    //求三角形的费马点
    Point3D GetFermatPoint() const;
    //------------------------------------------------------------------
    //Static getters:
    //------------------------------------------------------------------
    //静态函数，求三角形的面积
    static double GetArea(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //静态函数，求三角形的周长
    static double GetLength(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //静态函数，求三角形的法向量
    static Vector3D GetNormal(
        const Point3D& Point1,
        const Point3D& Point2,
        const Point3D& Point3);
    //静态函数，求三角形的单位法向量
    static Vector3D GetUnitNormal(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //静态函数，求三角形的重心
    static Point3D GetBarycenter(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //静态函数，求三角形的外心
    static Point3D GetCircumcenter(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //静态函数，求三角形的内心
    static Point3D GetIncenter(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //静态函数，求三角形的垂心
    static Point3D GetOrthocenter(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //静态函数，求三角形的费马点
    static Point3D GetFermatPoint(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //------------------------------------------------------------------
    //友元函数
    //------------------------------------------------------------------
    //重载流输出运算符
    friend std::ostream& operator<<(std::ostream& Stream, const Face3D& AFace);
};

#endif // FACE3D_HPP