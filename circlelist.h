#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "linklist.h"

namespace DTLib
{

template< typename T >
class CircleList : public LinkList<T>
{
    typedef typename LinkList<T>::Node Node;
protected:
    void lastToFirst() {
        Node* last = LinkList<T>::position(this->m_length - 1);
        last->next->next = this->m_header.next;
    }
    int mod(int i) const {
        return this->m_length == 0 ? 0 : (i%this->m_length);
    }

public:
    bool insert(const T& e) {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e) {
        bool ret = false;
        i = i % (this->m_length + 1);

        ret = LinkList<T>::insert(i, e);
        if (ret && i == 0) {//如果插入位置是0，就首尾相连
            lastToFirst();
        }

        return ret;
    }

    bool remove(int i) {
        bool ret = false;
        i = mod(i);
        if (i == 0) {//这里不可以先调remove，再调用lastToFirst，因为无法保证异常安全
            Node* toDel = this->m_header.next;
            if (toDel != NULL) {
                this->m_header.next = toDel->next;//注意这里当只有一个元素时自己指自己
                this->m_length--;

                if (this->m_length > 0) {//还有元素就首尾相连
                    lastToFirst();

                    if (this->m_current == toDel) {
                        this->m_current = toDel->next;
                    }
                }
                else {//如果没有这里要赋值为空
                    this->m_current = NULL;
                    this->m_header.next = NULL;
                }
                this->destroy(toDel);
                ret = true;
            }
        }
        else {
            ret = LinkList<T>::remove(i);
        }
        return ret;
    }

    virtual bool set(int i, const T& e) {
        return LinkList<T>::set(mod(i), e);
    }

    virtual bool get(int i, T& e) const {
        return LinkList<T>::get( mod(i), e);
    }

    T get(int i) const {
        return LinkList<T>::get(mod(i));
    }

    int find(const T& e) const {
        int ret = -1;
        Node* current = this->m_header.next;

        for (int i = 0; i < this->m_length; i++) {
            if (current->value == e) {
                ret = i;
                break;
            }
            else {
                current = current->next;
            }
        }
        return ret;
    }

    bool move(int i, int step = 1) {
        i = mod(i);
        return LinkList<T>::move(i, step);
    }

    bool end() {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    virtual void clear() {
        while(this->m_length > 1) {//remove(1)时不走i==0分支
            remove(1);
        }
        if (this->m_length == 1) {
            Node* toDel = this->m_header.next;
            this->m_header.next = NULL;
            this->m_current = NULL;
            this->m_length = 0;

            this->destroy(toDel);
        }

    }

    ~CircleList() {
        clear();
    }
};
}


#endif // CIRCLELIST_H
