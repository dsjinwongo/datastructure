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


typedef struct Node{
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
	printf("----------------[이진원]\t[2019038095]----------------\n");
	char command;
	int key;
	headNode* headnode = NULL;

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

		switch (command)
		{
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


int initialize(headNode** h)		//main에서 선언된 headnode 포인터변수를 직접 수정하기 위해 이중포인터변수로 받았다.
{
	if (*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));		//이중포인터가 가리키는 포인터에 메모리 할당
	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h)		//할당된 메모리 해제
{
	listNode* p = h->first;

	listNode* prev = NULL;		//현제 가리키는 메모리를 해제하여 다음 노드를 가리키지 못하는 상황 방지
	while (p != NULL)
	{
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h)		//리스트 출력
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* temp;
	node->key = key;

	temp = h->first;
	if (temp != NULL)
	{
		while (temp->rlink != NULL)		//노드를 가리키는 포인터를 맨 끝으로 이동
			temp = temp->rlink;
		temp->rlink = node;
		node->llink = temp;
		node->rlink = NULL;
	}
	else
	{
		h->first = node;
		h->first->llink = NULL;
		h->first->rlink = NULL;
	}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h)
{
	listNode* target;
	listNode* previous;

	target = h->first;
	while (target->rlink != NULL)		//타깃을 맨 뒤로 설정하기 위한 루프
	{
		previous = target;
		target = target->rlink;
	}
	previous->rlink = NULL;		//그 전 노드가 가리키는 곳을 비움
	free(target);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->llink = NULL;
	h->first->llink = node;
	node->rlink = h->first;
	h->first = node;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
{
	listNode* target;
	target = h->first;
	h->first = h->first->rlink;		//리스트의 첫번째 노드를 삭제하기 전에 맨앞 노드를 가리키는 포인터를 한칸 뒤로 옮겨줌
	h->first->llink = NULL;		//새로운 첫 노드의 왼쪽 연결을 끊는다.
	free(target);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h)
{
	listNode* trail;
	listNode* tmp;

	while (h->first != NULL)		//리스트의 맨 앞 노드를 가리키는 포인터를 맨 뒤로 보냄
	{
		trail = h->first;
		h->first = h->first->rlink;		//헤드가 가리키는 노드를 한칸 앞으로 변경
		tmp = trail->llink;		//이하 세줄은 trail이 가리키는 노드의 llink와 rlink를 변경
		trail->llink = trail->rlink;
		trail->rlink = tmp;
	}

	h->first = trail;		//빈곳으로 이동한 포인터를 맨 앞 노드(이전에는 맨뒤)를 가리키도록 함

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
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
		h->first->rlink = NULL;
		h->first->llink = NULL;
		return 0;
	}
	while (temp != NULL)
	{
		if (temp->key > key)
		{
			if (previous == NULL)		//리스트의 맨 앞에 삽입하게 될 경우
			{
				node->rlink = temp;
				temp->llink = node;
				h->first = node;
				h->first->llink = NULL;

			}
			else
			{
				node->rlink = temp;
				temp->llink = node;
				previous->rlink = node;		//리스트의 중간에 삽입하게 되는 경우
				node->llink = previous;
			}
			return 0;
		}
		previous = temp;
		temp = temp->rlink;
	}
	previous->rlink = node;		//리스트의 맨 뒤에 삽입하게 될 경우
	node->rlink = NULL;
	node->llink = previous;

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key)
{
	listNode* target;
	listNode* previous;

	previous = NULL;
	target = h->first;
	while (target != NULL)
	{
		if (target->key == key)		//타깃 값을 가진 노드를 찾은 경우
		{
			if (target == h->first)		//타깃이 리스트의 맨앞 노드일 경우
			{
				h->first = h->first->rlink;
				h->first->llink = NULL;
			}
			else if (target->rlink == NULL)
				previous->rlink = target->rlink;
			else
			{
				previous->rlink = target->rlink;		//중간에 위치할 경우
				target->rlink->llink = previous;
			}
			free(target);
			return 0;
		}
		previous = target;
		target = target->rlink;
	}

	printf("cannot find the node for key = %d\n", key);		//타깃을 찾지 못한 경우

	return 1;
}
