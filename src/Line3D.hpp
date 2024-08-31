/*************************************************************************
【文件名】                 Line3D.hpp
【功能模块和目的】         Line3D类声明，实现一个三维空间中的直线，继承自Element3D
【开发者及日期】           李想 2024/8/3
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef LINE3D_HPP
#define LINE3D_HPP
#include "Element3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <iostream>
#include <vector>



/*************************************************************************
【类名】             Line3D
【功能】             继承自Element3D的Line3D类声明，实现一个三维空间中的直线，
【接口说明】         公有继承Element3D类，得到Element3D类的所有接口
                    必备隐性行为：
                    带参构造函数 Line3D(std::initializer_list<Point3D> init);
                    析构函数 virtual ~Line3D();
                    拷贝构造函数 Line3D(const Line3D& Other);
                    赋值构造函数 Line3D& operator=(const Line3D& Other);
                    
                    Setters:
                    修改起点位置 void ModifyStartPoint
                        (const Point3D& Other_point);
                    修改终点位置 void ModifyEndPoint
                        (const Point3D& Other_point);
                    
                    Non-static getters:
                    检查直线是否平行 bool IsParallel(const Line3D& Other) const;
                    检查直线是否垂直 bool IsVertical(const Line3D& Other) const;
                    检查直线是否相交 bool IsIntersect(const Line3D& Other) const;
                    检查点是否在直线上 bool IsOnLine(const Point3D& p) const;
                    检查点是否在线段上 bool IsOnSegment(const Point3D& p) const;
                    求两直线之间的夹角 double Angle(const Line3D& Other) const;
                    求两直线间的距离 double Distance(const Line3D& Other) const;
                    计算直线的一个单位方向向量 Vector3D Direction() const;
                    计算直线的一个单位法向量 Vector3D Normal() const;
                    计算点到直线的距离 double Distance(const Point3D& p) const;
                    获取起点 const Point3D& GetStartPoint() const;
                    获取终点 const Point3D& GetEndPoint() const;
                    获取元素周长/长度 virtual double GetLength() const override;
                    获取元素面积 virtual double GetArea() const override;
                    重载流输出运算符 
                        friend std::ostream& 
                            operator<<(std::ostream& os, const Line3D& l);
                    
                    Static getters:
                    静态函数，检查两直线是否平行 
                        bool IsParallel
                            (const Line3D& Line1, const Line3D& Line2);
                    静态函数，检查两直线是否垂直 
                        bool IsVertical
                            (const Line3D& Line1, const Line3D& Line2);
                    静态函数，检查两直线是否相交 
                        bool IsIntersect
                            (const Line3D& Line1, const Line3D& Line2);
                    静态函数，求两直线之间的夹角 
                        double Angle
                            (const Line3D& Line1, const Line3D& Line2);
                    静态函数，求两直线间的距离 
                        double Distance
                            (const Line3D& Line1, const Line3D& Line2);
                    静态函数，计算点到直线的距离 
                        double Distance
                            (const Point3D& p, const Line3D& l);
【开发者及日期】     李想 2024/8/3
【更改记录】         （若修改过则必需注明）
*************************************************************************/

class Line3D : public Element3D<2> {
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //带参构造函数
    Line3D(std::initializer_list<Point3D> Init);
    //析构函数
    virtual ~Line3D();
    //拷贝构造函数
    Line3D(const Line3D& Other);
    //赋值构造函数
    Line3D& operator=(const Line3D& Other);
    //------------------------------------------------------------------
    //Setters:
    //------------------------------------------------------------------
    //修改起点位置
    void ModifyStartPoint(const Point3D& OtherPoint);
    //修改终点位置
    void ModifyEndPoint(const Point3D& OtherPoint);
    //------------------------------------------------------------------
    //Non-static getters:
    //------------------------------------------------------------------
    //检查直线是否平行
    bool IsParallel(const Line3D& Other) const;
    //检查直线是否垂直
    bool IsVertical(const Line3D& Other) const;
    //检查直线是否相交
    bool IsIntersect(const Line3D& Other) const;
    //检查点是否在直线上
    bool IsOnLine(const Point3D& APoint) const;
    //检查点是否在线段上
    bool IsOnSegment(const Point3D& APoint) const;
    //求两直线之间的夹角
    double Angle(const Line3D& Other) const;
    //求两直线间的距离
    double LineDistance(const Line3D& Other) const;
    //计算直线的一个单位方向向量
    Vector3D Direction() const;
    //计算直线的一个法向量
    Vector3D Normal() const override;
    //计算点到直线的距离
    double GetPointLineDistance(const Point3D& APoint) const;
    //获取起点
    const Point3D& GetStartPoint() const;
    //获取终点
    const Point3D& GetEndPoint() const;
    //获取直线长度
    virtual double GetLength() const override;
    //直线面积，直接返回0.0
    virtual double GetArea() const override;
    //------------------------------------------------------------------
    //Static getters:
    //------------------------------------------------------------------
    //静态函数，检查两直线是否平行
    static bool IsParallel(const Line3D& Line1, const Line3D& Line2);
    //静态函数，检查两直线是否垂直
    static bool IsVertical(const Line3D& Line1, const Line3D& Line2);
    //静态函数，检查两直线是否相交
    static bool IsIntersect(const Line3D& Line1, const Line3D& Line2);
    //静态函数，求两直线之间的夹角
    static double Angle(const Line3D& Line1, const Line3D& Line2);
    //静态函数，求两直线间的距离
    static double LineDistance(const Line3D& Line1, const Line3D& Line2);
    //静态函数，计算点到直线的距离
    static double GetPointLineDistance(
        const Point3D& APoint, 
        const Line3D& ALine);
    //------------------------------------------------------------------
    //友元函数
    //------------------------------------------------------------------
    //重载流输出运算符
    friend std::ostream& operator<<(std::ostream& Stream, const Line3D& ALine);
private:
    static constexpr double EPS = 1e-9; // 定义一个非常小的数值,用于比较
};
#endif // LINE3D_HPP