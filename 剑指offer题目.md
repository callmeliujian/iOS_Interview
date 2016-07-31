# 剑指offer相关题目

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
	-完整代码：[面试题五](https://github.com/callmeliujian/iOS_Interview/tree/master/示例程序/面试题5)
	- 面试题13:给定单项链表的头指针和一个节点指针，定义一个函数在O(1)时间删除该节点。
		- 解法：假如我们想删除节点i，i的下一个节点是j。我们可以把节点j的内容复制给i，把i的next指向j的next。如果我们要删除的节点位于尾部，我们只能从头节点开始，遍历到尾部的前一个节点，并删除尾部节点。如果只有一个节点我们就直接删除它。
		- 完整代码：[面试题13](https://github.com/callmeliujian/iOS_Interview/tree/master/示例程序/面试题13)
	- 面试题37:输入两个链表，找出它们的第一个公共节点。(如图)
		![面试题37](media/%E9%9D%A2%E8%AF%95%E9%A2%9837.png)

		- 解题思路：首先遍历两个链表得到它们的长度，就能知道哪个链表长，长多少。第二次遍历的时候，先在较长的链表上先走若干步，接着再同时在两个链表上遍历，找到的第一个相同的节点就是它们的公共节点。 
		- 主要算法
			
			```
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
			```
		- 完整代码：[面试题37](https://github.com/callmeliujian/iOS_Interview/tree/master/示例程序/面试题37) 
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
	* 完整代码：[合并两个排序链表](https://github.com/callmeliujian/iOS_Interview/tree/master/示例程序/合并两个排序链表)


