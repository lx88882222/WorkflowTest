/*************************************************************************
【文件名】                 Face3D.cpp
【功能模块和目的】         Face3D类的实现
【开发者及日期】           李想 2024/8/4
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include"Face3D.hpp"
#include"Point3D.hpp"
#include"Vector3D.hpp"
#include<initializer_list>
#include<iostream>




/*************************************************************************
【函数名称】       Face3D::Face3D
【函数功能】        带参数的构造函数
【参数】            输入参数 std::initializer_list<Point3D> init 三维点列表
【返回值】         无
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D::Face3D(std::initializer_list<Point3D> init):Element3D<3>(init){
    //调用基类构造函数
}

/*************************************************************************
【函数名称】       Face3D::~Face3D
【函数功能】        析构函数
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D::~Face3D(){
    //析构函数
}

/*************************************************************************
【函数名称】       Face3D::Face3D
【函数功能】       拷贝构造函数
【参数】           输入参数 const Face3D& Other 三维面
【返回值】         无
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D::Face3D(const Face3D& Other): 
Element3D(Other){
    //调用基类拷贝构造函数
}

/*************************************************************************
【函数名称】       Face3D::operator=
【函数功能】        赋值构造函数
【参数】            输入参数 const Face3D& Other 三维面
【返回值】         Face3D& 三维面
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Face3D& Face3D::operator=(const Face3D& Other){
    if (this == &Other) {
        return *this;
    }
    Element3D::operator=(Other);
    return *this;
}


/*************************************************************************
【函数名称】       Face3D::GetArea
【函数功能】       求三角形的面积
【参数】           无
【返回值】         double 三角形面积
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Face3D::GetArea() const{
    return GetArea(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}

/*************************************************************************
【函数名称】       Face3D::GetLength
【函数功能】       求三角形的周长
【参数】           无
【返回值】         double 三角形周长
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Face3D::GetLength() const{
    return GetLength(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}

/*************************************************************************
【函数名称】       Face3D::GetNormal
【函数功能】       求三角形的法向量
【参数】           无
【返回值】         Vector3D 三角形法向量
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Face3D::Normal() const{
    return GetNormal(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}


/*************************************************************************
【函数名称】       Face3D::GetBarycenter
【函数功能】       求三角形的重心
【参数】           无
【返回值】         Point3D 三角形重心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetBarycenter() const{
    return GetBarycenter(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}

/*************************************************************************
【函数名称】       Face3D::GetCircumcenter
【函数功能】       求三角形的外心
【参数】           无
【返回值】         Point3D 三角形外心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetCircumcenter() const{
    return GetCircumcenter(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}

/*************************************************************************
【函数名称】       Face3D::GetIncenter
【函数功能】       求三角形的内心
【参数】           无
【返回值】         Point3D 三角形内心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetIncenter() const{
    return GetIncenter(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}

/*************************************************************************
【函数名称】       Face3D::GetOrthocenter
【函数功能】       求三角形的垂心
【参数】           无
【返回值】         Point3D 三角形垂心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetOrthocenter() const{
    return GetOrthocenter(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}

/*************************************************************************
【函数名称】       Face3D::GetFermatPoint
【函数功能】       求三角形的费马点
【参数】           无
【返回值】         Point3D 三角形费马点
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetFermatPoint() const{
    return GetFermatPoint(
        GetPoint(0), 
        GetPoint(1), 
        GetPoint(2));
}

/*************************************************************************
【函数名称】       Face3D::GetArea
【函数功能】       静态函数，求三角形的面积
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         double 三角形面积
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Face3D::
GetArea(const Point3D& Point1, const Point3D& Point2, const Point3D& Point3){
    Vector3D v1 = Point2 - Point1;
    Vector3D v2 = Point3 - Point1;
    return 0.5 * v1.CrossProduct(v2).Length();
}

/*************************************************************************
【函数名称】       Face3D::GetLength
【函数功能】       静态函数，求三角形的周长
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         double 三角形周长
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
double Face3D::
GetLength(const Point3D& Point1, const Point3D& Point2, const Point3D& Point3){
    return Point1.Distance(Point2) 
        + Point2.Distance(Point3) + Point3.Distance(Point1);
}

/*************************************************************************
【函数名称】       Face3D::GetNormal
【函数功能】       静态函数，求三角形的法向量
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         Vector3D 三角形法向量
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Face3D::
GetNormal(const Point3D& Point1, const Point3D& Point2, const Point3D& Point3){
    Vector3D v1 = Point2 - Point1;
    Vector3D v2 = Point3 - Point1;
    return v1.CrossProduct(v2);
}

/*************************************************************************
【函数名称】       Face3D::GetUnitNormal
【函数功能】       静态函数，求三角形的单位法向量
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         Vector3D 三角形单位法向量
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Vector3D Face3D::GetUnitNormal(
    const Point3D& Point1, 
    const Point3D& Point2, 
    const Point3D& Point3){
    Vector3D v1 = Point2 - Point1;
    Vector3D v2 = Point3 - Point1;
    return v1.CrossProduct(v2).Unit();
}

/*************************************************************************
【函数名称】       Face3D::GetBarycenter
【函数功能】       静态函数，求三角形的重心
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         Point3D 三角形重心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetBarycenter(
    const Point3D& Point1, 
    const Point3D& Point2, 
    const Point3D& Point3){
    //没有重载点的加法，只能用坐标计算
    return Point3D(
        (Point1.X + Point2.X + Point3.X) / 3, 
        (Point1.Y + Point2.Y + Point3.Y) / 3, 
        (Point1.Z + Point2.Z + Point3.Z) / 3);
}

/*************************************************************************
【函数名称】       Face3D::GetCircumcenter
【函数功能】       静态函数，求三角形的外心
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         Point3D 三角形外心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetCircumcenter(
    const Point3D& Point1, 
    const Point3D& Point2, 
    const Point3D& Point3){
    Vector3D n = GetNormal(Point1, Point2, Point3);
    Point3D barycenter = GetBarycenter(Point1, Point2, Point3);
    //没有重载点的加法，只能用坐标计算
    return Point3D(
        barycenter.X + n.X, 
        barycenter.Y + n.Y, 
        barycenter.Z + n.Z);
}

/*************************************************************************
【函数名称】       Face3D::GetIncenter
【函数功能】       静态函数，求三角形的内心
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         Point3D 三角形内心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetIncenter(
    const Point3D& Point1, 
    const Point3D& Point2,
    const Point3D& Point3){
    double Len1 = Point2.Distance(Point3);
    double Len2 = Point1.Distance(Point3);
    double Len3 = Point1.Distance(Point2);
    double LenSum = Len1 + Len2 + Len3;
    double X = (Len1 * Point1.X + Len2 * Point2.X + Len3 * Point3.X) / LenSum;
    double Y = (Len1 * Point1.Y + Len2 * Point2.Y + Len3 * Point3.Y) / LenSum;
    double Z = (Len1 * Point1.Z + Len2 * Point2.Z + Len3 * Point3.Z) / LenSum;
    return Point3D(X, Y, Z);
}
/*************************************************************************
【函数名称】       Face3D::GetOrthocenter
【函数功能】       静态函数，求三角形的垂心
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         Point3D 三角形垂心
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetOrthocenter(
    const Point3D& Point1, 
    const Point3D& Point2, 
    const Point3D& Point3){
    Vector3D n = GetNormal(Point1, Point2, Point3);
    Point3D incenter = GetIncenter(Point1, Point2, Point3);
    //重载过点的减法，但返回的是向量，因此采用坐标计算
    return Point3D(incenter.X + n.X, incenter.Y + n.Y, incenter.Z + n.Z);
}

/*************************************************************************
【函数名称】       Face3D::GetFermatPoint
【函数功能】       静态函数，求三角形的费马点
【参数】           输入参数 const Point3D& Point1 三维点1
                 输入参数 const Point3D& Point2 三维点2
                 输入参数 const Point3D& Point3 三维点3
【返回值】         Point3D 三角形费马点
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Point3D Face3D::GetFermatPoint(
    const Point3D& Point1, 
    const Point3D& Point2, 
    const Point3D& Point3){
    double Len1 = Point2.Distance(Point3);
    double Len2 = Point1.Distance(Point3);
    double Len3 = Point1.Distance(Point2);
    double LenSum = Len1 + Len2 + Len3;
    double X = (Len1 * Point1.X + Len2 * Point2.X + Len3 * Point3.X) / LenSum;
    double Y = (Len1 * Point1.Y + Len2 * Point2.Y + Len3 * Point3.Y) / LenSum;
    double Z = (Len1 * Point1.Z + Len2 * Point2.Z + Len3 * Point3.Z) / LenSum;
    return Point3D(X, Y, Z);
}

/*************************************************************************
【函数名称】       std::ostream& operator<<
【函数功能】       重载流输出运算符
【参数】           输入参数 std::ostream& os 输出流
                 输入参数 const Face3D& f 三维面
【返回值】         std::ostream& 输出流
【开发者及日期】   李想 2024/8/4
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::ostream& operator<<(std::ostream& Stream, const Face3D& AFace){
    Stream << "Face3D: " << std::endl;
    for (size_t i = 0; i < 3; i++) {//三个顶点
        Stream << AFace.GetPoint(i) << std::endl;
    }
    return Stream;
}

