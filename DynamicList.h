#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "seqlist.h"

namespace DTLib
{

template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity) {
        this->m_array = new T[capacity];
        if (this->m_array != NULL) {
            this->m_capacity = capacity;
            this->m_length = 0;
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "no enough memery...");
        }
    }

    int capacity() const {
        return m_capacity;
    }

    void resize(int capacity) {
        if (capacity != this->m_capacity) {//只有不等于才进行resize
            int length = capacity > this->m_length ? this->m_length : capacity;
            T* newArray = new T[capacity];
            if (newArray != NULL) {
                for (int i = 0; i < length; i++) {
                    newArray[i] = this->m_array[i];//这里发生异常，相关属性还没被改，对象还是可以修复的
                }
                T* oldArray = this->m_array;//事先保存，准备最后释放

                this->m_array = newArray;
                this->m_length = length;
                this->m_capacity = capacity;

                delete[] oldArray;//最后再删除原先的内存，因为有可能有异常
            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memery...");
            }
        }
    }

    ~DynamicList() {
        delete[] this->m_array;
    }
};

}



#endif // DYNAMICLIST_H
