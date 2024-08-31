/*************************************************************************
【文件名】                 OBJ_To_Model3D_Importer.hpp
【功能模块和目的】         OBJ_To_Model3D_Importer类的声明，继承Importer，
                            实现导入OBJ文件存入Model3D的功能
【开发者及日期】           李想 2024/8/11
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef OBJ_TO_MODEL3D_IMPOTER_HPP
#define OBJ_TO_MODEL3D_IMPOTER_HPP
#include "Model3D.hpp"
#include "Importer.hpp"
#include <string>
#include <vector>
#include <memory>



/*************************************************************************
【类名】             OBJ_To_Model3D_Importer
【功能】             OBJ_To_Model3D_Importer类的声明，继承Importer，
                    实现导入OBJ文件存入Model3D的功能
【接口说明】         继承得到Importer全部接口
                    必备隐性行为：
                    构造函数 OBJ_To_Model3D_Importer();
                    析构函数 virtual ~OBJ_To_Model3D_Importer();
                    拷贝构造函数删除
                    赋值构造函数删除

                    Getters:
                    导入OBJ文件到Model3D对象
                        Model3D Import(const std::string& FileName) const;
                    传入Model3D对象和文件名，导入OBJ文件到Model3D对象
                        void Import
                            (const std::string& FileName, Model3D& AT) const;
                    注册.obj文件导入器
                        static void RegisterImporter();
【开发者及日期】     李想 2024/8/11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class OBJ_To_Model3D_Importer : public Importer<Model3D> {
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //构造函数
    OBJ_To_Model3D_Importer();
    //析构函数
    virtual ~OBJ_To_Model3D_Importer() = default;
    //拷贝构造函数删除
    OBJ_To_Model3D_Importer(const OBJ_To_Model3D_Importer& Other) = delete;
    //赋值构造函数删除
    OBJ_To_Model3D_Importer& operator=
    (const OBJ_To_Model3D_Importer& Other) = delete;//形参列表与返回值同级，对齐
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //导入OBJ文件到Model3D对象
    Model3D Import(const std::string& FileName) const override;
    //传入Model3D对象和文件名，导入OBJ文件到Model3D对象
    void Import(const std::string& FileName, Model3D& AT) const override;
    //注册.obj文件导入器
    static void RegisterImporter();
};
#endif // OBJ_To_Model3D_Importer_HPP