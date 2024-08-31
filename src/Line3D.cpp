/*************************************************************************
【文件名】                 Line3D.cpp
【功能模块和目的】         Line3D类的实现
【开发者及日期】           李想 2024/8/3
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include"Line3D.hpp"
#include"Vector3D.hpp"
#include"Point3D.hpp"
#include<iostream>
#include<cmath>
#include<initializer_list>



/*************************************************************************
【函数名称】       Line3D::Line3D
【函数功能】        带参数的构造函数
【参数】            输入参数 std::initializer_list<Point3D> init 三维点列表
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D::Line3D(std::initializer_list<Point3D> Init): Element3D<2>(Init){
    //调用基类构造函数
}

/*************************************************************************
【函数名称】       Line3D::~Line3D
【函数功能】        析构函数
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D::~Line3D() {
    //析构函数
}

/*************************************************************************
【函数名称】       Line3D::Line3D
【函数功能】       拷贝构造函数
【参数】           无
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Line3D::Line3D(const Line3D& Other): Element3D<2>(Other) {
    //调用基类拷贝构造函数
    }

/*************************************************************************
【函数名称】       Line3D::operator=
【函数功能】        赋值构造函数
【参数】            输入参数 const Line3D& Other 三维直线
【返回值】         Line3D& 三维直线
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Line3D& Line3D::operator=(const Line3D& Other) {
    if (this == &Other) {
        return *this;
    }
    Element3D<2>::operator=(Other);
    return *this;
}

/*************************************************************************
【函数名称】       Line3D::ModifyStartPoint
【函数功能】        修改起点位置
【参数】            输入参数 const Point3D& OtherPoint 三维点
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Line3D::ModifyStartPoint(const Point3D& OtherPoint) {
    Element3D<2>::ModifyPoint(0, OtherPoint);
}

/*************************************************************************
【函数名称】       Line3D::ModifyEndPoint
【函数功能】        修改终点位置
【参数】            输入参数 const Point3D& OtherPoint 三维点
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Line3D::ModifyEndPoint(const Point3D& OtherPoint) {
    Element3D<2>::ModifyPoint(1, OtherPoint);
}

/*************************************************************************
【函数名称】       Line3D::IsParallel
【函数功能】        检查直线是否平行
【参数】            输入参数 const Line3D& Other 三维直线
【返回值】         bool 是否平行
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsParallel(const Line3D& Other) const{
    //计算两直线的方向向量
    Vector3D v1 = GetPoint(1) - GetPoint(0);
    Vector3D v2 = Other.GetPoint(1) - Other.GetPoint(0);
    //检查两向量是否平行
    return v1.IsParallel(v2);
}

/*************************************************************************
【函数名称】       Line3D::IsVertical
【函数功能】        检查直线是否垂直
【参数】            输入参数 const Line3D& Other 三维直线
【返回值】         bool 是否垂直
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsVertical(const Line3D& Other) const{
    //计算两直线的方向向量
    Vector3D v1 = GetPoint(1) - GetPoint(0);
    Vector3D v2 = Other.GetPoint(1) - Other.GetPoint(0);
    //检查两向量是否垂直
    return v1.IsVertical(v2);
}

/*************************************************************************
【函数名称】       Line3D::IsIntersect
【函数功能】        检查直线是否相交
【参数】            输入参数 const Line3D& Other 三维直线
【返回值】         bool 是否相交
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsIntersect(const Line3D& Other) const{
    //计算两直线的方向向量
    Vector3D v1 = GetPoint(1) - GetPoint(0);
    Vector3D v2 = Other.GetPoint(1) - Other.GetPoint(0);
    //检查两向量是否共面
    if (v1.IsParallel(v2)) {
        //共面，检查是否平行
        if (v1.IsParallel(Other.GetPoint(0) - GetPoint(0))) {
            //平行，不相交
            return false;
        }
        else {
            //不平行，相交
            return true;
        }
    }
    else {
        //不共面，相交
        return true;
    }
}

/*************************************************************************
【函数名称】       Line3D::IsOnLine
【函数功能】        检查点是否在直线上
【参数】            输入参数 const Point3D& APoint 三维点
【返回值】         bool 是否在直线上
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsOnLine(const Point3D& APoint) const{
    //计算点到直线的距离
    double d = GetPointLineDistance(APoint);
    //检查距离是否为0
    return d < EPS;
}

/*************************************************************************
【函数名称】       Line3D::IsOnSegment
【函数功能】        检查点是否在线段上
【参数】            输入参数 const Point3D& p 三维点
【返回值】         bool 是否在线段上
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsOnSegment(const Point3D& APoint) const{
    //检查点是否在直线上
    if (!IsOnLine(APoint)) {
        return false;
    }
    //计算点到起点和终点的距离
    double d1 = GetPoint(0).Distance(APoint);
    double d2 = GetPoint(1).Distance(APoint);
    //检查是否在线段上
    return d1 < EPS || d2 < EPS;
}

/*************************************************************************
【函数名称】       Line3D::Angle
【函数功能】        求两直线之间的夹角
【参数】            输入参数 const Line3D& Other 三维直线
【返回值】         double 夹角
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::Angle(const Line3D& Other) const{
    //计算两直线的方向向量
    Vector3D v1 = GetPoint(1) - GetPoint(0);
    Vector3D v2 = Other.GetPoint(1) - Other.GetPoint(0);
    //计算两向量的夹角
    return v1.Angle(v2);
}


/*************************************************************************
【函数名称】       Line3D::LineDistance
【函数功能】        求两直线间的距离
【参数】            输入参数 const Line3D& Other 三维直线
【返回值】         double 距离
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::LineDistance(const Line3D& Other) const{
    // 计算两直线的方向向量
    Vector3D v1 = GetPoint(1) - GetPoint(0);
    Vector3D v2 = Other.GetPoint(1) - Other.GetPoint(0);

    // 检查两直线是否平行
    Vector3D n = v1 ^ v2;
    if (n.Length() < EPS) {
        // 如果平行，计算一条直线上的任意一点到另一条直线的距离
        Vector3D r = Other.GetPoint(0) - GetPoint(0);
        return (r ^ v1).Length() / v1.Length();
    }

    // 如果不平行，计算两直线间的距离
    Vector3D r = Other.GetPoint(0) - GetPoint(0);
    return std::abs(r * n) / n.Length();
}

/*************************************************************************
【函数名称】       Line3D::Direction
【函数功能】        计算直线的一个单位方向向量
【参数】            无
【返回值】         Vector3D 单位方向向量
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Line3D::Direction() const{
    //计算直线的方向向量
    return (GetPoint(1) - GetPoint(0)).Direction();
}
/*************************************************************************
【函数名称】       Line3D::GetStartPoint
【函数功能】        获取起点
【参数】            无
【返回值】         Vector3D 单位方向向量
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
const Point3D& Line3D::GetStartPoint() const{
    return GetPoint(0);
}

/*************************************************************************
【函数名称】       Line3D::GetEndPoint
【函数功能】        获取终点
【参数】            无
【返回值】         Vector3D 单位方向向量
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
const Point3D& Line3D::GetEndPoint() const{
    return GetPoint(1);
}
/*************************************************************************
【函数名称】       Line3D::Normal
【函数功能】        计算直线的一个单位法向量
【参数】            无
【返回值】         Vector3D 单位法向量
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Line3D::Normal() const{
    //计算直线的方向向量
    return (GetPoint(1) - GetPoint(0)).Normal();
}

/*************************************************************************
【函数名称】       Line3D::GetPointLineDistance
【函数功能】        计算点到直线的距离
【参数】            输入参数 const Point3D& p 三维点
【返回值】         double 距离
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::GetPointLineDistance(const Point3D& APoint) const{
    //计算点到直线的距离
    return (APoint - GetPoint(0)).CrossProduct(GetPoint(1) 
        - GetPoint(0)).Length() / (GetPoint(1) - GetPoint(0)).Length();
}

/*************************************************************************
【函数名称】       double GetLength() const;
【函数功能】        获取直线长度
【参数】            无
【返回值】         double 周长/长度
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::GetLength() const{
    //计算直线的长度
    return (GetPoint(1) - GetPoint(0)).Length();
}

/*************************************************************************
【函数名称】       virtual double GetArea() const 
【函数功能】        直线面积，直接返回0.0
【参数】            无
【返回值】        double 面积
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::GetArea() const{
    //直线面积为0
    return 0.0;
}

/*************************************************************************
【函数名称】       std::ostream& operator<<(std::ostream& os, const Line3D& l);
【函数功能】        重载流输出运算符
【参数】            输入参数 std::ostream& Stream 输出流
                   输入参数 const Line3D& l 三维直线
【返回值】        std::ostream& 输出流
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::ostream& operator<<(std::ostream& Stream, const Line3D& ALine){
    Stream << ALine.GetPoint(0) << " -> " << ALine.GetPoint(1);
    return Stream;
}

/*************************************************************************
【函数名称】       IsIntersect
【函数功能】       静态函数，检查两直线是否相交
【参数】            输入参数 std::ostream& os 输出流
                   输入参数 const Line3D& l 三维直线
【返回值】        bool 是否相交
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsIntersect(const Line3D& Line1, const Line3D& Line2){
    return Line1.IsIntersect(Line2);
}

/*************************************************************************
【函数名称】       Angle
【函数功能】        静态函数，求两直线之间的夹角
【参数】            输入参数 const Line3D& Line1 三维直线
                   输入参数 const Line3D& Line2 三维直线
【返回值】        double 夹角
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::Angle(const Line3D& Line1, const Line3D& Line2){
    return Line1.Angle(Line2);
}

/*************************************************************************
【函数名称】       LineDistance
【函数功能】        静态函数，求两直线间的距离
【参数】            输入参数 const Line3D& Line1 三维直线
                   输入参数 const Line3D& Line2 三维直线
【返回值】        double 距离
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::LineDistance(const Line3D& Line1, const Line3D& Line2){
    return Line1.LineDistance(Line2);
}

/*************************************************************************
【函数名称】       GetPointLineDistance
【函数功能】        静态函数，计算点到直线的距离
【参数】            输入参数 const Point3D& p 三维点
                   输入参数 const Line3D& l 三维直线
【返回值】        double 距离
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Line3D::GetPointLineDistance(const Point3D& APoint, const Line3D& ALine){
    return ALine.GetPointLineDistance(APoint);
}

/*************************************************************************
【函数名称】       IsParallel
【函数功能】        静态函数，计算两直线是否平行
【参数】            Line1 三维直线
                   Line2 三维直线
【返回值】        bool 是否平行
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsParallel(const Line3D& Line1, const Line3D& Line2){
    return Line1.IsParallel(Line2);
}

/*************************************************************************
【函数名称】       IsVertical
【函数功能】        静态函数，计算两直线是否垂直
【参数】            Line1 三维直线
                   Line2 三维直线
【返回值】        bool 是否垂直
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Line3D::IsVertical(const Line3D& Line1, const Line3D& Line2){
    return Line1.IsVertical(Line2);
}
