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

/* 
evaluate: 
 1. - 32 × 32: 8 points if m < 300, 0 points if m > 600
 2. - 64 × 64: 8 points if m < 1300, 0 points if m > 2000
 3. - 61 × 67: 10 points if m < 2000, 0 points if m > 3000
*/

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if(N==32&&M==32) {
        // 8*8 block 4*4 -> misses: 288 (ok)
        int i, j, a, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        for(i = 0; i < 32; i+=8) {
            for(j = 0; j < 32; j+=8) {
                for(a = 0; a < 8; a++) {
                    tmp0 = A[i+a][j+0];
                    tmp1 = A[i+a][j+1];
                    tmp2 = A[i+a][j+2];
                    tmp3 = A[i+a][j+3];
                    tmp4 = A[i+a][j+4];
                    tmp5 = A[i+a][j+5];
                    tmp6 = A[i+a][j+6];
                    tmp7 = A[i+a][j+7];
                    B[j+0][i+a] = tmp0;
                    B[j+1][i+a] = tmp1;
                    B[j+2][i+a] = tmp2;
                    B[j+3][i+a] = tmp3;
                    B[j+4][i+a] = tmp4;
                    B[j+5][i+a] = tmp5;
                    B[j+6][i+a] = tmp6;
                    B[j+7][i+a] = tmp7;
                }
            }
        }  
    }
    else if(N==64&&M==64) {
        // int i, j, a, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        // for(i=0;i<64;i+=4) {
        //     for(j=0;j<64;j+=4) {
        //         for(a=0;a<2;a++) {
        //             tmp0 = A[i + 2*a][j];
        //             tmp1 = A[i + 2*a][j + 1];
        //             tmp2 = A[i + 2*a][j + 2];
        //             tmp3 = A[i + 2*a][j + 3];
        //             tmp4 = A[i + 2*a + 1][j];
        //             tmp5 = A[i + 2*a + 1][j + 1];
        //             tmp6 = A[i + 2*a + 1][j + 2];
        //             tmp7 = A[i + 2*a + 1][j + 3];
        //             B[j][i + 2*a] = tmp0;
        //             B[j + 1][i + 2*a] = tmp1;
        //             B[j + 2][i + 2*a] = tmp2;
        //             B[j + 3][i + 2*a] = tmp3;
        //             B[j][i + 2*a + 1] = tmp4;
        //             B[j + 1][i + 2*a + 1] = tmp5;
        //             B[j + 2][i + 2*a + 1] = tmp6;
        //             B[j + 3][i + 2*a + 1] = tmp7;
        //         }
        //     }
        // }
        // // miss: 1652
        // int i, j;
        // int ii, jj;
        // int tmp0, tmp1, tmp2, tmp3;
        // for(i = 0; i < M; i += 8) {
        //     for(j = 0; j < N; j += 8) {
        //         for(ii = i; ii < i + 8 && ii < M; ii += 4) {
        //             for(jj = j; jj < j + 8 && jj < N; jj++) {
        //                 if(ii <= M) tmp0 = A[jj][ii];
        //                 if(ii+1 <= M) tmp1 = A[jj][ii+1];
        //                 if(ii+2 <= M) tmp2 = A[jj][ii+2];
        //                 if(ii+3 <= M) tmp3 = A[jj][ii+3];
        //                 if(ii <= M) B[ii][jj] = tmp0;
        //                 if(ii+1 <= M) B[ii+1][jj] = tmp1;
        //                 if(ii+2 <= M) B[ii+2][jj] = tmp2;
        //                 if(ii+3 <= M) B[ii+3][jj] = tmp3;
        //             }
        //         }
        //     } 
        // }
        // // miss: 1636
        int i, j;
        int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        for(i = 0; i < M; i += 4) {
            for(j = 0; j < N; j += 4) {
                tmp0 = A[j][i];
                tmp1 = A[j][i+1];
                tmp2 = A[j][i+2];
                tmp3 = A[j][i+3];
                tmp4 = A[j+2][i];
                tmp5 = A[j+2][i+1];
                tmp6 = A[j+2][i+2];
                tmp7 = A[j+2][i+3];
                B[i][j] = tmp0;
                B[i+1][j] = tmp1;
                B[i+2][j] = tmp2;
                B[i+3][j] = tmp3;
                B[i][j+2] = tmp4;
                B[i+1][j+2] = tmp5;
                B[i+2][j+2] = tmp6;
                B[i+3][j+2] = tmp7;
                tmp0 = A[j+1][i];
                tmp1 = A[j+1][i+1];
                tmp2 = A[j+1][i+2];
                tmp3 = A[j+1][i+3];
                tmp4 = A[j+3][i];
                tmp5 = A[j+3][i+1];
                tmp6 = A[j+3][i+2];
                tmp7 = A[j+3][i+3];
                B[i][j+1] = tmp0;
                B[i+1][j+1] = tmp1;
                B[i+2][j+1] = tmp2;
                B[i+3][j+1] = tmp3;
                B[i][j+3] = tmp4;
                B[i+1][j+3] = tmp5;
                B[i+2][j+3] = tmp6;
                B[i+3][j+3] = tmp7;
            }
        }
        // // miss: 8196 Wow! maybe this is the world's worst code! omg :(
        // int i, j;
        // for(i = 0; i < 8; i ++) {
        //     for(j = i; j < M*N; j += 8) {
        //         B[j%64][j/64] = A[j/64][j%64];
        //     }
        // }
        // Finding address of A and B
        // row-wise transpose --> saved A_tag, B_tag, A_set_index, B_set_index
        // int i, j, tmp;
        // for(i = 0; i < 64; i++) {
        //     for(j = 0; j < 64; j++) {
        //         tmp = A[i][j];
        //         B[j][i] = tmp;
        //     }
        // }
        // // diagonal?
        // int i, j;
        // int ii, jj;
        // int tmp0, tmp1, tmp2, tmp3;
        // int diag;
        // for(i = 0; i < M; i += 8) {
        //     for(j = 0; j < N; j += 8) {
        //         for(ii = i; ii < i + 8 && ii < M; ii += 4) {
        //             for(jj = j; jj < j + 8 && jj < N; jj++) {
        //                 diag = -1;
        //                 if(ii <= M && !(ii == jj)) tmp0 = A[jj][ii];
        //                 if(ii+1 <= M && !(ii+1 == jj)) tmp1 = A[jj][ii+1];
        //                 if(ii+2 <= M && !(ii+2 == jj)) tmp2 = A[jj][ii+2];
        //                 if(ii+3 <= M && !(ii+3 == jj)) tmp3 = A[jj][ii+3];
        //                 if(ii <= M && !(ii == jj)) B[ii][jj] = tmp0;
        //                 if(ii+1 <= M && !(ii+1 == jj)) B[ii+1][jj] = tmp1;
        //                 if(ii+2 <= M && !(ii+2 == jj)) B[ii+2][jj] = tmp2;
        //                 if(ii+3 <= M && !(ii+3 == jj)) B[ii+3][jj] = tmp3;
        //                 if(ii == jj) diag = ii;
        //                 else if(ii+1 == jj) diag = ii+1;
        //                 else if(ii+2 == jj) diag = ii+2;
        //                 else if(ii+3 == jj) diag = ii+3;
        //                 if(diag != -1) {
        //                     tmp0 = A[diag][diag];
        //                     B[diag][diag] = tmp0;
        //                 }
        //             }
        //         }
        //     } 
        // }
    }
    else {
        // int i, j;
        // int ii, jj;
        // int tmp;
        // for(i = 0; i < M; i += 16) {
        //     for(j = 0; j < N; j += 16) {
        //         for(ii = i; ii < i + 16 && ii < M; ii++) {
        //             for(jj = j; jj < j + 16 && jj < N; jj++) {
        //                 tmp = A[jj][ii];
        //                 B[ii][jj] = tmp;
        //             }
        //         }
        //     }
        // }
        // miss: 1914. Why this works so good? I'm so curious.
        int i, j;
        int ii, jj;
        int tmp0, tmp1, tmp2, tmp3;
        for(i = 0; i < M; i += 16) {
            for(j = 0; j < N; j += 16) {
                for(ii = i; ii < i + 16 && ii < M; ii += 4) {
                    for(jj = j; jj < j + 16 && jj < N; jj++) {
                        if(ii <= M) tmp0 = A[jj][ii];
                        if(ii+1 <= M) tmp1 = A[jj][ii+1];
                        if(ii+2 <= M) tmp2 = A[jj][ii+2];
                        if(ii+3 <= M) tmp3 = A[jj][ii+3];
                        if(ii <= M) B[ii][jj] = tmp0;
                        if(ii+1 <= M) B[ii+1][jj] = tmp1;
                        if(ii+2 <= M) B[ii+2][jj] = tmp2;
                        if(ii+3 <= M) B[ii+3][jj] = tmp3;
                    }
                }
            } 
        }
    }

}


