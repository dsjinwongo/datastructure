#include <stdio.h>
#include <stdlib.h>

int main()
{
    int list[5];
    int *plist[5];

    plist[0]=(int*)malloc(sizeof(int));                         

    list[0]=10;
    list[1]=11;

    printf("-------------------[2019038095]------[������]----------------\n\n");

    printf("list[0] \t=%d\n",list[0]);                  //list[0]�� ��
    printf("address of list \t=%p\n",list);             //list�� �迭�� �̸��̹Ƿ� �迭�� �����ּҸ� ��� == &list[0]
    printf("address of list[0] \t=%p\n",&list[0]);
    printf("address of list + 0 \t=%p\n",list+0);       //list+0�� list�κ��� 0ĭ ������ ���� �ּ�
    printf("address of list + 0 \t=%p\n",list+1);       //list+1�� list�κ��� 1ĭ ������ ���� �ּ�
    printf("address of list + 0 \t=%p\n",list+2);       //list+2�� list�κ��� 2ĭ ������ ���� �ּ�
    printf("address of list + 0 \t=%p\n",list+3);       //list+3�� list�κ��� 3ĭ ������ ���� �ּ�
    printf("address of list + 0 \t=%p\n",list+4);       //list+4�� list�κ��� 4ĭ ������ ���� �ּ�
    printf("address of list[4] \t=%p\n",&list[4]);      //list[4]�� �ּ� == list +4
   
    free(plist[0]);

    return 0;
}