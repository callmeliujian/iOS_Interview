//
//  main.cpp
//  奇数个节点的单向链表，查找其中间节点
//
//  Created by 😄 on 16/8/1.
//  Copyright © 2016年 😄. All rights reserved.
//

#include <iostream>

using namespace std;

typedef struct LNode
{
    int data;
    LNode *next;
}LNode, *LinkList;

void CreatList(LinkList &L, int n)
{
    L = new LNode;
    L -> next = NULL;
    cin >> L -> data;
    
    LNode *p,*q;
    p = L;
    for (int i = 1; i < n; i++) {
        q = new LNode;
        q -> next = NULL;
        cin >> q -> data;
        p -> next = q;
        p = q;
    }
}

void ShowList(LinkList &L)
{
    LNode *p = L;
    while (p) {
        cout << p -> data;
        p = p -> next;
    }
}

void Find(LinkList &L)
{
    LNode *p, *q;
    p = q = L;
    while (p -> next) {
        p = p -> next -> next;
        q = q -> next;
    }
    cout << q -> data;
}

int main(int argc, const char * argv[]) {
    
    LNode *L;
    
    CreatList(L, 5);
//    ShowList(L);
    Find(L);
    
    return 0;
}
