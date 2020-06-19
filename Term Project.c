#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20

typedef struct Vertex {
	int num;
	struct Vertex* link;
} Vertex;

typedef struct VertexHead {
	Vertex* head;
} VertexHead;

typedef struct Graph {
	VertexHead* vlist;
} Graph;

void createGraph(Graph** g);
void destoryGraph(Graph** g);
void insertVertex(VertexHead* vh);
int deleteVertex(VertexHead* vh, int v);
void insertEdge(VertexHead* vh);
void deleteEdge(VertexHead* vh);
int depthFS(VertexHead* vh);
int breadthFS(VertexHead* vh);
void printGraph(VertexHead* vh);

int deleteEdge_delete(VertexHead* vh, int v, int e);
void printmenu();
void push(int* stack, int* top, int num);
void pop(int* top);
void enQueue(int* Queue, int* front, int rear, int num);
int deQueue(int* Queue, int front, int* rear);

int main()
{
	Graph *mygraph;
	mygraph = NULL;

	int delete_v;
	char command;

	/*
	�� �Լ��� �����ϱ� ���� �׷����� �����Ǿ� �ִ��� �˻�
	*/
	do {
		printmenu();
		scanf(" %c", &command);

		switch (command)
		{
		case 'z': case 'Z':
			createGraph(&mygraph);
			break;
		case 'v': case 'V':
			if (mygraph != NULL)
				insertVertex(mygraph->vlist);
			else
				printf("\ncreateGraph first!");
			break;
		case 'e': case 'E':
			if (mygraph != NULL)
				insertEdge(mygraph->vlist);
			else
				printf("\ncreateGraph first!");
			break;
		case 'p': case 'P':
			if (mygraph != NULL)
				printGraph(mygraph->vlist);
			break;
		case 'd': case 'D':
			if (mygraph != NULL)
				depthFS(mygraph->vlist);
			else
				printf("\ncreateGraph first!");
			break;
		case 'b': case 'B':
			if (mygraph != NULL)
				breadthFS(mygraph->vlist);
			else
				printf("\ncreateGraph first!");
			break;
		case 'g': case 'G':
			if (mygraph != NULL)
				deleteEdge(mygraph->vlist);
			else
				printf("\ncreateGraph first!");
			break;
		case 't': case 'T':
			if (mygraph != NULL)
			{
				printf("������ Vertex: ");
				scanf("%d", &delete_v);
				deleteVertex(mygraph->vlist, delete_v);
			}
			else
				printf("\ncreateGraph first!");
			break;
		case 'y': case 'Y':
			if(mygraph!=NULL)
				destoryGraph(&mygraph);
			else
				printf("\ncreateGraph first!");
			break;
		default:
			printf("\nchoose correct menu!");
			break;
		}
	} while (command != command != 'q' && command != 'Q');

	return 0;
}

/*
�׷���(Graph) ����
*/
void destoryGraph(Graph** g)
{
	int i;
	for (i = 0; i < MAX_VERTEX; i++)
		if ((*g)->vlist[i].head != NULL)
			deleteVertex((*g)->vlist, (*g)->vlist[i].head->num);
	free((*g)->vlist);
	free(*g);
	*g = NULL;
}

/*
Vertex ����
*/
int deleteVertex(VertexHead* vh, int v)
{
	Vertex* previous;
	Vertex* target;
	int i;

	if (vh[v].head != NULL)	//Vertex�� ����Ǿ� �ִ��� Ȯ��
	{
		for (i = 0; i < MAX_VERTEX; i++)
		{
			if (i == v)	//������ Vertex�� ã�� ��� �ش� ���� ����Ʈ���� �� �޸� ������
			{
				previous = vh[i].head;
				target = previous->link;
				while (target != NULL)
				{
					free(previous);
					previous = target;
					target = target->link;
				}
			}
			else if (vh[i].head != NULL)	//�ٸ� Vertex�� ������ ��帮��Ʈ���� ������. �� ������ ������
			{
				target = vh[i].head->link;
				while (target != NULL)
				{
					if (target->num == v)
					{
						deleteEdge_delete(vh, i, v);	//deleteEdge�� �̿��Ѵ�
						break;
					}
					target = target->link;
				}
			}
		}
		vh[v].head = NULL;
	}
	else
		printf("\nVertex[%d] doesn't exist", v);
	return 1;
}

/*
����(Edge) ���� �μ��Լ�
*/
int deleteEdge_delete(VertexHead* vh, int v, int e)
{
	Vertex* previous;	//������ ������ �� ������ ������ ��� ����Ʈ�� �����ϱ� ����
	Vertex* target;

	if (vh[v].head == NULL)	//Vertex�� �����ϴ��� �˻�
	{
		printf("\nVertex[%d] doesn't exist", v);
		return 0;
	}

	previous = vh[v].head;
	target = vh[v].head->link;
	while (target != NULL)
	{
		if (target->num == e)	//������ ã��
		{
			previous->link = target->link;	//������ ����� ����Ʈ���� ����
			free(target);
			return 1;
		}
		previous = target;
		target = target->link;
	}

	printf("\nVertex[%d] doesn't have Edge[%d]", v, e);	//ã�� ������ ���
	return 0;
}

