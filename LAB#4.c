#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int** create_matrix(int row, int col);					//행렬 생성과 전처리검사함수
int free_matrix(int** matrix, int row, int col);		//할당된 메모리 삭제
void print_matrix(int** matrix, int row, int col);		//행렬출력
int fill_data(int** matrix, int row, int col);			//행렬 숫자입력
int transpose_matrix(int** matrix, int** matrix_t,		//전치행렬 구하는함수
	int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b,		//행렬의 합
	int **matrix_sum, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b,	//행렬의 뺄셈
	int** matrix_sub, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t,		//행렬과 전치행렬의 곱
	int** matrix_axt, int row, int col);

int main()
{
	int row, col, check[13];
	int** matrix_a;										//행렬A
	int** matrix_b;										//행렬B
	int** matrix_sum;									//행렬A+B
	int** matrix_sub;									//행렬A-B
	int** matrix_t;										//행렬A의 전치행렬T
	int** matrix_axt;									//행렬A*T

	printf("---------[이진원]----------[2019038095]-------\n");

	scanf("%d %d", &row, &col);

	matrix_a = create_matrix(row, col);						                    //메모리 할당
	matrix_b = create_matrix(row, col);
	matrix_sum = create_matrix(row, col);
	matrix_sub = create_matrix(row, col);
	matrix_t = create_matrix(col, row);											//전치행렬은 행 열이 뒤바뀜
	matrix_axt = create_matrix(row, row);										//행렬과 전치행렬의 곱은 본래 행렬의 열*열의 행렬이 된다

	srand(time(NULL));
	check[1] = fill_data(matrix_a, row, col);									//행렬A, B에 숫자 입력
	check[2] = fill_data(matrix_b, row, col);

	check[3] = addition_matrix(matrix_a, matrix_a, matrix_sum, row, col);		//행렬 덧셈 수행
	check[4] = subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);	//행렬 뺄셈 수행
	check[5] = transpose_matrix(matrix_a, matrix_t, row, col);					//행렬의 전치행렬 구함
	check[6] = multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);		//행렬의 곱 수행

	print_matrix(matrix_a, row, col);								            //행렬 출력
	print_matrix(matrix_b, row, col);
	print_matrix(matrix_sum, row, col);
	print_matrix(matrix_sub, row, col);
	print_matrix(matrix_t, col, row);
	print_matrix(matrix_axt, row, row);

	check[7] = free_matrix(matrix_a, row, col);								//할당된 메모리를 다시 풀어줌
	check[8] = free_matrix(matrix_b, row, col);
	check[9] = free_matrix(matrix_sum, row, col);
	check[10] = free_matrix(matrix_sub, row, col);
	check[11] = free_matrix(matrix_t, col, row);
	check[12] = free_matrix(matrix_axt, row, row);

	for (int i = 0; i < 13; i++)
		if (check[i] == -1)
		{
			printf("\n프로그램이 비정상종료되었습니다.");
			return 0;
		}
	printf("\n프로그램이 정상종료되었습니다.");
	return 0;
}

int free_matrix(int** matrix, int row, int col)                     //할당된 메모리 삭제
{
	if (row <= 0 || col <= 0 || matrix == NULL)						//pre_condition
	{
		printf("매개변수와 인자를 확인해주세요.\n");
		return -1;
	}

	int i;
	for (i = 0; i < row; i++)
		free(matrix[i]);											//행렬의 열에 해당하는 메모리 풀어줌
	free(matrix);													//행렬의 행에 해당한는 메모리 풀어줌

	matrix = NULL;

	if (matrix != NULL)												//post_condition
	{
		printf("메모리가 정상적으로 해제되지 않았습니다,\n");
		return -1;
	}
	return 1;
}

void print_matrix(int** matrix, int row, int col)					//행렬 출력
{
	int i, j;
	printf("\n");
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

}

int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)     //행렬의 곱
{
	if (row <= 0 || col <= 0 || matrix_a == NULL || matrix_t == NULL)	//pre_condition
	{
		printf("매개변수와 인자를 확인해주세요.\n");
		return -1;
	}

	int i, j, k, sum;
	for (i = 0; i < row; i++)
		for (j = 0; j < row; j++)
		{
			sum = 0;
			for (k = 0; k < col; k++)
				sum += matrix_a[i][k] * matrix_t[k][j];					//matrix_axt[i][j]를 구하는 곱
			matrix_axt[i][j] = sum;
		}

	if (matrix_axt[0][0] > 19*19*col)									/*post_condition
																		곱셈의 값이 이를 19*19*col를 넘을 수 없기 때문이다.*/
	{
		printf("행렬의 곱이 정상적으로 실행되지 못하였습니다.");
		return -1;
	}

	return 1;
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col)    //전치행렬 구하는함수
{
	if (row <= 0 || col <= 0 || matrix == NULL)					        //pre_condition
	{
		printf("매개변수와 인자를 확인해주세요.\n");
		return -1;
	}

	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_t[j][i] = matrix[i][j];						        //전치행렬 구함

	if (matrix_t[0][0] == -500)									        //post_condition
	{
		printf("전치행렬이 정상적으로 실행되지 못하였습니다.");
		return -1;
	}

	return 1;
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)
{
	if (row <= 0 || col <= 0 || matrix_a == NULL || matrix_b == NULL)	//pre_condition
	{
		printf("매개변수와 인자를 확인해주세요.\n");
		return -1;
	}

	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];			//행렬의 뺄셈을 저장

	if (matrix_sub[0][0] == -500)										//post_condition
	{
		printf("행렬의 차가 정상적으로 실행되지 못하였습니다.");
		return -1;
	}

	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int **matrix_sum, int row, int col)
{
	if (row <= 0 || col <= 0 || matrix_a == NULL || matrix_b == NULL)	//pre_condition
	{
		printf("매개변수와 인자를 확인해주세요.\n");
		return -1;
	}

	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];			//행렬의 합

	if (matrix_sum[0][0] == -500)										//post_condition
	{
		printf("행렬의 합이 정상적으로 실행되지 못하였습니다.");
		return -1;
	}

	return 1;
}

int** create_matrix(int row, int col)                   //행렬 생성과 전처리검사함수
{
	if (row <= 0 || col <= 0)							//pre_condition
	{
		printf("매개변수와 인자를 확인해주세요.\n");
		return -1;
	}

	int i;
	if (row <= 0 || col <= 0)
		return -1;

	int** matrix = (int**)malloc(sizeof(int*)*row);
	for (i = 0; i < row; i++)
		matrix[i] = (int*)malloc(sizeof(int)*col);

	for (i = 0; i < row; i++)
		memset(matrix[i], -500, sizeof(int)*col);		/*다른 함수에서 post_condition을 수행하기 위한 함수
														(500은 20*20=400이기 때문에 일부 함수에서 오류가 발생하기 않기 위해 설정하였다.)*/

	if (matrix == NULL)									//post_condition
	{
		printf("행렬의 생성이 정상적으로 실행되지 못하였습니다.");
		return -1;
	}

	return matrix;
}

int fill_data(int** matrix, int row, int col)               //행렬 숫자입력
{
	if (row <= 0 || col <= 0 || matrix == NULL)				//pre_condition
	{
		printf("매개변수와 인자를 확인해주세요.\n");
		return -1;
	}

	int i, j;

	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix[i][j] = rand() % 20;						//0~19의 숫자를 랜덤으로 저장

	if (matrix[0][0] == -500)								//post_condition
	{
		printf("행렬에 숫자가 정상적으로 저장되지 못하였습니다.");
		return -1;
	}

	return 1;
}