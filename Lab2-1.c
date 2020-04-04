#include <stdio.h>
int main(){

    char charType;
    int integerType;
    float floatType;
    double doubleType;

    printf("-----SOFTWARE, HongBeomsun, 2019038058-----\n");

    printf("Size of char: %ld byte\n",sizeof(charType));        //char자료형의 사이즈
    printf("Size of int: %ld bytes\n",sizeof(integerType));     //int자료형의 사이즈  
    printf("Size of float: %ld bytes\n",sizeof(floatType));     //float자료형의 사이즈
    printf("Size of double: %ld bytes\n",sizeof(doubleType));   //double자료형의 사이즈

    printf("-----------------------------------------\n");

    printf("Size of char: %ld byte\n",sizeof(char));
    printf("Size of int: %ld bytes\n",sizeof(int));
    printf("Size of float: %ld bytes\n",sizeof(float));
    printf("Size of double: %ld bytes\n",sizeof(double));

    printf("-----------------------------------------\n");

    printf("Size of char*: %ld bytes\n",sizeof(char*));          //char자료형포인터의 사이즈
    printf("Size of int*: %ld bytes\n",sizeof(int*));            //int자료형포인터의 사이즈
    printf("Size of float*: %ld bytes\n",sizeof(float*));        //float자료형포인터의 사이즈
    printf("Size of double*: %ld bytes\n",sizeof(double*));      //double자료형포인터의 사이즈

}