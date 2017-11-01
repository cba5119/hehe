#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class Array : public Object//数组和list的区别是数组没有增删操作，可以发现内存越界，用于替代原生数组
{
protected:
    T* m_array;
public:
    virtual bool set(int i, const T& e) {
        bool ret = (i >= 0) && (i < length());
        if (ret) {
            m_array[i] = e;
        }
        return ret;
    }

    virtual bool get(int i, T& e) const {
        bool ret = (i >= 0) && (i < length());
        if (ret) {
            e = m_array[i];
        }
        return ret;
    }
    virtual int length() const = 0;

    T& operator[] (int i) {
        if (i >= 0 && i < length()) {
            return m_array[i];
        }
        else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Index out of range...");
        }
    }

    T operator[] (int i) const {
        return (const_cast<Array<T>&>(*this))[i];
    }
};

}

#endif // ARRAY_H
