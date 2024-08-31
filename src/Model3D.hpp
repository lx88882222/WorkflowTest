/*************************************************************************
【文件名】                 Model3D.hpp
【功能模块和目的】         Model3D类的声明,储存并处理Line3D,Face3D
【开发者及日期】           李想 2024/8/5
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include <cstddef>
#ifndef MODEL3D_HPP
#define MODEL3D_HPP
#include "Line3D.hpp"
#include "Face3D.hpp"
#include "Point3D.hpp"
#include <vector>

/*************************************************************************
【类名】             Model3D
【功能】             Model3D类声明，储存并处理Line3D,Face3D
【接口说明】        必备隐性行为：
                    默认构造函数 Model3D();
                    带参构造函数 Model3D
                        (const std::vector<Face3D>& vFaces, 
                        const std::vector<Line3D>& vLines);
                    析构函数 virtual ~Model3D();
                    拷贝构造函数 Model3D(const Model3D& Other);
                    赋值构造函数 Model3D& operator=(const Model3D& Other);
                    
                    Getters:
                    重载加法运算符，实现模型合并
                        Model3D operator+(const Model3D& Other) const;
                    重载加法运算符，添加一个三角形
                        Model3D operator+(const Face3D& AFace) const;
                    重载加法运算符，添加一个直线
                        Model3D operator+(const Line3D& ALine) const;
                    重载减法运算符，实现模型差集
                        Model3D operator-(const Model3D& Other) const;
                    重载减法运算符，移除一个三角形
                        Model3D operator-(const Face3D& AFace) const;
                    重载减法运算符，移除一个直线
                        Model3D operator-(const Line3D& ALine) const;
                    重载==运算符，判断两个模型是否相等
                        bool operator==(const Model3D& Other) const;
                    
                    Setters:
                    添加一个三角形
                        bool AddFace(const Face3D& AFace);
                    以三个点的形式添加一个三角形
                        bool AddFace
                            (const Point3D& Point1, const Point3D& Point2, 
                            const Point3D& Point3);
                    添加一个直线
                        bool AddLine(const Line3D& ALine);
                    以两个点的形式添加一个直线
                        bool AddLine
                            (const Point3D& Point1, const Point3D& Point2);
                    修改一个三角形
                        bool ModifyFace
                            (const Face3D& OldFace, const Face3D& NewFace);
                    修改三角形中的一个点，这个点以索引的形式给出
【开发者及日期】        李想 2024/8/5
【更改记录】            （若修改过则必需注明）
*************************************************************************/
class Model3D {
private:
    //------------------------------------------------------------------
    //私有数据成员
    //------------------------------------------------------------------
    //用Vector存储直线
    std::vector<Line3D> m_Lines {};
    //用Vector存储三角形
    std::vector<Face3D> m_Faces {};
    //直线总数
    size_t m_ullLineNum {0};
    //三角形总数
    size_t m_ullFaceNum {0};
    //点的总数
    size_t m_ullPointNum {0};
    //Element3D总数（直线+三角形）
    size_t m_ullElementNum {0};
    //三角形总面积
    double m_rTotalArea {0};
    //三角形总周长
    double m_rTotalPerimeter {0};
    //直线总长度
    double m_rTotalLength {0};
    //包围盒体积
    double m_rBoundingBoxVolume {0};
    //包围盒表面积
    double m_rBoundingBoxArea {0};
    //包围盒X轴长度
    double m_rBoundingBoxX {0};
    //包围盒Y轴长度
    double m_rBoundingBoxY {0};
    //包围盒Z轴长度
    double m_rBoundingBoxZ {0};
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //默认构造函数
    Model3D();
    //带参构造函数
    Model3D(
        const std::vector<Face3D>& vFaces, 
        const std::vector<Line3D>& vLines);
    //析构函数
    virtual ~Model3D();
    //拷贝构造函数
    Model3D(const Model3D& Other);
    //赋值构造函数
    Model3D& operator=(const Model3D& Other);
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //重载加法运算符，实现模型合并
    Model3D operator+(const Model3D& Other) const;
    //重载加法运算符，添加一个三角形
    Model3D operator+(const Face3D& AFace) const;
    //重载加法运算符，添加一个直线
    Model3D operator+(const Line3D& ALine) const;
    //重载减法运算符，实现模型差集
    Model3D operator-(const Model3D& Other) const;
    //重载减法运算符，移除一个三角形
    Model3D operator-(const Face3D& AFace) const;
    //重载减法运算符，移除一个直线
    Model3D operator-(const Line3D& ALine) const;
    //重载==运算符，判断两个模型是否相等
    bool operator==(const Model3D& Other) const;
    //------------------------------------------------------------------
    //Setters:
    //------------------------------------------------------------------
    //添加一个三角形
    bool AddFace(const Face3D& AFace);
    //以三个点的形式添加一个三角形
    bool AddFace(
        const Point3D& Point1, 
        const Point3D& Point2, 
        const Point3D& Point3);
    //添加一个直线
    bool AddLine(const Line3D& ALine);
    //以两个点的形式添加一个直线
    bool AddLine(const Point3D& Point1, const Point3D& Point2);
    //修改一个三角形
    bool ModifyFace(const Face3D& OldFace, const Face3D& NewFace);
    //修改三角形中的一个点，这个点以索引的形式给出
    bool ModifyFacePoint(
        const Face3D& AFace, 
        const Point3D& NewPoint, 
        const size_t& Index);
    //修改三角形中的一个点，这个点以坐标的形式给出
    bool ModifyFacePoint(
        const Face3D& AFace, 
        const Point3D& OldPoint, 
        const Point3D& NewPoint);
    //修改一个直线
    bool ModifyLine(const Line3D& OldLine, const Line3D& NewLine);
    //修改一个直线的一个点，这个点以坐标形式给出
    bool ModifyLinePoint(
        const Line3D& ALine, 
        const Point3D& OldPoint, 
        const Point3D& NewPoint);
    //修改一个直线的一个点，这个点以索引形式给出
    bool ModifyLinePoint(
        const Line3D& ALine, 
        const Point3D& NewPoint, 
        const size_t& Index);
    //移除一个三角形
    bool RemoveFace(const Face3D& AFace);
    //移除一个直线
    bool RemoveLine(const Line3D& ALine);
    //移除所有三角形
    bool RemoveAllFaces();
    //移除所有直线
    bool RemoveAllLines();
    //移除所有元素
    bool RemoveAllElements();
    //------------------------------------------------------------------
    //私有数据成员的常引用
    //------------------------------------------------------------------
    //获取直线列表
    const std::vector<Line3D>& Lines{m_Lines};
    //获取三角形列表
    const std::vector<Face3D>& Faces{m_Faces};
    //获取直线总数
    const size_t& LineNum{m_ullLineNum};
    //获取三角形总数
    const size_t& FaceNum{m_ullFaceNum};
    //获取点的总数
    const size_t& PointNum{m_ullPointNum};
    //获取Element3D总数（直线+三角形）
    const size_t& ElementNum{m_ullElementNum};
    //获取三角形总面积
    const double& TotalArea{m_rTotalArea};
    //获取三角形总周长
    const double& TotalPerimeter{m_rTotalPerimeter};
    //获取直线总长度
    const double& TotalLength{m_rTotalLength};
    //获取包围盒体积
    const double& BoundingBoxVolume{m_rBoundingBoxVolume};
    //获取包围盒表面积
    const double& BoundingBoxArea{m_rBoundingBoxArea};
    //获取包围盒X轴长度
    const double& BoundingBoxX{m_rBoundingBoxX};
    //获取包围盒Y轴长度
    const double& BoundingBoxY{m_rBoundingBoxY};
    //获取包围盒Z轴长度
    const double& BoundingBoxZ{m_rBoundingBoxZ};
    //------------------------------------------------------------------
    //公有数据成员,无读取/写入规则
    //------------------------------------------------------------------
    //模型名称
    std::string Name{std::string{"DEFAULT"}};
private:
    //--------------------------------------------------------------------------
    //私有 Setters:
    //--------------------------------------------------------------------------
    //计算更新包围盒
    void UpdateBoundingBox();
};

#endif // MODEL3D_HPP