/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
}listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main()
{
	printf("--2019038058 HongBeomsun--\n\n");
	char command;
	int key;
	headNode* headnode = NULL;
	headnode = initialize(headnode);
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;	//입력받은 key값 넣고
	node->link = h->first;	//NULL이었던 헤드링크를 이쪽으로
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* curr = h->first;

	while(curr != NULL){
		if(curr->link->key >= key){		//양방향연결리스트가 아니므로 다음의 데이터를 미리확인(지금생각해보니 prev를 썼어도 좋았을것같다)
			listNode* node = (listNode*)malloc(sizeof(listNode));
			node->key = key;
			node->link = curr->link;
			curr->link = node;
			return 1;
		}
		curr = curr->link;
	}
	free(curr);
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* curr = h->first;	//마지막node를 찾기위한 순회용
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	while(curr->link != NULL){
		curr = curr->link;		//끝부분에 도달
	}
	curr->link = node;
	
	node->link = NULL;
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h->first == NULL){		//헤드가 비어있으면 노드가 0개이므로 삭제할게 없음
		printf("No node to delete\n");
	}

	listNode *rm = h->first;		//지우기 위한 임시노드
	h->first = rm->link;		//헤드를 첫노드를 건너뛴곳에 지정
	free(rm);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* curr = h->first;
	while(curr != NULL){
		if(curr->link->key == key){		//키값이 동일한지 확인
			listNode *rm = curr->link;
			curr->link = rm->link;
			free(rm);
			return 1;
		}
		curr = curr->link;
	}
	free(curr);
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL){
		printf("No node to delete\n");
	}
	
	listNode *curr = h->first;
	listNode *rm = curr->link;
	if(curr->link == NULL)		//마지막노드탐색후 제거
	{
		h->first = NULL;
	}
	else{
		while(curr->link == NULL)
			curr = curr->link;
	
	curr->link = NULL;
	}
	free(rm);
	free(curr);
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* prev = NULL;					//이전저장용
	listNode* curr = h->first;				//현재있는곳
	listNode* next = NULL;					//다음지정

	while(curr != NULL){
		next = curr->link;					//다음주소로 미리 옮겨놓는다
		curr->link = prev;					//link를 뒤집어놓는다
		prev = curr;						//이전저장을 현재로 해준다
		curr = next;						//현재있는곳을 다음으로 지정한다
	}

	h->first = prev;						//헤드의 첫번째를 변경해줌


	free(curr);
	free(next);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

