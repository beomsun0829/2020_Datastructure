#include<stdio.h>
#include<stdlib.h>

int main(){

    printf("------- 2019038058 HongBeomsun Software -------\n\n");
    
    int list[5];
    int *plist[5] = {NULL,};

    plist[0] = (int*) malloc(sizeof(int));
    
    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;
    
    printf("value of list[0] =            %d\n",list[0]);
    printf("address of list[0] =          %p\n",&list[0]);
    printf("value of list =               %p\n",list);      //list라는 배열의 이름 자체가 list의 첫번째 인덱스, 즉 list배열의 주소 시작점이 되는것이다.
    printf("address of list (&list) =     %p\n", &list);

    printf("----------------------------------------------------------------------------\n\n");
    printf("value of list[1] =          %d\n",list[1]);
    printf("address of list[1] =        %p\n",&list[1]);
    printf("value of *(list+1) =        %d\n" ,*(list+1));  //list[1] = list+1과 같다. +1 = sizeof(int)만큼의 주소를 이동한것과 같다는 의미.
    printf("address of list+1 =         %p\n", list+1);

    
    printf("----------------------------------------------------------------------------\n\n");

    printf("value of *plist[0] =    %d\n", *plist[0]);
    printf("&plist[0] =             %p\n", &plist[0]);  //plist의 주소는 다른곳에서 할당받은것.(malloc)
    printf("&plist =                %p\n", &plist);
    printf("plist =                 %p\n", plist);
    printf("plist[0] =              %p\n", plist[0]);
    printf("plist[1] =              %p\n", plist[1]);   //나머지는 할당받지 않았기때문에 주소가 null로 나온다.
    printf("plist[2] =              %p\n", plist[2]);
    printf("plist[3] =              %p\n", plist[3]);
    printf("plist[4] =              %p\n", plist[4]);

    free(plist[0]);



}