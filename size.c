#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("-------------------[2019038095]------[������]----------------\n\n");

    int **x;

    printf("sizeof(x) = %lu\n", sizeof(x));         //vscode�� 32��Ʈ �����̱� ������ �ּҰ��� 4����Ʈ�̴�.
    printf("sizeof(*x) = %lu\n", sizeof(*x));       //���� �����ϴ�
    printf("sizeof(**x) = %lu\n", sizeof(**x));     //int���� 4����Ʈ�̱� �����̴�.
}