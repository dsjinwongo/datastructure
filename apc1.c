#include <stdio.h>
#include <stdlib.h>

int main()
{
    int list[5];
    int *plist[5]={NULL,};

    plist[0]=(int*)malloc(sizeof(int));                         //int형 공간 1개를 heap영역에 생성하고 주소를 plist[0]에 저장한다

    list[0]=1;
    list[1]=100;

    *plist[0]=200;                                              //plist[0]을 역참조하여 200을 저장한다

    printf("-------------------[2019038095]------[이진원]----------------\n\n");

    printf("value of list[0]        = %d\n", list[0]);          //list[0]에 담긴 값
    printf("address of list[0]      = %p\n", &list[0]);         //list[0]의 주소
    printf("value of list           = %p\n", list);             //배열의 이름은 시작주소와 같다
    printf("address of list (&list) = %p\n", &list);            //list의 주소

    printf("------------------------------------------\n\n");
    printf("value of list[1]        = %d\n", list[1]);          //list[1]에 담긴 값
    printf("address of list[1]      = %p\n", &list[1]);         //list[1]의 주소
    printf("value of *(list+1)      = %d\n", *(list+1));        //list의 이름으로부터 1칸 떨어져 있는 주소를 역참조 == list[1]
    printf("address of list+1       = %p\n", list+1);           //list의 이름으로부터 1칼 떨어져 있는 주소 == &list[1]

    printf("------------------------------------------\n\n");
    printf("value of *plist[0]      = %d\n", *plist[0]);        //plist[0]을 역참조
    printf("&plist[0]               = %p\n", &plist[0]);        //plist[0]의 주소
    printf("&plist                  = %p\n", &plist);           //plist의 주소
    printf("plist                   = %p\n", plist);            //plist는 포인터배열의 이름이므로 &plist[0]과 같다
    printf("plist[0]                = %p\n", plist[0]);         //plist[0]에 담겨있는 값(주소)이다 != plist
    printf("plist[1]                = %p\n", plist[1]);         //여기서부터는 값이 NULL로 초기화되어있다.
    printf("plist[2]                = %p\n", plist[2]);
    printf("plist[3]                = %p\n", plist[3]);
    printf("plist[4]                = %p\n", plist[4]);
    
    free(plist[0]);

    return 0;
}