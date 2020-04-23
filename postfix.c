/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {											//�����ڵ��� �켱���� �ο�!!
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];    /* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];        /* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;       /* evalStack�� top */

int evalResult = 0;       /* ��� ����� ���� */

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;				//top�� ��ġ�� 1������Ų �� ����Ű�� ������ ��ġ�� ���� ����
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else
	{
		x = postfixStack[postfixStackTop--];			//top�� ����Ű�� ���� x�� �����Ͽ� ��ȯ�ϰ� top�� ���� -1�Ѵ�
	}
	return x;
}


void evalPush(int x)
{
	evalStack[++evalStackTop] = x;						//top�� 1�������� ����Ű�� ����(�ε�����) x�� ����
}

int evalPop()											//postfixPop�� ����� �˰���
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
	printf("Type the expression >>> ");					//������ �Է¹޾� ���ڿ��� �����Ѵ�.
	scanf("%s", infixExp);
}

precedence getToken(char symbol)						//�����ڵ��� �켱������ �ο��Ѵ�!!!*�߿�*
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

precedence getPriority(char x)							//�����ڸ� ���޹޾� �켱������ ���� �� ��ȯ�Ѵ�.
{
	return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)									//profixExp�� ���޹��� ���ڸ� �����Ѵ�.
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/*
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	char k;
	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while (*exp != '\0')
	{
		/* �ʿ��� ���� �ϼ� */
		x = exp[0];
		if (getPriority(x) == operand)					//���ڰ� ������ ��� �ٷ� postfixExp�� ����
			charCat(&x);
		else if (postfixStackTop == -1 || x == '(')		//top�� �� ó���̰ų� �Է��� '('�� ��� postfixstack�� ����
			postfixPush(x);								//������ '('�� ���ÿ� ���� ������ �켱������ ����!!
		else if (x == ')')								//')'�� ��� '('�� ��ȯ�� ������ postfixstack�� pop�Ͽ� postfixExp�� �����Ѵ�.
		{
			x = postfixPop();
			while (x != '(')
			{
				charCat(&x);
				x = postfixPop();
			}

		}
		else if (getPriority(x) > getPriority(postfixStack[postfixStackTop]))		//�������� �켱������ ������ postfixstack�� �����Ѵ�.
			postfixPush(x);
		else
		{												/*�������� �켱������ ������ ���� ����Ѵٴ� ��Ģ�� ������Ű�� ���� �˰����̴�.
														����, ������ ���ÿ� �޸� +,-�� *,/�� �켱������ �ٸ��� �����Ǿ��⿡
														����� �ٸ� �� �ִ�.*/
			do
			{
				k = postfixPop();
				charCat(&k);
			} while (getPriority(x) > getPriority(postfixStack[postfixStackTop]) && postfixStackTop != -1);
			postfixPush(x);
		}


		exp++;
	}
	do
	{													//postfixstack�� ����� �����͸� pop�Ͽ� postfixExp�� �����Ѵ�
		x = postfixPop();
		if (x == '(' || x == ')')						//Ȥ�ó� '(', ')'�� ������� �ʱ� ���� ���ǹ��̴�.
			continue;
		charCat(&x);
	} while (x != '\0');

	/* �ʿ��� ���� �ϼ� */

}
void debug()											//���õ��� ���¸� Ȯ���Ѵ�.
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()											//���õ��� �ʱ�ȭ�Ѵ�.
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()										//postfixExp�� ����ǥ������� ����� �����ڵ�� �ǿ����ڵ��� �ؼ��Ͽ� ����Ѵ�.
{
	/* postfixExp, evalStack�� �̿��� ��� */
	int i = 0;
	int a, b, c;
	char *exp = postfixExp;
	while (*exp != '\0')
	{
		if (getPriority(*exp) == operand)				//�ǿ����ڵ��� �ƽ�Ű�ڵ带 Ȱ���Ͽ� ���������� �����Ѵ�.
			evalPush(*exp - '0');
		else
		{
			b = evalPop();
			a = evalPop();
			switch (*exp)								//�����ڵ��� �а�, ����� �� �ǿ����ڵ��� pop�Ͽ� ����ϰ� �����Ѵ�.
			{
			case '+':
				evalPush(a + b);
				break;
			case '-':
				evalPush(a - b);
				break;
			case '/':
				evalPush(a / b);
				break;
			case '*':
				evalPush(a * b);
				break;
			}
		}
		exp++;
	}
	evalResult = evalPop();
}


int main()
{
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;
}