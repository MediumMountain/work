#include <stdio.h>
#include <stdlib.h>

/* 3次元配列の領域確保 */
int ***malloc_3dim_array(int n1, int n2, int n3) {
  int i, j;
  int ***array;
  array = (int ***)malloc(n1 * sizeof(int **));
  for (i = 0; i < n1; i++) {
    array[i] = (int **)malloc(n2 * sizeof(int *));
    for (j = 0; j < n2; j++)
      array[i][j] = (int*)malloc(n3 * sizeof(int));
  }
  return array;
}

/* 3次元配列の開放 */
void free_3dim_array(int ***array, int n1, int n2, int n3) {
  int i, j;
  for (i = 0; i < n1; i++) {
    for (j = 0; j < n2; j++)
      free(array[i][j]);
    free(array[i]);
  }
  free(array);
}

/* 3次元配列の表示 */
void print_3dim_array(int ***array, int n1, int n2, int n3) {
  int i, j, k;
  for (i = 0; i < n1; i++) {
    for (j = 0; j < n2; j++) {
      for (k = 0; k < n3; k++)
        printf("%d ", array[i][j][k]);
      printf("\n");
    }
    printf("\n");
  }
}

/* 3次元配列を扱うプログラム */
int main() {
  const int N1 = 2;
  const int N2 = 2;
  const int N3 = 3;

  int ***array = malloc_3dim_array(N1, N2, N3);
  
  array[0][0][0] = 1; array[0][0][1] = 2; array[0][0][2] = 3;
  array[0][1][0] = 4; array[0][1][1] = 5; array[0][1][2] = 6;
  
  array[1][0][0] = 7; array[1][0][1] = 8; array[1][0][2] = 9;
  array[1][1][0] = 0; array[1][1][1] = 1; array[1][1][2] = 2;
  
  print_3dim_array(array, N1, N2, N3);
  
  free_3dim_array(array, N1, N2, N3);

  return 0;
}