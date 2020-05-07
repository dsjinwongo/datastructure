#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main()
{
    printf("-------------------[2019038095]------[이진원]----------------\n\n");

    for(i=0; i<MAX_SIZE; i++)
        input[i]=i;                                 //배열 input 초기화

    printf("address of input = %p\n", input);       //input의 주소

    answer = sum(input, MAX_SIZE);                  //sum에 인자로 input과 100을 넣어주고 반환값을 answer에 저장
    printf("The sum is: %f\n",answer);
}

float sum(float list[], int n)
{
    printf("value of list = %p\n", list);           //배열 list의 이름이 가르키는 주소는 배열 input의 주소와 같다
    printf("address of list %p\n\n",&list);         //배열 list의 주소는 list가 가르키는 주소와는 다른 것이다.

    int i;
    float tempsum=0;
    for(i=0; i<n; i++)
        tempsum+=list[i];

    return tempsum;
}