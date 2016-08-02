//
//  main.cpp
//  判断一个单向链表是否形成了环形结构
//
//  Created by 😄 on 16/8/2.
//  Copyright © 2016年 😄. All rights reserved.
//

#include <iostream>
using namespace std;

typedef struct LNode
{
    int data;
    LNode *next;
}LNode, *LinkList;

LNode* CreatNode(int n)
{
    LNode *p = new LNode;
    p -> data = n;
    p -> next = NULL;
    return p;
}

void ConnectNode(LinkList &p, LinkList &q)
{
    p -> next = q;
}

void ShowLinkList(LinkList &L)
{
    LNode *p = L;
    while (p) {
        cout << p -> data << endl;
        p = p -> next;
    }
}

int FindLinkListCircle(LinkList &L)
{
    LNode *p = L;
    LNode *q = L;
    while (q && p && (p-> next != NULL)) {
            p = p -> next -> next;
        
        
        if (p == q) {
            return 1; //表示存在环
        }
        q = q -> next;
    }
    return 0;//表示不存在环
}

void Test1()
{
    LNode *p1 = CreatNode(1);
    ConnectNode(p1, p1);
    cout << FindLinkListCircle(p1)<< endl;
}

void Test2()
{
    LNode *p1 = CreatNode(1);
    LNode *p2 = CreatNode(2);
    ConnectNode(p1, p2);
    cout << FindLinkListCircle(p1)<< endl;
}

void Test3()
{
    LNode *p1 = CreatNode(1);
    LNode *p2 = CreatNode(2);
    ConnectNode(p1, p2);
    ConnectNode(p2, p1);
    cout << FindLinkListCircle(p1)<< endl;
}

void Test4()
{
    LNode *p1 = CreatNode(1);
    LNode *p2 = CreatNode(2);
    LNode *p3 = CreatNode(3);
    
    ConnectNode(p1, p2);
    ConnectNode(p2, p3);
    ConnectNode(p3, p1);
    
    cout << FindLinkListCircle(p1) << endl;
}

void Test5()
{
    LNode *p1 = CreatNode(1);
    LNode *p2 = CreatNode(2);
    LNode *p3 = CreatNode(3);
    
    ConnectNode(p1, p2);
    ConnectNode(p2, p3);
    
    cout << FindLinkListCircle(p1) << endl;
}

int main(int argc, const char * argv[]) {
    
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    
    return 0;
}
