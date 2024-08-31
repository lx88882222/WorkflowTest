/*************************************************************************
【文件名】                 Element3D.hpp
【功能模块和目的】         Element3D类声明及其定义，实现一个三维空间中的元素类，
                            用于表示三维空间中的线、面元素。初始化时固定点个数，
                            可以修改点的位置，但不能删除、添加、清空点。
                        由于使用了模板类，所以将声明和定义放在同一个文件中
【开发者及日期】           李想 2024/8/2
【更改记录】               李想 2024/8/2 添加了RepeatedPointException类声明，
                            用于表示重复点异常
                        李想 2024/8/3 添加了对受保护成员变量m_Points的常引用
                        李想 2024/8/5 添加了虚函数
                                 virtual Vector3D Normal() const = 0;
                        作为线、面元素的法向量的接口
                        李想 2024/8/4 添加了PointCount常引用，返回点的数目
*************************************************************************/

#include "Vector3D.hpp"
#ifndef ELEMENT3D_HPP
#define ELEMENT3D_HPP
#include "Point3D.hpp"
#include "CountFixedSet.hpp"
#include <cstddef> //size_t
#include <array> // std::array
#include <iostream> // std::ostream
#include <exception> // std::exception



/*************************************************************************
【类名】             Element3D
【功能】             Element3D类声明及定义，实现一个三维空间中的元素类，
                    用于表示三维空间中的线、面元素。
                    有一个CountFixedSet<Point3D,N>数据成员
                    初始化时固定点个数，
                    可以修改点的位置，但不能删除、添加、清空点。
                    由于使用了模板类，所以将声明和定义放在同一个文件中
【接口说明】         必备隐性行为：
                    默认构造函数 Element3D();
                    带参构造函数 Element3D(std::initializer_list<Point3D> init);
                    析构函数 virtual ~Element3D();
                    拷贝构造函数 Element3D(const Element3D& Other);
                    赋值构造函数 Element3D& operator=(const Element3D& Other);
                    
                    Setters:
                    修改点的位置 
                        void ModifyPoint(
                            size_t Index, const Point3D& OtherPoint);
                    修改点集 
                        void ModifyPoints(std::initializer_list<Point3D> init);
                    
                    Getters:
                    点个数的常引用
                        const size_t PointCount { N };
                    对受保护成员变量m_Points的常引用
                        const CountFixedSet<Point3D, N>& Points { m_Points };
                    获取点的个数 size_t GetPointCount() const;
                    获取点的位置 const Point3D& GetPoint(size_t Index) const;
                    获取点集 const CountFixedSet<Point3D, N>& GetPoints() const;
                    (虚函数）获取元素周长/长度 virtual double GetLength() const = 0;
                    (虚函数）获取元素面积 virtual double GetArea() const = 0;
                    (虚函数）获取元素法向量 virtual Vector3D Normal() const = 0;
                    检查有无重复点 bool HasRepeatedPoints() const;
                    重载==运算符 bool operator==(const Element3D& Other) const;
                    重载!=运算符 bool operator!=(const Element3D& Other) const;
                    重载[]运算符 const Point3D& operator[](size_t Index) const;
                    重载流输出运算符 friend std::ostream& operator<<
                                        (std::ostream& os, const Element3D& e);
                    
【开发者及日期】     李想 2024/8/2
【更改记录】         李想 2024/8/2 添加了RepeatedPointException类声明，
                            用于表示重复点异常
                    李想 2024/8/3 添加了对受保护成员变量m_Points的常引用
                    李想 2024/8/4 添加了PointCount常引用，返回点的数目
                    李想 2024/8/4 添加了虚函数virtual Vector3D Normal() const = 0;
                        作为线、面元素的法向量的接口
*************************************************************************/

