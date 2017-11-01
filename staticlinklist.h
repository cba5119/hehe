#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "linklist.h"

namespace DTLib
{

template< typename T, int N >
class StaticLinkList : public LinkList<T>//内存分配是自己已经分配好的，这样效率会高一些
{
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node {//为了调用new的时候是自己这边分的内存，因为node是基类，无法修改基类代码，所以要继承
        void* operator new(unsigned int size, void* loc) {
            (void)size;
            return loc;
        }
    };

protected:
    unsigned char m_space[sizeof(Node) * N];
    int m_used[N];

    Node* create() {//由于staticlinklist和一般linklist只有内存分配的不同，所以重载create和destroy就可以了
        SNode* ret = NULL;
        for (int i = 0; i < N; i++) {
            if (!m_used[i]) {
                ret = reinterpret_cast<SNode*>(m_space)+i;
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }

    void destroy(Node* pn) {
        SNode* tmp = reinterpret_cast<SNode*>(m_space);
        for (int i = 0; i < N; i++) {
            if (pn == (tmp + i)) {
                m_used[i] = 0;
                tmp->~SNode();
                break;
            }
        }
    }
public:
    StaticLinkList() {
        for (int i = 0; i < N; i++) {
            m_used[i] = 0;
        }
    }
    int capacity() {
        return N;
    }

};

}

#endif // STATICLINKLIST_H
