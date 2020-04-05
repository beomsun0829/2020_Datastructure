#include <stdio.h>

#define MAX_SIZE 100

float sum(float[], int);
float input[MAX_SIZE], answer;

int main()
{
    printf("------- 2019038058 HongBeomsun Software -------\n\n");

    for (int i = 0; i < MAX_SIZE; i++)
        input[i] = i;

    answer = sum(input, MAX_SIZE);
    printf("The sum is: %f\n", answer);
}

 

float sum(float list[], int n)
{

    printf("value of list = %p\n", list);
    printf("address of list = %p\n\n", &list);      //배열 전체가 아닌 주솟값만 가져옴.

    float tempsum = 0;
    for (int i = 0; i < n; i++)
    {
        tempsum += list[i]; 
    }

    return tempsum;
}