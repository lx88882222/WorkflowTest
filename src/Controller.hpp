/*************************************************************************
【文件名】                 Controller.hpp
【功能模块和目的】         控制器类的声明
【开发者及日期】           李想 2024/8/14
【更改记录】               无
*************************************************************************/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include "Model3D.hpp"
#include "OBJ_To_Model3D_Importer.hpp"
#include "Model3D_To_OBJ_Exporter.hpp"
#include "Point3D.hpp"
#include "Face3D.hpp"
#include "Line3D.hpp"
#include <vector>
#include <cstddef>
#include <memory>
#include <string>

//宏定义枚举转字符串
#define enum_to_string(x) #x

/*************************************************************************
【类名】             Controller
【功能】             单例模式的控制器类，实现没有界面的全部层级软件功能
【接口说明】         以下：
                    构造函数：Controller();
                    虚析构函数：virtual ~Controller();
                    拷贝构造函数删除 
                    赋值构造函数删除
                    静态函数：获取控制器实例的单例指针 GetInstance();
                    导入指定文件到Controller中的Model3D对象
                        RES ImportModel(const std::string& FileName);
                    导出Controller中的Model3D对象到指定文件
                        RES ExportModel(const std::string& FileName);
                    移除模型中的指定面
                        RES RemoveFace(const size_t& FaceIndex);
                    移除模型中的指定线
                        RES RemoveLine(const size_t& LineIndex);
                    向模型中添加指定面
                        RES AddFace(const Face3D& AFace);
                    向模型中添加指定线
                        RES AddLine(const Line3D& ALine);
                    修改模型中的指定面中的指定点
                        RES ModifyFace(const size_t& FaceIndex, 
                            const size_t& PointIndex, 
                            const Point3D& NewPoint);
                    修改模型中的指定线中的指定点
                        RES ModifyLine(const size_t& LineIndex, 
                            const size_t& PointIndex, 
                            const Point3D& NewPoint);
                    列出模型信息
                        RES ListModelInfo() const;
                    列出模型中的所有面信息
                        RES ListFaces() const;
                    列出模型中的所有线信息
                        RES ListLines() const;
                    列出模型中指定面的所有点信息
                        RES ListFacePoints (const size_t& FaceIndex) const;
                    列出模型中指定线的所有点信息
                        RES ListLinePoints (const size_t& LineIndex) const;


【开发者及日期】     李想 2024/8/14
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class Controller {
public:
    //--------------------------------------------------------------------------
    //必备隐性行为：
    //--------------------------------------------------------------------------
    //单例模式，因此删除拷贝构造函数
    Controller(const Controller& Other) = delete;
    //单例模式，因此删除赋值构造函数
    Controller& operator=(const Controller& Other) = delete;
    //虚析构函数
    virtual ~Controller() = default;
private:
    //--------------------------------------------------------------------------
    //私有的必备隐性行为：
    //--------------------------------------------------------------------------
    //单例模式，因此使用private的默认构造函数
    Controller();
    //--------------------------------------------------------------------------
    //私有的静态数据成员
    //--------------------------------------------------------------------------
    //控制器实例指针，初始化为指向NULL
    static std::shared_ptr<Controller> m_pInstance;
    //用于储存.obj文件中信息的model3D对象
    Model3D m_Model;
public:
    //--------------------------------------------------------------------------
    //内嵌类，用于实现数据交换
    //--------------------------------------------------------------------------
    //控制器中所有public函数的返回值的枚举类
    enum class RES {
        SUCCESS                             = 0,    //成功
        FACE_INDEX_OUT_OF_RANGE             = 1,    //面索引超出范围
        LINE_INDEX_OUT_OF_RANGE             = 2,    //线索引超出范围
        POINT_INDEX_OUT_OF_RANGE            = 3,    //点索引超出范围
        IMPORTER_ERROR                      = 4,    //导入器错误
        EXPORTER_ERROR                      = 5,    //导出器错误
        FILE_TYPE_ERROR                     = 6,    //文件类型错误
        FILE_OPEN_ERROR                     = 7,    //文件打开错误
        DUPLICATE_FACE_ERROR                = 8,    //重复面错误
        DUPLICATE_LINE_ERROR                = 9,    //重复线错误
        DUPLICATE_POINT_IN_FACE_ERROR       = 10, //重复面中的点错误
        DUPLICATE_POINT_IN_LINE_ERROR       = 11, //重复线中的点错误
        DUPLICTAE_IMPORTER_ERROR            = 12, //重复导入器错误
        DUPLICATE_EXPORTER_ERROR            = 13, //重复导出器错误
        UNKNOWN_ERROR                       = 14,   //未知错误
    };

    //模型信息
    class ModelInfo {
    public:
        //模型名称
        std::string Name;
        size_t FaceNum; //面数
        double TotalArea; //总面积
        size_t LineNum; //线数
        double TotalLength; //总长度
        size_t PointNum; //点数
        double BoundingBoxVolume; //包围盒体积
    };

    //点信息
    class PointInfo {
    public:
        double X; //X坐标
        double Y; //Y坐标
        double Z; //Z坐标
    };

    //线信息
    class LineInfo {
    public:
        double Length; //长度
        PointInfo PointsInfo[2]; //两点信息
    };

    //面信息
    class FaceInfo {
    public:
        double Area; //面积
        PointInfo PointsInfo[3]; //三点信息
    };

    //以下使用using简化名称
    //点信息列表
    using PointInfoList = std::vector<PointInfo>;

    //线信息列表
    using LineInfoList = std::vector<LineInfo>;

    //面信息列表
    using FaceInfoList = std::vector<FaceInfo>;

    //--------------------------------------------------------------------------
    //非静态Setters:
    //--------------------------------------------------------------------------
    //导入指定文件到Controller中的Model3D对象
    RES ImportModel(const std::string& FileName);
    //导出Controller中的Model3D对象到指定文件
    RES ExportModel(const std::string& FileName);
    //移除模型中的指定面
    RES RemoveFace(const size_t& FaceIndex);
    //移除模型中的指定线
    RES RemoveLine(const size_t& LineIndex);
    //向模型中添加指定面,传点而不是面对象，以实现在控制器中而不是界面类创建面对象
    RES AddFace(const Point3D& Point1, 
                const Point3D& Point2, 
                const Point3D& Point3);
    //向模型中添加指定线，传点而不是线对象，以实现在控制器中而不是界面类创建线对象
    RES AddLine(const Point3D& Point1, 
                const Point3D& Point2);
    //修改模型中的指定面中的指定点
    RES ModifyFace(const size_t& FaceIndex, 
        const size_t& PointIndex, const Point3D& NewPoint);
    //修改模型中的指定线中的指定点
    RES ModifyLine(const size_t& LineIndex, 
        const size_t& PointIndex, const Point3D& NewPoint);
    //--------------------------------------------------------------------------
    //非静态Getters:
    //--------------------------------------------------------------------------
    //列出模型信息
    RES ListModelInfo(ModelInfo& Info) const;
    //列出模型中的所有面信息
    RES ListFaces(FaceInfoList& Info) const;
    //列出模型中的所有线信息
    RES ListLines(LineInfoList& Info) const;
    //列出模型中指定面的所有点信息
    RES ListFacePoints (const size_t& FaceIndex, PointInfoList& Info) const;
    //列出模型中指定线的所有点信息
    RES ListLinePoints (const size_t& LineIndex, PointInfoList& Info) const;
    //--------------------------------------------------------------------------
    //静态函数：
    //--------------------------------------------------------------------------
    //获取控制器实例的单例指针
    static std::shared_ptr<Controller> GetInstance();
    //所有控制器公开成员函数返回值，对应的字符串
    static const std::string ResStr[];

};

#endif