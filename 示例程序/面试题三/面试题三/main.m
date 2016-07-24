//
//  main.m
//  面试题三
//
//  Created by 😄 on 16/7/24.
//  Copyright © 2016年 😄. All rights reserved.
//

#import <Foundation/Foundation.h>

bool Find(int * matrix, int rows, int cloumns, int number)
{
    bool found = false;
    
    if (matrix != NULL && rows > 0 && cloumns > 0 ) {
        int row = 0;
        int cloumn = cloumns - 1;
        
        while (row < rows && cloumn >= 0) {
            if (matrix[row * cloumns + cloumn] == number) {
                found = true;
                break;
            }else if (matrix[row * cloumns + cloumn] > number)
                cloumn --;
            else
                row ++;
        }
    }
    
    return found;
}

int main(int argc, const char * argv[]) {
    
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    
    printf("%d \n",Find(matrix, 4, 4, 15));
    
    return 0;
}

