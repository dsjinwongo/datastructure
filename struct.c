#include <stdio.h>
#include <stdlib.h>

struct student1
{
    char lastName;
    int studentId;
    char grade;
};

typedef struct          //typdef���� ������ ��� �Ŀ� ����ü�� ������ �� struct�� ������ �ʾƵ� �ȴ�.
{
    char lastName;
    int studentId;
    char grade;
} student2;

void main()
{
    printf("-------------------[2019038095]------[������]----------------\n\n");

    struct student1 st1={'A',100,'A'};                  //����ü ����, �ʱ�ȭ

    printf("st1.lastName = %c\n", st1.lastName);        //����ü��� �����ڸ� ���� ���
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2={'B',200,'B'};                         //typdef�� ����Ǿ��⿡ struct ���ʿ�

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    student2 st3;

    st3=st2;                                            //����ü �����̴�. �����ϴ�. ���� ���� st2�� ����

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);

    /*
    if(st3==st2)                                        //����ü�� �̷��� ���� ���� ����. �����ϴ� �͵��� ���ε��� ���ϸ� �ȴ�.
        printf("equal\n");
    else
        printf("not equal\n");
    */
}