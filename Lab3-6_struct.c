#include <stdio.h>

struct student1
{
    char lastName;
    int studentId;
    char grade;
};

typedef struct //typedef를 이용해서 struct 대신 student2로 쓸수있음
{
    char lastName;
    int studentId;
    char grade;
} student2;

int main()
{

    printf("------- 2019038058 HongBeomsun Software -------\n\n");

    struct student1 st1 = {'A', 100, 'A'};

    printf("st1.lastNmae = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'};

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    student2 st3;

    st3 = st2;

    printf("\nst3.lastName = %c\n", st3.lastName); //st3 = st2에서 구조체를 그대로 복사해놨으므로 동일한 데이터 출력
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);
}