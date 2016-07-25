//
//  main.cpp
//  面试题5
//
//  Created by 😄 on 16/7/25.
//  Copyright © 2016年 😄. All rights reserved.
//

#include <iostream>

using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode, *LinkLinst;

typedef struct SNode
{
    int data;
    struct SNode *next;
}SNode, *LinkStack;

void InitLinst(LinkLinst &L)
{
    L = new LNode;
    L -> next = NULL;
}

void CreatLink(LinkLinst &L, int n)
{
    LNode *p, *q;
    p = L;
    cout << "请输入数据" << endl;
    cin >> p -> data;
    
    for (int i = 1; i < n; i++) {
        q = new LNode;
        q -> next = NULL;
        cin >> q -> data;
        p -> next = q;
        p = q;
    }
}

//解法一，用栈实现
void ListToStack(LinkLinst &L, LinkStack &S)
{
    LNode *p;
    p = L;
    while (p) {
        //cout << p -> data << endl;
        SNode *q = new SNode;
        //cin >> q -> data;
        q -> data = p -> data;
        q -> next = S;
        S = q;
        
        p = p -> next;
    }
}

void InitStack(LinkStack &S)
{
    S = NULL;
}

void Pop(LinkStack &S)
{
    SNode *p;
    while (S) {
        cout << S -> data << endl;
        p = S;
        S = S -> next;
        delete p;
    }
}

//接发二，递归实现
void PrintListReversingly_Recursively(LinkLinst &L)
{
    if (L != NULL) {
        if (L -> next != NULL) {
            PrintListReversingly_Recursively(L -> next);
        }
        cout << L -> data << endl;;
    }
    
}

int main(int argc, const char * argv[]) {

    LinkLinst L;
    InitLinst(L);

    LinkStack S;
    InitStack(S);
    
    CreatLink(L, 5);
//    PrintListReversingly_Recursively(L);
    ListToStack(L, S);
    Pop(S);
    
    return 0;
}
