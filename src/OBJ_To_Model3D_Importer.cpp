/*************************************************************************
【文件名】                 OBJ_To_Model3D_Importer.cpp
【功能模块和目的】         OBJ_To_Model3D_Importer类的实现
【开发者及日期】           李想 2024/8/11
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#include "OBJ_To_Model3D_Importer.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <memory>


/*************************************************************************
【函数名称】       OBJ_To_Model3D_Importer::OBJ_To_Model3D_Importer
【函数功能】       构造函数,手动触发基类构造函数，指定文件扩展名为.obj
【参数】           无
【返回值】         无
【开发者及日期】   李想 2024/8/11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
OBJ_To_Model3D_Importer::OBJ_To_Model3D_Importer() : Importer<Model3D>
(std::string(".obj")){
    //调用基类构造函数
}

/*************************************************************************
【函数名称】       OBJ_To_Model3D_Importer::Import
【函数功能】       导入OBJ文件到Model3D对象
【参数】           输入参数 const std::string& FileName 文件名
【返回值】         Model3D Model3D对象
【开发者及日期】   李想 2024/8/11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
Model3D OBJ_To_Model3D_Importer::Import(const std::string& FileName) const{
    //创建Model3D对象
    Model3D model;
    //打开文件
    std::ifstream File(FileName);
    //检查文件后缀名是否正确
    CheckFileExtension(FileName, "obj");
    //检查文件是否打开成功
    CheckFileOpen(File);
    //初始化点线面队列，此后的点线面都将存入这三个队列
    std::vector<Point3D> Points;
    std::vector<Line3D> Lines;
    std::vector<Face3D> Faces;
    //读取文件
    std::string line;
    while (std::getline(File, line)) {
        //将一行字符串存入字符串流
        std::istringstream iss(line);
        //读取第一个字符串
        std::string type;
        iss >> type;
        //根据第一个字符串的内容进行处理
        if (type == "v") {
            //读取点坐标
            double x, y, z;
            iss >> x >> y >> z;
            //将点存入点队列
            Points.push_back(Point3D(x, y, z));
        } else if (type == "l") {
            //读取线的两个点的索引
            size_t p1, p2;
            iss >> p1 >> p2;
            //将线存入线队列
            Lines.push_back(Line3D({Points[p1-1], Points[p2-1]}));
        } else if (type == "f") {
            //读取面的三个点的索引
            size_t p1, p2, p3;
            iss >> p1 >> p2 >> p3;
            //将面存入面队列
            Faces.push_back
            (Face3D({Points[p1-1], Points[p2-1], Points[p3-1]}));
        } else if (type == "g") {
            //读取模型名称
            std::string name;
            iss >> name;
            //存入模型名称
            model.Name = name;
        } else {
            //忽略其他内容
        }
    }
    //将线面存入Model3D对象
    for (const auto& Line : Lines) {
        model.AddLine(Line);
    }
    for (const auto& Face : Faces) {
        model.AddFace(Face);
    }
    File.close();
    return model;
}

/*************************************************************************
【函数名称】       OBJ_To_Model3D_Importer::Import
【函数功能】       传入Model3D对象和文件名，导入OBJ文件到Model3D对象
【参数】           输入参数 const std::string& FileName 文件名
【参数】           输入输出参数 Model3D& AT Model3D对象
【返回值】         无
【开发者及日期】   李想 2024/8/11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void OBJ_To_Model3D_Importer::Import
(const std::string& FileName, Model3D& AT) const{
    AT = Import(FileName);
}

/*************************************************************************
【函数名称】       OBJ_To_Model3D_Importer::RegisterImporter
【函数功能】       注册.obj文件导入器
【参数】           无
【返回值】         无
【开发者及日期】   李想 2024/8/11
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
void OBJ_To_Model3D_Importer::RegisterImporter(){
    Importer<Model3D>::RegisterImporter<OBJ_To_Model3D_Importer>();
}