/*
����(Edge) ����
*/
void deleteEdge(VertexHead* vh)
{
	int e1, e2;
	printf("������ Edge1: ");	//�����ؾ��� Edge�� ���1 �Է�
	scanf("%d", &e1);
	printf("������ Edge2: ");	//�����ؾ��� Edge�� ���2 �Է�
	scanf("%d", &e2);

	deleteEdge_delete(vh, e1, e2);	//Edge������ ���1�� ������ ���鿡�� �����Ѵ�
	deleteEdge_delete(vh, e2, e1);	//���� ������ �ൿ�� ���2���� �ݺ��Ѵ�.
}

/*
�ʺ� �켱 Ž��
*/
int breadthFS(VertexHead* vh)
{
	int visited[MAX_VERTEX];	//��б���� ������ �迭(0�̸� �̹湮, 1�̸� �湮����)
	int Queue[MAX_VERTEX];
	memset(visited, 0, sizeof(visited));	//�湮��� �ʱ�ȭ

	int v, i, key, front, rear;
	front = -1;
	rear = -1;
	Vertex* temp;	//Vertex Ž���� ���� ������

	printf("First Vertex: ");
	scanf("%d", &v);	//Ž���� ������ ��带 ����

	if (vh[v].head == NULL)
	{
		printf("First vertex[%d] doesn't exist", v);
		return 0;
	}

	printf("\nBreath First Search: ");
	temp = vh[v].head;
	visited[temp->num] = 1;	//���� ����� �湮����� ����
	enQueue(Queue, &front, rear, temp->num);	//���� ��带 ť�� ����

	do {
		key = deQueue(Queue, front, &rear);	//ť�� �ִ� ��带 �����´�
		if (key == -1)	//ť�� ��� �ִ��� Ȯ��
			return 0;
		temp = vh[key].head->link;
		while (temp != NULL)
		{
			if (visited[temp->num] == 0)	//�湮����� Ȯ���Ͽ� �湮�� ������ �� ����
			{
				visited[temp->num] = 1;
				enQueue(Queue, &front, rear, temp->num);
			}
			temp = temp->link;	//���� ���� ��带 Ž��
		}
	} while (front != rear);	//ť�� �� ������ �ݺ�
}

/*
ť ����
*/
void enQueue(int* Queue, int* front, int rear, int num)
{
	if ((*front + 1) % MAX_VERTEX + 1 != rear)	//��ȯ ť ���� �� ť�� ���� ���ִ��� Ȯ��
	{
		*front = (*front + 1) % MAX_VERTEX;
		Queue[*front] = num;
	}
	else
		printf("\n\nQueue is full!\n");
}

/*
ť ���� �� ���
*/
int deQueue(int* Queue, int front, int* rear)
{
	int key;
	if (front != *rear)
	{
		*rear = (*rear + 1) % MAX_VERTEX;	//��ȯ ť ���� �� ť�� ����ִ��� Ȯ��
		key = Queue[(*rear)];
		printf("%d ", key);
		return key;
	}
	else
		printf("\n\nQueue is empty!\n");
	return -1;
}

/*
���̿켱Ž��
*/
int depthFS(VertexHead* vh)
{
	int visited[MAX_VERTEX];	//��б���� ������ �迭(0�̸� �̹湮, 1�̸� �湮����)
	int stack[MAX_VERTEX];
	memset(visited, 0, sizeof(visited));	//�湮��� �ʱ�ȭ

	int v, i, top;
	top = -1;
	Vertex* temp;	//Vertex�� Ž���ϱ� ���� ������
	Vertex* temp2;	//���� ��带 Ž���ϱ� ���� ������
	
	printf("First Vertex: ");	//Ž���� ������ ��� ����
	scanf("%d", &v);

	/*
	Vertex�� ����Ǿ� �ִ��� Ȯ��
	*/
	if (vh[v].head == NULL)
	{
		printf("First vertex[%d] doesn't exist", v);
		return 0;
	}

	printf("\nDepth First Search: ");
	temp = vh[v].head;
	do
	{
		if (visited[temp->num] == 0)	//�湮������ ���� ���
		{
			push(stack, &top, temp->num);
			visited[temp->num] = 1;	//�湮�Ͽ� ���ÿ� �����ϰ� �湮����� ����
			temp2 = temp->link;
			while (temp2 != NULL)	//�������� Ž��
			{
				if (visited[temp2->num] == 0)
				{
					temp = vh[temp2->num].head;
					break;
				}
				temp2 = temp2->link;
			}
			if (temp2 == NULL)	//���������� �������� �ʰų� ���� �� �湮���� ���
			{
				pop(&top);	//Vertex�� pop�Ͽ� �湮���θ� �����Ѵ�
				temp = vh[stack[top]].head;
			}
		}
		else
		{	//Vertex�� �̹� �湮�� ������ ���
			temp2 = temp->link;
			while (temp2 != NULL)	//������带 Ž��
			{
				if (visited[temp2->num] == 0)
				{
					temp = vh[temp2->num].head;
					break;
				}
				temp2 = temp2->link;
			}
			if (temp2 == NULL)	//���������� �������� �ʰų� ���� �� �湮���� ���
			{
				pop(&top);
				if (top != -1)
					temp = vh[stack[top]].head;
			}
		}
	} while (top != -1);

	return 0;
}

