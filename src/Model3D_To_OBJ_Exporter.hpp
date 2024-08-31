/*************************************************************************
【文件名】                 Model3D_To_OBJ_Exporter.hpp
【功能模块和目的】         Model3D_To_OBJ_Exporter类的声明，继承Exporter，
                            实现导出Model3D对象到OBJ文件的功能
【开发者及日期】           李想 2024/8/12
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef MODEL3D_TO_OBJ_EXPORTER_HPP
#define MODEL3D_TO_OBJ_EXPORTER_HPP
#include "Model3D.hpp"
#include "Exporter.hpp"
#include <string>
#include <vector>
#include <memory>

/*************************************************************************
【类名】             Model3D_To_OBJ_Exporter
【功能】             Model3D_To_OBJ_Exporter类的声明，继承Exporter，
                    实现导入OBJ文件存入Model3D的功能
【接口说明】         继承得到Exporter全部接口
                    必备隐性行为：
                    构造函数 Model3D_To_OBJ_Exporter();
                    析构函数 virtual ~Model3D_To_OBJ_Exporter();
                    拷贝构造函数删除
                    赋值构造函数删除

                    Getters:
                    传入Model3D对象和文件名，导出Model3D对象到OBJ文件
                        void Export
                            (const std::string& FileName, Model3D& AT) const;
                    注册.obj文件导出器
                        static void RegisterExporter();
【开发者及日期】     李想 2024/8/12
【更改记录】         （若修改过则必需注明）
*************************************************************************/

class Model3D_To_OBJ_Exporter : public Exporter<Model3D> {
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //构造函数
    Model3D_To_OBJ_Exporter();
    //析构函数
    virtual ~Model3D_To_OBJ_Exporter() = default;
    //拷贝构造函数删除
    Model3D_To_OBJ_Exporter(const Model3D_To_OBJ_Exporter& Other) = delete;
    //赋值构造函数删除
    Model3D_To_OBJ_Exporter& operator=
    (const Model3D_To_OBJ_Exporter& Other) = delete; //形参列表与返回值同级，对齐
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //传入Model3D对象和文件名，导出Model3D对象到OBJ文件
    void Export(const std::string& FileName, Model3D& AT) const override;
    //注册.obj文件导出器
    static void RegisterExporter();
};


#endif