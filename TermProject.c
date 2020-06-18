#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VERTEX  20			//최대크기는 변경가능



typedef struct Vertex {				//연결리스트에 있는 하나의 node
	int num;
	struct Vertex* link;
} Vertex;

typedef struct VertexHead {			//연결리스트의 시작부
	Vertex* head;
} VertexHead;

typedef struct Graph {				//연결리스트의 목록
	VertexHead* vlist;
} Graph;

int vnum = 0;						//현재 vertex의 수

Graph* createGraph();
void destroyGraph(Graph *g);
void insertVertex(Graph* g);
void deleteVertex(Graph* g, int key);
void insertEdge(Graph* g);
void deleteEdge(Graph* g, int i1, int i2);
void depthFS(Graph *g);
void breadthFS(Graph *g);
void printGraph(Graph* g);



int main() {
	printf("--2019038058 HongBeomsun--\n\n");
	char command;			//메뉴선택
	int key;		//입력값 하나일경우
	int i1, i2;		//입력값 두개일경우

	Graph *g = createGraph();			//처음에 틀을 생성

	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Adjacent List                           \n");
		printf("----------------------------------------------------------------\n");
		printf("                             Print         = p\n");
		printf(" Insert Vertex = i           Delete Vertex = d\n");
		printf(" BreadthFS     = b           Insert Edge   = e\n");
		printf(" deleteEdge    = f           DepthFS       = s\n");
		printf(" destroyGraph  = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'p': case 'P':
			printGraph(g);
			break;
		case 'i': case 'I':
			insertVertex(g);
			break;
		case 'd': case 'D':
			printf("input key : ");
			scanf("%d", &key);
			deleteVertex(g, key);
			break;
		case 'f': case 'F':
			printf("input 1 : ");
			scanf("%d", &i1);
			printf("input 2 : ");
			scanf("%d", &i2);
			printf("\n");
			deleteEdge(g, i1, i2);
			break;
		case 'e': case 'E':
			insertEdge(g);
			break;
		case 'r': case 'R':
			destroyGraph(g);
			createGraph();
			break;
		case 's': case 'S':
			depthFS(g);
			break;
		case 'b': case 'B':
			breadthFS(g);
			break;

		case 'q': case 'Q':
			//freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;

}


Graph* createGraph() {
	Graph* g;
	g = (Graph*)malloc(sizeof(Graph)*MAX_VERTEX);			//사이즈만큼 할당
	if (g == NULL)
		return NULL;										
	for (int i = 0; i < MAX_VERTEX; i++) {
		g[i].vlist = NULL;									//나중에 체크하기위해서 null로 초기화
	}
	return g;
}


void destroyGraph(Graph* g) {
	for (int i = 0; i < MAX_VERTEX; i++) {
		if (g[i].vlist != NULL) {
			deleteVertex(g, i);								//연결리스트 노드제거는 deletevertex에서
			free(g[i].vlist->head);							//head와 시작부를 free
			free(g[i].vlist);
		}
	}
	free(g);												//틀까지 전부 제거한 후 vnum을 0으로(아무것도 없으므로)
	vnum = 0;
}

void insertVertex(Graph* g) {
	VertexHead* vhead = (VertexHead*)malloc(sizeof(VertexHead));		//새로운 헤드를 생성하여 공간할당
	g[vnum].vlist = vhead;
	vhead->head = NULL;													//참조해도 오류안나게 null로
	vnum++;																//새로들어왔으니 vnum 추가
}


void deleteVertex(Graph* g, int key) {
	Vertex* p = g[key].vlist->head;										//key 입력받고 해당vertex제거
	if (p == NULL) {
		return;
	}
	while (p != NULL) {
		deleteEdge(g, p->num, key);										//여기에 있는 edge도 싹 제거
		p = p->link;													//연결리스트에서 다음edge찾기

	}
	free(p);
}

void insertEdge(Graph* g) {												//두개 입력받고 연결
	int input1, input2;
	printf("edge 1 : ");
	scanf("%d", &input1);
	printf("edge 2 : ");
	scanf("%d", &input2);
	printf("\n");

	if (g[input1].vlist == NULL || g[input2].vlist == NULL) {			//둘중 하나라도 NULL이면 안됨
		printf("Error : no edge point\n");
	}


	Vertex* now1 = g[input1].vlist->head;								//첫번째 탐색용
	Vertex* new1 = (Vertex*)malloc(sizeof(Vertex));						//새로 할당하여 now다음으로 삽입
	if (now1 != NULL) {
		for (; now1->link != NULL; now1 = now1->link) {					//맨 끝으로 이동
		}
		now1->link = new1;
	}
	else
		g[input1].vlist->head = new1;									//맨 앞노드가 비어있을경우 바로 삽입
	new1->num = input2;													//숫자넣어주기
	new1->link = NULL;

	Vertex* now2 = g[input2].vlist->head;
	Vertex* new2 = (Vertex*)malloc(sizeof(Vertex));
	if (now2 != NULL) {
		for (; now2->link != NULL; now2 = now2->link) {
		}
		now2->link = new2;
	}
	else
		g[input2].vlist->head = new2;
	new2->num = input1;
	new2->link = NULL;


}

void deleteEdge(Graph* g, int i1, int i2) {
	if (g[i1].vlist == NULL || g[i2].vlist == NULL || g[i1].vlist->head == NULL || g[i2].vlist->head == NULL)		//조건미충족
		return;

	Vertex* p1 = g[i1].vlist->head;			//탐색용
	Vertex* p2 = g[i2].vlist->head;			//탐색용

	if (p1->num == i2) {							//일치하는 num을 찾게 된 경우
		if (p1->link != NULL)
			g[i1].vlist->head = p1->link;			//중간에 껴있으면 이전꺼와 다음것을 연결하여 가운데를 생략시켜버림
		else
			g[i1].vlist->head = NULL;				//뒤에 아무것도없으면 NULL로 처리

	}

	if (p2->num == i1) {
		if (p2->link != NULL) {
			g[i2].vlist->head = p2->link;
		}
		else
			g[i2].vlist->head = NULL;

	}

	Vertex* par1 = p1;
	Vertex* par2 = p2;
	p1 = p1->link;
	p2 = p2->link;

	while (p1 != NULL) {
		if (p1->num == i2) {
			par1->link = p1->link;
			free(p1);
			break;
		}
		par1 = p1;
		p1 = p1->link;
	}

	while (p2 != NULL) {
		if (p2->num == i1) {
			par2->link = p2->link;
			free(p2);
			break;
		}
		par2 = p2;
		p2 = p2->link;
	}

}

//스택, DFS
int visited[MAX_VERTEX];				//0이면 방문x , 1이면 방문
int stack[100];								//스택저장
int top = 0;								//stack의 top

int pop() {
	return stack[top--];
}

void push(int num) {
	stack[++top] = num;
}

void depthFS(Graph *g) {
	top = 0;
	memset(stack, -1, 100);						//스택전체 -1로 초기화
	for (int i = 0; i < MAX_VERTEX; i++) {		//memset 알수없는오류로 for문으로 초기화
		visited[i] = 0;
	}
	stack[0] = 0;								//stack의 첫번째는 v0

	Vertex* p = g[0].vlist->head;
	while (top != -1) {
		int curr = pop();						//우선 stack의 맨위에 있는것 빼서 curr에 저장

		if (!visited[curr]) {					//방문안한거면 방문한거로 만들어주고 바로출력
			visited[curr] = 1;
			printf("%d -> ", curr);
			p = g[curr].vlist->head;			//다음노드 탐색
			while (p != NULL) {					//계속탐색가능한경우 push 반복
				if (visited[p->num] == 0)
					push(p->num);
				p = p->link;
			}
		}
	}
	printf("END\n");
}

//스택,dfs끝


//큐, bfs 시작

int queue[100];
int front = 0;		//현재위치
int rear = 1;		//큐의 끝

int dequeue(){
	return queue[front++];
}

void enqueue(int num){
	queue[++rear] = num;
}

void breadthFS(Graph *g) {

	memset(queue, -1, 100);						//큐전체 -1로 초기화
	for (int i = 0; i < MAX_VERTEX; i++) {
		visited[i] = 0;
	}
	int curr = 0;
	queue[0] = 0;
	visited[0] = 1;
	Vertex* p = g[0].vlist->head;

	while(front <= rear){						//큐의 탈출조건, front는 현재위치, rear는 큐의 마지막위치
		curr = dequeue();
		if(!visited[curr]){						//방문안했으면 1로만들고 출력
			visited[curr] = 1;
			printf("%d -> ", curr);
			p = g[curr].vlist->head;
			while (p != NULL) {					//큐에 계속쌓는다.
				if (visited[p->num] == 0)
					enqueue(p->num);
				p = p->link;
			}
		}
	}
	printf("END\n");

}

//큐, bfs 끝


void printGraph(Graph* g) {
	for (int i = 0; i < vnum; i++) {
		printf("[%d ] : ", i);

		Vertex* now;
		for (now = g[i].vlist->head; now != NULL; now = now->link)
			printf("%3d ->   ", now->num);

		printf("NULL");
		printf("\n");
	}

}