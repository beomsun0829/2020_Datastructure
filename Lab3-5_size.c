#include<stdio.h>
#include<stdlib.h>

int main(){

    printf("------- 2019038058 HongBeomsun Software -------\n\n");
    
    int **x;
    
    //%lu = long unsigned decimal

    printf("sizeof(x) = %lu\n", sizeof(x));     //주소를 저장하는 곳(64비트환경이면 8바이트, 32비트환경이면 4바이트)
    printf("sizeof(*x) = %lu\n", sizeof(*x));   //위와 동일하게 주소저장
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //두번 레퍼런스 해서 간 곳의 크기는 (int)를 저장하는 곳 -> int는 4바이트
}