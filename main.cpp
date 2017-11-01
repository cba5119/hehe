#include <iostream>
#include "Exception.h"
#include "Object.h"
#include "SmartPointer.h"
#include "staticlist.h"
#include "dynamiclist.h"
#include "staticarray.h"
#include "dynamicarray.h"
#include "linklist.h"
#include "stdio.h"
#include "windows.h"
#include "staticlinklist.h"
#include "sharedpointer.h"
#include "circlelist.h"
#include "duallinklist.h"
#include "LinuxList.h"

using namespace std;
using namespace DTLib;

class Test : public Object{
public:
    Test(int v = 0) {
        //throw 0;
       // cout<<"Test()"<<endl;
        value = v;
    }
    ~Test() {
       //cout<<"~Test()"<<endl;
    }
    bool operator == (const Test& t) {
        return this->value == t.value;
    }

    int value;
};

void josephus(int n, int s, int m) {//s是起始报数 m是报数要死得人
    {
        CircleList<int> cl;
        for (int i = 0; i < n; i++) {
            cl.insert(i);
        }

        for (cl.move(s-1, m-1); !cl.end(); cl.next()) {
           cout<<cl.current()<<" "<<cl.length()<<endl;
           cl.remove(cl.find(cl.current()));
        }
    }
    {
        CircleList<int> cl;
        for (int i = 0; i < n; i++) {
            cl.insert(i);
        }
        cl.move(s-1, m-1);
        while(cl.length() > 0) {
           cl.next();//开始报数
           cout<<cl.current()<<" "<<cl.length()<<endl;
           cl.remove(cl.find(cl.current()));
        }
    }
}

void DualLinkListTest() {
    DualLinkList<Test> list;

    Test t1(1), t2(2), t3(3);


    list.insert(0, t1);
    list.insert(0, t2);
    list.insert(0, t3);

    list.remove(2);

    for (list.move(0); !list.end(); list.next()) {
        cout<<list.current().value<<endl;
    }

    for (list.move(1); !list.end(); list.pre()) {
        cout<<list.current().value<<endl;
    }
}

struct Student {
    int x;
    int y;

    list_head node;
    char z;
};


int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    list_head head;
    INIT_LIST_HEAD(&head);

    Student s1;
    s1.z = '1';
    Student s2;
    s2.z = '2';
    Student s3;
    s3.z = '3';

    list_add_tail(&s1.node, &head);
    list_add_tail(&s2.node, &head);
    list_add_tail(&s3.node, &head);

    list_head* cur;

    list_for_each(cur, &head) {
        printf("%c\n", container_of(cur, Student, node)->z);
    }




    cout << "Hello World!" << endl;
    return 0;
}
