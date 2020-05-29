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
	printf("-------[2019038095] [이진원]---------");
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
	Node* new_node;		//새로운 노드를 할당하기 위한 포인터
	Node* temp;

	new_node = (Node*)malloc(sizeof(Node));		//새로운 노드 할당
	new_node->key = key;		//key값으로 초기화
	new_node->left = NULL;		//초기화
	new_node->right = NULL;		//초기화

	if (head != NULL)		//초기화 이전 동작 방지
	{
		temp = head;
		if (temp->left != NULL)		//노드가 첫 삽입이 아닐경우
		{
			temp = temp->left;		//루트노드로 이동
			while (1)
			{
				if (key < temp->key)		//삽입하려는 값이 노드의 값보다 작을 경우
				{
					if (temp->left != NULL)		//리프노드가 아닐경우 자녀노드로 이동
						temp = temp->left;
					else
					{
						temp->left = new_node;
						return 1;
					}
				}
				else if (key == temp->key)		//삽입하려는 값과 노드의 값이 같을 경우
					return 0;
				else						//삽입하려는 값이 노드의 값보다 클 경우
				{
					if (temp->right != NULL)		//리프노드가 아닐경우 자녀노드로 이동
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
			temp->left = new_node;		//노드가 첫 삽입일 경우
	}

	return 1;
}



int deleteNode(Node* head, int key)
{
	Node* temp;
	Node* temp_l;
	Node* previous;		//부모노드가 삭제된 자녀와 연결된 branch를 NULL로 수정하기 위함

	if (head != NULL)		//초기화 이전 동작 방지
	{
		temp = head->left;
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				if (temp->left != NULL && temp->right != NULL)		//자녀노드가 존재하는 경우
				{
					temp_l = temp->left;
					previous = temp;
					while (temp_l->right != NULL)
					{										//왼쪽 서브트리에서 가장 큰 값 찾기
						previous = temp_l;
						temp_l = temp_l->right;
					}
					temp->key = temp_l->key;
					if (temp_l == temp->left)		//만약 왼쪽 서브트리에서 가장 큰 값이 왼쪽 서브트리의 루트인 경우
						previous->left = temp_l->left;
					else if (temp_l->left == NULL)		//가장 큰 값의 왼쪽 서브트리가 존재하지 않는 경우
						previous->right = NULL;
					else
						previous->right = temp_l->left;		//가장 큰 값의 왼쪽 서브트리가 존재하는 경우
					free(temp_l);
					return 1;
				}
				else if (temp->left == NULL)		//오른쪽 자녀만 존재하는 경우
				{
					if (previous->left == temp)		//부모노드에서 branch 수정
						previous->left = temp->right;
					else
						previous->right = temp->right;
					free(temp);
					return 1;
				}
				else if (temp->right == NULL)		//왼쪽 자녀만 존재하는 경우
				{
					if (previous->left == temp)		//부모노드에서 branch 수정
						previous->left = temp->left;
					else
						previous->right = temp->left;
					free(temp);
					return 1;
				}
				else if(temp->right == NULL && temp->left == NULL)
				{
					if (previous->left == temp)		//부모노드에서 branch 수정
						previous->left = NULL;
					else
						previous->right = NULL;
					free(temp);
					return 1;
				}
			}
			else if (key < temp->key)		//삭제하려는 값이 노드의 값보다 작을 경우
			{
				previous = temp;		//부모노드를 기억하기 위함
				temp = temp->left;
			}
			else if (key > temp->key)		//삭제하려는 값이 노드의 값보다 클 경우
			{
				previous = temp;		//부모노드를 기억하기 위함
				temp = temp->right;
			}
		}

		printf("\n Cannot find the node [%d]\n", key);		//노드를 찾지 못했을 경우
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
		return stack[top--];		//값 반환 후 top-1
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
		return queue[++rear];		//값 반환 전 rear+1
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