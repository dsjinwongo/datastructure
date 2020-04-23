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

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {											//연산자들의 우선순위 부여!!
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];        /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;       /* evalStack용 top */

int evalResult = 0;       /* 계산 결과를 저장 */

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;				//top의 위치를 1증가시킨 후 가리키는 스택의 위치에 값을 저장
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else
	{
		x = postfixStack[postfixStackTop--];			//top이 가리키는 값을 x에 저장하여 반환하고 top의 값은 -1한다
	}
	return x;
}


void evalPush(int x)
{
	evalStack[++evalStackTop] = x;						//top을 1증가시켜 가리키는 곳에(인덱스에) x를 저장
}

int evalPop()											//postfixPop과 비슷한 알고리즘
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");					//수식을 입력받아 문자열로 저장한다.
	scanf("%s", infixExp);
}

precedence getToken(char symbol)						//연산자들의 우선순위를 부여한다!!!*중요*
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

precedence getPriority(char x)							//연산자를 전달받아 우선순위를 구한 뒤 반환한다.
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)									//profixExp에 전달받은 문자를 저장한다.
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/*
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	char k;
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		/* 필요한 로직 완성 */
		x = exp[0];
		if (getPriority(x) == operand)					//문자가 숫자일 경우 바로 postfixExp에 저장
			charCat(&x);
		else if (postfixStackTop == -1 || x == '(')		//top이 맨 처음이거나 입력이 '('일 경우 postfixstack에 저장
			postfixPush(x);								//이유는 '('은 스택에 들어가기 전에는 우선순위가 높다!!
		else if (x == ')')								//')'일 경우 '('가 반환될 때까지 postfixstack을 pop하여 postfixExp에 저장한다.
		{
			x = postfixPop();
			while (x != '(')
			{
				charCat(&x);
				x = postfixPop();
			}

		}
		else if (getPriority(x) > getPriority(postfixStack[postfixStackTop]))		//연산자의 우선순위가 높으면 postfixstack에 저장한다.
			postfixPush(x);
		else
		{												/*연산자의 우선순위가 높으면 먼저 출력한다는 규칙을 만족시키기 위한 알고리즘이다.
														한편, 교재의 예시와 달리 +,-와 *,/의 우선순위가 다르게 설정되었기에
														결과가 다를 수 있다.*/
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
	{													//postfixstack에 저장된 데이터를 pop하여 postfixExp에 저장한다
		x = postfixPop();
		if (x == '(' || x == ')')						//혹시나 '(', ')'가 저장되지 않기 위한 조건문이다.
			continue;
		charCat(&x);
	} while (x != '\0');

	/* 필요한 로직 완성 */

}
void debug()											//스택들의 상태를 확인한다.
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

void reset()											//스택들을 초기화한다.
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()										//postfixExp에 후위표기법으로 저장된 연산자들과 피연산자들을 해석하여 계산한다.
{
	/* postfixExp, evalStack을 이용한 계산 */
	int i = 0;
	int a, b, c;
	char *exp = postfixExp;
	while (*exp != '\0')
	{
		if (getPriority(*exp) == operand)				//피연산자들은 아스키코드를 활용하여 정수형으로 저장한다.
			evalPush(*exp - '0');
		else
		{
			b = evalPop();
			a = evalPop();
			switch (*exp)								//연산자들을 읽고, 저장된 두 피연산자들을 pop하여 계산하고 저장한다.
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