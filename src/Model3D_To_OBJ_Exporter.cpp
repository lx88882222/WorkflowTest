/*************************************************************************
【文件名】                 Model3D_To_OBJ_Exporter.cpp
【功能模块和目的】         Model3D_To_OBJ_Exporter类的实现
【开发者及日期】           李想 2024/8/12
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include "Model3D_To_OBJ_Exporter.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

/*************************************************************************
【函数名称】       Model3D_To_OBJ_Exporter::Model3D_To_OBJ_Exporter
【函数功能】       构造函数,手动触发基类构造函数，指定文件扩展名为.obj
【参数】           无
【返回值】         无
【开发者及日期】   李想 2024/8/12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D_To_OBJ_Exporter::Model3D_To_OBJ_Exporter(): Exporter<Model3D>
(std::string(".obj")){
    //调用基类构造函数
}

/*************************************************************************
【函数名称】       Model3D_To_OBJ_Exporter::Export
【函数功能】       传入Model3D对象和文件名，导出Model3D对象到OBJ文件
【参数】           输入参数 const std::string& FileName 文件名
【参数】           输入参数 Model3D& AT Model3D对象
【返回值】         无
【开发者及日期】   李想 2024/8/12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model3D_To_OBJ_Exporter::Export
(const std::string& FileName, Model3D& AModel) const{
    std::ifstream file1(FileName);
    //检查文件是否打开成功
    CheckFileOpen(file1);
    //检查文件后缀名是否正确
    CheckFileExtension(FileName, "obj");
    file1.close();
    //打开文件
    std::ofstream file(FileName);
    //获取线面队列
    auto lines = AModel.Lines;
    auto faces = AModel.Faces;
    //保存模型名称
    file << "g " << AModel.Name << std::endl;
    //保存所有线上的点
    for (auto& line : lines) {
        file << "v " <<line.Points[0].X
            << " " << line.Points[0].Y
            << " " << line.Points[0].Z << std::endl;
        file << "v " <<line.Points[1].X
            << " " << line.Points[1].Y
            << " " << line.Points[1].Z << std::endl;
    }
    //保存所有面上的点
    for (auto& face : faces) {
        file << "v " <<face.Points[0].X 
            << " " << face.Points[0].Y 
            << " " << face.Points[0].Z << std::endl;
        file << "v " <<face.Points[1].X
            << " " << face.Points[1].Y
            << " " << face.Points[1].Z << std::endl;
        file << "v " <<face.Points[2].X
            << " " << face.Points[2].Y
            << " " << face.Points[2].Z << std::endl;
    }

    //保存线
    size_t Index = 1;
    for (auto line : lines) {
        file << "l " << Index << ' ' << (Index + 1) << std::endl;
        Index += 2;
    }
        
    //保存面
    for (auto face : faces) {
        file << "f " << Index << ' '
            << (Index + 1) << ' '
            << (Index + 2) << std::endl;
        Index += 3;
    }
    //关闭文件
    file.close();
}

/*************************************************************************
【函数名称】       Model3D_To_OBJ_Exporter::RegisterExporter
【函数功能】       注册.obj文件导出器
【参数】           无
【返回值】         无
【开发者及日期】   李想 2024/8/12
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void Model3D_To_OBJ_Exporter::RegisterExporter(){
    //注册导出器
    Exporter<Model3D>::RegisterExporter<Model3D_To_OBJ_Exporter>();
}

