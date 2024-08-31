/*************************************************************************
【文件名】                 CountFixedSet.hpp
【功能模块和目的】         CountFixedSet类声明与定义，
                            实现一个固定元素数量的集合类，
                            只能在初始化时添加元素，不能删除元素，可以修改元素值，
                            由于使用了模板类，所以将声明和定义放在同一个文件中
【开发者及日期】           李想 2024/8/2
【更改记录】               李想 2024/8/2 添加了CountFixedSetException类声明，
                                        用于处理CountFixedSet类的异常
*************************************************************************/

#ifndef COUNTFIXEDSET_HPP
#define COUNTFIXEDSET_HPP
#include <array>//array
#include <cstddef>//size_t
#include <iostream>//ostream
#include <initializer_list>//initializer_list
#include <string>//string
#include <exception>//exception




/*************************************************************************
【类名】             CountFixedSet
【功能】             CountFixedSet类声明，实现一个固定元素数量的集合类，
                        只能在初始化时添加元素，不能删除元素，可以修改元素值
                        元素不可重复
【接口说明】         必备隐性行为：
                    默认构造函数 CountFixedSet();
                    构造函数 CountFixedSet(std::initializer_list<T> init);
                    析构函数 ~CountFixedSet();
                    拷贝构造函数 CountFixedSet(const CountFixedSet&);
                    赋值构造函数 CountFixedSet& operator=(const CountFixedSet&);
                    
                    Setters:
                    禁止添加元素 void insert(const T&);
                    禁止删除元素 void erase(const T&);
                    允许修改元素值，但必须是集合中存在的元素
                        void modify(const T& OldValue, const T& NewValue);
                    
                    Getters:
                    元素数量的常引用 const size_t& size {m_ullCount};
                    重载[]运算符，返回集合中的元素 
                        const T& operator[](size_t Index) const;
                    重载流输出运算符
                        friend std::ostream& operator<<
                            (std::ostream& os, const CountFixedSet& set);
【开发者及日期】     李想 2024/8/2
【更改记录】         （若修改过则必需注明）
*************************************************************************/


template <typename T, size_t N>
class CountFixedSet {
public:
/*************************************************************************
【类名】             CountFixedSetException
【功能】             CountFixedSetException类声明，继承自std::exception，
                        内嵌于CountFixedSet类，用于处理CountFixedSet类的异常
【接口说明】         必备隐性行为：
                    构造函数 
                        explicit CountFixedSetException(const std::string& msg);
                    what函数 const char* what() const noexcept override;
【开发者及日期】     李想 2024/8/2
【更改记录】         （若修改过则必需注明）
*************************************************************************/
    class CountFixedSetException : public std::exception {
    private:
        std::string message;
    public:
        explicit CountFixedSetException(const std::string& msg);
        virtual const char* what() const noexcept override;
    };
private:
    std::array<T, N> m_Elements; // 存储元素的数组
    size_t m_ullCount; // 实际存储的元素数量

public:
    //------------------------------------------------------------------
    //必备隐性行为：
    //------------------------------------------------------------------
    //默认构造函数
    CountFixedSet() : m_ullCount(0) {}
    //带参构造函数，接受初始化列表,有重复元素或者元素数量超过N时抛出异常
    CountFixedSet(std::initializer_list<T> init);
    //析构函数
    virtual ~CountFixedSet() = default;
    //拷贝构造函数
    CountFixedSet(const CountFixedSet&);
    //赋值构造函数
    CountFixedSet& operator=(const CountFixedSet&) ;
    //------------------------------------------------------------------
    //Setters:
    //------------------------------------------------------------------
    // 禁止添加元素
    void insert(const T&);
    // 禁止删除元素
    void erase(const T&);
    // 允许修改元素值，但必须是集合中存在的元素
    void modify(const T& OldValue, const T& NewValue);
    //------------------------------------------------------------------
    //Getters:
    //------------------------------------------------------------------
    //元素数量的常引用
    const size_t& size {m_ullCount};
    //重载[]运算符，返回集合中的元素
    const T& operator[](size_t Index) const;
    //------------------------------------------------------------------
    //友元函数
    //------------------------------------------------------------------
    // 重载流输出运算符，由于是友元函数，所以在类内实现
    friend std::ostream& operator<<(
        std::ostream& Stream, 
        const CountFixedSet& ACFS) {
        for (size_t i = 0; i < ACFS.m_ullCount; ++i) {
            Stream << ACFS.m_Elements[i] << " ";
        }
        return Stream;
    }
};

