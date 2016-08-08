//
//  main.cpp
//  面试题58
//
//  Created by 😄 on 16/8/8.
//  Copyright © 2016年 😄. All rights reserved.
//

#include <iostream>

using namespace std;

struct BinaryTreeNode
{
    int value;
    BinaryTreeNode *Left;
    BinaryTreeNode *Right;
    BinaryTreeNode *Parent;
};

void getNet(BinaryTreeNode *node)
{
    if (node == NULL) {
        return;
    }
    BinaryTreeNode *nextNode = NULL;
    if (node -> Right != NULL) {
        BinaryTreeNode *right = node -> Right;
        while (right -> Left != NULL) {
            right = right -> Left;
        }
        nextNode = right;
        //cout << "the next node is " << right -> value << endl;
    }else if(node -> Parent != NULL){
        BinaryTreeNode *currentNode = node;
        BinaryTreeNode *parentNode = node -> Parent;
        while (parentNode != NULL && currentNode == parentNode -> Right) {
            currentNode = parentNode;
            parentNode = parentNode -> Parent;
        }
        nextNode = parentNode;
       // cout << "the next node is " << parentNode -> value << endl;
    }
    if (nextNode) {
        cout << "tne next node is " << nextNode -> value << endl;
    }else{
        cout << "the next node is null" << endl;
    }
    
}

BinaryTreeNode* CreateBinaryTreeNode(int value)
{
    BinaryTreeNode *treeNode = new BinaryTreeNode();
    treeNode -> value = value;
    treeNode -> Left = NULL;
    treeNode -> Right = NULL;
    treeNode -> Parent = NULL;
    
    return treeNode;
}

void ConnectTreeNode(BinaryTreeNode *parent, BinaryTreeNode *left, BinaryTreeNode *right)
{
    if (parent != NULL) {
        parent -> Left = left;
        parent -> Right = right;
        
        if (left != NULL) {
            left -> Parent = parent;
        }
        
        if (right != NULL) {
            right -> Parent = parent;
        }
    }
}

void printTreeNode(BinaryTreeNode *node)
{
    if (node != NULL) {
        cout << "the value of this node is:" << node -> value << endl;
        if (node -> Left != NULL) {
            cout << "the value of left child is " << node -> Left -> value << endl;
        }else{
            cout << "the value of letf child is null" << endl;
        }
        if (node -> Right != NULL) {
            cout << "the value of right child is " << node -> Right -> value << endl;
        }else{
            cout << "the value of right child is null" << endl;
        }
    }else{
        cout << "the value of this node is null" << endl;
    }
    cout << endl;
}

void printTree(BinaryTreeNode *root)
{
    printTreeNode(root);
    
    if (root -> Left != NULL) {
        printTree(root -> Left);
    }
    if (root -> Right != NULL) {
        printTree(root -> Right);
    }
}

void DestroyTree(BinaryTreeNode *root)
{
    if (root != NULL) {
        BinaryTreeNode *left = root -> Left;
        BinaryTreeNode *right = root -> Right;
        
        delete root;
        
        DestroyTree(left);
        DestroyTree(right);
    }
}

int main(int argc, const char * argv[]) {
    
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);
    
    ConnectTreeNode(pNode8, pNode6, pNode10);
    ConnectTreeNode(pNode6, pNode5, pNode7);
    ConnectTreeNode(pNode10, pNode9, pNode11);
    
    //printTree(pNode8);
    
    getNet(pNode7);
    
    return 0;
}
