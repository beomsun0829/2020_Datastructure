/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
	initialize(&headnode);
	printf("--2019038058 HONGBEOMSUN--\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
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

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	if (*h != NULL)
		freeList(*h);
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	*h = temp;
	temp->first = NULL;
	return 0;
}

int freeList(headNode* h) {
	listNode* p = h->first;
	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));

	node->key = key;
	if(h->first == NULL){
		node->llink = NULL;	//NULL이었던 헤드링크를 이쪽으로
		h->first = node;
		node->rlink = NULL;
	}

	else{
		listNode* p;
		p = h->first;
		while(p->rlink != NULL){
			p = p->rlink;
		}

		p->rlink = node;
		node->llink = p;
		node->rlink = NULL;
	}
	
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode *p;
	p = h->first;
	if(p==NULL){
		printf("---NOTHING TO DELETE---\n");
		return 0;
	}

	else if(p->rlink == NULL){	//리스트에 하나밖에 없는경우
		h->first = NULL;
		free(p);
		return 0;
	}

	while(p->rlink != NULL){
		p = p->rlink;
	}
	
	p->llink->rlink = NULL;

	free(p);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));

	node->key = key;	//입력받은 key값 넣고
	if (h->first == NULL) {
		node->llink = NULL;	//NULL이었던 헤드링크를 이쪽으로
		h->first = node;
		node->rlink = NULL;
	}

	else {
		h->first->llink = node;
		node->rlink = h->first;
		h->first = node;
		node->llink = NULL;
	}


	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode *p;


	if(h->first == NULL){
		printf("---NOTHING TO DELETE---\n");
		return 0;
	}



	p = h->first;
	h->first = p->rlink;
	free(p);
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode *p;
	listNode *prev;
	listNode *next;

	if(h->first == NULL){		//리스트가 비었을경우
		return 0;
	}

	else if(h->first->rlink == NULL){		//리스트에 하나밖에없는경우
		return 0;
	}

	prev = h->first;
	p = prev->rlink;

	if(p->rlink == NULL){	//리스트에 두개가 있는경우(next를 쓸수없어 예외처리)
		p->rlink = prev;
		prev->llink = p;
		p->llink = NULL;
		prev->rlink = NULL;
		h->first = p;
		return 1;
	}

	next = p->rlink;

	
	prev -> rlink = NULL;
	prev -> llink = p;

	while(1){
		p->rlink = prev;
		p->llink = next;

		if(next->rlink == NULL){	//끝이면
			next -> rlink = p;
			next -> llink = NULL;
			h->first = next;
			return 1;
		}
		prev = p;			//다음 순서검색
		p = next;		
		next = next->rlink;
	}
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode *p;
 
	p = h->first;

	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	

	if(h->first == NULL){	//비어있는경우
		node->llink = NULL;
		h->first = node;
		node->rlink = NULL;
		return 0;
	}
	else if(h->first->key >= key){	//처음에 넣어야할경우
		h->first->llink = node;
		node->rlink = h->first;
		h->first = node;
		node->llink = NULL;
		return 0;
	}


	while(1){

		if(key <= p->key){
			node->llink = p->llink;
			node->rlink = p;
			p->llink->rlink = node;
			p->llink = node;
			return 0;
		}

		else if(p->rlink == NULL){	//맨뒤일경우
			p->rlink = node;
			node->llink = p;
			node->rlink = NULL;
			return 0;
		}

		p = p->rlink;
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode *p;
	listNode *deltemp;
	p = h->first;

	if(h->first == NULL){			//리스트가 비어있는경우
		printf("---LIST EMPTY---\n");
		return 0;
	}

	else if(p->key == key){		//삭제할 노드가 맨 처음에 있는경우

		if(p->rlink == NULL){
			h->first = NULL;
			free(p);
			return 1;
		}

		p->rlink->llink = NULL;
		h->first = p->rlink;
		free(p);
		return 1;
	}
	


	while(1){
		if(p->rlink == NULL){		//검색했는데 key랑 같은게 없는경우
			printf("---NO KEY---\n");
			return 0;
		}

		else if(p->rlink->key == key){		
			deltemp = p->rlink;
			if(p->rlink->rlink == NULL){		//삭제할 노드가 맨끝에 잇는경우
				p->rlink = NULL;
				free(deltemp);
				return 1;
			}


			p->rlink->rlink->llink = p;			//삭제할 노드가 중간에있는경우
			p->rlink = deltemp->rlink;
			free(deltemp);
			return 1;
		}

		p = p->rlink;
		
	}
	


	return 1;
}


