#ifndef LIST_H
#define LIST_H

#include"common.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//结点类型的定义
typedef struct ListNode {
    struct ListNode* pNextNode;
    void* pData;
}ListNode;

//链表的定义
typedef struct {
    ListNode* pFirstNode;
    int length;
    int elementSize;
}List;

ListNode* ListMakeNode(List* pList, void* pData);
/*
功能：创建结点
参数：第一个参数是链表的指针，第二个参数是传入数据的指针，把pData指向的数据存入新节点。
返回值：如果成功，返回指向新节点的指针；如果失败，返回NULL。
*/

void ListFreeNode(ListNode* pNode);
/*
功能：释放结点
参数：参数是结点的指针
返回值：无返回值
*/

void ListClear(List* pList);
/*
功能：清空链表。链表上的所有结点清空，但链表仍存在
参数：参数是链表的指针
返回值：无返回值
*/

void* ListGetData(ListNode* pNode);
/*
功能：取结点上的数据
参数：参数是结点的指针
返回值：返回pNode节点上数据的地址。参数pNode不能为NULL
*/

bool EmptyNode(ListNode* pNode);
/*
功能：判断结点是否为空
参数：参数是结点的指针
返回值：为空返回true，不为空返回false
*/

Status ListAppendToEnd(List* pList, void* pData);
/*
功能：尾部插入数据
参数：第一个参数是链表的指针，第二个参数是传入数据的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListInsertAfter(List* pList, ListNode* pNode, void* pData);
/*
功能：某节点后插入数据
参数：第一个参数是链表的指针，第二个参数是结点的指针，第三个参数是传入数据的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListDeleteFirstNode(List* pList);
/*
功能：删除第一个结点
参数：参数是链表的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListDeleteLastNode(List* pList);
/*
功能：删除最后一个结点
参数：参数是链表的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

Status ListDeleteNode(List* pList, ListNode* pNode);
/*
功能：删除某一结点
参数：第一个参数是链表的指针，第二个参数是结点的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

ListNode* ListAppendToHead(List* pList, void* pData);
/*
功能：头部插入数据
参数：第一个参数是链表的指针，第二个参数是传入数据的指针
返回值：如果成功，返回指向新节点的指针；如果失败，返回NULL。
*/

Status ListRound(List* pList);
/*
功能：循环链表
参数：参数是链表的指针
返回值：如果成功，返回OK，失败返回ERROR
*/

List* ListReverse(List* pList);
/*
功能：链表反转
参数：参数是链表的指针
返回值：如果成功，返回指向新节点的指针；如果失败，返回NULL。
*/

List* ListFusion(List* pList1, List* pList2);
/*
功能：链表合并 第二个链表链接到第一个链表的尾部
参数：第一个参数是链表的指针，第二个参数是链表的指针
返回值：如果成功，返回将list2接在list1后面后合并后的链表；如果失败，返回NULL。
注意：这个过程中list1被改变成了合并后的链表。
*/

bool JudgmentRingList(List* pList);
/*
功能：判断链表是否有环
参数：参数是链表的指针
返回值：如果成功，返回true，失败返回false。
*/


Status ListTraverse(List* pList, void(*pVisit)(void* pData));
/*
功能：遍历链表
参数：第一个参数是链表的指针，第二个参数是函数指针，pVisit是把数据记录和关键字做比较的函数
返回值：如果成功，返回OK，失败返回ERROR。
*/

Status ListPrint(List* pList);
/*
功能：打印链表
参数：参数是链表的指针
返回值：如果成功，返回OK，失败返回ERROR。
*/
#endif
