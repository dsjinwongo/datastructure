#include <stdio.h>
#include <stdlib.h>

struct student
{
    char lastName[13];
    int studentId;
    short grade;
};

void main()
{
    printf("-------------------[2019038095]------[������]----------------\n\n");

    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student));      //����ü�� ũ��(16+4+4)(lastName[13]�� ũ�Ⱑ 13+padding�� ����3���� 16�̴�.)
    printf("size of int = %ld\n", sizeof(int));                     //int�� ũ��� 4
    printf("size of short = %ld\n", sizeof(short));                 //short�� ũ��� 3�̳� padding�� ���� 4�� �Ҵ�
}