/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	initialize(&headnode);
	printf("---2019038058 Hongbeomsun---\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	if(h->rlink == h->llink){
		h->rlink->llink = h->llink;
		h->llink->rlink = h->rlink;
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->rlink = h;
	node->llink = h->llink;
	node->llink->rlink = node;
	h->llink = node;

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if(h->rlink == h){	//리스트가 비어있음
		printf("Nothing to delete\n");
		return 0;
	}
	listNode *p;
	p = h->llink;
	p->llink->rlink = h;
	h->llink = p->llink;
	free(p);


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->llink = h;
	node->rlink = h->rlink;
	node->rlink->llink = node;
	h->rlink = node;

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if(h->rlink == h){	//리스트가 비어있음
		printf("Nothing to delete\n");
		return 0;
	}

	listNode *p;
	p = h->rlink;		//헤드를 다음거로 넘김
	p->rlink->llink = h;
	h->rlink = p->rlink;
	free(p);		//현재 픽한거 할당해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	if(h->rlink == h || h->rlink->rlink == h){	//리스트가 비어있거나 하나일때
		return 1;
	}
	listNode *curr;
	curr = h->rlink;
	listNode *prev;
	prev = h;
	listNode *next;
	next = curr->rlink;

	prev->llink = curr;		//헤드 미리 바꿔주기
	prev->rlink = prev->llink;

	while(1){

		curr->rlink = prev;		//순서변경
		curr->llink = next;

		if(curr == h){		//종료조건
			return 1;
		}

		prev = curr;		//prev,curr,next 옮겨주기
		curr = next;
		next = next->rlink;

	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode *p;
	p = h->rlink;
	
	listNode *node = (listNode*)malloc(sizeof(listNode));		//키할당
	node->key = key;

	if(node->key <= h->rlink->key){		//헤드 다음의 키가 더 크다면 삽입(예외처리)
		node->llink = h;
		node->rlink = h->rlink;
		node->rlink->llink = node;
		h->rlink = node;
		return 1;

	}
	
	while(1){
		if(p == h){		//지금 키가 제일 클 경우(못찾음) 맨뒤삽입
			node->rlink = h;
			node->llink = h->llink;
			node->llink->rlink = node;
			h->llink = node;
			return 1;
		}

		if(key <= p->key){		//자리를 찾은경우
			node->rlink = p;
			node->llink = p->llink;
			node->llink->rlink = node;
			p->llink = node;
			return 1;
		}

		p = p->rlink;

	}




	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode *p;
	p = h->llink;
	
	
	while(1){
		if(p == h){
			printf("No key\n");
			return 0;
		}

		if(key == p->key){	//키랑 같으면
			p->llink->rlink = p->rlink;		//노드제거
			p->rlink->llink = p->llink;
			free(p);
			return 1;
		}

		p = p->llink;

	}

	return 0;
}


