/*************************************************************************
【文件名】                 Controller.cpp
【功能模块和目的】         控制器类的实现
【开发者及日期】           李想 2024/8/14
【更改记录】               无
*************************************************************************/

#include "Controller.hpp"
#include "CountFixedSet.hpp"
#include "FilePorter.hpp"
#include "OBJ_To_Model3D_Importer.hpp"
#include "Model3D_To_OBJ_Exporter.hpp"
#include "Point3D.hpp"
#include "Face3D.hpp"
#include "Line3D.hpp"
#include <vector>
#include <cstddef>
#include <memory>
#include <string>

//控制器实例指针
std::shared_ptr<Controller> Controller::m_pInstance{ nullptr };

//所有控制器公开成员函数返回值，对应的字符串
const std::string Controller::ResStr[]{
    "SUCCESS",
    "FACE_INDEX_OUT_OF_RANGE",
    "LINE_INDEX_OUT_OF_RANGE",
    "POINT_INDEX_OUT_OF_RANGE",
    "IMPORTER_ERROR",
    "EXPORTER_ERROR",
    "FILE_TYPE_ERROR",
    "FILE_OPEN_ERROR",
    "DUPLICATE_FACE_ERROR",
    "DUPLICATE_LINE_ERROR",
    "DUPLICATE_POINT_IN_FACE_ERROR",
    "DUPLICATE_POINT_IN_LINE_ERROR",
    "DUPLICTAE_IMPORTER_ERROR",
    "DUPLICATE_EXPORTER_ERROR",
    "UNKNOWN_ERROR"
};

