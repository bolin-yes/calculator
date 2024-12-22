
#include"list.h"

#define DEBUG 1
//创建结点
ListNode* ListMakeNode(List* pList, void* pData) {
    ListNode* pNewNode;
    pList->elementSize=sizeof(pData);
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
    pList->length=1;
    pNewNode->pNextNode = NULL;
    return pNewNode;
}

//释放结点
void ListFreeNode(ListNode* pNode) {
    if (pNode == NULL) {
        return;
    }
	#if DEBUG
	printf("释放结点：%d\n", *(int*)(pNode->pData));
	#endif
    free(pNode->pData);
    free(pNode);
    return;
}

//清空链表
void ListClear(List* pList) {
    ListNode* pCurrentNode, * pNextNode;
    pCurrentNode = pList->pFirstNode;
    int len=0;//用于判断链表释放内存时何时应该停止
    while (pCurrentNode != NULL&&len<pList->length) { //释放结点，但不释放链表(即保留头结点)
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
    List*List1=(List*)malloc(sizeof(List));
    ListNode* pTempNode=pList->pFirstNode;
    while (pTempNode->pNextNode!= NULL)
    {
        pTempNode = pTempNode->pNextNode;
    }
    List1->pFirstNode=ListMakeNode(List1,pTempNode->pData);
    pTempNode = pList->pFirstNode->pNextNode;
    while (pTempNode!= NULL){
        ListAppendToHead(List1,pTempNode->pData);
        pTempNode = pTempNode->pNextNode;
    }
    return List1;
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
        printf("%d->", *(int*)(pTempNode->pData));
        pTempNode = pTempNode->pNextNode;
    }
    printf("NULL\n");
    return OK;
}

int main(){
    int *p= (int*)malloc(sizeof(int)),*q = (int*)malloc(sizeof(int));
    *p=1,*q=1;
    List* list1=(List*)malloc(sizeof(List)) ;
    list1->elementSize=sizeof(int);
    list1->pFirstNode=ListMakeNode(list1,p);
    List*list2=(List*)malloc(sizeof(List)) ;
    list2->elementSize=sizeof(int);
    list2->pFirstNode=ListMakeNode(list2,q);


//先对list1进行操作，再对list2进行操作
    ListAppendToHead(list1,p);
    (*p)++;
    ListAppendToEnd(list1,p);
    (*p)++;
    ListPrint(list1);
    ListInsertAfter(list1,list1->pFirstNode,p);
    (*p)++;
    ListPrint(list1);
    ListAppendToEnd(list1,p);
    (*p)++;
    ListPrint(list1);
    ListAppendToHead(list1,p);
    (*p)++;
    ListPrint(list1);
    ListDeleteFirstNode(list1);
    ListPrint(list1);
    ListDeleteLastNode(list1);
    ListPrint(list1);
    ListDeleteNode(list1,list1->pFirstNode);
    ListPrint(list1);

//对list2进行操作
    ListAppendToHead(list2,q);
    (*q)++;
    ListAppendToEnd(list2,q);
    (*q)++;
    ListPrint(list2);
    ListInsertAfter(list2,list2->pFirstNode,q);
    (*q)++;
    ListPrint(list2);
    ListAppendToEnd(list2,q);
    (*q)++;
    ListPrint(list2);
    ListAppendToHead(list2,q);
    (*q)++;
    ListPrint(list2);
    ListDeleteFirstNode(list2);
    ListPrint(list2);
    ListDeleteLastNode(list2);
    ListPrint(list2);
    ListDeleteNode(list2,list2->pFirstNode);
    ListPrint(list2);

//合并两个链表
    List* list3 = ListFusion(list1,list2);
    ListPrint(list3);

//将list3转换为环形链表
    ListRound(list3);

//判断list3是否为环形链表
    bool flag = JudgmentRingList(list3);
    if(flag == true){
        printf("list3是环形链表\n");
    }else{
        printf("list3不是环形链表\n");
    }

//反转函数测试
    printf("反转函数测试\n");
    int *z = (int*)malloc(sizeof(int));
    *z=2;
    List* list4 = (List*)malloc(sizeof(List));
    list4->pFirstNode=ListMakeNode(list4,z);
    ListAppendToEnd(list4,z);
    (*z)++;
    ListAppendToHead(list4,z);
    (*z)++;
    ListInsertAfter(list4,list4->pFirstNode,z);
    ListPrint(list4);
    list4 = ListReverse(list4);
    ListPrint(list4);

//清空链表

    ListClear(list1);
    ListClear(list2);
    free(list1);
    free(list2);


    return 0;




    
}