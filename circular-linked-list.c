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
/* �ʿ��� ������� �߰� */

typedef struct Node
{
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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
	printf("-----------[2019038095]\t[������]-------------");

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

    /* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
    if(*h != NULL)
        freeList(*h);

    /* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* �޸� ���� */
int freeList(listNode* h)
{
	listNode* p = h->rlink;
	listNode* prev = NULL;		//���� ����Ű�� �޸𸮸� �����Ͽ� ���� ��带 ����Ű�� ���ϴ� ��Ȳ ����
	while (p != h)		//p�� �ѹ��� ���� �ٽ� h�� ����ų ������
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* temp;
	node->key = key;

	if (h != NULL)		//initialize ���� ���� ����
	{
		temp = h->rlink;
		if (h->rlink != h)		//��尡 �ϳ��� ���� ��� ����
		{
			while (temp->rlink != h)		//��带 ����Ű�� �����͸� �� ������ �̵�
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
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h)
{
	listNode* target;
	listNode* previous;

	if (h != NULL)		//initialize ���� ���� ����
	{
		target = h->rlink;
		previous = h;
		if (h->rlink != h)
		{
			while (target->rlink != h)		//Ÿ���� �� �ڷ� �����ϱ� ���� ����
			{
				previous = target;
				target = target->rlink;
			}
			previous->rlink = h;		//�� �� ��尡 ����Ű�� ���� ���
			h->llink = previous;
			free(target);
		}
	}
	else
		printf("initialize first..\n");

    return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h != NULL)		//initialize ���� ���� ����
	{
		if (h->rlink != h)		//����Ʈ�� ��尡 �������� ���� ��� ����
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
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h)
{
	listNode* target;
	if (h != NULL)		//initialize ���� ���� ����
	{
		target = h->rlink;
		if (h->rlink != h)		//����Ʈ�� ��尡 �������� ���� ��� ����
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
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h)
{
	listNode* trail;
	listNode* trans;
	listNode* temp;

	if (h != NULL)		//initialize ���� ���� ����
	{
		temp = h->rlink;
		while (temp != h)		//����Ʈ Ž������
		{
			trail = temp;
			temp = temp->rlink;
			trans = trail->rlink;		//�¿쿬�ḵũ ����
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



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key)
{
	listNode* temp;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h != NULL)		//initialize ���� ���� ����
	{
		temp = h->rlink;
		while (temp != h)
		{
			if (temp->key > key)		//������ġ �߰�
			{
				node->rlink = temp;
				node->llink = temp->llink;
				temp->llink->rlink = node;
				temp->llink = node;

				return 0;
			}
			temp = temp->rlink;
		}
		node->rlink = temp;		//������ġ �߰� ������ ���(�ǵ�)
		node->llink = temp->llink;
		temp->llink->rlink = node;
		temp->llink = node;
	}
	else
		printf("initialize first..\n");

    return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key)
{
	listNode* target;
	listNode* previous;

	if (h != NULL)		//initialize ���� ���� ����
	{
		target = h->rlink;
		previous = h;
		while (target != h)
		{
			if (target->key == key)		//������ ��带 �߰��� ���
			{
				previous->rlink = target->rlink;
				target->rlink->llink = previous;
				free(target);

				return 0;
			}
			previous = target;
			target = target->rlink;
		}
		printf("cannot find the node for key = %d\n", key);		//Ÿ���� ã�� ���� ���
	}	
	else
		printf("initialize first..\n");
    return 0;
}