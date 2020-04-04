#include <stdio.h>
int main()
{
    int i;
    int *ptr;
    int **dptr;

    i = 1234;

    printf("-----SOFTWARE, HongBeomsun, 2019038058-----\n");

    printf("[checking values before ptr = &i] \n");
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);     //i의 주소값
    printf("value of ptr == %p\n", ptr);    //초기화되지않은 쓰레기값
    printf("address of ptr == %p\n", &ptr); //ptr의 주소값

    ptr = &i; 

    printf("\n[checking values after ptr = &i] \n");
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);     //i의 주소값 그대로
    printf("value of ptr == %p\n", ptr);    //i의 주소값이 ptr에게 있으니까 위에줄과 같다
    printf("address of ptr == %p\n", &ptr); //ptr의 주소는 선언되었을때 그대로
    printf("value of *ptr == %d\n", *ptr);  //*ptr는 i의 value와 같음

    dptr = &ptr;

    printf("\n[checking values after dptr = &ptr] \n");
    
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);
    printf("value of ptr == %p\n", ptr);
    printf("address of ptr == %p\n", &ptr);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of dptr == %p\n", dptr);  //dptr의 값은 &ptr 즉 ptr의 주소값과 같다
    printf("address of dptr == %p\n", &dptr);   //dptr의 주소는 선언될때
    printf("value of *dptr == %p\n", *dptr);    //*dptr의 값은 ptr의 값
    printf("value of **dptr == %d\n", **dptr);  //*dptr == ptr고 *ptr == i 이므로 **dptr == i

    *ptr = 7777; 

    printf("\n[after *ptr = 7777] \n");
    printf("value of i == %d\n", i);    //*ptr == i 이므로 i가 7777
    printf("value of *ptr == %d\n", *ptr);  //*ptr = 7777
    printf("value of **dptr == %d\n", **dptr);  //**dptr == i 이므로 7777

    **dptr = 8888; 

    printf("\n[after **dptr = 8888] \n");
    printf("value of i == %d\n", i);
    printf("value of *ptr == %d\n", *ptr);
    printf("value of **dptr == %d\n", **dptr);
}