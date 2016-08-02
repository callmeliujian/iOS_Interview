//
//  main.cpp
//  面试题16
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

void CreatLinkList(LinkList &L, int n)
{
    L = new LNode;
    L -> next = NULL;
    cin >> L -> data;
    LNode *p = L;
    for (int i = 1; i < n; i++) {
        LNode *q = new LNode;
        q -> next = NULL;
        cin >> q -> data;
        p -> next = q;
        p = q;
    }
}

void ShowLinkList(LinkList &L)
{
    LNode *p = L;
    while (p) {
        cout << p -> data << endl;
        p = p -> next;
    }
}

LNode* ReverseLinkList(LinkList &L)
{
    LNode *p, *pPrev, *head, *pNext;
    p = L;
    pPrev = head = NULL;
    while (p) {
        pNext = p -> next;
        if (!pNext) {
            head = p;
        }
        p -> next = pPrev;
        pPrev = p;
        p = pNext;
    }
    return head;
}

int main(int argc, const char * argv[]) {
    
    LNode *L;
    CreatLinkList(L, 1);
    L = ReverseLinkList(L);
    ShowLinkList(L);
    return 0;
}
