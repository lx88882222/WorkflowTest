/*************************************************************************
【文件名】                 View.cpp
【功能模块和目的】         界面类View类的实现
【开发者及日期】           李想 2024/8/14
【更改记录】               无
*************************************************************************/

#include"View.hpp"
#include <string>
#include <vector>
#include <memory>
#include "Controller.hpp"
#include "Face3D.hpp"
#include <cstddef>
#include <iostream>

//使用using声明使代码更简洁
using namespace std;
using RES = Controller::RES;
using ModelInfo = Controller::ModelInfo;
using PointInfo = Controller::PointInfo;
using LineInfo = Controller::LineInfo;
using FaceInfo = Controller::FaceInfo;
using FaceInfoList = Controller::FaceInfoList;
using LineInfoList = Controller::LineInfoList;
using PointInfoList = Controller::PointInfoList;


/*************************************************************************
【函数名称】       View::View
【函数功能】        默认构造函数，作为程序入口，调用显示主菜单
【参数】            无
【返回值】         无
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
View::View() {
    cout << "Welcome to 3D Constructor!" << endl;
    cout << "xiang-li22@mails.tsinghua.edu.cn" << endl;
    cout << "LiXiang 2024/8/14" << endl;
    ShowMainMenu();
}

/*************************************************************************
【函数名称】       View::ShowMainMenu
【函数功能】        显示主菜单界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowMainMenu() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2"
        && choice != "3" && choice != "4" && choice != "5") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Import model" << endl;
        cout << "2. Export model" << endl;
        cout << "3. Edit model" << endl;
        cout << "4. List info" << endl;
        cout << "5. Exit" << endl;
        cout << "Your choice (1/2/3/4/5):";
        //读取用户的选择
        getline(cin, choice);
        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << ShowImportModel() << endl;
        }
        else if (choice == "2") {
            cout << ShowExportModel() << endl;
        }
        else if (choice == "3") {
            cout << ShowEditModel() << endl;
        }
        else if (choice == "4") {
            cout << ShowListInfo() << endl;
        }
        else if (choice == "5") {
            cout << "-------------------------------------" << endl;
            cout << "Goodbye!" << endl;
            cout << "LiXiang 2024/8/14" << endl;
            cout << "-------------------------------------" << endl;
            cout << "press any key to exit..." << endl;
            cin.get();
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "LiXiang 2024/8/14";
}

/*************************************************************************
【函数名称】       View::ShowImportModel
【函数功能】        显示导入模型界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowImportModel() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Import model from file" << endl;
        cout << "2. Return to previous menu" << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "Please enter the file name:";
            string FileName;
            getline(cin, FileName);
            RES Res = controller->ImportModel(FileName);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "File: " << FileName
                    << " has been imported successfully. " << endl;
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowExportModel
【函数功能】        显示导出模型界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowExportModel() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Export model to file" << endl;
        cout << "2. Return to previous menu" << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "Please enter the file name:";
            string FileName;
            getline(cin, FileName);
            RES Res = controller->ExportModel(FileName);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Model has been exported successfully to "
                    << FileName << endl
                    << "Back to previous menu" << endl;
                break;
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowEditModel
【函数功能】        显示编辑模型界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowEditModel() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2" && choice != "3"
        && choice != "4" && choice != "5" && choice != "6") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Add face" << endl;
        cout << "2. Add line" << endl;
        cout << "3. Remove face" << endl;
        cout << "4. Remove line" << endl;
        cout << "5. Modify face" << endl;
        cout << "6. Modify line" << endl;
        cout << "7. Return to previous menu." << endl;
        cout << "Your choice (1/2/3/4/5/6/7):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << ShowAddFace() << endl;
        }
        else if (choice == "2") {
            cout << ShowAddLine() << endl;
        }
        else if (choice == "3") {
            cout << ShowRemoveFace() << endl;
        }
        else if (choice == "4") {
            cout << ShowRemoveLine() << endl;
        }
        else if (choice == "5") {
            cout << ShowModifyFacePoint() << endl;
        }
        else if (choice == "6") {
            cout << ShowModifyLinePoint() << endl;
        }
        else if (choice == "7") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowAddFace
【函数功能】        显示添加面界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowAddFace() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Add face" << endl;
        cout << "2. Return to previous menu." << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "---ADDING FACE---" << endl;
            double P0X;
            double P0Y;
            double P0Z;
            double P1X;
            double P1Y;
            double P1Z;
            double P2X;
            double P2Y;
            double P2Z;
            cout << "Point[0].X :";
            cin >> P0X;
            cout << "Point[0].Y :";
            cin >> P0Y;
            cout << "Point[0].Z :";
            cin >> P0Z;
            cout << "Point[1].X :";
            cin >> P1X;
            cout << "Point[1].Y :";
            cin >> P1Y;
            cout << "Point[1].Z :";
            cin >> P1Z;
            cout << "Point[2].X :";
            cin >> P2X;
            cout << "Point[2].Y :";
            cin >> P2Y;
            cout << "Point[2].Z :";
            cin >> P2Z;
            cin.get();
            RES Res = controller->AddFace(
                Point3D(P0X, P0Y, P0Z),
                Point3D(P1X, P1Y, P1Z),
                Point3D(P2X, P2Y, P2Z) );
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Face has been added successfully." << endl
                    << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowAddLine
【函数功能】        显示添加线界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowAddLine() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Add line" << endl;
        cout << "2. Return to previous menu" << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "---ADDING LINE---" << endl;
            double P0X;
            double P0Y;
            double P0Z;
            double P1X;
            double P1Y;
            double P1Z;
            cout << "Point[0].X :";
            cin >> P0X;
            cout << "Point[0].Y :";
            cin >> P0Y;
            cout << "Point[0].Z :";
            cin >> P0Z;
            cout << "Point[1].X :";
            cin >> P1X;
            cout << "Point[1].Y :";
            cin >> P1Y;
            cout << "Point[1].Z :";
            cin >> P1Z;
            cin.get();
            RES Res = controller->AddLine(
                Point3D(P0X, P0Y, P0Z),
                Point3D(P1X, P1Y, P1Z));
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Line has been added successfully." << endl
                    << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowRemoveFace
【函数功能】        显示移除面界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowRemoveFace() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Remove face" << endl;
        cout << "2. Return to previous menu" << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "---REMOVING FACE---" << endl;
            size_t Index;
            FaceInfoList InfoList;
            controller->ListFaces(InfoList);
            if (InfoList.size() == 0) {
                cout << "No face in model" << endl;
                return "";
            }
            cout << "Face index(0~" << InfoList.size() - 1 << "):" << endl;
            cin >> Index;
            cin.get();
            RES Res = controller->RemoveFace(Index);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Face has been removed successfully." << endl
                    << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowRemoveLine
【函数功能】        显示移除线界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowRemoveLine() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Remove line" << endl;
        cout << "2. Return to previous menu" << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "---REMOVING LINE---" << endl;
            size_t Index;
            LineInfoList InfoList;
            controller->ListLines(InfoList);
            if (InfoList.size() == 0) {
                cout << "No line in model" << endl;
                return "";
            }
            cout << "Line index(0~" << InfoList.size() - 1 << "):" << endl;
            cin >> Index;
            cin.get();
            RES Res = controller->RemoveLine(Index);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Line has been removed successfully." << endl;
                cout << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowModifyFacePoint
【函数功能】        显示修改面上的点界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowModifyFacePoint() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Modify face" << endl;
        cout << "2. Return to previous menu" << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "---MODIFYING FACE---" << endl;
            size_t Index;
            FaceInfoList InfoList;
            controller->ListFaces(InfoList);
            if (InfoList.size() == 0) {
                cout << "No face in model" << endl;
                return "";
            }
            cout << "Face index(0~" << InfoList.size() - 1 << "):";
            cin >> Index;
            cin.get();
            PointInfoList pInfoList;
            RES Res = controller->ListFacePoints(Index, pInfoList);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Face[" << Index << "]:" << endl;
                cout << "Point[0]: (" << pInfoList[0].X << ", "
                    << pInfoList[0].Y << ", " << pInfoList[0].Z << ")" << endl;
                cout << "Point[1]: (" << pInfoList[1].X << ", "
                    << pInfoList[1].Y << ", " << pInfoList[1].Z << ")" << endl;
                cout << "Point[2]: (" << pInfoList[2].X << ", "
                    << pInfoList[2].Y << ", " << pInfoList[2].Z << ")" << endl;
                size_t PointIndex;
                cout << "Point index(0~2):";
                cin >> PointIndex;
                double X;
                double Y;
                double Z;
                cout << "X:";
                cin >> X;
                cout << "Y:";
                cin >> Y;
                cout << "Z:";
                cin >> Z;
                cin.get();
                Res = controller->ModifyFace
                (Index, PointIndex, { X, Y, Z });
                if (Res != RES::SUCCESS) {
                    cout << controller->ResStr[static_cast<int>(Res)] << endl;
                    cout << "Please try again." << endl;
                }
                else {
                    cout << "Face has been modified successfully." << endl
                        << "Back to previous menu." << endl;
                    break;
                }
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowModifyLinePoint
【函数功能】        显示修改线上的点界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowModifyLinePoint() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. Modify line" << endl;
        cout << "2. Return to previous menu" << endl;
        cout << "Your choice (1/2):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "---MODIFYING LINE---" << endl;
            size_t Index;
            LineInfoList InfoList;
            controller->ListLines(InfoList);
            if (InfoList.size() == 0) {
                cout << "No line in model" << endl;
                return "";
            }
            cout << "Line index(0~" << InfoList.size() - 1 << "):";
            cin >> Index;
            cin.get();
            PointInfoList pInfoList;
            RES Res = controller->ListLinePoints(Index, pInfoList);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Line[" << Index << "]:" << endl;
                cout << "Point[0]: (" << pInfoList[0].X << ", "
                    << pInfoList[0].Y << ", " << pInfoList[0].Z << ")" << endl;
                cout << "Point[1]: (" << pInfoList[1].X << ", "
                    << pInfoList[1].Y << ", " << pInfoList[1].Z << ")" << endl;
                size_t PointIndex;
                cout << "Point index(0~1):";
                cin >> PointIndex;
                double X;
                double Y;
                double Z;
                cout << "X:";
                cin >> X;
                cout << "Y:";
                cin >> Y;
                cout << "Z:";
                cin >> Z;
                cin.get();
                Res = controller->ModifyLine
                (Index, PointIndex, { X, Y, Z });
                if (Res != RES::SUCCESS) {
                    cout << controller->ResStr[static_cast<int>(Res)] << endl;
                    cout << "Please try again." << endl;
                }
                else {
                    cout << "Line has been modified successfully." << endl;
                    cout << "Back to previous menu." << endl;
                    break;
                }
            }
        }
        else if (choice == "2") {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}

/*************************************************************************
【函数名称】       View::ShowListInfo
【函数功能】        显示列出信息界面
【参数】            无
【返回值】         string 作者信息字符串
【开发者及日期】   李想 2024/8/14
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
string View::ShowListInfo() const{
    //获取控制器实例指针
    shared_ptr<Controller> controller = Controller::GetInstance();
    //用户键入的选择
    string choice;
    //循环显示菜单，直到用户键入预期选择
    while (choice != "1" && choice != "2" && choice != "3"
        && choice != "4" && choice != "5" && choice != "6") {
        cout << "-------------------------------------" << endl;
        cout << "Please choose from the following options:" << endl;
        cout << "1. List model info" << endl;
        cout << "2. List face info by index" << endl;
        cout << "3. List line info by index" << endl;
        cout << "4. List all faces" << endl;
        cout << "5. List all lines" << endl;
        cout << "6. Return to previous menu" << endl;
        cout << "Your choice (1/2/3/4/5/6):";
        //读取用户的选择
        getline(cin, choice);

        //根据用户的选择调用不同的函数
        if (choice == "1") {
            cout << "---LISTING MODEL INFO---" << endl;
            ModelInfo Info;
            RES Res = controller->ListModelInfo(Info);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Model Info:" << endl;
                cout << "Name: " << Info.Name << endl;
                cout << "FaceNum: " << Info.FaceNum << endl;
                cout << "TotalArea: " << Info.TotalArea << endl;
                cout << "LineNum: " << Info.LineNum << endl;
                cout << "TotalLength: " << Info.TotalLength << endl;
                cout << "PointNum: " << Info.PointNum << endl;
                cout << "BoundingBoxVolume: " << Info.BoundingBoxVolume << endl;
                cout << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "2") {
            cout << "---LISTING FACE INFO BY INDEX---" << endl;
            size_t Index;
            FaceInfoList InfoList;
            controller->ListFaces(InfoList);
            if (InfoList.size() == 0) {
                cout << "No face in model" << endl;
                return "";
            }
            cout << "Face index(0~" << InfoList.size() - 1 << "):";
            cin >> Index;
            cin.get();
            PointInfoList pInfoList;
            RES Res = controller->ListFacePoints(Index, pInfoList);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Face[" << Index << "]:" << endl;
                cout << "Area: " << InfoList[Index].Area << endl;
                cout << "Point[0]: (" << pInfoList[0].X << ", "
                    << pInfoList[0].Y << ", " << pInfoList[0].Z << ")" << endl;
                cout << "Point[1]: (" << pInfoList[1].X << ", "
                    << pInfoList[1].Y << ", " << pInfoList[1].Z << ")" << endl;
                cout << "Point[2]: (" << pInfoList[2].X << ", "
                    << pInfoList[2].Y << ", " << pInfoList[2].Z << ")" << endl;
                cout << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "3") {
            cout << "---LISTING LINE INFO BY INDEX---" << endl;
            size_t Index;
            LineInfoList InfoList;
            controller->ListLines(InfoList);
            if (InfoList.size() == 0) {
                cout << "No line in model" << endl;
                return "";
            }
            cout << "Line index(0~" << InfoList.size() - 1 << "):";
            cin >> Index;
            cin.get();
            PointInfoList pInfoList;
            RES Res = controller->ListLinePoints(Index, pInfoList);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Line[" << Index << "]:" << endl;
                cout << "Length: " << InfoList[Index].Length << endl;
                cout << "Point[0]: (" << pInfoList[0].X << ", "
                    << pInfoList[0].Y << ", " << pInfoList[0].Z << ")" << endl;
                cout << "Point[1]: (" << pInfoList[1].X << ", "
                    << pInfoList[1].Y << ", " << pInfoList[1].Z << ")" << endl;
                cout << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "4") {
            cout << "---LISTING ALL FACES---" << endl;
            FaceInfoList InfoList;
            RES Res = controller->ListFaces(InfoList);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Face Info:" << endl;
                for (size_t i = 0; i < InfoList.size(); i++) {
                    cout << "Face[" << i << "]:" << endl;
                    cout << "Area: " << InfoList[i].Area << endl;
                    cout << "Point[0]: (" << InfoList[i].PointsInfo[0].X << ", "
                        << InfoList[i].PointsInfo[0].Y
                        << ", " << InfoList[i].PointsInfo[0].Z << ")" << endl;
                    cout << "Point[1]: (" << InfoList[i].PointsInfo[1].X << ", "
                        << InfoList[i].PointsInfo[1].Y << ", "
                        << InfoList[i].PointsInfo[1].Z << ")" << endl;
                    cout << "Point[2]: (" << InfoList[i].PointsInfo[2].X << ", "
                        << InfoList[i].PointsInfo[2].Y << ", "
                        << InfoList[i].PointsInfo[2].Z << ")" << endl;
                    cout << "-------------------------------------" << endl;
                }
                cout << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "5") {
            cout << "---LISTING ALL LINES---" << endl;
            LineInfoList InfoList;
            RES Res = controller->ListLines(InfoList);
            if (Res != RES::SUCCESS) {
                cout << controller->ResStr[static_cast<int>(Res)] << endl;
                cout << "Please try again." << endl;
            }
            else {
                cout << "Line Info:" << endl;
                for (size_t i = 0; i < InfoList.size(); i++) {
                    cout << "Line[" << i << "]:" << endl;
                    cout << "Length: " << InfoList[i].Length << endl;
                    cout << "Point[0]: (" << InfoList[i].PointsInfo[0].X << ", "
                        << InfoList[i].PointsInfo[0].Y << ", "
                        << InfoList[i].PointsInfo[0].Z << ")" << endl;
                    cout << "Point[1]: (" << InfoList[i].PointsInfo[1].X << ", "
                        << InfoList[i].PointsInfo[1].Y << ", "
                        << InfoList[i].PointsInfo[1].Z << ")" << endl;
                    cout << "-------------------------------------" << endl;
                }
                cout << "Back to previous menu." << endl;
                break;
            }
        }
        else if (choice == "6") {
            break;

        }
        else {
            cout << "Invalid choice!" << endl;
        }
        choice.clear();
    }
    return "";
}
