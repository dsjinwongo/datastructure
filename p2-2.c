#include <stdio.h>
#include <stdlib.h>

void print1(int *ptr, int rows);

void main()
{
    printf("-------------------[2019038095]------[������]----------------\n\n");

    int one[]={0,1,2,3,4};

    printf("one     = %p\n",one);               //one�� �迭�� �̸����� == &one[0]
    printf("&one    = %p\n",&one);              //one�� �ּ�
    printf("&one[0] = %p\n",&one[0]);           //&one[0]�� ��

    print1(&one[0], 5);
}

void print1(int *ptr, int rows)                 //�Ű����� ������ ptr�� one[0]�� �ּҸ� ��´�
{
    int i;
    printf("Address \t Contents\n");
    for(i=0; i<rows; i++)
        printf("%p \t %5d\n",ptr+i,*(ptr+i));   //ptr�� ��� �ּҷκ��� i��ŭ ������ ���� �ּҿ� �������� ���� ����Ѵ�
    printf("\n");
}