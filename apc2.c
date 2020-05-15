#include <stdio.h>
#include <stdlib.h>

int main()
{
    int list[5];
    int *plist[5];

    plist[0]=(int*)malloc(sizeof(int));                         

    list[0]=10;
    list[1]=11;

    printf("-------------------[2019038095]------[이진원]----------------\n\n");

    printf("list[0] \t=%d\n",list[0]);                  //list[0]의 값
    printf("address of list \t=%p\n",list);             //list는 배열의 이름이므로 배열의 시작주소를 출력 == &list[0]
    printf("address of list[0] \t=%p\n",&list[0]);
    printf("address of list + 0 \t=%p\n",list+0);       //list+0은 list로부터 0칸 떨어진 곳의 주소
    printf("address of list + 0 \t=%p\n",list+1);       //list+1은 list로부터 1칸 떨어진 곳의 주소
    printf("address of list + 0 \t=%p\n",list+2);       //list+2은 list로부터 2칸 떨어진 곳의 주소
    printf("address of list + 0 \t=%p\n",list+3);       //list+3은 list로부터 3칸 떨어진 곳의 주소
    printf("address of list + 0 \t=%p\n",list+4);       //list+4은 list로부터 4칸 떨어진 곳의 주소
    printf("address of list[4] \t=%p\n",&list[4]);      //list[4]의 주소 == list +4
   
    free(plist[0]);

    return 0;
}