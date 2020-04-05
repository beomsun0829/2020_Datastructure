#include <stdio.h>

void print1(int *ptr, int rows);

int main()
{
    printf("------- 2019038058 HongBeomsun Software -------\n\n");

    int one[] = {0, 1, 2, 3, 4};
    printf("one         = %p\n", one);      //셋 다 시작점주소를 나타냄.
    printf("&one        = %p\n", &one);
    printf("&one[0]     = %p\n", &one[0]);

    print1(&one[0], 5);

    return 0;
}

void print1(int *ptr, int rows)
{
    printf("Address \t Contents\n");
    for (int i = 0; i < rows; i++)
        printf("%p \t %5d\n", ptr + i, *(ptr + i));     //int형 배열이기때문에 4바이트씩 주소가 이동
    printf("\n");
}