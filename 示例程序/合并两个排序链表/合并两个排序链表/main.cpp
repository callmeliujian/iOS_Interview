//
//  main.cpp
//  合并两个排序链表
//
//  Created by 😄 on 16/7/24.
//  Copyright © 2016年 😄. All rights reserved.
//

#include <iostream>

using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode, *LinkList;

void InitLink(LinkList &L)
{
    LNode *p = new LNode;
    L = p;
    p -> next = NULL;
}

void CreatLink(LinkList &L, int n)
{
    LNode *p, *q;
    
    p = L;
    
    cin >> p -> data;
    
    for (int i = 1; i < n; i++) {
        q = new LNode;
        q -> next = NULL;
        cin >> q -> data;
        p -> next = q;
        p = q;
    }
    
}

void ShowLink(LinkList &L)
{
    LNode *p;
    p = L;
    while (p) {
        cout << p -> data << endl;
        p = p -> next;
    }
}

LNode * Merge(LNode *p, LNode *q)
{
    if (p == NULL) {
        return q;
    }else if (q == NULL){
        return p;
    }
    
    LNode *r;
    
    if (p -> data < q -> data) {
        r = p;
        r -> next = Merge(p -> next, q);
    }else{
        r = q;
        r -> next = Merge(p, q -> next);
    }
    
    return r;
    
}

int main()
{
    
    LinkList L;
    LinkList R;
    LNode *P;
    
    InitLink(L);
    InitLink(R);
    
    CreatLink(L, 2);
    CreatLink(R, 2);
    
    //    ShowLink(L);
    //    ShowLink(R);
    
    P = Merge(L, R);
    cout << "---------------" << endl;
    ShowLink(P);
    
    return 0;
}

