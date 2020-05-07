#include <stdio.h>
#include <stdlib.h>

struct student1
{
    char lastName;
    int studentId;
    char grade;
};

typedef struct          //typdef으로 선언할 경우 후에 구조체를 선언할 때 struct를 붙이지 않아도 된다.
{
    char lastName;
    int studentId;
    char grade;
} student2;

void main()
{
    printf("-------------------[2019038095]------[이진원]----------------\n\n");

    struct student1 st1={'A',100,'A'};                  //구조체 선언, 초기화

    printf("st1.lastName = %c\n", st1.lastName);        //구조체요소 연산자를 통한 출력
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2={'B',200,'B'};                         //typdef로 선언되었기에 struct 불필요

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    student2 st3;

    st3=st2;                                            //구조체 복사이다. 가능하다. 따라서 값이 st2와 동일

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);

    /*
    if(st3==st2)                                        //구조체를 이렇게 비교할 수는 없다. 구성하는 것들을 따로따로 비교하면 된다.
        printf("equal\n");
    else
        printf("not equal\n");
    */
}