/*************************************************************************
【文件名】                 View.hpp
【功能模块和目的】         界面类View类的声明
【开发者及日期】           李想 2024/8/14
【更改记录】               无
*************************************************************************/

#ifndef VIEW_HPP
#define VIEW_HPP
#include <string>
#include <vector>
#include <memory>
#include "Controller.hpp"
#include <cstddef>

/*************************************************************************
【类名】             View
【功能】             界面类，程序入口，实现用户交互，调用controller控制器
【接口说明】         默认构造函数 
                    虚析构函数 
                    拷贝构造函数删除
                    赋值构造函数删除
                    为了派生时快速修改，以下函数均为虚函数：
                    虚函数：显示主菜单界面
                    虚函数：显示导入模型界面
                    虚函数：显示导出模型界面
                    虚函数：显示编辑模型界面
                    虚函数：显示添加面界面
                    虚函数：显示添加线界面
                    虚函数：显示移除面界面
                    虚函数：显示移除线界面
                    虚函数：显示修改面上的点界面
                    虚函数：显示修改线上的点界面
                    虚函数：显示列出信息界面
【开发者及日期】     李想 2024/8/14
【更改记录】         （若修改过则必需注明）
*************************************************************************/
class View{
public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //默认构造函数
    View();
    //虚析构函数
    virtual ~View() = default;
    //拷贝构造函数删除
    View(const View& other) = delete;
    //赋值构造函数删除
    View& operator=(const View& other) = delete;
protected:
    //------------------------------------------------------------------
    //为了派生时快速修改，以下函数均为虚函数：
    //------------------------------------------------------------------
    //显示主菜单界面
    virtual std::string ShowMainMenu() const;
    //显示导入模型界面
    virtual std::string ShowImportModel() const;
    //显示导出模型界面
    virtual std::string ShowExportModel() const;
    //显示编辑模型界面
    virtual std::string ShowEditModel() const;
    //显示添加面界面
    virtual std::string ShowAddFace() const;
    //显示添加线界面
    virtual std::string ShowAddLine() const;
    //显示移除面界面
    virtual std::string ShowRemoveFace() const;
    //显示移除线界面
    virtual std::string ShowRemoveLine() const;
    //显示修改面上的点界面
    virtual std::string ShowModifyFacePoint() const;
    //显示修改线上的点界面
    virtual std::string ShowModifyLinePoint() const;
    //显示列出信息界面
    virtual std::string ShowListInfo() const;
};
#endif // VIEW_HPP