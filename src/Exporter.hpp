/*************************************************************************
【文件名】                 Exporter.hpp
【功能模块和目的】         Exporter类的声明，作为文件导入接口,继承FilePorter
【开发者及日期】           李想 2024/8/12
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef EXPORTER_HPP
#define EXPORTER_HPP
#include "FilePorter.hpp"
#include <vector>
#include <string>
#include <memory>
#include <type_traits>

/*************************************************************************
【类名】             Exporter
【功能】             文件导出接口类，继承FilePorter,作为具体文件类型导出器的基类
【接口说明】         继承得到FilePorter全部接口
                    必备隐性行为：
                    构造函数 Exporter(const std::string& FileExt);
                    析构函数 virtual ~Exporter();
                    拷贝构造函数 Exporter(const Exporter& other);
                    赋值构造函数 Exporter& operator=(const Exporter& other);
                    
                    Getters:
                    常引用，文件扩展名
                        const std::string& ExtName{m_FileExtension};
                    纯虚函数，传入T和文件名，根据文件名导出T类型对象
                        virtual void Export
                            (const std::string& FileName, T& AT) const = 0;
                    
                    静态函数：根据文件名获取具体导出器实例指针
                        static std::shared_ptr<Exporter<T>> 
                            GetExporterByFileName(const std::string& FileName);
                    静态函数：根据文件扩展名获取具体导出器实例指针
                        static std::shared_ptr<Exporter<T>> 
                            GetExporterByExtension(const std::string& FileExt);
                    静态函数：根据可能的派生类类型注册具体导出器
                        static void RegisterExporter();
                    
【开发者及日期】     李想 2024/8/12
【更改记录】         （若修改过则必需注明）
*************************************************************************/
template<class T>
class Exporter : public FilePorter<FilePorterType::EXPORTER> {
private:
    //------------------------------------------------------------------
    //私有数据成员
    //------------------------------------------------------------------
    //文件扩展名
    std::string m_FileExtension;
    //所有以Exporter<T>为基类的实例指针列表
    static std::vector<std::shared_ptr<Exporter<T>>> m_pExporters;
protected:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //构造函数
    Exporter(const std::string& FileExt);
    //析构函数
    virtual ~Exporter() = default;
    //拷贝构造函数,删除
    Exporter(const Exporter& Other) = delete;
    //赋值构造函数,删除
    Exporter& operator=(const Exporter& Other) = delete;
public:
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //纯虚函数，传入T和文件名，根据文件名导出T类型对象
    virtual void Export (const std::string& FileName, T& AT) const = 0;
    //常引用，文件扩展名
    const std::string& FileExtName{m_FileExtension};
    //------------------------------------------------------------------
    //静态函数：
    //------------------------------------------------------------------
    //根据文件名获取具体导出器实例指针
    static std::shared_ptr<Exporter<T>> 
        GetExporterByFileName(const std::string& FileName);
    //根据文件扩展名获取具体导出器实例指针
    static std::shared_ptr<Exporter<T>> 
        GetExporterByExtension(const std::string& FileExt);
    //根据可能的派生类类型注册具体导出器
    template<class DERIVED>
    static void RegisterExporter();
};

//Exporter类的实现


//以Exporter<T>为基类的实例指针列表
template<class T>
std::vector<std::shared_ptr<Exporter<T>>> Exporter<T>::m_pExporters{};

/*************************************************************************
【函数名称】         Exporter::Exporter
【函数功能】         构造函数
【参数】             const std::string& FileExt，文件扩展名
【返回值】           无
【开发者及日期】     李想 2024/8/12
【更改记录】         无
*************************************************************************/
template<class T>
Exporter<T>::Exporter(const std::string& FileExt) 
: FilePorter<FilePorterType::EXPORTER>(),m_FileExtension(FileExt){
    //如果文件后缀名为空，抛出异常
    if (FileExt.empty()) {
        throw FilePorter<FilePorterType::EXPORTER>::
            INVALID_FILE_EXTENSION("'EMPTY'");
    }
}

/*************************************************************************
【函数名称】         Exporter::GetExporterByFileName
【函数功能】         根据文件名获取具体导出器实例指针
【参数】             const std::string& FileName，文件名
【返回值】           std::shared_ptr<Exporter<T>>，导出器实例指针
【开发者及日期】     李想 2024/8/12
【更改记录】         无
*************************************************************************/
template<class T>
std::shared_ptr<Exporter<T>> Exporter<T>::GetExporterByFileName
    (const std::string& FileName){
    std::string FileExt = GetFileExtension(FileName);
    return GetExporterByExtension(FileExt);
}

/*************************************************************************
【函数名称】         Exporter::GetExporterByExtension
【函数功能】         根据文件扩展名获取具体导出器实例指针
【参数】             const std::string& FileExt，文件扩展名
【返回值】           std::shared_ptr<Exporter<T>>，导出器实例指针
【开发者及日期】     李想 2024/8/12
【更改记录】         无
*************************************************************************/
template<class T>
std::shared_ptr<Exporter<T>> Exporter<T>::GetExporterByExtension
    (const std::string& FileExt){
    for (auto& pExporter : m_pExporters) {
        if (pExporter->m_FileExtension == FileExt) {
            return pExporter;
        }
    }
    return nullptr;
}

/*************************************************************************
【函数名称】         Exporter::RegisterExporter
【函数功能】         根据可能的派生类类型注册具体导出器
【参数】             无
【返回值】           无
【开发者及日期】     李想 2024/8/12
【更改记录】         无
*************************************************************************/
template<class T>
template<class DERIVED>
void Exporter<T>::RegisterExporter(){
    //断言，检查是否继承自Exporter<T>
    static_assert(
        std::is_base_of<Exporter<T>, DERIVED>::value, 
        "DERIVED must inherit Exporter<T>");
        //创建具体导入器实例指针
    std::shared_ptr<Exporter<T>> pDerivedExporter(new DERIVED());
    for (auto pExporter : m_pExporters) {//检查是否重复注册
        if (pExporter->FileExtName == pDerivedExporter->FileExtName) {
            throw FilePorter<FilePorterType::EXPORTER>::
            INVALID_FILE_EXTENSION(pDerivedExporter->FileExtName);
        }
    }
    //将具体导入器实例指针存入列表
    m_pExporters.push_back(pDerivedExporter);
}

#endif //EXPORTER_HPP
