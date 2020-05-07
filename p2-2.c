#include <stdio.h>
#include <stdlib.h>

void print1(int *ptr, int rows);

void main()
{
    printf("-------------------[2019038095]------[이진원]----------------\n\n");

    int one[]={0,1,2,3,4};

    printf("one     = %p\n",one);               //one은 배열의 이름으로 == &one[0]
    printf("&one    = %p\n",&one);              //one의 주소
    printf("&one[0] = %p\n",&one[0]);           //&one[0]의 값

    print1(&one[0], 5);
}

void print1(int *ptr, int rows)                 //매개변수 포인터 ptr에 one[0]의 주소를 담는다
{
    int i;
    printf("Address \t Contents\n");
    for(i=0; i<rows; i++)
        printf("%p \t %5d\n",ptr+i,*(ptr+i));   //ptr에 담긴 주소로부터 i만큼 떨어진 곳의 주소와 역참조한 값을 출력한다
    printf("\n");
}