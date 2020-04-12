#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int **create_matrix(int row, int col){
    if (row <= 0 || col <= 0)       //배열의 최소 범위를 벗어나면 오류
    {
        printf("Check the sizes of row and col!\n");
        return -1;
    }

    int **arr = (int**)malloc(sizeof(int *) * row);     //1차할당을 하고 그속에 2차할당을 하여 2차원배열 생성.
    for (int i = 0; i < row; i++)
        arr[i] = (int*)malloc(sizeof(int) * col);


    if (arr == NULL)
    {
        return -1;
    }
    return arr;
}

int fill_data(int **matrix,int row, int col){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 20;     //srand와 time을 이용하여 무작위 생성, rand()%20은 0~20까지의 랜덤숫자 형성
        }
    }
    return 1;
}

void print_matrix(int** matrix, int row, int col){
    for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    printf("\n\n");
}

int free_matrix(int** matrix, int row, int col){
    for(int i=0;i<row;i++){     //메모리에서 할당해제
        free(matrix[i]);
    }
    free(matrix);
    return 1;
}


int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum,int row, int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];     //행렬 더하기
        }
    }
    return 1;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sum,int row, int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix_sum[i][j] = matrix_a[i][j] - matrix_b[i][j];     //행렬 빼기
        }
    }
    return 1;
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix_t[i][j] = matrix[j][i];      //전치행렬(대각행을 중심으로 반전되었으므로 행과열을 바꾸어 넣으면 된다)
        }
    }
    return 1;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt,int row, int col){
    if(row != col){ 
        printf("행렬연산 수행불가\n");      //두 행렬중 a의 뒤와 t의 앞의 size가 다른경우 행렬연산 수행불가
        return -1;
    }
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            for(int k = 0; k < col; k++){
                matrix_axt[i][j] +=matrix_a[i][k] * matrix_t[k][j];     //행렬곱셈연산
            }
        }
    }
    return 0;
}


int main()
{
    
    srand(time(NULL));
    printf("---2019038058 Hongbeomsun---\n\n");
    int row, col;
    scanf("%d %d", &row, &col);
    printf("\n");

    int **dt_A = create_matrix(row, col);
    int **dt_B = create_matrix(row, col);
    int **dt_SUM = create_matrix(row,col);
    int **dt_SUB = create_matrix(row,col);
    int **dt_T = create_matrix(row,col);
    int **dt_axT = create_matrix(row,col);

    fill_data(dt_A,row, col);
    fill_data(dt_B,row, col);
    
    addition_matrix(dt_A,dt_B,dt_SUM,row,col);
    subtraction_matrix(dt_A,dt_B,dt_SUB,row,col);
    transpose_matrix(dt_A,dt_T,row,col);
    multiply_matrix(dt_A,dt_T,dt_axT,row,col);



    print_matrix(dt_A,row,col);
    print_matrix(dt_B,row,col);
    print_matrix(dt_SUM,row,col);
    print_matrix(dt_SUB,row,col);
    print_matrix(dt_T,row,col);
    print_matrix(dt_axT,row,col);

    free_matrix(dt_A,row,col);
    free_matrix(dt_B,row,col);
}