template <size_t N>
class Element3D {
public:

/*************************************************************************
【类名】             RepeatedPointException
【功能】             自定义异常类，内嵌于Element3D类，用于表示重复点异常
【开发者及日期】     李想 2024/8/2
*************************************************************************/
    class RepeatedPointException : public std::exception {
    public:
        const char* what() const noexcept override;
    };
protected:
    //受保护数据成员，Point3D的固定数量容器，完美避免了重复点的问题
    CountFixedSet<Point3D, N> m_Points;
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //默认构造函数
    Element3D();
    //带参构造函数
    Element3D(std::initializer_list<Point3D> init);
    //析构函数
    virtual ~Element3D() = default;
    //拷贝构造函数
    Element3D(const Element3D& Other);
    //赋值构造函数
    Element3D& operator=(const Element3D& Other);
    //------------------------------------------------------------------
    //Setters:
    //------------------------------------------------------------------
    //修改点的位置，这个点用索引来确定
    void ModifyPoint(size_t Index, const Point3D& OtherPoint);
    //修改点集，这个点用坐标来确定
    void ModifyPoint(const Point3D& OldPoint, const Point3D& NewPoint);
    //修改点集
    void ModifyPoints(std::initializer_list<Point3D> init);
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //对受保护成员变量m_Points的常引用
    const CountFixedSet<Point3D, N>& Points { m_Points };
    //获取点的个数
    size_t GetPointCount() const;
    //获取点的位置
    const Point3D& GetPoint(size_t Index) const;
    //获取点集
    const CountFixedSet<Point3D, N>& GetPoints() const;
    //获取元素周长/长度
    virtual double GetLength() const = 0;
    //获取元素面积
    virtual double GetArea() const = 0;
    //获取元素法向量
    virtual Vector3D Normal() const = 0;
    //检查有无重复点
    bool HasRepeatedPoints() const;
    //重载==运算符,考虑点相同但点的顺序不同的情况
    bool operator==(const Element3D& Other) const;
    //重载!=运算符
    bool operator!=(const Element3D& Other) const;
    //重载[]运算符
    const Point3D& operator[](size_t Index) const;
    //------------------------------------------------------------------
    //友元函数
    //------------------------------------------------------------------
    //重载流输出运算符，由于是友元函数，所以在类内实现
    friend std::ostream& operator<<
    (std::ostream& Stream, const Element3D& AElem){
        for (size_t i = 0; i < N; ++i) {
            Stream << AElem.m_Points[i] << " ";
        }
        return Stream;
    }
};


//RepeatedPointException类的实现
template <size_t N>
const char* Element3D<N>::RepeatedPointException::what() const noexcept {
    return "Repeated points are not allowed.";
}

