/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;									//char형을 element가 대신한다
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();								//원형 큐 생성
int freeQueue(QueueType *cQ);							//메모리 해제
int isEmpty(QueueType *cQ);								//큐가 비어있는지 확인
int isFull(QueueType *cQ);								//큐가 가득 차 있는지 확인
void enQueue(QueueType *cQ, element item);				//큐에 원소 입력
void deQueue(QueueType *cQ, element* item);				//큐의 원소 제거
void printQ(QueueType *cQ);								//원형큐 출력
void debugQ(QueueType *cQ);								//큐 상태 표시

element getElement();


int main(void)
{
	printf("------------------[이진원]------------[2019038095]--------------------\n");
	QueueType *cQ = createQueue();						//원형큐 생성
	element data;

	char command;

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			freeQueue(cQ);									//할당된 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');



	return 1;
}
int freeQueue(QueueType *cQ)
{
	if (cQ != NULL)
	{
		free(cQ);
		return 1;
	}
	else
		return 0;
}

QueueType *createQueue()								//메모리를 할당하여 원형큐 생성
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()									//element(char)형을 입력받고 반환
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)								/*원형큐가 비어있는지 확인하고 비어있으면
														다음 문장을 출력하고 0을 반환*/
{
	if (cQ->front == cQ->rear)
	{
		printf("\nQueue is empty!\n");
		return 0;
	}
	else
		return 1;
}

/* complete the function */
int isFull(QueueType *cQ)								/*원형큐가 가득 차 있는지 확인하고 가득 차있으면
														다음 문장을 출력하고 0을 반환*/
{
	if ((cQ->front) == (cQ->rear + 1) % MAX_QUEUE_SIZE)
	{
		printf("\nQueue is full!\n");
		return 0;
	}
	else
		return 1;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)				//원형큐가 가득 차있는지 확인하고 반환값이 0이 아니면 값을 입력
{
	int check;
	check = isFull(cQ);
	if (check == 1)
	{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;		//rear 1 증가하고 값을 채움
		cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)				//원형큐가 비어있는지 확인하고 반환값이 0이 아니면 값을 제거하고 초기화
{
	int check;
	check = isEmpty(cQ);
	if (check == 1)
	{
		cQ->queue[cQ->front] = '?';
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;	//front가 가르키는 칸을 비운 후 1 증가
	}
}


void printQ(QueueType *cQ)								//원형큐의 원소들을 출력
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;			//front+1의 위치부터 rear+1의 위치를 탐색하며 출력
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)								//원형큐 정보 출력하여 상태를 확인한다.(front, rear의 위치)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}