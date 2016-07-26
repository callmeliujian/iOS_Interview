//
//  main.cpp
//  面试题37
//
//  Created by 😄 on 16/7/26.
//  Copyright © 2016年 😄. All rights reserved.
//

#include <iostream>

using namespace std;

typedef struct ListNode
{
    int m_Key;
    ListNode *m_pNext;
}ListNode, *LinkList;

//创建节点
ListNode* CreateNode(int n)
{
    ListNode *p = new ListNode;
    p -> m_Key = n;
    p -> m_pNext = NULL;
    return p;
    
}

//链接节点
void ConnectNode(ListNode *P, ListNode *Q)
{
    P -> m_pNext = Q;
}

void Show(ListNode *P)
{
    while (P) {
        cout << P -> m_Key << endl;
        P = P -> m_pNext;
    }
}

//获得链表长度
int GetListLength(ListNode *P)
{
    int length = 0;
    ListNode *q = P;
    while (q) {
        length ++;
        q = q  -> m_pNext;
    }
    return length;
}

void FindFirstCommonNode(ListNode *p, ListNode *q)
{
    int lengthList1 = GetListLength(p);
    int lengthList2 = GetListLength(q);
    
    int listDiff;
    ListNode *listLong, *listShort;
    
    if (lengthList1 > lengthList2) {
        listDiff = lengthList1 - lengthList2;
        listLong = p;
        listShort = q;
    }else{
        listDiff = lengthList2 - lengthList1;
        listLong = q;
        listShort = p;
    }
    
    for (int i = 0; i < listDiff; i++) {
        listLong = listLong -> m_pNext;
    }
    
    while (listLong != NULL && listShort != NULL && listLong != listShort) {
        listLong = listLong -> m_pNext;
        listShort = listShort -> m_pNext;
    }
    
    cout << listLong -> m_Key;
    
}

int main(int argc, const char * argv[]) {
    
    ListNode *node1 = CreateNode(1);
    ListNode *node2 = CreateNode(2);
    ListNode *node3 = CreateNode(3);
    ListNode *node4 = CreateNode(4);
    ListNode *node5 = CreateNode(5);
    ListNode *node6 = CreateNode(6);
    ListNode *node7 = CreateNode(7);
    
    ConnectNode(node1, node2);
    ConnectNode(node2, node3);
    ConnectNode(node3, node6);
    ConnectNode(node6, node7);
    ConnectNode(node4, node5);
    ConnectNode(node5, node6);
    
//    Show(node1);
//    Show(node4);
//    printf("%d",GetListLength(node1));
//    printf("%d",GetListLength(node4));
    
    FindFirstCommonNode(node1, node4);
    
    return 0;
}
