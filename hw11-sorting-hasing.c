/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE            13    /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
    printf("---------------[2019038095] [이진원]---------------");
    char command;
    int *array = NULL;
    int *hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));

    do{
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

int initialize(int** a)
{
    int *temp = NULL;

    /* array가 NULL인 경우 메모리 할당 */
    if(*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else
        temp = *a;

    /* 랜덤값을 배열의 값으로 저장 */
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int *a)
{
    if(a != NULL)
        free(a);
    return 0;
}

void printArray(int *a)
{
    if (a == NULL) {
        printf("nothing to print.\n");
        return;
    }
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("a[%02d] ", i);
    printf("\n");
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}

/*
정렬되지 않은 뒷 부분 중 최소값을 찾아 정렬된 부분을 제외한 맨 처음 위치와 교체한다.
Best: O(n^2)
Worst: O(n^2)
*/
int selectionSort(int *a)
{
    int min;
    int minindex;
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i;
        min = a[i];
        for(j = i+1; j < MAX_ARRAY_SIZE; j++)
        {
            if (min > a[j])
            {
                min = a[j];
                minindex = j;
            }
        }
        a[minindex] = a[i];
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);
    return 0;
}

/*
앞부분-정렬된 부분, 뒷부분-정렬되지 않은 부분
정렬되지 않은 부분의 맨앞: j(i+1) // 정렬된 부분의 맨뒤: i
i--하면서 들어갈 위치를 탐색함.(한개씩 밀리는 구조)
Best: O(n)
Worst: O(n^2)
*/
int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i];
        j = i;
        while (a[j-1] > t && j > 0)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = t;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

/*
인접한 배열의 요소를 비교.교환하여 가장 큰 값을 맨 뒤로 보냄(인덱스 12비교 23비교 34비교 등등)
Best: O(n^2)
Worst: O(n^2)
*/
int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        /*
        가장 큰값을 맨 뒤로 보내주어 맨뒤는 정렬된 것이다.
        따라서 범위는 j < MAX_ARRAY_SIZE - i
        */
        for (j = 1; j < MAX_ARRAY_SIZE - i; j++)
        {
            if (a[j-1] > a[j])
            {
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

/*
삽입정렬의 단점(Worst case)을 보완하기 위함
h만큼 떨어져 있는 것과 비교한 후 교체
어느정도 정렬되면 삽입정렬 실행
*/
int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
    {
        for (i = 0; i < h; i++)
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
            {
                v = a[j];
                k = j;
                while (k > h-1 && a[k-h] > v)
                {
                    a[k] = a[k-h];
                    k -= h;
                }
                a[k] = v;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

/*
기준 값을 중심으로 왼쪽 부분집합과 오른쪽 부분집합으로 분할하여 정렬
ex. 한 부분집합
1. left, right 선정
2. left는 기준값보다 큰 값을 찾는다(i++), right는 기준값보다 작은걸 찾는다.(j--)
3. 이를 left가 right보다 커질 때까지 반복한다.
4. 기준값과 left의 위치를 바꾼다.
5. 기준값의 위치를 기준으로 왼쪽과 오른쪽으로 나누어 각각 퀵 정렬을 시행한다.

Worst: O(n^2) (피봇을 기준으로 부분이 한쪽으로만 나눠지는 상황이 반복)
Average: O(nlog(n)) (왼쪽와 오른쪽의 서브트리 크기가 같을 경우)
*/
int quickSort(int *a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)
    {
        v = a[n-1];
        i = -1;
        j = n - 1;

        while(1)
        {
            while(a[++i] < v);
            while(a[--j] > v);

            if (i >= j) break;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        t = a[i];
        a[i] = a[n-1];
        a[n-1] = t;

        quickSort(a, i);
        quickSort(a+i+1, n-i-1);
    }


    return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
    int *hashtable = NULL;

    /* hash table이 NULL인 경우 메모리 할당 */
    if(*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else {
        hashtable = *ht;    /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
    }

    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */

    int key = -1;
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key);       //해쉬코드를 구한다.
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1)
        {
            hashtable[hashcode] = key;
        } else     {

            index = hashcode;

            while(hashtable[index] != -1)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;        //해쉬테이블이 비지 않았다면 한칸 증가시켜 저장한다.
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key;
        }
    }

    return 0;
}

//해쉬코드를 이용하여 값을 탐색한다.
int search(int *ht, int key)
{
    int index = hashCode(key);

    if(ht[index] == key)
        return index;

    while(ht[++index] != key)
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;
}