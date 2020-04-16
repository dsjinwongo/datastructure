#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int** create_matrix(int row, int col);					//��� ������ ��ó���˻��Լ�
int free_matrix(int** matrix, int row, int col);		//�Ҵ�� �޸� ����
void print_matrix(int** matrix, int row, int col);		//������
int fill_data(int** matrix, int row, int col);			//��� �����Է�
int transpose_matrix(int** matrix, int** matrix_t,		//��ġ��� ���ϴ��Լ�
	int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b,		//����� ��
	int **matrix_sum, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b,	//����� ����
	int** matrix_sub, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t,		//��İ� ��ġ����� ��
	int** matrix_axt, int row, int col);

int main()
{
	int row, col, check[13];
	int** matrix_a;										//���A
	int** matrix_b;										//���B
	int** matrix_sum;									//���A+B
	int** matrix_sub;									//���A-B
	int** matrix_t;										//���A�� ��ġ���T
	int** matrix_axt;									//���A*T

	printf("---------[������]----------[2019038095]-------\n");

	scanf("%d %d", &row, &col);

	matrix_a = create_matrix(row, col);						                    //�޸� �Ҵ�
	matrix_b = create_matrix(row, col);
	matrix_sum = create_matrix(row, col);
	matrix_sub = create_matrix(row, col);
	matrix_t = create_matrix(col, row);											//��ġ����� �� ���� �ڹٲ�
	matrix_axt = create_matrix(row, row);										//��İ� ��ġ����� ���� ���� ����� ��*���� ����� �ȴ�

	srand(time(NULL));
	check[1] = fill_data(matrix_a, row, col);									//���A, B�� ���� �Է�
	check[2] = fill_data(matrix_b, row, col);

	check[3] = addition_matrix(matrix_a, matrix_a, matrix_sum, row, col);		//��� ���� ����
	check[4] = subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col);	//��� ���� ����
	check[5] = transpose_matrix(matrix_a, matrix_t, row, col);					//����� ��ġ��� ����
	check[6] = multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);		//����� �� ����

	print_matrix(matrix_a, row, col);								            //��� ���
	print_matrix(matrix_b, row, col);
	print_matrix(matrix_sum, row, col);
	print_matrix(matrix_sub, row, col);
	print_matrix(matrix_t, col, row);
	print_matrix(matrix_axt, row, row);

	check[7] = free_matrix(matrix_a, row, col);								//�Ҵ�� �޸𸮸� �ٽ� Ǯ����
	check[8] = free_matrix(matrix_b, row, col);
	check[9] = free_matrix(matrix_sum, row, col);
	check[10] = free_matrix(matrix_sub, row, col);
	check[11] = free_matrix(matrix_t, col, row);
	check[12] = free_matrix(matrix_axt, row, row);

	for (int i = 0; i < 13; i++)
		if (check[i] == -1)
		{
			printf("\n���α׷��� ����������Ǿ����ϴ�.");
			return 0;
		}
	printf("\n���α׷��� ��������Ǿ����ϴ�.");
	return 0;
}

int free_matrix(int** matrix, int row, int col)                     //�Ҵ�� �޸� ����
{
	if (row <= 0 || col <= 0 || matrix == NULL)						//pre_condition
	{
		printf("�Ű������� ���ڸ� Ȯ�����ּ���.\n");
		return -1;
	}

	int i;
	for (i = 0; i < row; i++)
		free(matrix[i]);											//����� ���� �ش��ϴ� �޸� Ǯ����
	free(matrix);													//����� �࿡ �ش��Ѵ� �޸� Ǯ����

	matrix = NULL;

	if (matrix != NULL)												//post_condition
	{
		printf("�޸𸮰� ���������� �������� �ʾҽ��ϴ�,\n");
		return -1;
	}
	return 1;
}

void print_matrix(int** matrix, int row, int col)					//��� ���
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

