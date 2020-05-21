/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("---------------[2019038095] [이진원]-----------------");

	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h)
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)		//중위순회(LVR) 왼쪽->노드->오른쪽
{
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left);		//왼쪽을 먼저 재귀호출
		printf("[%d] ", ptr->key);		//왼쪽노드가 존재하지 않을 시 출력
		inorderTraversal(ptr->right);		//오른쪽 재귀호출
	}
}

void preorderTraversal(Node* ptr)		//전위순회(VLR) 노드->왼쪽->오른쪽
{
	if (ptr != NULL)
	{
		printf("[%d] ", ptr->key);		//노드를 먼저 출력
		preorderTraversal(ptr->left);		//왼쪽 재귀호출
		preorderTraversal(ptr->right);		//오른쪽 재귀호출
	}
}

void postorderTraversal(Node* ptr)		//후위순회(LRV) 왼쪽->오른쪽->노드
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);		//왼쪽 재귀호출
		postorderTraversal(ptr->right);		//오른쪽 재귀호출
		printf("[%d] ", ptr->key);		//노드 출력
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

int deleteLeafNode(Node* head, int key)
{
	Node* temp;
	Node* previous;		//부모노드가 삭제된 자녀와 연결된 branch를 NULL로 수정하기 위함
	
	if (head != NULL)		//초기화 이전 동작 방지
	{
		temp = head->left;
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				if (temp->left != NULL || temp->right != NULL)		//자녀노드가 존재하는 경우
				{
					printf("This node [%d] is not a leaf!", key);
					return 0;
				}
				else
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

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr != NULL)
	{
		if (key < ptr->key)		//찾으려는 노드의 값이 현재 노드의 값보다 작은 경우
		{
			if (ptr->left != NULL)		//자녀노드가 존재하는 경우
				ptr = searchRecursive(ptr->left, key);		//왼쪽자녀노드로 이동하여 재귀호출
			else
				return NULL;		//값을 찾지 못한 경우
		}
		else if (key > ptr->key)
		{
			if (ptr->right != NULL)
				ptr = searchRecursive(ptr->right, key);
			else
				return NULL;
		}
		return ptr;		//값을 찾은 경우
	}

	return NULL;		//노드가 존재하지 않는 경우
}


Node* searchIterative(Node* head, int key)
{
	Node* temp;
	if (head != NULL)
	{
		temp = head->left;
		if (temp != NULL)
		{
			while (1)		//무한루프
			{
				if (key < temp->key)		//찾으려는 값이 현재 노드의 값보다 작은 경우
				{
					if (temp->left != NULL)		//자녀노드가 존재하는 경우
						temp = temp->left;
					else
						return NULL;		//값을 찾지 못한 경우
				}
				else if (key == temp->key)		//값을 찾은 경우
					return temp;
				else
				{
					if (temp->right != NULL)
						temp = temp->right;
					else
						return NULL;
				}
			}
		}
	}
	return 0;
}


int freeBST(Node* head)
{
	if (head != NULL)
	{
		if (head->key == -9999)		//노드가 존재하지 않는경우
		{
			freeBST(head->left);
			free(head);
		}
		else
		{
			freeBST(head->left);
			freeBST(head->right);
			free(head);
		}
	}
	return 0;
}