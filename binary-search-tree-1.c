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
	printf("---------------[2019038095] [������]-----------------");

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



void inorderTraversal(Node* ptr)		//������ȸ(LVR) ����->���->������
{
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left);		//������ ���� ���ȣ��
		printf("[%d] ", ptr->key);		//���ʳ�尡 �������� ���� �� ���
		inorderTraversal(ptr->right);		//������ ���ȣ��
	}
}

void preorderTraversal(Node* ptr)		//������ȸ(VLR) ���->����->������
{
	if (ptr != NULL)
	{
		printf("[%d] ", ptr->key);		//��带 ���� ���
		preorderTraversal(ptr->left);		//���� ���ȣ��
		preorderTraversal(ptr->right);		//������ ���ȣ��
	}
}

void postorderTraversal(Node* ptr)		//������ȸ(LRV) ����->������->���
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);		//���� ���ȣ��
		postorderTraversal(ptr->right);		//������ ���ȣ��
		printf("[%d] ", ptr->key);		//��� ���
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

int deleteLeafNode(Node* head, int key)
{
	Node* temp;
	Node* previous;		//�θ��尡 ������ �ڳ�� ����� branch�� NULL�� �����ϱ� ����
	
	if (head != NULL)		//�ʱ�ȭ ���� ���� ����
	{
		temp = head->left;
		while (temp != NULL)
		{
			if (temp->key == key)
			{
				if (temp->left != NULL || temp->right != NULL)		//�ڳ��尡 �����ϴ� ���
				{
					printf("This node [%d] is not a leaf!", key);
					return 0;
				}
				else
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

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr != NULL)
	{
		if (key < ptr->key)		//ã������ ����� ���� ���� ����� ������ ���� ���
		{
			if (ptr->left != NULL)		//�ڳ��尡 �����ϴ� ���
				ptr = searchRecursive(ptr->left, key);		//�����ڳ���� �̵��Ͽ� ���ȣ��
			else
				return NULL;		//���� ã�� ���� ���
		}
		else if (key > ptr->key)
		{
			if (ptr->right != NULL)
				ptr = searchRecursive(ptr->right, key);
			else
				return NULL;
		}
		return ptr;		//���� ã�� ���
	}

	return NULL;		//��尡 �������� �ʴ� ���
}


Node* searchIterative(Node* head, int key)
{
	Node* temp;
	if (head != NULL)
	{
		temp = head->left;
		if (temp != NULL)
		{
			while (1)		//���ѷ���
			{
				if (key < temp->key)		//ã������ ���� ���� ����� ������ ���� ���
				{
					if (temp->left != NULL)		//�ڳ��尡 �����ϴ� ���
						temp = temp->left;
					else
						return NULL;		//���� ã�� ���� ���
				}
				else if (key == temp->key)		//���� ã�� ���
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
		if (head->key == -9999)		//��尡 �������� �ʴ°��
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