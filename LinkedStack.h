#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include"List.h"
#include"debug.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef List Stack;
//栈相关函数
Stack *StackConstruct(int sizeOfElment);
/*
初始化栈
参数为栈元素的大小
返回值OK表示初始化成功，ERROR表示失败
*/

void StackDestruct(Stack* pStack);
/*
释放栈的内存
参数为栈的指针
*/

bool IsEmpty(Stack* pStack);
/*
判断栈是否为空
参数为栈指针
返回值true表示栈为空，false表示栈不为空
*/

int StackLength(Stack* pStack);
/*
求栈的长度
参数为栈的指针
返回值为栈的长度
*/

Status StackPush(Stack* pStack, void* pElem);
/*
入栈
第一个参数为栈指针，第二个参数为入栈元素的指针
返回值OK表示入栈成功，ERROR表示失败
*/

Status StackPop(Stack* pStack, void* pElem);
/*
出栈
第一个参数为栈指针，第二个参数为出栈元素存放的数据位置的指针
返回值OK表示出栈成功，ERROR表示出栈失败
*/

void* StackGetTop(Stack* pStack);
/*
取栈顶元素
第一个参数为栈指针，第二个参数为存放栈顶元素的数据的指针
返回值OK表示成功，ERROR表示失败
*/



Status StackTraverse(Stack* pStack, Status(*visit)(void*));
/*
遍历栈
第二个参数为栈指针，第二个参数为函数指针
返回值OK表示成功，ERROR表示失败
*/

#endif
