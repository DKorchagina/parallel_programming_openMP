#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define N 700

// инициализация матрицы N на N
void randomiseMatrix(int** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 21;
        }
    }

    return;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    double start;
    double end;
    // время в начале работы программы
    start = omp_get_wtime();


    //Матрица A (N*N)
    int** matrix1;
    //Матрица B (N*N)
    int** matrix2;

    matrix1 = (int**)malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) {
        matrix1[i] = (int*)malloc(sizeof(int) * N);
    }
    matrix2 = (int**)malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) {
        matrix2[i] = (int*)malloc(sizeof(int) * N);
    }

    //Генерируем матрицы A, B для умножения
    randomiseMatrix(matrix1);
    randomiseMatrix(matrix2);

    //результирующая матрица С (N*N)
    int** result = (int**)malloc(sizeof(int*) * N);;
    for (int i = 0; i < N; i++) {
        result[i] = (int*)malloc(sizeof(int) * N);
    }

    //Устанавливаем число потоков
    omp_set_num_threads(4);

    int i, j, k;
    //параллельный регион, который является областью программы, которая будет выполняться многими потоками параллельно
    #pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                result[i][j] = 0;
                for (k = 0; k < N; k++) {
                    result[i][j] += (matrix1[i][k] * matrix2[k][j]);
                }
            }
        }

        //вывод результата
        /*for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf(" %d", result[i][j]);
            }
            printf("\n");
        }*/

    //время конца работы программы
    end = omp_get_wtime();
    //время работы программы
    printf_s("Work took %f sec. time.\n", end - start);
    return 0;
}