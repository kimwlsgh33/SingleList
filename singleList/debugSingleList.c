//
//  debugSingleList.c
//  singleList
//
//  Created by 김진호 on 2023/02/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char szData[64];
    struct NODE* pNext;
} NODE;

// dummy head
NODE g_head = {0};
// tail pointer
//NODE* g_pTail = &g_head;
NODE* g_pTail = 0;


// 리스트가 비어있는지 확인
int IsEmpty(void){
    if(g_head.pNext == NULL)
        return 1;
    return 0;
}

void PrintList(void){
    NODE* pHead = g_head.pNext;
    
    while(pHead != NULL)
    {
        printf("[%p] %s, next[%p]\n", pHead, pHead->szData, pHead->pNext);
        pHead = pHead->pNext;
    }
    putchar('\n');
}

int InsertAtHead(const char* pszData)
{
    // heap영역 메모리 동적할당
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    // 할당 받은 메모리 초기화
    memset(pNode, 0, sizeof(NODE));
    // 데이터 Write
    strlcpy(pNode->szData, pszData, sizeof(pNode->szData));
    
    if(IsEmpty())
    {
        g_head.pNext = pNode;
        g_pTail = pNode;
    }
    else
    {
        // 새로운 노드에, dummy 앞의 노드주소 저장
        pNode->pNext = g_head.pNext;
        // dummy에 새로운 노드주소 저장
        g_head.pNext = pNode;
    }
    
    return 1;
}

int InsertAtTail(const char* pszData)
{
    // heap영역 메모리 동적할당
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    // 할당 받은 메모리 초기화
    memset(pNode, 0, sizeof(NODE));
    // 데이터 Write
    strlcpy(pNode->szData, pszData, sizeof(pNode->szData));
    
    //NODE* pTmp = &g_head;
    
    //while(pTmp->pNext != NULL)
    //    pTmp = pTmp->pNext;
    
    // 마지막 노드 다음에, 새로운 노드 주소 저장
    //pTmp->pNext = pNode;
    //g_pTail->pNext = pNode;
    if(IsEmpty())
        g_head.pNext = pNode;
    else
        g_pTail->pNext = pNode;
    
    g_pTail = pNode;
    // 마지막 노드 포인터 주소경변경
    //g_pTail = pNode;
   
    return 1;
}

//int FindData(const char* pszData)
NODE* FindData(const char* pszData)
{
    NODE* pCur = g_head.pNext;
    NODE* pPrev = &g_head;
    while(pCur != NULL)
    {
        if(strcmp(pCur->szData, pszData) == 0)
            return pPrev; // single linked list 이므로, 전 노드 반환 ( 삭제시 필요, Dummy 있어야 사용가능 )
        pCur = pCur->pNext;
        pPrev = pPrev->pNext;
    }
    return 0;
}

int DeleteData(const char* pszData)
{
    /*
    NODE* pCur = g_head.pNext;
    NODE* pPrev = &g_head;
    while(pCur != NULL)
    {
        if(strcmp(pCur->szData, pszData) == 0){
            printf("DeleteData(): %s\n", pCur->szData);
            pPrev->pNext = pCur->pNext;
            free(pCur);
            return 1;
        }
        pCur = pCur->pNext;
        pPrev = pPrev->pNext;
    }
     */
    NODE* pPrev = FindData(pszData);
    if(pPrev != 0)
    {
        
        NODE* pDelete = pPrev->pNext;
        // 만약 삭제할 노드가, 마지막 노드라면, tail 포인터 수정
        // if(pDelete->pNext == 0) g_pTail = pPrev;
        if(pDelete == g_pTail) g_pTail = pPrev;
        pPrev->pNext = pDelete->pNext;
        
        printf("DeleteData(): %s\n", pDelete->szData);
        free(pDelete);
        return 1;
    }
    
    return 0;
}

void ReleaseList(void)
{
    NODE* pTmp = g_head.pNext;
    
    while(pTmp != NULL){
        NODE* pDelete = pTmp;
        pTmp = pTmp->pNext;
        
        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
        free(pDelete);
        // free(g_pHead);
    }
    
    // 모든 노드를 삭제했지만, 이전의 주소를 저장하고 있음
    // printf("g_head.pNext : %p\n", g_head.pNext);
    // 초기화
    g_head.pNext = 0;
    g_pTail = &g_head;
    // p화rintf("g_head.pNext : %p\n", g_head.pNext);
}

