/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		50
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
	initializeBST(&head);
	printf("---2019038058 Hongbeomsun---\n");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}


void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);		//중위순회방식이므로 left와 right사이에서 출력
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)		//반복중위순회
{
	Node* p = node;		//현재 지목 포인터
	while(1){
		while(p != NULL){		//p가 존재한다면 push하고 다음(left)로 이동
			push(p);
			p = p->left;
		}
		if(top >= 0){		//스택에 값이 남아있는경우 (!stack.empty)
			p = pop();		//팝하고 pop한 결과를 가져온다음 출력
			printf(" [%d] ",p->key);
			p = p->right;	//출력 후 right로 계속이동하면 된다,
		}
		else			//스택에 값이 없는경우
			break;
	}
	for (int i = 0; i < MAX_STACK_SIZE; i++)		//스택초기화
		stack[i] = NULL;
	top = -1;
	return;
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)		//queue로 BFS탐색
{
	enQueue(ptr);		//head->left꺼 미리 queue로 넣어놓기
	while (front < rear) {		//queue탈출조건은 front와 rear값이 일치하거나 front가 더 큰 경우
		printf(" [%d] ", deQueue()->key);		//전위출력과 동시에 큐에서 제거
		if (queue[front]->left != NULL) {		//값이 있으면 큐에 값을 쌓아놓기
			enQueue(queue[front]->left);
		}
		if (queue[front]->right != NULL) {
			enQueue(queue[front]->right);
		}
	}
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {		//큐 초기화
		queue[i] = NULL;
	}
	rear = -1;
	front = -1;
	return;
}


int insert(Node* head, int key)
{
	Node* new = (Node*)malloc(sizeof(Node));		//새로운 구조체 생성해서 동적할당
	new -> left = NULL;		//좌,우를 NULL로 만들고
	new -> right = NULL;
	new -> key = key;		//들어온 key값 대입
	
	Node* p;	//부모 지목하는곳
	Node* n;	//현재 있는곳
	p = NULL;	//root노드의 부모는 없음
	n = head->left;		//시작주소


	while(n){		//n이 NULL이면 while문 탈출
		if(key == n->key){		//키가 동일할경우 판독불가 -> 대입하지 않는다
			printf("Err : same key\n");
			free(new);			//넣을필요가 없으므로 할당해제
			return 0;
		}

		p = n;		//부모노드를 현재 위치로 만들고 아래 if문에서 n을 다음으로 옮기기
		if(key < p->key){
			n = p->left;
		}
		else
			n = p->right;
	}

	if(p){		//p가 NULL이 아닌경우 (n은 현재 NULL이기 때문에 참조할 수 없기 때문)
		if(key<p->key)
			p->left = new;
		else
			p->right = new;
	}
	else
		head->left = new;

}


int deleteNode(Node* head, int key)
{
	Node* p;
	Node* n;
	p = head;		//부모
	n = head->left;	//현재위치

	while(n){
		if(key == n->key){		//동일한키를 찾았다면
			if(n -> left == NULL && n->right == NULL){		//leaf노드인경우
				printf("[%d] deleted\n",n->key);
				if(p->left == n){		//제거했기때문에 부모노드의 지목되는걸 제거시킴.
					p->left = NULL;
					free(n);
				}
				else{
					p->right = NULL;
					free(n);
				}
				return 1;
			}

			else if (n->left == NULL || n->right == NULL){		//둘중하나만 있는경우
				printf("[%d] deleted\n",n->key);
				if(n->left == NULL && p->left == n){
					p->left = n->left;
					free(n);
				}
				else if(n->left == NULL && p->right == n){
					p->right = n->left;
					free(n);
				}
				else if(n->left == NULL && p->left == n){
					p->left = n->left;
					free(n);
				}
				else if(n->left == NULL && p->left == n){
					p->left = n->left;
					free(n);
				}
				
				return 1;
			}

			else{		//left right 둘다 값이 존재하는경우
				printf("[%d] deleted\n",n->key);
				if(p->left == n){		//제거했기때문에 부모노드의 지목되는걸 변경.
					p->left = n->left;
					
					free(n);
				}
				else{
					p->right = n->right;
					free(n);
				}
				return 1;
			}

		}
		p = n;							//다음값으로 이동
		if(key < p->key){
			n = p->left;
		}
		else
			n = p->right;
	}
	printf("NO KEY\n");	//n이 NULL인경우 -> 동일한 키를 찾지 못한경우
	return 0;

	return 0;
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()		//pop에서 값을 리턴한 후 top--
{
	return stack[top--];
}

void push(Node* aNode)
{
	stack[++top] = aNode;		//push하기전 top을 ++시켜줘야 범위오류가 안난다
}


void printStack() {

}

Node* deQueue()
{
	front++;					//큐에서 제거(front를 한칸앞으로)
	return queue[front];
}

void enQueue(Node* aNode)
{
	rear++;
	queue[rear] = aNode;		//큐에 삽입하면서 인덱스를 증가
}





