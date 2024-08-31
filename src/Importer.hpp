/*************************************************************************
【文件名】                 Importer.hpp
【功能模块和目的】         Importer类的声明，作为文件导入接口,继承FilePorter
【开发者及日期】           李想 2024/8/11
【更改记录】               （若修改过则必需注明）
*************************************************************************/

#ifndef IMPORTER_HPP
#define IMPORTER_HPP
#include "FilePorter.hpp"
#include <vector>
#include <string>
#include <memory>
#include <type_traits>


/*************************************************************************
【类名】             Importer
【功能】             文件导入接口类，继承FilePorter,作为具体文件类型导入器的基类
【接口说明】         继承得到FilePorter全部接口
                    必备隐性行为：
                    构造函数 Importer(const std::string& FileExt);
                    析构函数 virtual ~Importer();
                    拷贝构造函数 Importer(const Importer& other);
                    赋值构造函数 Importer& operator=(const Importer& other);
                    
                    Getters:
                    纯虚函数，根据文件名导入到T类型对象
                        virtual T Import(const std::string& FileName) const = 0;
                    纯虚函数，传入T和文件名，根据文件名导入到T类型对象
                        virtual void Import
                            (const std::string& FileName, T& AT) const = 0;
                    
                    静态函数：根据文件名获取具体导入器实例指针
                        static std::shared_ptr<Importer<T>> 
                            GetImporterByFileName(const std::string& FileName);
                    静态函数：根据文件扩展名获取具体导入器实例指针
                        static std::shared_ptr<Importer<T>> 
                            GetImporterByExtension(const std::string& FileExt);
                    静态函数：根据可能的派生类类型注册具体导入器
                        static void RegisterImporter();
                    
【开发者及日期】     李想 2024/8/11
【更改记录】         （若修改过则必需注明）
*************************************************************************/
template<class T>
class Importer : public FilePorter<FilePorterType::IMPORTER> {
private:
    //------------------------------------------------------------------
    //私有数据成员
    //------------------------------------------------------------------
    //文件扩展名
    std::string m_FileExtension;
    //所有以Importer<T>为基类的实例指针列表
    static std::vector<std::shared_ptr<Importer<T>>> m_pImporters;
protected:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //构造函数
    Importer(const std::string& FileExt);
    //析构函数
    virtual ~Importer() = default;
    //拷贝构造函数,由于是接口类，不允许拷贝
    Importer(const Importer& other) = delete;
    //赋值构造函数,由于是接口类，不允许赋值
    Importer& operator=(const Importer& other) = delete;
public:
    //------------------------------------------------------------------
    //Getters
    //------------------------------------------------------------------
    //纯虚函数，根据文件名导入到T类型对象
    virtual T Import(const std::string& FileName) const= 0;
    //纯虚函数，传入T和文件名，根据文件名导入到T类型对象
    virtual void Import(const std::string& FileName, T& AT) const= 0;
    //静态函数：根据文件名获取具体导入器实例指针
    static std::shared_ptr<Importer<T>> 
        GetImporterByFileName(const std::string& FileName);
    //静态函数：根据文件扩展名获取具体导入器实例指针
    static std::shared_ptr<Importer<T>> 
        GetImporterByExtension(const std::string& FileExt);
    //静态函数，根据可能的派生类类型注册具体导入器
    template<class DERIVED>
    static void RegisterImporter();
    //常引用，文件扩展名
    const std::string& FileExtName{m_FileExtension};
};
//Importer类的实现

/*************************************************************************
【函数名称】         Importer::Importer
【函数功能】         构造函数
【参数】             const std::string& FileExt，文件扩展名
【返回值】           无
【开发者及日期】     李想 2024/8/11
【更改记录】         无
*************************************************************************/
template<class T>
Importer<T>::Importer(const std::string& FileExt) : 
FilePorter<FilePorterType::IMPORTER>(),m_FileExtension(FileExt){
    //如果文件后缀名为空，抛出异常
    if (FileExt.empty()) {
        throw FilePorter<FilePorterType::IMPORTER>::
            INVALID_FILE_EXTENSION("'EMPTY'");
    }
}



//以Importer<T>为基类的实例指针列表
template<class T>
std::vector<std::shared_ptr<Importer<T>>> Importer<T>::m_pImporters{};

/*************************************************************************
【函数名称】         Importer::GetImporterByFileName
【函数功能】         根据文件名获取具体导入器实例指针
【参数】             const std::string& FileName，文件名
【返回值】           std::shared_ptr<Importer<T>>，导入器实例指针
【开发者及日期】     李想 2024/8/11
【更改记录】         无
*************************************************************************/
template<class T>
std::shared_ptr<Importer<T>>
Importer<T>::GetImporterByFileName(const std::string& FileName){
    //获取文件扩展名
    std::string FileExt = FileName.substr(FileName.find_last_of('.') + 1);
    //返回根据文件扩展名获取的导入器实例指针
    return GetImporterByExtension(FileExt);
}

/*************************************************************************
【函数名称】         Importer::GetImporterByExtension
【函数功能】         根据文件扩展名获取具体导入器实例指针
【参数】             const std::string& FileExt，文件扩展名
【返回值】           std::shared_ptr<Importer<T>>，导入器实例指针
【开发者及日期】     李想 2024/8/11
【更改记录】         无
*************************************************************************/
template<class T>
std::shared_ptr<Importer<T>>
Importer<T>::GetImporterByExtension(const std::string& FileExt){
    //遍历所有导入器实例指针，如果文件扩展名匹配，返回该导入器实例指针
    for (auto& p : m_pImporters) {
        if (p->m_FileExtension == FileExt) {
            return p;
        }
    }
    //未找到，则抛出异常
    throw FilePorter<FilePorterType::IMPORTER>::
        INVALID_FILE_EXTENSION(FileExt);
    //返回空指针
    return nullptr;
}

/*************************************************************************
【函数名称】         Importer::RegisterImporter
【函数功能】         根据文件后缀名注册具体导入器
【参数】             无
【返回值】           无
【开发者及日期】     李想 2024/8/11
【更改记录】         无
*************************************************************************/
template<class T>
template<class DERIVED>
void Importer<T>::RegisterImporter(){
    //断言，检查是否继承自Importer<T>
    static_assert(
        std::is_base_of<Importer<T>, DERIVED>::value, 
            "DERIVED must inherit Importer<T>");
        //创建具体导入器实例指针
    std::shared_ptr<Importer<T>> pDerivedImporter(new DERIVED());
    for (auto pImporter : m_pImporters) {//检查是否重复注册
        if (pImporter->FileExtName == pDerivedImporter->FileExtName) {
            throw FilePorter<FilePorterType::IMPORTER>::
            INVALID_FILE_EXTENSION(pDerivedImporter->FileExtName);
        }
    }
    //将具体导入器实例指针存入列表
    m_pImporters.push_back(pDerivedImporter);
}

#endif //IMPORTER_HPP