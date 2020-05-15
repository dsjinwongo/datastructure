#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("-------------------[2019038095]------[이진원]----------------\n\n");

    int **x;

    printf("sizeof(x) = %lu\n", sizeof(x));         //vscode는 32비트 엔진이기 때문에 주소값이 4바이트이다.
    printf("sizeof(*x) = %lu\n", sizeof(*x));       //위와 동일하다
    printf("sizeof(**x) = %lu\n", sizeof(**x));     //int형은 4바이트이기 때문이다.
}