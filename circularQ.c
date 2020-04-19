/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	printf("2019038058 Hongbeomsun\n\n");
	QueueType *cQ = createQueue();
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));	//원형큐 할당
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear){	//front와 rear 위치가 같으면 queue가 비어있다는 뜻
		return 1;
	}
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if(((cQ->rear) + 1) % MAX_QUEUE_SIZE == cQ->front){	//큐의 끝부분에 1을더한값과 큐의 최댓값이 front의 위치로 나누어떨어지면 큐가 꽉찼다는뜻
		return 1;										//즉 front자리를 제외한 모든부분이 max_queue_size만큼 있다는것
	}
    return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)){
		printf("-- Queue FULL --\n");
	}
	else{
		cQ->rear = (cQ->rear+1) % MAX_QUEUE_SIZE;		//큐가 꽉차지않았을경우 rear를 하나 증가시키되, maxsize에 도달하면 0으로 되게한다.
		cQ->queue[cQ->rear] = item;						//그리고 하나증가시킨 rear인덱스에 입력한 값을 넣는다
	}

}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)){
		printf("-- Queue EMPTY --\n");
		
	}
	else{
		cQ->front = ((cQ->front) + 1) % MAX_QUEUE_SIZE;	//큐가 비어있지 않은경우, front값을 증가시키되, maxsize에 도달하면 0으로 되게 한다.
	}
	
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}