/*************************************************************************
【文件名】                 FilePorter.hpp
【功能模块和目的】         FilePorter类的声明，作为文件读写接口
                        Importer和Exporter的基类，由于带有模板参数，实现在头文件中
【开发者及日期】           李想 2024/8/11
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef FILEPORTER_HPP
#define FILEPORTER_HPP
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>



/*************************************************************************
【类名】             FilePorter
【功能】             文件导入导出接口类，作为Importer和Exporter的基类
【接口说明】         构造函数 FilePorter
                    虚析构函数 virtual ~FilePorter
                    删除拷贝构造函数
                    删除赋值构造函数
                    检查文件扩展名是否匹配 CheckFileExtension
                    检查文件是否打开成功 CheckFileOpen
                    获取指定文件的扩展名 GetFileExtension
                    获取文件名 GetFileName
                    获取文件大小 GetFileSize
【开发者及日期】     李想 2024/8/11
【更改记录】         （若修改过则必需注明）
*************************************************************************/

/*************************************************************************
【类名】             enum class FilePorterType
【功能】             内嵌的枚举类，表示文件导入导出器的类型
【接口说明】         无
【开发者及日期】     李想 2024/8/11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
enum class FilePorterType {
    IMPORTER, //导入器
    EXPORTER  //导出器
};

template<FilePorterType ENUM>
class FilePorter {
public:
/*************************************************************************
【类名】             INVALID_FILE_EXTENSION
【功能】             内嵌的异常类，表示文件扩展名不匹配
【接口说明】         无
【开发者及日期】     李想 2024/8/11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
    class INVALID_FILE_EXTENSION : public std::runtime_error {
    public:
        INVALID_FILE_EXTENSION(const std::string& FileExt)
            : std::runtime_error(FileExt
                +std::string(" is invalid file extension name.")) {}
    };

/*************************************************************************
【类名】             FILE_OPEN_FAILED
【功能】             内嵌的异常类，表示文件无法打开
【接口说明】         无
【开发者及日期】     李想 2024/8/11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
    class FILE_OPEN_FAILED : public std::runtime_error {
    public:
        FILE_OPEN_FAILED(const std::string& FileName): 
        std::runtime_error(FileName+std::string(" open failed.")) {}
    };
    //------------------------------------------------------------------
    //常引用
    //------------------------------------------------------------------
    //Porter类型
    static constexpr FilePorterType Type{ENUM};
    //------------------------------------------------------------------
    //static-setters
    //------------------------------------------------------------------
    //检查文件扩展名是否匹配
    static void CheckFileExtension
    (const std::string& FileName, const std::string& FileExt){
        if (FileName.substr(FileName.find_last_of('.') + 1) != FileExt) {
            throw INVALID_FILE_EXTENSION(FileExt);
        }
    }
    //检查文件是否打开成功
    static void CheckFileOpen(const std::ifstream& File){
        if (!File.is_open()) {
            throw FILE_OPEN_FAILED("File");
        }
    }
    //获取指定文件的扩展名
    static std::string GetFileExtension(const std::string& FileName) {
        return FileName.substr(FileName.find_last_of('.') + 1);
    }
    //获取文件名
    static std::string GetFileName(const std::string& FileName){
        return FileName.substr(0, FileName.find_last_of('.'));
    }
    //获取文件大小
    static std::streampos GetFileSize(const std::string& FileName) {
        std::ifstream File(FileName, std::ios::binary | std::ios::ate);
        CheckFileOpen(File);
        return File.tellg();
    }

protected:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //默认构造函数
    FilePorter() = default;
    //析构函数
    virtual ~FilePorter() = default;
    //拷贝构造函数,由于是接口类，禁止拷贝构造
    FilePorter(const FilePorter& other) = delete;
    //赋值构造函数，由于是接口类，禁止赋值构造
    FilePorter& operator=(const FilePorter& other) = delete;
};

#endif // FILEPORTER_HPP