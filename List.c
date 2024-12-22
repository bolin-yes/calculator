#include"list.h"
//创建结点
ListNode* ListMakeNode(List* pList, void* pData) {
    ListNode* pNewNode;
    pNewNode = (ListNode*)malloc(sizeof(ListNode));
    if (pNewNode == NULL) {
        return NULL;
    }
    pNewNode->pData = malloc(pList->elementSize);
    if (pNewNode->pData == NULL) {
        free(pNewNode);
        return NULL;
    }
    memcpy(pNewNode->pData, pData, pList->elementSize);
    pNewNode->pNextNode = NULL;
    return pNewNode;
}

//释放结点
void ListFreeNode(ListNode* pNode) {
    if (pNode == NULL) {
        return;
    }
    free(pNode->pData);
    free(pNode);
    return;
}

//清空链表
void ListClear(List* pList) {
    ListNode* pCurrentNode, * pNextNode;
    pCurrentNode = pList->pFirstNode;
    int len=0;//用于判断链表释放内存时何时应该停止
    while (len<pList->length){ //释放结点，但不释放链表(即保留头结点)
        pNextNode = pCurrentNode->pNextNode;
        ListFreeNode(pCurrentNode);
        pCurrentNode = pNextNode;
        len++;
    }
    pList->pFirstNode = NULL;
    pList->length = 0;
    return;
}

//取结点上的数据
void* ListGetData(ListNode* pNode) {
    if (pNode->pData == NULL) return NULL;
    return pNode->pData;
}

//判断结点是否为空
bool EmptyNode(ListNode* pNode) {
    return pNode == NULL ? true : false;
}

//尾部插入数据
Status ListAppendToEnd(List* pList, void* pData) {
    ListNode* pNewNode, * pTail;
    pNewNode = ListMakeNode(pList, pData);//创建一个结点
    if (pNewNode == NULL) {
        return ERROR;
    }
    if (pList->pFirstNode == NULL) {
        pList->pFirstNode = pNewNode;//当链表为空(即只有头结点)
    }
    else {
        pTail = pList->pFirstNode;
        while (pTail->pNextNode != NULL) {
            pTail = pTail->pNextNode;
        }
        pTail->pNextNode = pNewNode;//将创造的结点插入到链表尾部
    }
    pList->length++;
    return OK;
}

//某节点后插入数据
Status ListInsertAfter(List* pList, ListNode* pNode, void* pData) {
    ListNode* pNewNode;
    pNewNode = ListMakeNode(pList, pData);//创建结点
    if (pNewNode == NULL) {
        return ERROR;
    }
    pNewNode->pNextNode = pNode->pNextNode;
    pNode->pNextNode = pNewNode;
    pList->length++;
    return OK;
}

//删除第一个结点
Status ListDeleteFirstNode(List* pList) {
    ListNode* pTempNode;
    if (pList->length == 0) {
        return ERROR;
    }
    pTempNode = pList->pFirstNode;
    pList->pFirstNode = pTempNode->pNextNode;
    ListFreeNode(pTempNode);
    pTempNode = NULL;
    pList->length--;
    return OK;
}

//删除最后一个结点
Status ListDeleteLastNode(List* pList) {
    ListNode* p, * q;
    p = NULL;
    if (pList->length == 0) {
        return ERROR;
    }
    q = pList->pFirstNode;
    if (q->pNextNode == NULL) {//q的nest域为空，说明链表(除头结点外)只有一个结点
        return ListDeleteFirstNode(pList);//删除第一个结点
    }
    while (q->pNextNode != NULL) {
        p = q;
        q = q->pNextNode;//将p、q不断往链表尾部移动，直到q的next域为空，则说明已经遍历到了链表尾部
    }
    p->pNextNode = NULL;//此时p变成了新链表的尾部
    ListFreeNode(q);//释放原链表的尾部
    q = NULL;
    pList->length--;//链表长度减1
    return OK;
}

//删除某一结点
Status ListDeleteNode(List* pList, ListNode* pNode) {
    ListNode* pTempNode;
    if (pNode == NULL) {
        return OK;
    }  
    if (pList->length == 0) {
        return ERROR;
    }
    pTempNode = pList->pFirstNode;
    if (pTempNode == pNode) {
        pList->pFirstNode = pNode->pNextNode;
    }
    else {
        while (pTempNode != NULL && pTempNode->pNextNode != pNode) {
            pTempNode = pTempNode->pNextNode;//找到所要删除的结点位置
        }
        if (pTempNode == NULL) {
            return ERROR;
        }
        pTempNode->pNextNode = pNode->pNextNode;//删除结点
    }
    ListFreeNode(pNode);
    pList->length--;
    return OK;
}

//头部插入数据
ListNode* ListAppendToHead(List* pList, void* pData){
    ListNode* pNewNode;
    pNewNode = ListMakeNode(pList, pData);//创建结点
    if (pNewNode == NULL) {
        return NULL;
    }
    pNewNode->pNextNode = pList->pFirstNode;
    pList->pFirstNode = pNewNode;
    pList->length++;
    return pNewNode;

}


//循环链表
Status ListRound(List* pList){
    ListNode* pTempNode;
    pTempNode = pList->pFirstNode;
    while (pTempNode->pNextNode != NULL) {
        pTempNode = pTempNode->pNextNode;
    }
    pTempNode->pNextNode = pList->pFirstNode;
    return OK;
}



//链表反转
List* ListReverse(List* pList){
    ListNode* pTempNode, * pNextNode;
    pTempNode = pList->pFirstNode;
    pList->pFirstNode = NULL;
    while (pTempNode!= NULL) {
        pNextNode = pTempNode->pNextNode;
        pTempNode->pNextNode = pList->pFirstNode;
        pList->pFirstNode = pTempNode;
        pTempNode = pNextNode;
    }
    return pList;
}


//链表合并
List* ListFusion(List* pList1, List* pList2){
    ListNode* pTempNode;
    pTempNode = pList1->pFirstNode;
    while (pTempNode->pNextNode!= NULL) {
        pTempNode = pTempNode->pNextNode;
    }
    pTempNode->pNextNode = pList2->pFirstNode;
    pList1->length += pList2->length;
    return pList1;
}

//判断链表是否有环
bool JudgmentRingList(List* pList){
    ListNode* pTempNode, * pNextNode;
    pTempNode = pList->pFirstNode;
    pNextNode = pList->pFirstNode;
    while (pNextNode!= NULL && pNextNode->pNextNode!= NULL) {
        pTempNode = pTempNode->pNextNode;
        pNextNode = pNextNode->pNextNode->pNextNode;
        if (pTempNode == pNextNode) {
            return true;
        }
    }
    return false;
}


//遍历链表
Status ListTraverse(List* pList, void(*pVisit)(void* pData)){
    ListNode* pTempNode;
    pTempNode = pList->pFirstNode;
    while (pTempNode!= NULL) {
        pVisit(pTempNode->pData);
        pTempNode = pTempNode->pNextNode;
    }
    return OK;
}

//打印链表
Status ListPrint(List* pList){
    ListNode* pTempNode;
    pTempNode = pList->pFirstNode;
    while (pTempNode!= NULL){
        printf("%f->", pTempNode->pData);
        pTempNode = pTempNode->pNextNode;
    }
    printf("NULL\n");
    return OK;
}
