#include <stdio.h>

struct student
{
    char lastName[13]; //13바이트
    int studentId;     //4바이트
    short grade;       //2바이트
};

//구조체 합산19바이트
//char에서 (4 * 4) - 13 = 3바이트 패딩

int main()
{

    printf("------- 2019038058 HongBeomsun Software -------\n\n");

    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student)); //출력결과 24바이트, padding된 바이트 총 5바이트
    printf("size of int = %ld\n", sizeof(int));
    printf("size of short = %ld\n", sizeof(short)); //short에서 (4 - 2 = 2) 바이트 패딩
}