#include"LinkedStack.h"



//创建栈
Stack* StackConstruct(int sizeOfElem) {
    Stack* pList = (Stack*)malloc(sizeof(Stack));
    if (pList == NULL) {
        return NULL;
    }
    pList->pFirstNode = NULL;
    pList->length = 0;
    pList->elementSize = sizeOfElem;
    return pList;
}

//析构栈
void StackDestruct(Stack* pStack) {
    ListClear(pStack);
    free(pStack);
    return;
}

//判断栈是否为空
bool IsEmpty(Stack* pStack) {
    return pStack->length == 0 ? true : false;
}

//求链表长度
int StackLength(Stack* pStack) {
    return pStack->length;
}

//头部插入数据(入栈)
Status StackPush(Stack* pStack, void* pElem) {
    ListNode* pNewNode;
    pNewNode = ListMakeNode(pStack, pElem);
    if (pNewNode == NULL) {
        return ERROR;
    }
    pNewNode->pNextNode = pStack->pFirstNode;
    pStack->pFirstNode = pNewNode;
    pStack->length++;
    return OK;
}

//出栈
Status StackPop(Stack* pStack, void* pElem) {
    ListNode* pTempNode;
    if (pStack->length == 0) {
        return ERROR;
    }
    pTempNode = pStack->pFirstNode;
    pStack->pFirstNode = pTempNode->pNextNode;
    void* pTemp = ListGetData(pTempNode);
    memcpy(pElem, pTemp, pStack->elementSize);
    ListFreeNode(pTempNode);
    pTempNode = NULL;
    pStack->length--;
    return OK;
}

//取栈顶数据
void* StackGetTop(Stack* pStack) {
    ListNode* pTempNode;
    if (pStack->length == 0) {
        return NULL;
    }
    pTempNode = pStack->pFirstNode;
    void* pTemp = ListGetData(pTempNode);
    void* pElem=malloc(sizeof(pStack->elementSize));
    memcpy(pElem, pTemp, pStack->elementSize);
    pTempNode = NULL;
    return pElem;
}

//定义visit函数
Status Visit(void* pElem) {
    if (!pElem) return ERROR;
    char* ch = (char*)pElem;
    printf("%s", ch);
    return OK;
}

//遍历栈
Status StackTraverse(Stack* pStack, Status(*visit)(void*)) {
    ListNode* pTempNode;
    pTempNode = pStack->pFirstNode;
    while (pTempNode != NULL) {
        if (visit(pTempNode->pData) == ERROR) {
            return ERROR;
        }  pTempNode = pTempNode->pNextNode;
    }
    return OK;
}
