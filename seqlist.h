#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;
    int m_length;
public:
    bool insert(int i, const T& e) {
        bool ret = (i >= 0) && (i <= m_length) && (m_length < capacity());
        if (ret) {
            for (int n = m_length - 1; n >= i; n--) {
                m_array[n+1] = m_array[n];
            }
            m_array[i] = e;
            m_length++;
        }
        return ret;
    }

    bool remove(int i) {
        bool ret = i >= 0 && i < m_length;
        if (ret) {
            for (int n = i; n < m_length - 1; n++) {
                m_array[n] = m_array[n+1];
            }
            m_length--;
        }
        return ret;
    }

    bool set(int i, const T& e) {
        bool ret = (i >= 0) && (i < m_length);
        if (ret) {
            m_array[i] = e;
        }
        return ret;
    }

    bool get(int i, T& e) const {
        bool ret = (i >= 0) && (i < m_length);
        if (ret) {
            e = m_array[i];
        }
        return ret;
    }

     int find(const T& e) const {
         int ret = -1;
         for (int i = 0; i < m_length; i++) {
             if (m_array[i] == e) {
                 ret = i;
                 break;
             }
         }
         return ret;
     }

    int length() const {
        return m_length;
    }

    void clear() {
        m_length = 0;
    }

    T& operator[] (int i) {
        if (i >= 0 && i < m_length) {
            return m_array[i];
        }
        else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "index is out of range...");
        }
    }

    T operator[] (int i) const {
        return (const_cast<SeqList<T>&>(*this))[i];
    }

    virtual int capacity() const = 0;
};

}

#endif // SEQLIST_H
