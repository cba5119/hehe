#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object//这样类T必须要定义默认无参构造函数，否则会编译不过，因为create函数？问题：stl的容器为什么可以？
    {
        T value;
        Node* next;
    };

    mutable struct : public Object {
        char reserved[sizeof(T)];
        Node* next;
    } m_header;
    int m_length;
    int m_step;
    Node* m_current;

    Node* position(int i) const {//注意这里要加上const 否则无法被const函数调用
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for (int n = 0; n < i; n++) {
            ret = ret->next;
        }
        return ret;//这里的逻辑是返回当前节点前一个节点，所以需要强制转换
    }

    virtual Node* create() {
        return new Node();
    }

    virtual void destroy(Node* pn) {//注意这里别忘记写返回值，否则会导致编译器报冲突的错误
        delete pn;
    }

public:
    LinkList() {
        m_length = 0;
        m_header.next = NULL;
        m_step = 1;
        m_current = NULL;
    }

    virtual bool insert(int i, const T& e) {
        bool ret = (i >= 0) && (i <= m_length);
        if (ret) {
            Node* node = create();
            if (node != NULL) {
                node->value = e;
                Node* current = reinterpret_cast<Node*>(&m_header);
                for (int n = 0; n < i; n++) {
                    current = current->next;
                }
                node->next = current->next;
                current->next = node;
                m_length++;
            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memery...");
            }
        }
        return ret;
    }

    virtual bool remove(int i) {
        bool ret = (i >= 0) && (i < m_length);
        if (ret) {
            Node* current = position(i);
            Node* node = current->next;
            current->next = node->next;
            if (m_current == node) {//如果current恰好指向删除的元素，删除之后要指向下一个
                m_current = node->next;
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

    ~LinkList() {
        clear();
    }
};

}


#endif // LINKLIST_H
