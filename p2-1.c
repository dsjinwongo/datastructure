#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main()
{
    printf("-------------------[2019038095]------[������]----------------\n\n");

    for(i=0; i<MAX_SIZE; i++)
        input[i]=i;                                 //�迭 input �ʱ�ȭ

    printf("address of input = %p\n", input);       //input�� �ּ�

    answer = sum(input, MAX_SIZE);                  //sum�� ���ڷ� input�� 100�� �־��ְ� ��ȯ���� answer�� ����
    printf("The sum is: %f\n",answer);
}

float sum(float list[], int n)
{
    printf("value of list = %p\n", list);           //�迭 list�� �̸��� ����Ű�� �ּҴ� �迭 input�� �ּҿ� ����
    printf("address of list %p\n\n",&list);         //�迭 list�� �ּҴ� list�� ����Ű�� �ּҿʹ� �ٸ� ���̴�.

    int i;
    float tempsum=0;
    for(i=0; i<n; i++)
        tempsum+=list[i];

    return tempsum;
}