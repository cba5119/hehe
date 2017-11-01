#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"

namespace DTLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;
    T* copy(T* array, int len, int newLen) {//创建新内存用以赋值array的内容
        T* ret = new T[newLen];
        if (ret != NULL) {
            int size = (len < newLen) ? len : newLen;
            for (int i = 0; i < size; i++) {
                ret[i] = array[i];
            }
        }
        return ret;
    }

    void update(T* array, int length) {//删除原先的内存，用新的内存替换
        if (array != NULL) {
            T* temp = this->m_array;
            this->m_array = array;
            this->m_length = length;
            delete[] temp;
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "cannot create Obj...");
        }
    }

    void init(T* array, int length) {//指定内存和长度，用以初始化
        if (array != NULL) {
            this->m_array = array;
            this->m_length = length;
        }
        else {
           THROW_EXCEPTION(NoEnoughMemoryException, "cannot create Obj...");
        }
    }

public:
    DynamicArray(int length) {
        init(new T[length], length);
    }

    DynamicArray(const DynamicArray<T>& obj) {
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    DynamicArray<T>& operator =(const DynamicArray<T>& obj) {
        if (this != &obj) {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }
        return *this;
    }

    int length() const {
        return this->m_length;
    }

    void resize(int length) {
        if (this->m_length != length) {
            update(copy(this->m_array, this->m_length, length), length);
        }
    }

    ~DynamicArray() {
        delete[] this->m_array;
    }
};

}


#endif // DYNAMICARRAY_H
