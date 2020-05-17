/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("---2019038058 Hongbeomsun---\n");
	initializeBST(&head);

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);		//초기화하는 재귀함수호출

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}


void inorderTraversal(Node* ptr)		//중위순회방식(recursive)
{
	if(ptr == NULL)		//현재위치가 NULL일경우 다음노드탐색불가
		return;

	inorderTraversal(ptr -> left);	//왼쪽으로 재귀 호출

	printf("[%d]  ",ptr->key);		//현재위치 출력(중위)

	inorderTraversal(ptr -> right);	//오른쪽으로 재귀 호출
}

void preorderTraversal(Node* ptr)		//전위순회방식(recursive)
{
	if(ptr == NULL)
		return;

	printf("[%d]  ",ptr->key);	//현재위치 출력(전위)

	preorderTraversal(ptr -> left);	//왼쪽으로 재귀 호출

	preorderTraversal(ptr -> right);	//오른쪽으로 재귀 호출
}

void postorderTraversal(Node* ptr)		//후위순회방식(recursive)
{
	if(ptr == NULL)
		return;
	
	postorderTraversal(ptr -> left);	//왼쪽으로 재귀 호출

	postorderTraversal(ptr -> right);	//오른쪽으로 재귀 호출

	printf("[%d]  ",ptr->key);			//현재위치 출력(후위)
}


int insert(Node* head, int key)			//비교 -> 작으면 왼쪽 크면 오른쪽
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


int deleteLeafNode(Node* head, int key)		//key값과 일치하는 leaf노드 delete
{
	Node* p;
	Node* n;
	p = head;		//부모
	n = head->left;	//현재위치

	while(n){
		if(key == n->key){		//동일한키를 찾았다면
			if(n -> left == NULL && n->right == NULL){		//leaf노드인지 확인
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
			else{
				printf("Not a Leaf node\n");
				return 0;
			}
		}
		p = n;
		if(key < p->key){
			n = p->left;
		}
		else
			n = p->right;
	}
	printf("NO KEY\n");	//n이 NULL인경우 -> 동일한 키를 찾지 못한경우
	return 0;

}

Node* searchRecursive(Node* ptr, int key)		//key값과 일치하는 노드 찾기(Node포인터를 return) Recursive방식
{
	if(ptr == NULL){	//일치하는 node를 찾지 못한경우
		return NULL;
	}

	if(ptr->key == key){
		return ptr;		//일치하는 node를 찾은경우
	}

	if(ptr->key > key)
		return searchRecursive(ptr->left,key);	//재귀탐색
	
	else
		return searchRecursive(ptr->right,key);
		
	
}

Node* searchIterative(Node* head, int key)		//Iterative방식 search
{
	Node* stack[1000];		//스택 생성
	int top = -1;	//스택의 top을 가리키는곳
	Node* p = head->left;	//현재 위치
	if(p != NULL)	//트리가 비어있지 않은경우
		stack[++top] = p;		//스택에 쌓기
	
	while(1){
		if(top >= 0)	//스택이 비어있지 않은경우
			p = stack[top--];	//pop
		else
			return NULL; //스택이 비어있으면 모든 탐색이 끝났으므로 값을찾지못함

		if(p -> key == key)	//일치한것을 찾았으면 포인터 리턴
			return p;
		
		
		if(p->key > key){
			if(p->left != NULL)
				stack[++top] = p->left;	//스택 왼쪽쌓기
			
		}
		
		else{
			if(p->right != NULL)
				stack[++top] = p->right;	//스택 오른쪽 쌓기
		}
	}
}


int freeBST(Node* head)			//전체node free
{
	if(head->right == head)
		return 1;

	if(head->left == NULL && head->right == NULL)
		free(head);
	
	if(head->left != NULL)
		freeBST(head -> left);

	if(head->left != NULL)
		freeBST(head -> right);

	
	return 1;
}