void PushData(char *pszData)
{
    InsertAtHead(pszData);
}

// Stack구조의 리스트에서 데이터 하나 꺼냄
// 리스트를 사용하는 측에서, 데이터를 삭제하는 것 || 함수 내부에서 삭제하는 것, 어떤 것이 더 좋은가?
// 구조체 주소값을 저장할 매개변수 선언 ( 포인터 )
int PopData(NODE* pPopNode)
{
    // 첫번째 노드의 주소 ( head 제외 )
    NODE* sp = g_head.pNext;
    if(IsEmpty()) return 0;
    
    // 메모리 복사 sp => pPopNode
    memcpy(pPopNode, sp, sizeof(NODE));
    
    // 연결리스트에서 첫번째 노드 제거하기
    g_head.pNext = sp->pNext;
    
    // 첫번째 노드 메모리 삭제
    free(sp);
    
    return 1;
}

void Enqueue(char* pszData){
    // 마지막에 넣음
    InsertAtTail(pszData);
}

int Dequeue(NODE* pQueueNode){
    // 첫번째 노드 주소 저장
    // NODE* qp = g_head.pNext;
    // 매개변수로 받은 주소에, 첫번째 노드 메모리 복사
    // memcpy(pQueueData, qp, sizeof(NODE));
    
    // 연결 리스트에서 첫 번째 노드 제외
    // g_head.pNext = qp->pNext;
    // 첫 번재 노드 메모리 해제
    // free(qp);
    return PopData(pQueueNode);
}

void TestQueue(void){
    // Queue 테스트를 위한 코드
    puts("*** QueueData() ***");
    Enqueue("Queue01");
    PrintList();
    Enqueue("Queue02");
    PrintList();
    Enqueue("Queue03");
    PrintList();
    
    NODE node = {0};
    
    Dequeue(&node);
    printf("node.szData : %s\n", node.szData);
    PrintList();
    Dequeue(&node);
    printf("node.szData : %s\n", node.szData);
    PrintList();
    Dequeue(&node);
    printf("node.szData : %s\n", node.szData);
    PrintList();
    if(Dequeue(&node) == 0) puts("Empty");
}

void TestStack(void){
    // Stack 테스트를 위한 코드
    puts("*** PushData() ***");
    PushData("Stack01");
    PrintList();
    PushData("Stack02");
    PrintList();
    PushData("Stack03");
    PrintList();
    
    // NODE* pPopNode : 구조체 포인터
    NODE node = {0};
    PopData(&node);
    printf("node->szData : %s\n", node.szData);
    PrintList();
    PopData(&node);
    printf("node->szData : %s\n", node.szData);
    PrintList();
    PopData(&node);
    printf("node->szData : %s\n", node.szData);
    PrintList();
}

int main(int argc, const char * argv[]) {
    // List 테스트를 위한 코드
    puts("*** InsertAtHead() ***");
    InsertAtHead("TEST01");
    InsertAtHead("TEST02");
    InsertAtHead("TEST03");
    PrintList();
    
    if(FindData("TEST01") == 1)
        printf("FindData(): TEST01 found\n");
    if(FindData("TEST02") == 1)
        printf("FindData(): TEST02 found\n");
    if(FindData("TEST03") == 1)
        printf("FindData(): TEST03 found\n");
    printf("Tail [%p]\n", g_pTail);
    
    DeleteData("TEST01");
    PrintList();
    DeleteData("TEST02");
    PrintList();
    DeleteData("TEST03");
    PrintList();
    
    puts("*** InsertAtTail() ***");
    InsertAtTail("TEST01");
    InsertAtTail("TEST02");
    InsertAtTail("TEST03");
    PrintList();
    
    if(FindData("TEST01") == 1)
        printf("FindData(): TEST01 found\n");
    if(FindData("TEST02") == 1)
        printf("FindData(): TEST02 found\n");
    if(FindData("TEST03") == 1)
        printf("FindData(): TEST03 found\n");
    
//    DeleteData("TEST01");
//    PrintList();
//    DeleteData("TEST02");
//    PrintList();
//    DeleteData("TEST03");
//    PrintList();
    
    ReleaseList();
    InsertAtHead("TEST99");
    PrintList();
    ReleaseList();
    return 0;
}