/*************************************************************************
【函数名称】       Controller::Controller
【函数功能】        构造函数，注册.obj文件导入器和导出器
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::Controller(){
    //注册导入器
    OBJ_To_Model3D_Importer::RegisterImporter();
    //注册导出器
    Model3D_To_OBJ_Exporter::RegisterExporter();
}

/*************************************************************************
【函数名称】       Controller::GetInstance
【函数功能】        获取控制器实例的单例指针,若为空则创建一个新的实例
【参数】            无
【返回值】         控制器实例的单例指针
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
std::shared_ptr<Controller> Controller::GetInstance(){
    if (m_pInstance == nullptr) {
        m_pInstance = std::shared_ptr<Controller>(new Controller);
    }
    return m_pInstance;
}

/*************************************************************************
【函数名称】       Controller::ImportModel
【函数功能】        导入指定文件到Controller中的Model3D对象
【参数】            输入参数 const std::string& FileName 文件名
【返回值】         RES 返回导入结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ImportModel(const std::string& FileName){
    try {
        //创建导入器
        OBJ_To_Model3D_Importer importer;
        //导入模型
        m_Model = importer.Import(FileName);
    }
    catch (const OBJ_To_Model3D_Importer::FILE_OPEN_FAILED& e) {
        //文件打开失败
        return RES::FILE_OPEN_ERROR;
    }
    catch (const OBJ_To_Model3D_Importer::INVALID_FILE_EXTENSION& e) {
        //文件扩展名错误
        return RES::FILE_TYPE_ERROR;
    }
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::ExportModel
【函数功能】        导出Controller中的Model3D对象到指定文件
【参数】            输入参数 const std::string& FileName 文件名
【返回值】         RES 返回导出结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ExportModel(const std::string& FileName){
    try {
        //创建导出器
        Model3D_To_OBJ_Exporter exporter;
        //导出模型
        exporter.Export(FileName, m_Model);
    }
    catch (const Model3D_To_OBJ_Exporter::FILE_OPEN_FAILED& e) {
        //文件打开失败
        return RES::FILE_OPEN_ERROR;
    }
    catch (const Model3D_To_OBJ_Exporter::INVALID_FILE_EXTENSION& e) {
        //文件扩展名错误
        return RES::FILE_TYPE_ERROR;
    }
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::RemoveFace
【函数功能】        移除模型中的指定面
【参数】            输入参数 const size_t& FaceIndex 面索引
【返回值】         RES 返回移除结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::RemoveFace(const size_t& FaceIndex){
    //越界错误
    if (FaceIndex >= m_Model.FaceNum) {
        return RES::FACE_INDEX_OUT_OF_RANGE;
    }
    //移除面
    Face3D TempFace = m_Model.Faces[FaceIndex];
    m_Model.RemoveFace(TempFace);
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::RemoveLine
【函数功能】        移除模型中的指定线
【参数】            输入参数 const size_t& LineIndex 线索引
【返回值】         RES 返回移除结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::RemoveLine(const size_t& LineIndex){
    //越界错误
    if (LineIndex >= m_Model.LineNum) {
        return RES::LINE_INDEX_OUT_OF_RANGE;
    }
    //移除线
    Line3D TempLine = m_Model.Lines[LineIndex];
    m_Model.RemoveLine(TempLine);
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::AddFace
【函数功能】        向模型中添加指定面
【参数】            输入参数 const Point3D& Point1 点1
                    输入参数 const Point3D& Point2 点2
                    输入参数 const Point3D& Point3 点3
【返回值】         RES 返回添加结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::AddFace(
    const Point3D& Point1,
    const Point3D& Point2,
    const Point3D& Point3){
    try {
        //创建面
        Face3D AFace({ Point1, Point2, Point3 });
        if (!m_Model.AddFace(AFace)) {
            return RES::DUPLICATE_FACE_ERROR;//重复添加面
        }
    }
    catch (const CountFixedSet<Point3D, 3>::CountFixedSetException & e) {
        if (std::string(e.what()) == "Duplicate elements are not allowed.") {
            //面中不能有重复点
            return RES::DUPLICATE_POINT_IN_FACE_ERROR;
        }
        else {
            //未知错误
            return RES::UNKNOWN_ERROR;
        }
    }
    catch (const Element3D<3>::RepeatedPointException & e) {
        //面中不能有重复点
        return RES::DUPLICATE_POINT_IN_FACE_ERROR;
    }
    return RES::SUCCESS;

}


/*************************************************************************
【函数名称】       Controller::AddLine
【函数功能】        向模型中添加指定线
【参数】            输入参数 const Point3D& Point1 点1
                    输入参数 const Point3D& Point2 点2
【返回值】         RES 返回添加结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::AddLine
(const Point3D& Point1,const Point3D& Point2){
    try {
        //创建线
        Line3D ALine({ Point1, Point2 });
        if (!m_Model.AddLine(ALine)) {
            return RES::DUPLICATE_LINE_ERROR;//重复添加线
        }
    }
    catch (const CountFixedSet<Point3D, 2>::CountFixedSetException & e) {
        if (std::string(e.what()) == "Duplicate elements are not allowed.") {
            //线中不能有重复点
            return RES::DUPLICATE_POINT_IN_LINE_ERROR;
        }
        else {
            //未知错误
            return RES::UNKNOWN_ERROR;
        }
    }
    catch (const Element3D<2>::RepeatedPointException & e) {
        //线中不能有重复点
        return RES::DUPLICATE_POINT_IN_LINE_ERROR;
    }
    return RES::SUCCESS;

}

/*************************************************************************
【函数名称】       Controller::ModifyFace
【函数功能】        修改模型中的指定面中的指定点
【参数】            输入参数 const size_t& FaceIndex 面索引
                    输入参数 const size_t& PointIndex 点索引
                    输入参数 const Point3D& NewPoint 新点
【返回值】         RES 返回修改结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ModifyFace
(const size_t& FaceIndex, const size_t& PointIndex, const Point3D& NewPoint){
    //越界错误
    if (FaceIndex >= m_Model.FaceNum) {
        return RES::FACE_INDEX_OUT_OF_RANGE;
    }
    //越界错误
    if (PointIndex >= 3) {
        return RES::POINT_INDEX_OUT_OF_RANGE;
    }
    try {
        //修改面
        Face3D TempFace = m_Model.Faces[FaceIndex];
        TempFace.ModifyPoint(PointIndex, NewPoint);
        if (!m_Model.ModifyFace(m_Model.Faces[FaceIndex],
            TempFace)) {
            return RES::DUPLICATE_FACE_ERROR;//重复添加面
        }
    }
    catch (const CountFixedSet<Point3D, 3>::CountFixedSetException & e) {
        //点不能重复
        return RES::DUPLICATE_POINT_IN_FACE_ERROR;
    }
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::ModifyLine
【函数功能】        修改模型中的指定线中的指定点
【参数】            输入参数 const size_t& LineIndex 线索引
                    输入参数 const size_t& PointIndex 点索引
                    输入参数 const Point3D& NewPoint 新点
【返回值】         RES 返回修改结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ModifyLine(
    const size_t& LineIndex,
    const size_t& PointIndex, 
    const Point3D& NewPoint){
    //越界错误
    if (LineIndex >= m_Model.LineNum) {
        return RES::LINE_INDEX_OUT_OF_RANGE;
    }
    //越界错误
    if (PointIndex >= 2) {
        return RES::POINT_INDEX_OUT_OF_RANGE;
    }
    //修改线
    try {
        Line3D TempLine = m_Model.Lines[LineIndex];
        TempLine.ModifyPoint(PointIndex, NewPoint);
        if (!m_Model.ModifyLine(m_Model.Lines[LineIndex], TempLine)) {
            return RES::DUPLICATE_LINE_ERROR;//重复添加线
        }
    }
    catch (const CountFixedSet<Point3D, 2>::CountFixedSetException & e) {
        //点不能重复
        return RES::DUPLICATE_POINT_IN_LINE_ERROR;
    }
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::ListModelInfo
【函数功能】        列出模型信息
【参数】            输入参数 ModelInfo& Info，会被重写
【返回值】         RES 返回函数执行结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ListModelInfo(ModelInfo& Info) const{
    //列出模型信息
    Info.Name = m_Model.Name;
    Info.FaceNum = m_Model.FaceNum;
    Info.LineNum = m_Model.LineNum;
    Info.PointNum = m_Model.PointNum;
    Info.TotalArea = m_Model.TotalArea;
    Info.TotalLength = m_Model.TotalLength;
    Info.BoundingBoxVolume = m_Model.BoundingBoxVolume;
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::ListFaces
【函数功能】        列出模型中的所有面信息
【参数】            FaceInfoList& Info
【返回值】         RES 返回函数执行结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ListFaces(FaceInfoList& Info) const{
    //先清空
    Info.clear();
    //逐一生成并添加面信息
    for (auto face : m_Model.Faces) {
        FaceInfo TempInfo;
        for (size_t i = 0; i < 3; i++) {
            TempInfo.PointsInfo[i].X = face.Points[i].X;
            TempInfo.PointsInfo[i].Y = face.Points[i].Y;
            TempInfo.PointsInfo[i].Z = face.Points[i].Z;
        }
        TempInfo.Area = face.GetArea();
        Info.push_back(TempInfo);
    }
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::ListLines
【函数功能】        列出模型中的所有线信息
【参数】            LineInfoList& Info
【返回值】         RES 返回函数执行结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ListLines(LineInfoList& Info) const{
    //先清空
    Info.clear();
    //逐一生成并添加线信息
    for (auto line : m_Model.Lines) {
        LineInfo TempInfo;
        for (size_t i = 0; i < 2; i++) {
            TempInfo.PointsInfo[i].X = line.Points[i].X;
            TempInfo.PointsInfo[i].Y = line.Points[i].Y;
            TempInfo.PointsInfo[i].Z = line.Points[i].Z;
        }
        TempInfo.Length = line.GetLength();
        Info.push_back(TempInfo);
    }
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::ListFacePoints
【函数功能】        列出模型中的指定面的所有点信息
【参数】            输入参数 const size_t& FaceIndex 面索引
                    PointInfoList& Info
【返回值】         RES 返回函数执行结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::
ListFacePoints(const size_t& FaceIndex,PointInfoList& Info) const{
    //越界错误
    if (FaceIndex >= m_Model.FaceNum) {
        return RES::FACE_INDEX_OUT_OF_RANGE;
    }
    //先清空
    Info.clear();
    //逐一生成并添加点信息
    for (size_t i = 0; i < 3; i++) {
        PointInfo TempInfo;
        TempInfo.X = m_Model.Faces[FaceIndex].Points[i].X;
        TempInfo.Y = m_Model.Faces[FaceIndex].Points[i].Y;
        TempInfo.Z = m_Model.Faces[FaceIndex].Points[i].Z;
        Info.push_back(TempInfo);
    }
    return RES::SUCCESS;
}

/*************************************************************************
【函数名称】       Controller::ListLinePoints
【函数功能】        列出模型中的指定线的所有点信息
【参数】            输入参数 const size_t& LineIndex 线索引
                    PointInfoList& Info
【返回值】         RES 返回函数执行结果
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Controller::RES Controller::ListLinePoints
(const size_t& LineIndex, PointInfoList& Info) const{
    //越界错误
    if (LineIndex >= m_Model.LineNum) {
        return RES::LINE_INDEX_OUT_OF_RANGE;
    }
    //先清空
    Info.clear();
    //逐一生成并添加点信息
    for (size_t i = 0; i < 2; i++) {
        PointInfo TempInfo;
        TempInfo.X = m_Model.Lines[LineIndex].Points[i].X;
        TempInfo.Y = m_Model.Lines[LineIndex].Points[i].Y;
        TempInfo.Z = m_Model.Lines[LineIndex].Points[i].Z;
        Info.push_back(TempInfo);
    }
    return RES::SUCCESS;
}
