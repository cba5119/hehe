#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "duallinklist.h"
#include "linuxlist.h"


namespace DTLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
       list_head* head;
       T value;
    };

    list_head m_header;
    list_head* m_current;
    int m_length;
    int m_step;

    list_head* position(int i) const
    {
        list_head* ret = &m_header;
        i = i%m_length;
        while (i--){
            ret = ret->next;
        }
        return ret;
    }

    virtual Node* create() {
        return new Node();
    }

    virtual void destroy(Node* pn) {
        delete pn;
    }

public:
    DualCircleList() {
        m_length = 0;
        INIT_LIST_HEAD(&m_header);
        m_step = 1;
        m_current = NULL;
    }

    virtual bool insert(int i, const T& e) {
        bool ret = (i >= 0);
        if (ret) {
            Node* node = create();
            if (node != NULL) {
                node->value = e;
                Node* current = reinterpret_cast<Node*>(&m_header);
                i = i%(m_length+1);
                for (int n = 0; n < i; n++) {
                    current = current->next;
                }
               list_add(node, &m_header);
                m_length++;
            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memery...");
            }
        }
        return ret;
    }

    virtual bool insert(const T& e) {
        return insert(length(), e);
    }

    virtual bool remove(int i) {
        bool ret = (i >= 0) && (i < m_length);
        if (ret) {
            Node* current = position(i);
            Node* node = current->next;
            Node* next = node->next;
            current->next = node->next;
            if (next != NULL) {
                next->pre = current;
            }
            if (m_current == node) {//如果current恰好指向删除的元素，删除之后要指向下一个
                m_current = next;
            }
            m_length--;//注意这个要放在前面，因为节点连接已经少了
            destroy(node);
        }
        return ret;
    }

    virtual bool set(int i, const T& e) {
        bool ret = (i >= 0) && (i < m_length);
        if (ret) {
            Node* current = position(i);
            Node* node = current->next;
            node->value = e;
        }
        return ret;
    }

    virtual bool get(int i, T& e) const {
        bool ret = (i >= 0) && (i < m_length);
        if (ret) {
            Node* current = position(i);
            Node* node = current->next;
            e = node->value;
        }
        return ret;
    }

    int find(const T& e) const {
        int ret = -1;
        Node* node = m_header.next;
        int i = 0;
        while(node) {
            if (node->value == e) {
                ret = i;
                break;
            }
            else {
                node = node->next;
                i++;
            }
        }
        return ret;
    }

    virtual bool move(int i, int step = 1) {//移动到指定位置，设置步长
        int ret = (i >= 0 ) && (i < m_length) && (step > 0);
        if (ret) {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
    }

    virtual bool end() {
        return (m_current == NULL);
    }

    virtual T current() {
        if (m_current != NULL) {
            return m_current->value;
        }
        else {
            THROW_EXCEPTION(InValidOperationException, "no value at this position...");
        }
    }

    virtual bool next() {
        int i = 0;
        while (i < m_step && m_current != NULL) {
            m_current = m_current->next;
            i++;
        }
        return (i == m_step);
    }

    virtual bool pre() {
        int i = 0;
        while (i < m_step && m_current != reinterpret_cast<Node*>(&m_header)) {
            m_current = m_current->pre;
            i++;
        }
        if ( m_current == reinterpret_cast<Node*>(&m_header)) {//这里第一个节点的pre指向的是header，也可以指向NULL，这样这里就不用特殊处理了，但是在insert的时候就要做处理
            m_current = NULL;
        }
        return (i == m_step);
    }

    T get(int i) const {
        T ret;
        if (get(i, ret)) {
            return ret;
        }
        else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "index is out of range...");
        }
    }

    virtual int length() const {
        return m_length;
    }

    virtual void clear() {
        while(m_header.next != NULL) {
            Node* node = m_header.next;
            m_header.next = m_header.next->next;
            m_length--;//在删除之前--
            destroy(node);
        }
    }

    ~DualLinkList() {
        clear();
    }

};



}


#endif // DUALCIRCLELIST_H
