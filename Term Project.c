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
	각 함수를 실행하기 전에 그래프가 생성되어 있는지 검사
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
				printf("삭제할 Vertex: ");
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
그래프(Graph) 삭제
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
Vertex 삭제
*/
int deleteVertex(VertexHead* vh, int v)
{
	Vertex* previous;
	Vertex* target;
	int i;

	if (vh[v].head != NULL)	//Vertex가 선언되어 있는지 확인
	{
		for (i = 0; i < MAX_VERTEX; i++)
		{
			if (i == v)	//삭제할 Vertex를 찾은 경우 해당 인접 리스트까지 다 메모리 해제함
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
			else if (vh[i].head != NULL)	//다른 Vertex의 인접한 노드리스트에서 삭제함. 즉 간선을 삭제함
			{
				target = vh[i].head->link;
				while (target != NULL)
				{
					if (target->num == v)
					{
						deleteEdge_delete(vh, i, v);	//deleteEdge를 이용한다
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
간선(Edge) 삭제 부속함수
*/
int deleteEdge_delete(VertexHead* vh, int v, int e)
{
	Vertex* previous;	//간선을 삭제한 후 끊어진 인접한 노드 리스트를 연결하기 위함
	Vertex* target;

	if (vh[v].head == NULL)	//Vertex가 존재하는지 검사
	{
		printf("\nVertex[%d] doesn't exist", v);
		return 0;
	}

	previous = vh[v].head;
	target = vh[v].head->link;
	while (target != NULL)
	{
		if (target->num == e)	//간선을 찾음
		{
			previous->link = target->link;	//인접한 노드의 리스트에서 삭제
			free(target);
			return 1;
		}
		previous = target;
		target = target->link;
	}

	printf("\nVertex[%d] doesn't have Edge[%d]", v, e);	//찾지 못했을 경우
	return 0;
}

/*
간선(Edge) 삭제
*/
void deleteEdge(VertexHead* vh)
{
	int e1, e2;
	printf("삭제할 Edge1: ");	//삭제해야할 Edge의 노드1 입력
	scanf("%d", &e1);
	printf("삭제할 Edge2: ");	//삭제해야할 Edge의 노드2 입력
	scanf("%d", &e2);

	deleteEdge_delete(vh, e1, e2);	//Edge정보를 노드1의 인접한 노드들에서 삭제한다
	deleteEdge_delete(vh, e2, e1);	//위와 동일한 행동을 노드2에서 반복한다.
}

/*
너비 우선 탐색
*/
int breadthFS(VertexHead* vh)
{
	int visited[MAX_VERTEX];	//방분기록을 저장할 배열(0이면 미방문, 1이면 방문했음)
	int Queue[MAX_VERTEX];
	memset(visited, 0, sizeof(visited));	//방문기록 초기화

	int v, i, key, front, rear;
	front = -1;
	rear = -1;
	Vertex* temp;	//Vertex 탐색을 위한 포인터

	printf("First Vertex: ");
	scanf("%d", &v);	//탐색을 시작할 노드를 지정

	if (vh[v].head == NULL)
	{
		printf("First vertex[%d] doesn't exist", v);
		return 0;
	}

	printf("\nBreath First Search: ");
	temp = vh[v].head;
	visited[temp->num] = 1;	//시작 노드의 방문기록을 저장
	enQueue(Queue, &front, rear, temp->num);	//시작 노드를 큐에 저장

	do {
		key = deQueue(Queue, front, &rear);	//큐에 있는 노드를 가져온다
		if (key == -1)	//큐가 비어 있는지 확인
			return 0;
		temp = vh[key].head->link;
		while (temp != NULL)
		{
			if (visited[temp->num] == 0)	//방문기록을 확인하여 방문이 가능할 때 실행
			{
				visited[temp->num] = 1;
				enQueue(Queue, &front, rear, temp->num);
			}
			temp = temp->link;	//다음 인접 노드를 탐색
		}
	} while (front != rear);	//큐가 빌 때까지 반복
}

/*
큐 저장
*/
void enQueue(int* Queue, int* front, int rear, int num)
{
	if ((*front + 1) % MAX_VERTEX + 1 != rear)	//순환 큐 구현 및 큐가 가득 차있는지 확인
	{
		*front = (*front + 1) % MAX_VERTEX;
		Queue[*front] = num;
	}
	else
		printf("\n\nQueue is full!\n");
}

/*
큐 삭제 및 출력
*/
int deQueue(int* Queue, int front, int* rear)
{
	int key;
	if (front != *rear)
	{
		*rear = (*rear + 1) % MAX_VERTEX;	//순환 큐 구현 및 큐가 비어있는지 확인
		key = Queue[(*rear)];
		printf("%d ", key);
		return key;
	}
	else
		printf("\n\nQueue is empty!\n");
	return -1;
}

/*
깊이우선탐색
*/
int depthFS(VertexHead* vh)
{
	int visited[MAX_VERTEX];	//방분기록을 저장할 배열(0이면 미방문, 1이면 방문했음)
	int stack[MAX_VERTEX];
	memset(visited, 0, sizeof(visited));	//방문기록 초기화

	int v, i, top;
	top = -1;
	Vertex* temp;	//Vertex를 탐색하기 위한 포인터
	Vertex* temp2;	//인접 노드를 탐색하기 위한 포인터
	
	printf("First Vertex: ");	//탐색을 시작할 노드 지정
	scanf("%d", &v);

	/*
	Vertex가 선언되어 있는지 확인
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
		if (visited[temp->num] == 0)	//방문전적이 없는 경우
		{
			push(stack, &top, temp->num);
			visited[temp->num] = 1;	//방문하여 스택에 저장하고 방문기록을 수정
			temp2 = temp->link;
			while (temp2 != NULL)	//인접노드들 탐색
			{
				if (visited[temp2->num] == 0)
				{
					temp = vh[temp2->num].head;
					break;
				}
				temp2 = temp2->link;
			}
			if (temp2 == NULL)	//인접노드들이 존재하지 않거나 전부 다 방문했을 경우
			{
				pop(&top);	//Vertex를 pop하여 방문여부를 조사한다
				temp = vh[stack[top]].head;
			}
		}
		else
		{	//Vertex가 이미 방문한 상태인 경우
			temp2 = temp->link;
			while (temp2 != NULL)	//인접노드를 탐색
			{
				if (visited[temp2->num] == 0)
				{
					temp = vh[temp2->num].head;
					break;
				}
				temp2 = temp2->link;
			}
			if (temp2 == NULL)	//인접노드들이 존재하지 않거나 전부 다 방문했을 경우
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
stack에 push
*/
void push(int* stack, int* top, int num)
{
	printf("%d ", num);	//트리의 preorder과 비슷하기에 push할 때 출력
	stack[++(*top)] = num;
}

/*
stack을 pop
*/
void pop(int* top)
{
	(*top)--;
}

/*
그래프를 출력한다.

=======================형식========================
index[Vertex]: Vertex - 인접 노드(한칸씩 띄워 출력)
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
Edge를 생성하여 Vertex를 연결한다.
*/
void insertEdge(VertexHead* vh)
{
	int n1, n2;
	Vertex* find;
	Vertex* v1;
	Vertex* v2;

	printf("연결할 Vertex1: ");
	scanf("%d", &n1);
	printf("연결할 Vertex2: ");
	scanf("%d", &n2);

	/*
	해당 Vertex가 선언되어 있는지 먼저 확인
	v와 n의 숫자 짝이 반대인 이유
	: ex) 1, 4연결할 경우 4는 1의 리스트에, 1은 4의 리스트에 들어가야 하기 때문(이를 시각적으로 표현)
	*/
	if (vh[n1].head != NULL && vh[n2].head != NULL)	//둘 다 선언된 Vertex이어야 함
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
Vertex를 만드는 함수
함수를 좀더 보기 편하고 전체적으로 효과적으로 동작하기 위해
처음에 Vertex를 만들 때 연결된 노드를 하나 만들고
해당 노드의 num은 index 즉 Vertex와 동일하게 만듬

즉, Vertex생성시 하나의 노드가 같이 생성되고
이것을 Vertex가 사용여부를 판단함 
*/
void insertVertex(VertexHead* vh)
{
	int key;

	printf("Vertex: ");
	scanf("%d", &key);

	if (0 <= key && key < 20)
	{
		Vertex *new;
		new = (Vertex*)malloc(sizeof(Vertex));	//index, 즉 Vertex를 나타낼 노드생성(함수를 간편하게 하기 위함)
		vh[key].head = new;

		vh[key].head->num = key;
		vh[key].head->link = NULL;
	}
	else
		printf("\nInput number in range(0,19)");
}

/*
메뉴를 출력하는 함수
*/
void printmenu()
{
	printf("\n\n");
	printf("---------------------[2019038095] [이진원]-----------------------\n");
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
그래프를 만드는 함수
다른 명령어들 사용전에 필수적으로 제일먼저 사용해야함
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