int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)     //����� ��
{
	if (row <= 0 || col <= 0 || matrix_a == NULL || matrix_t == NULL)	//pre_condition
	{
		printf("�Ű������� ���ڸ� Ȯ�����ּ���.\n");
		return -1;
	}

	int i, j, k, sum;
	for (i = 0; i < row; i++)
		for (j = 0; j < row; j++)
		{
			sum = 0;
			for (k = 0; k < col; k++)
				sum += matrix_a[i][k] * matrix_t[k][j];					//matrix_axt[i][j]�� ���ϴ� ��
			matrix_axt[i][j] = sum;
		}

	if (matrix_axt[0][0] > 19*19*col)									/*post_condition
																		������ ���� �̸� 19*19*col�� ���� �� ���� �����̴�.*/
	{
		printf("����� ���� ���������� ������� ���Ͽ����ϴ�.");
		return -1;
	}

	return 1;
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col)    //��ġ��� ���ϴ��Լ�
{
	if (row <= 0 || col <= 0 || matrix == NULL)					        //pre_condition
	{
		printf("�Ű������� ���ڸ� Ȯ�����ּ���.\n");
		return -1;
	}

	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_t[j][i] = matrix[i][j];						        //��ġ��� ����

	if (matrix_t[0][0] == -500)									        //post_condition
	{
		printf("��ġ����� ���������� ������� ���Ͽ����ϴ�.");
		return -1;
	}

	return 1;
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)
{
	if (row <= 0 || col <= 0 || matrix_a == NULL || matrix_b == NULL)	//pre_condition
	{
		printf("�Ű������� ���ڸ� Ȯ�����ּ���.\n");
		return -1;
	}

	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];			//����� ������ ����

	if (matrix_sub[0][0] == -500)										//post_condition
	{
		printf("����� ���� ���������� ������� ���Ͽ����ϴ�.");
		return -1;
	}

	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int **matrix_sum, int row, int col)
{
	if (row <= 0 || col <= 0 || matrix_a == NULL || matrix_b == NULL)	//pre_condition
	{
		printf("�Ű������� ���ڸ� Ȯ�����ּ���.\n");
		return -1;
	}

	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];			//����� ��

	if (matrix_sum[0][0] == -500)										//post_condition
	{
		printf("����� ���� ���������� ������� ���Ͽ����ϴ�.");
		return -1;
	}

	return 1;
}

int** create_matrix(int row, int col)                   //��� ������ ��ó���˻��Լ�
{
	if (row <= 0 || col <= 0)							//pre_condition
	{
		printf("�Ű������� ���ڸ� Ȯ�����ּ���.\n");
		return -1;
	}

	int i;
	if (row <= 0 || col <= 0)
		return -1;

	int** matrix = (int**)malloc(sizeof(int*)*row);
	for (i = 0; i < row; i++)
		matrix[i] = (int*)malloc(sizeof(int)*col);

	for (i = 0; i < row; i++)
		memset(matrix[i], -500, sizeof(int)*col);		/*�ٸ� �Լ����� post_condition�� �����ϱ� ���� �Լ�
														(500�� 20*20=400�̱� ������ �Ϻ� �Լ����� ������ �߻��ϱ� �ʱ� ���� �����Ͽ���.)*/

	if (matrix == NULL)									//post_condition
	{
		printf("����� ������ ���������� ������� ���Ͽ����ϴ�.");
		return -1;
	}

	return matrix;
}

int fill_data(int** matrix, int row, int col)               //��� �����Է�
{
	if (row <= 0 || col <= 0 || matrix == NULL)				//pre_condition
	{
		printf("�Ű������� ���ڸ� Ȯ�����ּ���.\n");
		return -1;
	}

	int i, j;

	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix[i][j] = rand() % 20;						//0~19�� ���ڸ� �������� ����

	if (matrix[0][0] == -500)								//post_condition
	{
		printf("��Ŀ� ���ڰ� ���������� ������� ���Ͽ����ϴ�.");
		return -1;
	}

	return 1;
}