char trans_attempt_desc[] = "This is collection of attempt, represented in comments";
void trans_attempt(int M, int N, int A[N][M], int B[M][N]) {
    // int i, j, a, b, tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    // if(M==32&&N==32) {
        // Fortunatelly prob 1 is solved at once!
    // }
    // else if(M==64&&N==64) {
        // // 8*8 block 8*8 -> misses: 4612 (so bad!)
        // for(i=0;i<64;i+=8) {
        //     for(j=0;j<64;j+=8) {
        //         for(a=0;a<8;a++) {
        //             tmp0 = A[i+a][j+0];
        //             tmp1 = A[i+a][j+1];
        //             tmp2 = A[i+a][j+2];
        //             tmp3 = A[i+a][j+3];
        //             tmp4 = A[i+a][j+4];
        //             tmp5 = A[i+a][j+5];
        //             tmp6 = A[i+a][j+6];
        //             tmp7 = A[i+a][j+7];
        //             B[j+0][i+a] = tmp0;
        //             B[j+1][i+a] = tmp1;
        //             B[j+2][i+a] = tmp2;
        //             B[j+3][i+a] = tmp3;
        //             B[j+4][i+a] = tmp4;
        //             B[j+5][i+a] = tmp5;
        //             B[j+6][i+a] = tmp6;
        //             B[j+7][i+a] = tmp7;
        //         }
        //     }
        // }
        // // 2*2 blocks 32*32 -> miss: 2660 (better, but still bad)
        // for(i=0;i<64;i+=2) {
        //     for(j=0;j<64;j+=2) {
        //         tmp0 = A[i][j];
        //         tmp1 = A[i][j+1];
        //         tmp2 = A[i+1][j];
        //         tmp3 = A[i+1][j+1];
        //         B[j][i] = tmp0;
        //         B[j+1][i] = tmp1;
        //         B[j][i+1] = tmp2;
        //         B[j+1][i+1] = tmp3;
        //     }
        // }
        // // 4*4 block 16*16 -> misses: 1668 (not ok, limit is 1300)
        // // archive - No.3
        // for(i=0;i<64;i+=4) {
        //     for(j=0;j<64;j+=4) {
        //         for(a=0;a<2;a++) {
        //             tmp0 = A[i + 2*a][j];
        //             tmp1 = A[i + 2*a][j + 1];
        //             tmp2 = A[i + 2*a][j + 2];
        //             tmp3 = A[i + 2*a][j + 3];
        //             tmp4 = A[i + 2*a + 1][j];
        //             tmp5 = A[i + 2*a + 1][j + 1];
        //             tmp6 = A[i + 2*a + 1][j + 2];
        //             tmp7 = A[i + 2*a + 1][j + 3];
        //             B[j][i + 2*a] = tmp0;
        //             B[j + 1][i + 2*a] = tmp1;
        //             B[j + 2][i + 2*a] = tmp2;
        //             B[j + 3][i + 2*a] = tmp3;
        //             B[j][i + 2*a + 1] = tmp4;
        //             B[j + 1][i + 2*a + 1] = tmp5;
        //             B[j + 2][i + 2*a + 1] = tmp6;
        //             B[j + 3][i + 2*a + 1] = tmp7;
        //         }
        //     }
        // }
        // // 4*4 block 16*16 (fixed ver) -> misses: 1700 (still...)
        // for(i=0;i<64;i+=4) {
        //     for(j=0;j<64;j+=4) {
        //         for(a=0;a<4;a++) {
        //             tmp0 = A[i + a][j];
        //             tmp1 = A[i + a][j + 1];
        //             tmp2 = A[i + a][j + 2];
        //             tmp3 = A[i + a][j + 3];
        //             B[j][i + a] = tmp0;
        //             B[j + 1][i + a] = tmp1;
        //             B[j + 2][i + a] = tmp2;
        //             B[j + 3][i + a] = tmp3;
        //         }
        //     }
        // }
    // }
        // archive -- No. 4, (miss: 2216)
        // else { 
        //     int i, j;
        //     int ii, jj;
        //     int tmp;
        //     for(i = 0; i < M; i += 8) {
        //         for(j = 0; j < N; j += 8) {
        //             for(ii = i; ii < i + 8 && ii < M; ii++) {
        //                 for(jj = j; jj < j + 8 && jj < N; jj++) {
        //                     tmp = A[jj][ii];
        //                     B[ii][jj] = tmp;
        //                 }
        //             }
        //         }
        //     }
        // }
    // }
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
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    
}


char col_wise_trans_desc[] = "Simple column-wise scan transpose";
void col_wise_trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[j][i];
            B[i][j] = tmp;
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
    registerTransFunction(col_wise_trans, col_wise_trans_desc);
    // registerTransFunction(trans1, trans1_desc);

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

