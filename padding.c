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
    printf("-------------------[2019038095]------[이진원]----------------\n\n");

    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student));      //구조체의 크기(16+4+4)(lastName[13]의 크기가 13+padding에 의한3으로 16이다.)
    printf("size of int = %ld\n", sizeof(int));                     //int의 크기는 4
    printf("size of short = %ld\n", sizeof(short));                 //short의 크기는 3이나 padding에 의해 4가 할당
}