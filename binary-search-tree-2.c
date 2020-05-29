/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack()
{

}



int main()
{
	printf("-------[2019038095] [������]---------");
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	top = -1;
	while (1)
	{
		while (node != NULL)
		{
			push(node);
			node = node->left;
		}
		node = pop();

		if (node == NULL)
			break;

		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front = -1;
	rear = -1;

	if (ptr == NULL)
		return;
	enQueue(ptr);

	while (1)
	{
		ptr = deQueue();
		if (ptr != NULL)
		{
			printf(" [%d] ", ptr->key);
			if (ptr->left != NULL)
				enQueue(ptr->left);
			if (ptr->right != NULL)
				enQueue(ptr->right);
		}
		else
			break;
	}
}


int insert(Node* head, int key)
{
	Node* new_node;		//���ο� ��带 �Ҵ��ϱ� ���� ������
	Node* temp;

	new_node = (Node*)malloc(sizeof(Node));		//���ο� ��� �Ҵ�
	new_node->key = key;		//key������ �ʱ�ȭ
	new_node->left = NULL;		//�ʱ�ȭ
	new_node->right = NULL;		//�ʱ�ȭ

	if (head != NULL)		//�ʱ�ȭ ���� ���� ����
	{
		temp = head;
		if (temp->left != NULL)		//��尡 ù ������ �ƴҰ��
		{
			temp = temp->left;		//��Ʈ���� �̵�
			while (1)
			{
				if (key < temp->key)		//�����Ϸ��� ���� ����� ������ ���� ���
				{
					if (temp->left != NULL)		//������尡 �ƴҰ�� �ڳ���� �̵�
						temp = temp->left;
					else
					{
						temp->left = new_node;
						return 1;
					}
				}
				else if (key == temp->key)		//�����Ϸ��� ���� ����� ���� ���� ���
					return 0;
				else						//�����Ϸ��� ���� ����� ������ Ŭ ���
				{
					if (temp->right != NULL)		//������尡 �ƴҰ�� �ڳ���� �̵�
						temp = temp->right;
					else
					{
						temp->right = new_node;
						return 1;
					}
				}
			}
		}
		else
			temp->left = new_node;		//��尡 ù ������ ���
	}

	return 1;
}



int deleteNode(Node* head, int key)
{
	Node* temp;
	Node* temp_l;
	Node* previous;		//�θ��尡 ������ �ڳ�� ����� branch�� NULL�� �����ϱ� ����

	if (head != NULL)		//�ʱ�ȭ ���� ���� ����
	{
		temp = head->left;
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				if (temp->left != NULL && temp->right != NULL)		//�ڳ��尡 �����ϴ� ���
				{
					temp_l = temp->left;
					previous = temp;
					while (temp_l->right != NULL)
					{										//���� ����Ʈ������ ���� ū �� ã��
						previous = temp_l;
						temp_l = temp_l->right;
					}
					temp->key = temp_l->key;
					if (temp_l == temp->left)		//���� ���� ����Ʈ������ ���� ū ���� ���� ����Ʈ���� ��Ʈ�� ���
						previous->left = temp_l->left;
					else if (temp_l->left == NULL)		//���� ū ���� ���� ����Ʈ���� �������� �ʴ� ���
						previous->right = NULL;
					else
						previous->right = temp_l->left;		//���� ū ���� ���� ����Ʈ���� �����ϴ� ���
					free(temp_l);
					return 1;
				}
				else if (temp->left == NULL)		//������ �ڳุ �����ϴ� ���
				{
					if (previous->left == temp)		//�θ��忡�� branch ����
						previous->left = temp->right;
					else
						previous->right = temp->right;
					free(temp);
					return 1;
				}
				else if (temp->right == NULL)		//���� �ڳุ �����ϴ� ���
				{
					if (previous->left == temp)		//�θ��忡�� branch ����
						previous->left = temp->left;
					else
						previous->right = temp->left;
					free(temp);
					return 1;
				}
				else if(temp->right == NULL && temp->left == NULL)
				{
					if (previous->left == temp)		//�θ��忡�� branch ����
						previous->left = NULL;
					else
						previous->right = NULL;
					free(temp);
					return 1;
				}
			}
			else if (key < temp->key)		//�����Ϸ��� ���� ����� ������ ���� ���
			{
				previous = temp;		//�θ��带 ����ϱ� ����
				temp = temp->left;
			}
			else if (key > temp->key)		//�����Ϸ��� ���� ����� ������ Ŭ ���
			{
				previous = temp;		//�θ��带 ����ϱ� ����
				temp = temp->right;
			}
		}

		printf("\n Cannot find the node [%d]\n", key);		//��带 ã�� ������ ���
	}

	return 0;
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top != -1)
		return stack[top--];		//�� ��ȯ �� top-1
	return NULL;
}

void push(Node* aNode)
{
	if (top + 1 != 20)
	{
		top++;
		stack[top] = aNode;
	}
}



Node* deQueue()
{
	if (rear != front)
		return queue[++rear];		//�� ��ȯ �� rear+1
	return NULL;
}

void enQueue(Node* aNode)
{
	if (front + 1 != rear)
	{
		front = (front + 1) % 20;
		queue[front] = aNode;
	}
}