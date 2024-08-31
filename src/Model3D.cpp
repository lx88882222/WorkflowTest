/*************************************************************************
【文件名】                 Model3D.cpp
【功能模块和目的】         Line3D类的实现
【开发者及日期】           李想 2024/8/8
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include "Model3D.hpp"
#include <vector>
#include <algorithm>
#include <cmath>


/*************************************************************************
【函数名称】      Model3D::Model3D
【函数功能】        默认构造函数
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Model3D::Model3D(){
    m_Lines.clear();
    m_Faces.clear();
    m_ullLineNum = 0;
    m_ullFaceNum = 0;
    m_ullPointNum = 0;
    m_ullElementNum = 0;
    m_rTotalArea = 0;
    m_rTotalPerimeter = 0;
    m_rTotalLength = 0;
    m_rBoundingBoxVolume = 0;
    m_rBoundingBoxArea = 0;
    m_rBoundingBoxX = 0;
    m_rBoundingBoxY = 0;
    m_rBoundingBoxZ = 0;
}

/*************************************************************************
【函数名称】      Model3D::Model3D
【函数功能】        带参构造函数
【参数】           const std::vector<Face3D>& vFaces, const std::vector<Line3D>& vLines
【返回值】         无
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Model3D::
Model3D(const std::vector<Face3D>& vFaces, const std::vector<Line3D>& vLines){
    //逐一添加元素，具体的添加函数与统计值更新在后面
    //逐一添加直线
    for (auto Face : vFaces) {
        AddFace(Face);
    }
    //逐一添加线
    for (auto Line : vLines) {
        AddLine(Line);
    }
    UpdateBoundingBox();
}

/*************************************************************************
【函数名称】      Model3D::~Model3D
【函数功能】        析构函数
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Model3D::~Model3D(){
    //析构函数
}

/*************************************************************************
【函数名称】      Model3D::Model3D
【函数功能】        拷贝构造函数
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Model3D::Model3D(const Model3D& Other){
    Name = Other.Name;
    m_Lines = Other.m_Lines;
    m_Faces = Other.m_Faces;
    m_ullLineNum = Other.m_ullLineNum;
    m_ullFaceNum = Other.m_ullFaceNum;
    m_ullPointNum = Other.m_ullPointNum;
    m_ullElementNum = Other.m_ullElementNum;
    m_rTotalArea = Other.m_rTotalArea;
    m_rTotalPerimeter = Other.m_rTotalPerimeter;
    m_rTotalLength = Other.m_rTotalLength;
    m_rBoundingBoxVolume = Other.m_rBoundingBoxVolume;
    m_rBoundingBoxArea = Other.m_rBoundingBoxArea;
    m_rBoundingBoxX = Other.m_rBoundingBoxX;
    m_rBoundingBoxY = Other.m_rBoundingBoxY;
    m_rBoundingBoxZ = Other.m_rBoundingBoxZ;
}

/*************************************************************************
【函数名称】      Model3D::operator=
【函数功能】        赋值构造函数
【参数】            const Model3D& Other
【返回值】         Model3D&
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/

Model3D& Model3D::operator=(const Model3D& Other){
    if (this == &Other) {
        return *this;
    }
    Name = Other.Name;
    m_Lines = Other.m_Lines;
    m_Faces = Other.m_Faces;
    m_ullLineNum = Other.m_ullLineNum;
    m_ullFaceNum = Other.m_ullFaceNum;
    m_ullPointNum = Other.m_ullPointNum;
    m_ullElementNum = Other.m_ullElementNum;
    m_rTotalArea = Other.m_rTotalArea;
    m_rTotalPerimeter = Other.m_rTotalPerimeter;
    m_rTotalLength = Other.m_rTotalLength;
    m_rBoundingBoxVolume = Other.m_rBoundingBoxVolume;
    m_rBoundingBoxArea = Other.m_rBoundingBoxArea;
    m_rBoundingBoxX = Other.m_rBoundingBoxX;
    m_rBoundingBoxY = Other.m_rBoundingBoxY;
    m_rBoundingBoxZ = Other.m_rBoundingBoxZ;
    return *this;
}

/*************************************************************************
【函数名称】      Model3D::operator+
【函数功能】        重载加法运算符，实现模型合并
【参数】            const Model3D& Other
【返回值】         Model3D
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D Model3D::operator+(const Model3D& Other) const{
    Model3D NewModel;
    NewModel = *this;
    for (auto Face : Other.m_Faces) {
        NewModel.AddFace(Face);
    }
    for (auto Line : Other.m_Lines) {
        NewModel.AddLine(Line);
    }
    NewModel.Name = Name + "+" + Other.Name;
    return NewModel;
}

/*************************************************************************
【函数名称】      Model3D operator+
【函数功能】        重载加法运算符，添加一个三角形
【参数】            const Face3D& Face
【返回值】         Model3D
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D Model3D::operator+(const Face3D& AFace) const{
    Model3D NewModel;
    NewModel = *this;
    NewModel.AddFace(AFace);
    return NewModel;
}

/*************************************************************************
【函数名称】      Model3D operator+
【函数功能】        重载加法运算符，添加一个直线
【参数】            const Line3D& Line
【返回值】         Model3D
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D Model3D::operator+(const Line3D& ALine) const{
    Model3D NewModel;
    NewModel = *this;
    NewModel.AddLine(ALine);
    return NewModel;
}

/*************************************************************************
【函数名称】      Model3D::operator-
【函数功能】        重载减法运算符，实现模型差集
【参数】            const Model3D& Other
【返回值】         Model3D
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D Model3D::operator-(const Model3D& Other) const{
    Model3D NewModel;
    NewModel = *this;
    for (auto Face : Other.m_Faces) {
        NewModel.RemoveFace(Face);
    }
    for (auto Line : Other.m_Lines) {
        NewModel.RemoveLine(Line);
    }
    NewModel.Name = Name + "-" + Other.Name;
    return NewModel;
}

/*************************************************************************
【函数名称】      Model3D::operator-
【函数功能】        重载减法运算符，移除一个三角形
【参数】            const Face3D& Face
【返回值】         Model3D
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D Model3D::operator-(const Face3D& AFace) const{
    Model3D NewModel;
    NewModel = *this;
    NewModel.RemoveFace(AFace);
    return NewModel;
}

/*************************************************************************
【函数名称】      Model3D::operator-
【函数功能】        重载减法运算符，移除一个直线
【参数】            const Line3D& Line
【返回值】         Model3D
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D Model3D::operator-(const Line3D& ALine) const{
    Model3D NewModel;
    NewModel = *this;
    NewModel.RemoveLine(ALine);
    return NewModel;
}

/*************************************************************************
【函数名称】      Model3D::operator==
【函数功能】        重载==运算符，判断两个模型是否相等
【参数】            const Model3D& Other
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::operator==(const Model3D& Other) const{
    if (m_Faces.size() != Other.m_Faces.size() 
        || m_Lines.size() != Other.m_Lines.size()) {
        return false;//如果元素数量不同，直接返回false
    }
    for (int i = 0; i < m_Faces.size(); i++) {
        if (m_Faces[i] != Other.m_Faces[i]) {
            return false;
        }
    }
    for (int i = 0; i < m_Lines.size(); i++) {
        if (m_Lines[i] != Other.m_Lines[i]) {
            return false;
        }
    }
    return true;
}

/*************************************************************************
【函数名称】      Model3D::AddFace
【函数功能】        添加一个三角形，如添加后有重复，禁止添加
【参数】            const Face3D& Face
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::AddFace(const Face3D& AFace){
    //检查是否有重复
    for (int i = 0; i < m_Faces.size(); i++) {
        if (m_Faces[i] == AFace) {
            return false;
        }
    }
    m_Faces.push_back(AFace);
    m_ullFaceNum++;
    m_ullElementNum++;
    m_rTotalArea += AFace.GetArea();
    m_rTotalPerimeter += AFace.GetLength();
    m_ullPointNum += 3;
    UpdateBoundingBox();
    return true;
}

/*************************************************************************
【函数名称】      Model3D::AddFace
【函数功能】        以三个点的形式添加一个三角形，如果添加后有重复，禁止添加
【参数】            const Point3D& Point1, 
                    const Point3D& Point2, 
                    const Point3D& Point3
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::
AddFace(const Point3D& Point1, const Point3D& Point2, const Point3D& Point3){
        //检查是否有重复
        for (int i = 0; i < m_Faces.size(); i++) {
            if (m_Faces[i] == Face3D({Point1, Point2, Point3})) {
                return false;
            }
        }
        Face3D NewFace({Point1, Point2, Point3});
        m_Faces.push_back(NewFace);
        m_ullFaceNum++;
        m_ullElementNum++;
        m_rTotalArea += NewFace.GetArea();
        m_rTotalPerimeter += NewFace.GetLength();
        m_ullPointNum += 3;
        UpdateBoundingBox();
        return true;
}

/*************************************************************************
【函数名称】      Model3D::AddLine
【函数功能】        添加一条直线，如添加后有重复，禁止添加
【参数】            const Line3D& Line
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::AddLine(const Line3D& ALine){
    //检查是否有重复
    for (int i = 0; i < m_Lines.size(); i++) {
        if (m_Lines[i] == ALine) {
            return false;
        }
    }
    m_Lines.push_back(ALine);
    m_ullLineNum++;
    m_ullElementNum++;
    m_rTotalLength += ALine.GetLength();
    m_ullPointNum += 2;
    UpdateBoundingBox();
    return true;
}

/*************************************************************************
【函数名称】      Model3D::AddLine
【函数功能】        以两个点的形式添加一条直线，如添加后有重复，禁止添加
【参数】            const Point3D& Point1, const Point3D& Point2
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::AddLine(const Point3D& Point1, const Point3D& Point2){
    //检查是否有重复
    for (int i = 0; i < m_Lines.size(); i++) {
        if (m_Lines[i] == Line3D({Point1, Point2})) {
            return false;
        }
    }
    Line3D NewLine({Point1, Point2});
    m_Lines.push_back(NewLine);
    m_ullLineNum++;
    m_ullElementNum++;
    m_rTotalLength += NewLine.GetLength();
    m_ullPointNum += 2;
    UpdateBoundingBox();
    return true;
}

/*************************************************************************
【函数名称】      Model3D::ModifyFace
【函数功能】        修改一个三角形，如修改后有重复，禁止修改
【参数】            const Face3D& OldFace, const Face3D& NewFace
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::ModifyFace(const Face3D& OldFace, const Face3D& NewFace){
    //检查是否有重复
    for (int i = 0; i < m_Faces.size(); i++) {
        if (m_Faces[i] == NewFace) {
            return false;
        }
    }
    for (int i = 0; i < m_Faces.size(); i++) {
        if (m_Faces[i] == OldFace) {
            m_Faces[i] = NewFace;
            m_rTotalArea -= OldFace.GetArea();
            m_rTotalPerimeter -= OldFace.GetLength();
            m_rTotalArea += NewFace.GetArea();
            m_rTotalPerimeter += NewFace.GetLength();
            UpdateBoundingBox();
            return true;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】      Model3D::ModifyLine
【函数功能】        修改一条直线，如修改后有重复，禁止修改
【参数】            const Line3D& OldLine, const Line3D& NewLine
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::ModifyLine(const Line3D& OldLine, const Line3D& NewLine){
    //检查是否有重复
    for (int i = 0; i < m_Lines.size(); i++) {
        if (m_Lines[i] == NewLine) {
            return false;
        }
    }
    for (int i = 0; i < m_Lines.size(); i++) {
        if (m_Lines[i] == OldLine) {
            m_Lines[i] = NewLine;
            m_rTotalLength -= OldLine.GetLength();
            m_rTotalLength += NewLine.GetLength();
            UpdateBoundingBox();
            return true;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】      Model3D::ModifyFacePoint
【函数功能】        修改三角形中的一个点，这个点以索引的形式给出，
                    如修改后有重复，禁止修改
【参数】            const Face3D& Face, const Point3D& NewPoint, size_t& Index
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::ModifyFacePoint(
    const Face3D& Face, 
    const Point3D& NewPoint, 
    const size_t& Index){
        for (int i = 0; i < m_Faces.size(); i++) {
            if (m_Faces[i] == Face) {
                //一个临时Face3D对象，用于检查是否有重复
                Face3D tempFace = m_Faces[i];
                tempFace.ModifyPoint(Index,NewPoint);
                for (int j = 0; j < m_Faces.size(); j++) {
                    if (m_Faces[j] == tempFace) {
                        return false;
                    }
                }
                m_Faces[i].ModifyPoint(Index,NewPoint);
                m_rTotalArea -= Face.GetArea();
                m_rTotalPerimeter -= Face.GetLength();
                m_rTotalArea += m_Faces[i].GetArea();
                m_rTotalPerimeter += m_Faces[i].GetLength();
                UpdateBoundingBox();
                return true;
            }
        }
        return false;
}

/*************************************************************************
【函数名称】      Model3D::ModifyFacePoint
【函数功能】        修改三角形中的一个点，这个点以坐标的形式给出，
                    如修改后有重复，禁止修改
【参数】            const Face3D& Face, 
                    const Point3D& OldPoint, const Point3D& NewPoint
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::ModifyFacePoint(
    const Face3D& Face,
    const Point3D& OldPoint, 
    const Point3D& NewPoint){
    for (int i = 0; i < m_Faces.size(); i++) {
        if (m_Faces[i] == Face) {
            //一个临时Face3D对象，用于检查是否有重复
            Face3D tempFace = m_Faces[i];
            tempFace.ModifyPoint(OldPoint,NewPoint);
            for (int j = 0; j < m_Faces.size(); j++) {
                if (m_Faces[j] == tempFace) {
                    return false;
                }
            }
            m_Faces[i].ModifyPoint(OldPoint,NewPoint);
            m_rTotalArea -= Face.GetArea();
            m_rTotalPerimeter -= Face.GetLength();
            m_rTotalArea += m_Faces[i].GetArea();
            m_rTotalPerimeter += m_Faces[i].GetLength();
            UpdateBoundingBox();
            return true;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】      Model3D::ModifyLinePoint
【函数功能】        修改直线中的一个点，这个点以索引的形式给出，
                    如修改后有重复，禁止修改
【参数】            const Line3D& Line, const Point3D& NewPoint, size_t& Index
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::ModifyLinePoint(
    const Line3D& Line, 
    const Point3D& NewPoint, 
    const size_t& Index){
        for (int i = 0; i < m_Lines.size(); i++) {
            if (m_Lines[i] == Line) {
                //一个临时Line3D对象，用于检查是否有重复
                Line3D tempLine = m_Lines[i];
                tempLine.ModifyPoint(Index,NewPoint);
                for (int j = 0; j < m_Lines.size(); j++) {
                    if (m_Lines[j] == tempLine) {
                        return false;
                    }
                }
                m_Lines[i].ModifyPoint(Index,NewPoint);
                m_rTotalLength -= Line.GetLength();
                m_rTotalLength += m_Lines[i].GetLength();
                UpdateBoundingBox();
                return true;
            }
        }
        return false;
}

/*************************************************************************
【函数名称】      Model3D::ModifyLinePoint
【函数功能】        修改直线中的一个点，这个点以坐标的形式给出，
                    如修改后有重复，禁止修改
【参数】            const Line3D& Line, 
                    const Point3D& OldPoint, const Point3D& NewPoint
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::ModifyLinePoint(
    const Line3D& Line, 
    const Point3D& OldPoint, 
    const Point3D& NewPoint){
        for (int i = 0; i < m_Lines.size(); i++) {
            if (m_Lines[i] == Line) {
                //一个临时Line3D对象，用于检查是否有重复
                Line3D tempLine = m_Lines[i];
                tempLine.ModifyPoint(OldPoint,NewPoint);
                for (int j = 0; j < m_Lines.size(); j++) {
                    if (m_Lines[j] == tempLine) {
                        return false;
                    }
                }
                m_Lines[i].ModifyPoint(OldPoint,NewPoint);
                m_rTotalLength -= Line.GetLength();
                m_rTotalLength += m_Lines[i].GetLength();
                UpdateBoundingBox();
                return true;
            }
        }
        return false;
}

/*************************************************************************
【函数名称】      Model3D::RemoveFace
【函数功能】        移除一个三角形
【参数】            const Face3D& Face
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::RemoveFace(const Face3D& AFace){
    for (int i = 0; i < m_Faces.size(); i++) {
        if (m_Faces[i] == AFace) {
            m_Faces.erase(m_Faces.begin() + i);
            m_ullFaceNum--;
            m_ullElementNum--;
            m_rTotalArea -= AFace.GetArea();
            m_rTotalPerimeter -= AFace.GetLength();
            m_ullPointNum -= 3;
            UpdateBoundingBox();
            return true;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】      Model3D::RemoveLine
【函数功能】        移除一条直线
【参数】            const Line3D& Line
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::RemoveLine(const Line3D& ALine){
    for (int i = 0; i < m_Lines.size(); i++) {
        if (m_Lines[i] == ALine) {
            m_Lines.erase(m_Lines.begin() + i);
            m_ullLineNum--;
            m_ullElementNum--;
            m_rTotalLength -= ALine.GetLength();
            m_ullPointNum -= 2;
            UpdateBoundingBox();
            return true;
        }
    }
    return false;
}

/*************************************************************************
【函数名称】      Model3D::RemoveAllFaces
【函数功能】        移除所有三角形
【参数】            无
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::RemoveAllFaces() {
    m_Faces.clear();
    m_ullFaceNum = 0;
    m_ullElementNum -= m_ullFaceNum;
    m_rTotalArea = 0;
    m_rTotalPerimeter = 0;
    m_ullPointNum -= m_ullFaceNum * 3;
    UpdateBoundingBox();
    return true;
}

/*************************************************************************
【函数名称】      Model3D::RemoveAllLines
【函数功能】        移除所有直线
【参数】            无
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::RemoveAllLines(){
    m_Lines.clear();
    m_ullLineNum = 0;
    m_ullElementNum -= m_ullLineNum;
    m_rTotalLength = 0;
    m_ullPointNum -= m_ullLineNum * 2;
    UpdateBoundingBox();
    return true;
}

/*************************************************************************
【函数名称】      Model3D::RemoveAllElements
【函数功能】        移除所有元素
【参数】            无
【返回值】         bool
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
bool Model3D::RemoveAllElements(){
    m_Lines.clear();
    m_Faces.clear();
    m_ullLineNum = 0;
    m_ullFaceNum = 0;
    m_ullElementNum = 0;
    m_rTotalArea = 0;
    m_rTotalPerimeter = 0;
    m_rTotalLength = 0;
    m_ullPointNum = 0;
    UpdateBoundingBox();
    return true;
}

/*************************************************************************
【函数名称】      Model3D::UpdateBoundingBox
【函数功能】        更新包围盒
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/8
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model3D::UpdateBoundingBox(){
    m_rBoundingBoxX = 0; //初始化包围盒
    m_rBoundingBoxY = 0;
    m_rBoundingBoxZ = 0;
    m_rBoundingBoxVolume = 0;
    m_rBoundingBoxArea = 0;
    //如果没有元素，直接返回
    if (m_ullElementNum == 0) {
        return;
    }
    //初始化包围盒所有坐标的最大最小值
    double Max_X;
    double Max_Y;
    double Max_Z;
    double Min_X;
    double Min_Y;
    double Min_Z;
    //如果有直线，初始化为第一条直线的起点坐标
    if (m_ullLineNum > 0) {
        Max_X = m_Lines[0].GetPoint(0).X;
        Max_Y = m_Lines[0].GetPoint(0).Y;
        Max_Z = m_Lines[0].GetPoint(0).Z;
        Min_X = m_Lines[0].GetPoint(0).X;
        Min_Y = m_Lines[0].GetPoint(0).Y;
        Min_Z = m_Lines[0].GetPoint(0).Z;
    }
    //否则，初始化为第一个三角形的第一个点坐标
    else {
        Max_X = m_Faces[0].GetPoint(0).X;
        Max_Y = m_Faces[0].GetPoint(0).Y;
        Max_Z = m_Faces[0].GetPoint(0).Z;
        Min_X = m_Faces[0].GetPoint(0).X;
        Min_Y = m_Faces[0].GetPoint(0).Y;
        Min_Z = m_Faces[0].GetPoint(0).Z;
    }
    //在所有Face3D中逐一点比较，更新包围盒所有坐标最小值和最大值
    for (auto Face : m_Faces) {
        for (int i = 0; i < 3; i++) {
            if (Face.GetPoint(i).X > Max_X) {
                Max_X = Face.GetPoint(i).X;
            }
            if (Face.GetPoint(i).Y > Max_Y) {
                Max_Y = Face.GetPoint(i).Y;
            }
            if (Face.GetPoint(i).Z > Max_Z) {
                Max_Z = Face.GetPoint(i).Z;
            }
            if (Face.GetPoint(i).X < Min_X) {
                Min_X = Face.GetPoint(i).X;
            }
            if (Face.GetPoint(i).Y < Min_Y) {
                Min_Y = Face.GetPoint(i).Y;
            }
            if (Face.GetPoint(i).Z < Min_Z) {
                Min_Z = Face.GetPoint(i).Z;
            }
        }
    }
    //在所有Line3D中逐一点比较，更新包围盒所有坐标最小值和最大值
    for (auto Line : m_Lines) {
        for (int i = 0; i < 2; i++) {
            if (Line.GetPoint(i).X > Max_X) {
                Max_X = Line.GetPoint(i).X;
            }
            if (Line.GetPoint(i).Y > Max_Y) {
                Max_Y = Line.GetPoint(i).Y;
            }
            if (Line.GetPoint(i).Z > Max_Z) {
                Max_Z = Line.GetPoint(i).Z;
            }
            if (Line.GetPoint(i).X < Min_X) {
                Min_X = Line.GetPoint(i).X;
            }
            if (Line.GetPoint(i).Y < Min_Y) {
                Min_Y = Line.GetPoint(i).Y;
            }
            if (Line.GetPoint(i).Z < Min_Z) {
                Min_Z = Line.GetPoint(i).Z;
            }
        }
    }
    //边长为最大坐标减去最小坐标
    m_rBoundingBoxX = Max_X - Min_X;
    m_rBoundingBoxY = Max_Y - Min_Y;
    m_rBoundingBoxZ = Max_Z - Min_Z;
    //体积为长乘宽乘高
    m_rBoundingBoxVolume = m_rBoundingBoxX * m_rBoundingBoxY * m_rBoundingBoxZ;
    //表面积为长乘宽乘2加长乘高乘2加宽乘高乘2
    m_rBoundingBoxArea = m_rBoundingBoxX * m_rBoundingBoxY * 2 
        + m_rBoundingBoxX * m_rBoundingBoxZ * 2 
        + m_rBoundingBoxY * m_rBoundingBoxZ * 2;
}