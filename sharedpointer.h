#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include <malloc.h>
#include "Exception.h"

namespace DTLib
{

template < typename T >
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;//因为多个指针要共用计数，所以这里必须要是内存而不是值
    void assign(const SharedPointer<T>& obj) {
        this->m_pointer = obj.m_pointer;
        this->m_ref = obj.m_ref;
        if (m_ref) {
            (*m_ref)++;
        }
    }

public:
    SharedPointer(T* p = NULL) : Pointer<T>(p) {
        if (p) {
            m_ref = (int*)malloc(sizeof(int));
            this->m_pointer = p;
            if (m_ref) {
                *m_ref = 1;
            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "Not enough memory...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL) {//由于行为和父类的行为不一样，所以没有必要调用父类的拷贝构造函数
        assign(obj);
    }

    SharedPointer<T>& operator = (const SharedPointer<T>& obj) {
        if (this != &obj) {//注意这里写this != obj居然也可以编译过
            clear();//自己原来的指向清空
            assign(obj);
        }
        return *this;
    }

    void clear() {
        int* tmp = m_ref;
        T* oldPoint = this->m_pointer;
        m_ref = NULL;
        this->m_pointer = NULL;

        if (tmp) {
            (*tmp)--;
            if (*tmp == 0) {
                free(m_ref);//注意这里也要释放
                delete oldPoint;
            }
        }
    }

    ~SharedPointer() {
        clear();
    }
};

template< typename T >
bool operator == (const SharedPointer<T>& sp1, const SharedPointer<T>& sp2) {
    return (sp1.get() == sp2.get());
}

template< typename T >
bool operator != (const SharedPointer<T>& sp1, const SharedPointer<T>& sp2) {
    return (sp1.get() != sp2.get());
}

}

#endif // SHAREDPOINTER_H
