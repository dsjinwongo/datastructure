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
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node{
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	printf("----------------[������]\t[2019038095]----------------\n");
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


int initialize(headNode** h)		//main���� ����� headnode �����ͺ����� ���� �����ϱ� ���� ���������ͺ����� �޾Ҵ�.
{
	if (*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));		//���������Ͱ� ����Ű�� �����Ϳ� �޸� �Ҵ�
	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h)		//�Ҵ�� �޸� ����
{
	listNode* p = h->first;

	listNode* prev = NULL;		//���� ����Ű�� �޸𸮸� �����Ͽ� ���� ��带 ����Ű�� ���ϴ� ��Ȳ ����
	while (p != NULL)
	{
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h)		//����Ʈ ���
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* temp;
	node->key = key;

	temp = h->first;
	if (temp != NULL)
	{
		while (temp->rlink != NULL)		//��带 ����Ű�� �����͸� �� ������ �̵�
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
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h)
{
	listNode* target;
	listNode* previous;

	target = h->first;
	while (target->rlink != NULL)		//Ÿ���� �� �ڷ� �����ϱ� ���� ����
	{
		previous = target;
		target = target->rlink;
	}
	previous->rlink = NULL;		//�� �� ��尡 ����Ű�� ���� ���
	free(target);

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
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
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h)
{
	listNode* target;
	target = h->first;
	h->first = h->first->rlink;		//����Ʈ�� ù��° ��带 �����ϱ� ���� �Ǿ� ��带 ����Ű�� �����͸� ��ĭ �ڷ� �Ű���
	h->first->llink = NULL;		//���ο� ù ����� ���� ������ ���´�.
	free(target);

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h)
{
	listNode* trail;
	listNode* tmp;

	while (h->first != NULL)		//����Ʈ�� �� �� ��带 ����Ű�� �����͸� �� �ڷ� ����
	{
		trail = h->first;
		h->first = h->first->rlink;		//��尡 ����Ű�� ��带 ��ĭ ������ ����
		tmp = trail->llink;		//���� ������ trail�� ����Ű�� ����� llink�� rlink�� ����
		trail->llink = trail->rlink;
		trail->rlink = tmp;
	}

	h->first = trail;		//������� �̵��� �����͸� �� �� ���(�������� �ǵ�)�� ����Ű���� ��

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key)
{
	listNode* previous;
	listNode* temp;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	temp = h->first;
	previous = NULL;
	if (h->first == NULL)		//���� ����Ʈ�� ù ����� ���
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
			if (previous == NULL)		//����Ʈ�� �� �տ� �����ϰ� �� ���
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
				previous->rlink = node;		//����Ʈ�� �߰��� �����ϰ� �Ǵ� ���
				node->llink = previous;
			}
			return 0;
		}
		previous = temp;
		temp = temp->rlink;
	}
	previous->rlink = node;		//����Ʈ�� �� �ڿ� �����ϰ� �� ���
	node->rlink = NULL;
	node->llink = previous;

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key)
{
	listNode* target;
	listNode* previous;

	previous = NULL;
	target = h->first;
	while (target != NULL)
	{
		if (target->key == key)		//Ÿ�� ���� ���� ��带 ã�� ���
		{
			if (target == h->first)		//Ÿ���� ����Ʈ�� �Ǿ� ����� ���
			{
				h->first = h->first->rlink;
				h->first->llink = NULL;
			}
			else
			{
				previous->rlink = target->rlink;		//�߰��� ��ġ�� ���
				target->rlink->llink = previous;
			}
			free(target);
			return 0;
		}
		previous = target;
		target = target->rlink;
	}

	printf("cannot find the node for key = %d\n", key);		//Ÿ���� ã�� ���� ���

	return 1;
}