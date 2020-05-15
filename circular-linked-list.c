/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node
{
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("-----------[2019038095]\t[이진원]-------------");

    char command;
    int key;
    listNode* headnode=NULL;
	
    do{
        printf("----------------------------------------------------------------\n");
        printf("                  Doubly Circular Linked List                   \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command)
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

    }while(command != 'q' && command != 'Q');

    return 1;
}


int initialize(listNode** h)
{

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if(*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* 메모리 해제 */
int freeList(listNode* h)
{
	listNode* p = h->rlink;
	listNode* prev = NULL;		//현제 가리키는 메모리를 해제하여 다음 노드를 가리키지 못하는 상황 방지
	while (p != h)		//p가 한바퀴 돌아 다시 h를 가리킬 때까지
	{
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	
    return 1;
}



void printList(listNode* h)
{
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if(h == NULL)
	{
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while(p != NULL && p != h)
	{
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("  items = %d\n", i);


    /* print addresses */
    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

    i = 0;
    p = h->rlink;
    while(p != NULL && p != h)
	{
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
        p = p->rlink;
        i++;
    }

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* temp;
	node->key = key;

	if (h != NULL)		//initialize 이전 동작 방지
	{
		temp = h->rlink;
		if (h->rlink != h)		//노드가 하나도 없을 경우 방지
		{
			while (temp->rlink != h)		//노드를 가리키는 포인터를 맨 끝으로 이동
				temp = temp->rlink;
			temp->rlink = node;
			node->llink = temp;
			node->rlink = h;
			h->llink = node;
		}
		else
		{
			temp->rlink = node;
			temp->llink = node;
			node->llink = h;
			node->rlink = h;
		}
	}
	else
		printf("initialize first..\n");

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h)
{
	listNode* target;
	listNode* previous;

	if (h != NULL)		//initialize 이전 동작 방지
	{
		target = h->rlink;
		previous = h;
		if (h->rlink != h)
		{
			while (target->rlink != h)		//타깃을 맨 뒤로 설정하기 위한 루프
			{
				previous = target;
				target = target->rlink;
			}
			previous->rlink = h;		//그 전 노드가 가리키는 곳을 비움
			h->llink = previous;
			free(target);
		}
	}
	else
		printf("initialize first..\n");

    return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h != NULL)		//initialize 이전 동작 방지
	{
		if (h->rlink != h)		//리스트에 노드가 존재하지 않을 경우 방지
		{
			node->rlink = h->rlink;
			node->llink = h;
			h->rlink->llink = node;
			h->rlink = node;
		}
		else
		{
			h->rlink = node;
			h->llink = node;
			node->rlink = h;
			node->llink = h;
		}
	}
	else
		printf("initialize first..\n");

    return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h)
{
	listNode* target;
	if (h != NULL)		//initialize 이전 동작 방지
	{
		target = h->rlink;
		if (h->rlink != h)		//리스트에 노드가 존재하지 않을 경우 방지
		{
			h->rlink = target->rlink;
			target->rlink->llink = h;
			free(target);
		}
	}
	else
		printf("initialize first..\n");

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h)
{
	listNode* trail;
	listNode* trans;
	listNode* temp;

	if (h != NULL)		//initialize 이전 동작 방지
	{
		temp = h->rlink;
		while (temp != h)		//리스트 탐색루프
		{
			trail = temp;
			temp = temp->rlink;
			trans = trail->rlink;		//좌우연결링크 변경
			trail->rlink = trail->llink;
			trail->llink = trans;
		}
		trans = h->rlink;
		h->rlink = h->llink;
		h->llink = trans;
	}
	else
		printf("initialize first..\n");

    return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key)
{
	listNode* temp;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h != NULL)		//initialize 이전 동작 방지
	{
		temp = h->rlink;
		while (temp != h)
		{
			if (temp->key > key)		//삽입위치 발견
			{
				node->rlink = temp;
				node->llink = temp->llink;
				temp->llink->rlink = node;
				temp->llink = node;

				return 0;
			}
			temp = temp->rlink;
		}
		node->rlink = temp;		//삽입위치 발견 못했을 경우(맨뒤)
		node->llink = temp->llink;
		temp->llink->rlink = node;
		temp->llink = node;
	}
	else
		printf("initialize first..\n");

    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key)
{
	listNode* target;
	listNode* previous;

	if (h != NULL)		//initialize 이전 동작 방지
	{
		target = h->rlink;
		previous = h;
		while (target != h)
		{
			if (target->key == key)		//삭제할 노드를 발견한 경우
			{
				previous->rlink = target->rlink;
				target->rlink->llink = previous;
				free(target);

				return 0;
			}
			previous = target;
			target = target->rlink;
		}
		printf("cannot find the node for key = %d\n", key);		//타깃을 찾지 못한 경우
	}	
	else
		printf("initialize first..\n");
    return 0;
}