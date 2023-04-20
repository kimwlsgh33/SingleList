//
//  main.c
//  singleList
//
//  Created by 김진호 on 2023/02/26.
//

/*
 전체 리스트 출력 함수
 
 노드 추가 함수 ( 글로 작성 )
 - free 너무 신경 쓰지 말기,
 
 전체 리스트 삭제 함수
 
 main에서 테스트 코드 작성
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char szData[64];
    // 형선언시, struct 예약어를 생략할 수 없음
    struct NODE* pNext;
} NODE;

// 연결 리스트 현재 포인터
NODE* g_pHead = NULL;


// 연결 리스트 전체 데이터 출력
void PrintList02(void){
    // 현재 포인터를 복사 ( g_pHead는 새로운 데이터를 연결하는 용도로 사용해야하므로, 출력시에 변조되면 안된다. )
    NODE* pHead = g_pHead;
    
    while(pHead != NULL)
    {
        printf("[%p] %s, next[%p]\n", pHead, pHead->szData, pHead->pNext);
        pHead = pHead->pNext;
    }
    putchar('\n');
}

// 데이터 받아서, NODE 생성
int InsertNewNode(char* pszData)
{
    // 구조체 만큼의 메모리할당, malloc이 반환하는 주소를 구조체를 가리키는 포인터로 강제 형전환(지정) <stdlib.h>
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    
    // pNode 메모리를, 구조체 크기만큼 0으로 초기화 <string.h>
    memset(pNode, 0, sizeof(NODE));
    
    // pNode의 szData에, pszData 문자열 값 복사
    // strcpy_s(pNode->szData, pszData); // _s
    strlcpy(pNode->szData, pszData, sizeof(pNode->szData));
    
    // 어디에 추가???
    if(g_pHead == NULL)
        g_pHead = pNode;
    else {
        // 1. 새로운 노드에, 기존 g_pHead 주소저장
        pNode->pNext = g_pHead;
        // 2. g_pHead에, 새로운 노드 주소저장
        g_pHead = pNode;
    }
    
    return 1;
}

void ReleaseList02(void)
{
    NODE* pTmp = g_pHead;
    while(pTmp != NULL){
        NODE* pDelete = pTmp;
        pTmp = pTmp->pNext;
        
        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
        free(pDelete);
        // free(g_pHead);
        g_pHead = pTmp;
    }
}

int FindData02(char* szData){
    NODE* pTmp = g_pHead;
    
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, szData) == 0)
            return 1;
        pTmp = pTmp->pNext;
    }
    
    return 0;
}

int DeleteData02(char* pszData){
    NODE* pTmp = g_pHead;
    NODE* pPrev = NULL;
    
    while(pTmp != NULL)
    {
        if(strcmp(pTmp->szData, pszData) == 0)
        {
            // 삭제
            printf("DeleteData(): [%p] %s", pTmp, pTmp->szData);
            pPrev->pNext = pTmp->pNext;
            return 1;
        }
        pPrev = pTmp;
        pTmp = pTmp->pNext;
    }
    
    return 0;
}

int main_lecture(int argc, const char * argv[]) {
    // List 테스트를 위한 코드
    InsertNewNode("TEST01");
    PrintList02();
    InsertNewNode("TEST02");
    PrintList02();
    InsertNewNode("TEST03");
    PrintList02();
    
    if(FindData02("TEST01") == 1)
        printf("FindData(): TEST01 found\n");
    if(FindData02("TEST02") == 1)
        printf("FindData(): TEST02 found\n");
    if(FindData02("TEST03") == 1)
        printf("FindData(): TEST03 found\n");
    
    DeleteData02("TEST01");
    
    ReleaseList02();
    return 0;
}
