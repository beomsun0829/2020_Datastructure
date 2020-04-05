#include<stdio.h>
#include<stdlib.h>

int main(){
    printf("------- 2019038058 HongBeomsun Software -------\n\n");

    int list[5];
    int *plist[5];

    list[0] = 10;
    list[1] = 11;


    plist[0] = (int*)malloc(sizeof(int));

    printf("list[0] \t = %d\n", list[0]);   
    printf("address of list \t = %p\n", list);     //배열의 시작부분( list == list[0] ) 
    printf("address of list[0] \t = %p\n", &list[0]);
    printf("address of list + 0 \t = %p\n", list + 0);
    printf("address of list + 1 \t = %p\n", list + 1);
    printf("address of list + 2 \t = %p\n", list + 2);      //주소 하나당 sizeof(int) 만큼, 즉 4바이트만큼 주소값이 증가함.
    printf("address of list + 3 \t = %p\n", list + 3);
    printf("address of list + 4 \t = %p\n", list + 4);
    printf("address of list[4] \t = %p\n", &list[4]);

    free(plist[0]);
}