#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "pointer.h"

namespace DTLib
{

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p) {

    }

    SmartPointer(const SmartPointer<T>& obj) {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;//注意这里要用const_cast
    }

    SmartPointer<T>& operator= (const SmartPointer<T>& obj) {
        if (this != &obj) {
            T* p = this->m_pointer;//先保存，直接删除原来对象就不可用了
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            delete p;//最后删除
        }
        return *this;
    }

    ~SmartPointer() {
        delete this->m_pointer;
    }
};

}



#endif // SMARTPOINTER_H
