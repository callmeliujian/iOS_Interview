# 剑指offer相关题目

- - -
- 链表相关题目：
	- 面试题5:输入一个链表的头节点，从尾到头反过来打印出每个节点的值。
		- 解法一：将每个链表中的数据放进栈中，之后出栈即可。
		
			```c
			void ListToStack(LinkLinst &L, 			LinkStack &S)
			{
    			LNode *p;
    			p = L;
    			while (p) {
        			SNode *q = new SNode;
        			q -> data = p -> data;
        			q -> next = S;
        			S = q;
        			p = p -> next;
    			}
			}
			```
		- 解法二：递归实现。（递归本质上就是一个栈结构）

			```
			void PrintListReversingly_Recursively(LinkLinst &L)
			{
    			if (L != NULL) {
        			if (L -> next != NULL) {
       	PrintListReversingly_Recursively(L -> next);
        			}
        		cout << L -> data << endl;;
    			}
			}
			```
	-完整代码：   
* 面试题三
	- 题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下的顺序排序。请完成一个函数，输入这样的一个二维数组盒一个整数，判断数组中是否含有该整数。
	- 解题思路：首先选取数组中右上角的数字。如果该数字等于要查找的数字，结束查找；如果该数字大于要查找的数字，剔除该数字所在的列；如果该数字小于要查找的数字，剔除该数字所在的行。
	- 代码：
	
		```c
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
		```
	- 完整代码：[面试题三](https://github.com/callmeliujian/iOS_Interview/tree/master/示例程序/面试题三) 
* 合并两个排序链表
	* 两个链表中的头节点值较小的节点作为合并后连标的头节点。
	* 两个链表剩余的节点依旧是顺序的，所以可以把较小的节点连接到合并后的链表中。
	* 因为每次的步骤是一样的，所以可以使用递归。
	* 完整代码：