/*
stack�� push
*/
void push(int* stack, int* top, int num)
{
	printf("%d ", num);	//Ʈ���� preorder�� ����ϱ⿡ push�� �� ���
	stack[++(*top)] = num;
}

/*
stack�� pop
*/
void pop(int* top)
{
	(*top)--;
}

/*
�׷����� ����Ѵ�.

=======================����========================
index[Vertex]: Vertex - ���� ���(��ĭ�� ��� ���)
===================================================
*/
void printGraph(VertexHead* vh)
{
	int i;
	Vertex* temp;
	for (i = 0; i < MAX_VERTEX; i++)
	{
		if (vh[i].head != NULL)
		{
			printf("\nindex[%d]: %d  -  ", i, vh[i].head->num);
			temp = vh[i].head->link;
			while (temp != NULL)
			{
				printf("%d ", temp->num);
				temp = temp->link;
			}
		}
	}
}

/*
Edge�� �����Ͽ� Vertex�� �����Ѵ�.
*/
void insertEdge(VertexHead* vh)
{
	int n1, n2;
	Vertex* find;
	Vertex* v1;
	Vertex* v2;

	printf("������ Vertex1: ");
	scanf("%d", &n1);
	printf("������ Vertex2: ");
	scanf("%d", &n2);

	/*
	�ش� Vertex�� ����Ǿ� �ִ��� ���� Ȯ��
	v�� n�� ���� ¦�� �ݴ��� ����
	: ex) 1, 4������ ��� 4�� 1�� ����Ʈ��, 1�� 4�� ����Ʈ�� ���� �ϱ� ����(�̸� �ð������� ǥ��)
	*/
	if (vh[n1].head != NULL && vh[n2].head != NULL)	//�� �� ����� Vertex�̾�� ��
	{
		v1 = (Vertex*)malloc(sizeof(Vertex));
		v1->num = n2;
		v1->link = NULL;

		v2 = (Vertex*)malloc(sizeof(Vertex));
		v2->num = n1;
		v2->link = NULL;


		find = vh[n1].head;
		while (find->link != NULL)
			find = find->link;
		find->link = v1;

		find = vh[n2].head;
		while (find->link != NULL)
			find = find->link;
		find->link = v2;
	}
	else
		printf("\nCannot find Vertex");
}

/*
Vertex�� ����� �Լ�
�Լ��� ���� ���� ���ϰ� ��ü������ ȿ�������� �����ϱ� ����
ó���� Vertex�� ���� �� ����� ��带 �ϳ� �����
�ش� ����� num�� index �� Vertex�� �����ϰ� ����

��, Vertex������ �ϳ��� ��尡 ���� �����ǰ�
�̰��� Vertex�� ��뿩�θ� �Ǵ��� 
*/
void insertVertex(VertexHead* vh)
{
	int key;

	printf("Vertex: ");
	scanf("%d", &key);

	if (0 <= key && key < 20)
	{
		Vertex *new;
		new = (Vertex*)malloc(sizeof(Vertex));	//index, �� Vertex�� ��Ÿ�� ������(�Լ��� �����ϰ� �ϱ� ����)
		vh[key].head = new;

		vh[key].head->num = key;
		vh[key].head->link = NULL;
	}
	else
		printf("\nInput number in range(0,19)");
}

/*
�޴��� ����ϴ� �Լ�
*/
void printmenu()
{
	printf("\n\n");
	printf("---------------------[2019038095] [������]-----------------------\n");
	printf("                         Term Project                            \n");
	printf("-----------------------------------------------------------------\n");
	printf(" Create Graph          = z      depthFS                      = d \n");
	printf(" Insert Vertex         = v      breadthFS                    = b \n");
	printf(" Insert Edge           = e      deleteEdge                   = g \n");
	printf(" Print Graph           = p      deleteVertex                 = t \n");
	printf(" Quit                  = q      destroyGraph                 = y \n");
	printf("-----------------------------------------------------------------\n");

	printf("Command = ");
}

/*
�׷����� ����� �Լ�
�ٸ� ��ɾ�� ������� �ʼ������� ���ϸ��� ����ؾ���
*/
void createGraph(Graph** g)
{
	if (*g != NULL)
		destoryGraph(g);
	*g = (Graph*)malloc(sizeof(Graph));
	(*g)->vlist = (VertexHead*)malloc(sizeof(VertexHead)*MAX_VERTEX);
	for (int i = 0; i < MAX_VERTEX; i++)
		(*g)->vlist[i].head = NULL;
}