//Element3D类的实现
/*************************************************************************
【函数名称】         Element3D构造函数
【函数功能】         Element3D类的构造函数，初始化点集
【参数】             无
【返回值】           无
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
Element3D<N>::Element3D() : m_Points(){
}

/*************************************************************************
【函数名称】         Element3D构造函数
【函数功能】         Element3D类的构造函数，初始化点集,检查有无重复点,有则抛出异常
【参数】             std::initializer_list<Point3D> init: 初始化列表
【返回值】           无
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
Element3D<N>::Element3D(std::initializer_list<Point3D> init) : m_Points(init){
        //检查有无重复点
        if (HasRepeatedPoints()) {
            throw RepeatedPointException();
        }
}

/*************************************************************************
【函数名称】         Element3D拷贝构造函数
【函数功能】         Element3D类的拷贝构造函数
【参数】             const Element3D& Other: 被拷贝的对象
【返回值】           无
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
Element3D<N>::Element3D(const Element3D& Other) : m_Points(Other.m_Points){
    // 这里显式调用 CountFixedSet 的拷贝构造函数
}

/*************************************************************************
【函数名称】         Element3D赋值构造函数
【函数功能】         Element3D类的赋值构造函数
【参数】             const Element3D& Other: 被赋值的对象
【返回值】           Element3D&: 赋值后的对象
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
Element3D<N>& Element3D<N>::operator=(const Element3D& Other){
    if (this != &Other) {
        m_Points = Other.m_Points;
    }
    return *this;
}

/*************************************************************************
【函数名称】         Element3D::ModifyPoint
【函数功能】         修改点的位置
【参数】             size_t Index: 点的索引
                    const Point3D& OtherPoint: 新的点
【返回值】           无
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
void Element3D<N>::ModifyPoint(size_t Index, const Point3D& OtherPoint){
    m_Points.modify(m_Points[Index], OtherPoint);
}

/*************************************************************************
【函数名称】         Element3D::ModifyPoint
【函数功能】         修改点的位置
【参数】             const Point3D& OldPoint: 旧的点
                    const Point3D& NewPoint: 新的点
【返回值】           无
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
void Element3D<N>::
ModifyPoint(const Point3D& OldPoint, const Point3D& NewPoint){
    m_Points.modify(OldPoint, NewPoint);
}
/*************************************************************************
【函数名称】         Element3D::ModifyPoints
【函数功能】         修改点集
【参数】             std::initializer_list<Point3D> init: 新的点集
【返回值】           无
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
void Element3D<N>::ModifyPoints(std::initializer_list<Point3D> init){
    CountFixedSet<Point3D, N> NewPoints(init);
    m_Points = NewPoints;
    //检查赋值之后有无重复点
    if (HasRepeatedPoints()) {
        throw RepeatedPointException();
    }
}

/*************************************************************************
【函数名称】         Element3D::GetPointCount
【函数功能】         获取点的个数
【参数】             无
【返回值】           size_t: 点的个数
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
size_t Element3D<N>::GetPointCount() const{
    return m_Points.GetSize();
}

/*************************************************************************
【函数名称】         Element3D::GetPoint
【函数功能】         获取点的位置
【参数】             size_t Index: 点的索引
【返回值】           const Point3D&: 点的位置
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
const Point3D& Element3D<N>::GetPoint(size_t Index) const{
    return m_Points[Index];
}

/*************************************************************************
【函数名称】         Element3D::GetPoints
【函数功能】         获取点集
【参数】             无
【返回值】           const CountFixedSet<Point3D, N>&: 点集
【开发者及日期】     李想 2024/8/4
【更改记录】         无
*************************************************************************/
template <size_t N>
const CountFixedSet<Point3D, N>& Element3D<N>::GetPoints() const{
    return m_Points;
}

/*************************************************************************
【函数名称】         Element3D::HasRepeatedPoints
【函数功能】         检查有无重复点
【参数】             无
【返回值】           bool: 有重复点返回true，否则返回false
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
bool Element3D<N>::HasRepeatedPoints() const{
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i + 1; j < N; ++j) {
            if (m_Points[i] == m_Points[j]) {
                return true;
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】         Element3D::operator==
【函数功能】         重载==运算符,考虑点相同但点的顺序不同的情况
【参数】             const Element3D& Other: 另一个元素
【返回值】           bool: 相等返回true，否则返回false
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
bool Element3D<N>::operator==(const Element3D& Other) const{
    std::array<bool, N> matched = {false}; // 用于标记是否匹配过的点
    for (size_t i = 0; i < N; ++i) {
        bool found = false; // 用于标记是否找到匹配的点
        for (size_t j = 0; j < N; ++j) {
            if (!matched[j] && m_Points[i] == Other.m_Points[j]) {
                matched[j] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

/*************************************************************************
【函数名称】         Element3D::operator!=
【函数功能】         重载!=运算符
【参数】             const Element3D& Other: 另一个元素
【返回值】           bool: 不等返回true，否则返回false
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
bool Element3D<N>::operator!=(const Element3D& Other) const{
    return !(*this == Other);
}

/*************************************************************************
【函数名称】         Element3D::operator[]
【函数功能】         重载[]运算符
【参数】             size_t Index: 索引
【返回值】           const Point3D&: 点的位置
【开发者及日期】     李想 2024/8/2
【更改记录】         无
*************************************************************************/
template <size_t N>
const Point3D& Element3D<N>::operator[](size_t Index) const{
    return m_Points[Index];
}

#endif // ELEMENT3D_HPP