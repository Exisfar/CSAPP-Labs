/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
/* 采用分块（blocking）方式，使子块能够驻留在缓存中，从而减少miss次数 */
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, l;
    // ? cache块大小为32B，每个cache行能存8个4字节int。这里模拟的cache有1KiB，cache最多有32行。模拟cache最多容纳个256字节int，所以block_size最好设为16。
    int block_size = 16;
    int tmp;

    // 在块中处理来改进缓存的局部性
    for (i = 0; i < N; i += block_size) {
        for (j = 0; j < M; j += block_size) {
            for (k = i; k < i + block_size && k < N; k++) {
                for (l = j; l < j + block_size && l < M; l++) {
                    tmp = A[k][l];
                    B[l][k] = tmp;
                }
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp; // 为什么要有tmp：如果A、B是相同矩阵，没有tmp就会出错

    // * 1. A访问模式好：按行读取A（连续内存），一次cache块hit多个元素
    // ! 2. B访问模式差：按列写入B（跳跃式访问），每次写B都是不同cache行，导致大量miss（Cache只有1KB，32字节block，存不了整列。每写一个B[j][i]就可能evict之前的数据）
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

