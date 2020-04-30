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

typedef struct Node		//구조체 선언
{
	int key;
	struct Node* link;
} listNode;

typedef struct Head		//구조체를 가리킬 포인터를 포함한 구조체 선언
{
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
	printf("------------[이진원]	[2019038095]-------------\n");
	char command;
	int key;
	headNode* headnode = NULL;

	do {
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

		switch (command) {
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

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h)		/*구조체를 가리키는 포인터를 포함한 구조체의 포인터에 메모리를 할당한다.
										만약 선언하기 전에 비어있지 않으면 초기화한다.*/
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h)
{
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/*
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key)		//리스트의 맨 앞에 노드를 추가한다.
{

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key)
{
	listNode* previous;
	listNode* temp;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	temp = h->first;
	previous = NULL;
	if (h->first == NULL)		//만약 리스트의 첫 노드일 경우
	{
		h->first = node;
		h->first->link = NULL;
		return 0;
	}
	while (temp != NULL)
	{
		if (temp->key > key)
		{
			if (previous == NULL)		//리스트의 맨 앞에 삽입하게 될 경우
				node->link = temp;
			else
			{
				previous->link = node;		//리스트의 중간에 삽입하게 되는 경우
				node->link = temp;
			}
			return 0;
		}
		previous = temp;
		temp = temp->link;
	}
	previous->link = node;		//리스트의 맨 뒤에 삽입하게 될 경우
	node->link = NULL;
	return 0;
}

/*
 * list에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key)		//리스트의 맨 끝에 노드를 삽입
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* temp;
	node->key = key;
	
	temp = h->first;
	while (temp->link != NULL)		//노드를 가리키는 포인터를 맨 끝으로 이동
		temp = temp->link;
	temp->link = node;
	node->link = NULL;

	return 0;
}


/*
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
{
	listNode* target;
	target = h->first;
	h->first = h->first->link;		//리스트의 첫번째 노드를 삭제하기 전에 맨앞 노드를 가리키는 포인터를 한칸 뒤로 옮겨줌
	free(target);

	return 0;
}


/*
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key)
{
	listNode* target;
	listNode* previous;

	previous = NULL;
	target = h->first;
	while (target!= NULL)
	{
		if (target->key == key)		//타깃 값을 가진 노드를 찾은 경우
		{
			if(target==h->first)		//타깃이 리스트의 맨앞 노드일 경우
				h->first = h->first->link;
			else
				previous->link = target->link;		//중간에 위치할 경우
			free(target);
			return 0;
		}
		previous = target;
		target = target->link;
	}

	printf("cannot find the node for key = %d\n", key);		//타깃을 찾지 못한 경우
	return 0;
}

/*
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h)
{
	listNode* target;
	listNode* previous;

	target = h->first;
	while (target->link != NULL)		//타깃을 맨 뒤로 설정하기 위한 루프
	{
		previous = target;
		target = target->link;
	}
	previous->link = NULL;		//그 전 노드가 가리키는 곳을 비움
	free(target);

	return 0;
}


/*
 * 리스트의 링크를 역순으로 재배치
 */
int invertList(headNode* h)
{
	listNode* trail;
	listNode* middle;

	middle = NULL;
	while (h->first != NULL)		//리스트의 맨 앞 노드를 가리키는 포인터를 맨 뒤로 보냄
	{
		trail = middle;		//trail은 먼저 앞서 간 middle의 link가 가리키도록 수정할 직전 노드를 담고 있음
		middle = h->first;
		h->first = h->first->link;
		middle->link = trail;
	}

	h->first = middle;		//빈곳으로 이동한 포인터를 맨 앞 노드(이전에는 맨뒤)를 가리키도록 함
	return 0;
}


void printList(headNode* h)
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL)
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
