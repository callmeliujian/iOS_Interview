//
//  main.cpp
//  面试题15
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
    cin >> L -> data;
    L -> next = NULL;
    LNode *p;
    p = L;
    for (int i = 1; i < n; i ++) {
        LNode *q = new LNode;
        cin >> q -> data;
        q -> next = NULL;
        p -> next = q;
        p = q;
    }
}

void FindKthToTail(LinkList &L, int k)
{
    if (L != NULL && k != 0) {
        LNode *p = L;
        LNode *q = L;
        for (int i = 0; i < k; i ++) {
            if (p!= NULL) {
                p = p -> next;
            }else{
                return;
            }
        }
        
        while (p) {
            q = q -> next;
            p = p -> next;
        }
        cout << q -> data;
    }
}

void ShowList(LinkList &L)
{
    LNode *p;
    p = L;
    while (p) {
        cout << p -> data;
        p = p -> next;
    }
}

int main()
{
    
    LinkList L;
    CreatList(L, 6);
    ShowList(L);
    cout << "输入k：" << endl;
    int k;
    cin >> k;
    FindKthToTail(L, k);
    
    return 0;
}
