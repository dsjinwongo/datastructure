/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;									//char���� element�� ����Ѵ�
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();								//���� ť ����
int freeQueue(QueueType *cQ);							//�޸� ����
int isEmpty(QueueType *cQ);								//ť�� ����ִ��� Ȯ��
int isFull(QueueType *cQ);								//ť�� ���� �� �ִ��� Ȯ��
void enQueue(QueueType *cQ, element item);				//ť�� ���� �Է�
void deQueue(QueueType *cQ, element* item);				//ť�� ���� ����
void printQ(QueueType *cQ);								//����ť ���
void debugQ(QueueType *cQ);								//ť ���� ǥ��

element getElement();


int main(void)
{
	printf("------------------[������]------------[2019038095]--------------------\n");
	QueueType *cQ = createQueue();						//����ť ����
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
			freeQueue(cQ);									//�Ҵ�� �޸� ����
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

QueueType *createQueue()								//�޸𸮸� �Ҵ��Ͽ� ����ť ����
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement()									//element(char)���� �Է¹ް� ��ȯ
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)								/*����ť�� ����ִ��� Ȯ���ϰ� ���������
														���� ������ ����ϰ� 0�� ��ȯ*/
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
int isFull(QueueType *cQ)								/*����ť�� ���� �� �ִ��� Ȯ���ϰ� ���� ��������
														���� ������ ����ϰ� 0�� ��ȯ*/
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
void enQueue(QueueType *cQ, element item)				//����ť�� ���� ���ִ��� Ȯ���ϰ� ��ȯ���� 0�� �ƴϸ� ���� �Է�
{
	int check;
	check = isFull(cQ);
	if (check == 1)
	{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;		//rear 1 �����ϰ� ���� ä��
		cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)				//����ť�� ����ִ��� Ȯ���ϰ� ��ȯ���� 0�� �ƴϸ� ���� �����ϰ� �ʱ�ȭ
{
	int check;
	check = isEmpty(cQ);
	if (check == 1)
	{
		cQ->queue[cQ->front] = '?';
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;	//front�� ����Ű�� ĭ�� ��� �� 1 ����
	}
}


void printQ(QueueType *cQ)								//����ť�� ���ҵ��� ���
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;			//front+1�� ��ġ���� rear+1�� ��ġ�� Ž���ϸ� ���
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)								//����ť ���� ����Ͽ� ���¸� Ȯ���Ѵ�.(front, rear�� ��ġ)
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