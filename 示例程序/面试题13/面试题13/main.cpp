//
//  main.cpp
//  面试题13
//
//  Created by 😄 on 16/7/31.
//  Copyright © 2016年 😄. All rights reserved.
//

#include <iostream>

using namespace std;

typedef struct ListNode
{
    int m_nValue;
    ListNode *m_next;
}ListNode, *LinkList;

ListNode* CreateListNode(int n)
{
    ListNode *p = new ListNode;
    p -> m_nValue = n;
    p -> m_next = NULL;
    return p;
}

void DeleteNode(LinkList &L, ListNode *p)
{
    //删除的不是尾节点
    if (p -> m_next != NULL) {
        ListNode *q = p -> m_next;
        p -> m_nValue = q -> m_nValue;
        p -> m_next = q -> m_next;
        delete q;
    }else if (L == p){ //只有一个节点，无法删除，把m_Value置空
        p -> m_nValue = NULL;
    }else{  //是尾节点
        ListNode *q = L;
        while (q -> m_next -> m_next!= NULL) {
            q = q -> m_next;
        }
        delete q -> m_next;
        q -> m_next = NULL;
    }
    
    
}

void ConnectListLondes(LinkList &p, LinkList &q)
{
    p -> m_next = q;
    q -> m_next = NULL;
}

void ShowList(LinkList &L)
{
    ListNode *p;
    p = L;
    while (p) {
        cout << p->m_nValue << endl;
        p = p -> m_next;
    }
}

int main(int argc, const char * argv[]) {
    
    ListNode *p1 = CreateListNode(1);
    ListNode *p2 = CreateListNode(2);
    ListNode *p3 = CreateListNode(3);
    ListNode *p4 = CreateListNode(4);
    ListNode *p5 = CreateListNode(5);
    ListNode *p6 = CreateListNode(6);
    
    ConnectListLondes(p1, p2);
    ConnectListLondes(p2, p3);
    ConnectListLondes(p3, p4);
    ConnectListLondes(p4, p5);
    ConnectListLondes(p5, p6);
    
    ShowList(p1);
    
    cout << "-------------" << endl;
    //删除第一个节点
    DeleteNode(p1, p1);
    ShowList(p1);
    
    //删除最后一个节点
    //DeleteNode(p1, p6);
    //ShowList(p1);
    
    return 0;
}