// CountFixedSetException实现
/*************************************************************************
【函数名称】       CountFixedSetException
【函数功能】        CountFixedSetException类构造函数
【参数】            const std::string& Message
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
CountFixedSet<T, N>::CountFixedSetException::
CountFixedSetException(const std::string& Message) : message(Message) {}

/*************************************************************************
【函数名称】       what
【函数功能】        CountFixedSetException类what函数，返回异常信息
【参数】            无
【返回值】         const char*
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
const char* CountFixedSet<T, N>::CountFixedSetException::what() const noexcept {
    return message.c_str();
}

// CountFixedSet实现
/*************************************************************************
【函数名称】       CountFixedSet
【函数功能】        CountFixedSet类构造函数，
                    接受初始化列表,有重复元素或者元素数量超过N时抛出异常
【参数】            std::initializer_list<T> init
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N> 
CountFixedSet<T, N>::CountFixedSet
(std::initializer_list<T> init) : m_ullCount(0){
    if (init.size() > N) {
        throw CountFixedSetException("Too many elements in init list.");
    }
    for (const T& item : init) {
        if (m_ullCount == N) {
            throw CountFixedSetException("Too many elements in init list.");
        }
        for (size_t i = 0; i < m_ullCount; ++i) {
            if (m_Elements[i] == item) {
                throw CountFixedSetException 
                    ("Duplicate elements are not allowed.");
            }
        }
        m_Elements[m_ullCount++] = item;
    }
}

/*************************************************************************
【函数名称】       CountFixedSet
【函数功能】        CountFixedSet类拷贝构造函数
【参数】           const CountFixedSet&
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
CountFixedSet<T, N>::CountFixedSet(const CountFixedSet& Other) : 
    m_Elements(Other.m_Elements), m_ullCount(Other.m_ullCount) {}


/*************************************************************************
【函数名称】       operator=
【函数功能】       CountFixedSet类赋值构造函数
【参数】           const CountFixedSet&
【返回值】         CountFixedSet&
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
CountFixedSet<T, N>& CountFixedSet<T, N>::
operator=(const CountFixedSet& Other){
    if (this != &Other) {
        m_Elements = Other.m_Elements;
        m_ullCount = Other.m_ullCount;
    }
    return *this;
}

/*************************************************************************
【函数名称】       insert
【函数功能】       CountFixedSet类禁止添加元素
【参数】           const T&
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
void CountFixedSet<T, N>::insert(const T&){
    throw CountFixedSetException("Cannot add elements to CountFixedSet.");
}

/*************************************************************************
【函数名称】       erase
【函数功能】       CountFixedSet类禁止删除元素
【参数】           const T&
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
void CountFixedSet<T, N>::erase(const T&){
    throw CountFixedSetException("Cannot remove elements from CountFixedSet.");
}

/*************************************************************************
【函数名称】       modify
【函数功能】       CountFixedSet类允许修改元素值，但必须是集合中存在的元素
【参数】           const T& OldValue, const T& NewValue
【返回值】         无
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
void CountFixedSet<T, N>::modify(const T& OldValue, const T& NewValue){
    for (size_t i = 0; i < m_ullCount; ++i) {
        if (m_Elements[i] == OldValue) {
            for (size_t j = 0; j < m_ullCount; ++j) {
                if (j != i && m_Elements[j] == NewValue) {
                    throw CountFixedSetException//新值不能是重复值
                        ("New value must not be a duplicate.");
                }
            }
            m_Elements[i] = NewValue;
            return;
        }
    }
    throw CountFixedSetException("Element to modify not found.");
}

/*************************************************************************
【函数名称】       operator[]
【函数功能】       CountFixedSet类重载[]运算符，返回集合中的元素
【参数】           size_t Index
【返回值】         const T&
【开发者及日期】   李想 2024/8/3
【更改记录】       （若有修改，则必需注明）
*************************************************************************/
template <typename T, size_t N>
const T& CountFixedSet<T, N>::operator[](size_t Index) const{
    if (Index >= m_ullCount || Index < 0) {
        throw CountFixedSetException("Index out of range.");
    }
    return m_Elements[Index];
}


#endif // COUNTFIXEDSET_HPP