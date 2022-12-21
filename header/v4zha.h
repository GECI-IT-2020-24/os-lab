#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef V4ZHA
#define V4ZHA

struct Matrix {
  int r_size;
  int c_size;
  int **data;
};

struct Vector {
  int size;
  int *data;
};

// Dynamic allocated types

struct Matrix *Matrix(int, int);
void getMatrix(struct Matrix *);
void setMatrix(struct Matrix *);
struct Vector *Vector(int);
void getVector(struct Vector *);
void setVector(struct Vector *);
int *arrMap(int *, int, int (*fn)(int));
int arrReduce(int *, int, int, int (*fn)(int, int));
struct Vector *pushVec(struct Vector *, int);
struct Vector *vecMap(struct Vector *, int (*fn)(int));
int vecReduce(struct Vector *, int, int (*fn)(int, int));
struct Vector *vecFilter(struct Vector *, bool (*fn)(int));

#define arrReduceD(arr, size, fn) (arrReduce(arr, size, 0, fn))

#define vecReduceD(vec, fn) (vecReduce(vec, 0, fn))

#define new_vec(size) (Vector(size))

#define new_mtx(m, n) (Matrix(m, n))

typedef struct Vector *Vec;
typedef struct Matrix *Mtx;

#endif

struct Matrix *Matrix(int m, int n) {
  int **data = (int **)malloc(m * sizeof(int *));
  for (int i = 0; i < m; i++) {
    *(data + i) = (int *)malloc(sizeof(int) * n);
  }
  struct Matrix *mtx = (struct Matrix *)malloc(sizeof(struct Matrix));
  mtx->r_size = m;
  mtx->c_size = n;
  mtx->data = data;
  return mtx;
}

void getMtx(struct Matrix *mtx) {
  printf("Mtx Size : < %d x %d >\n", mtx->r_size, mtx->c_size);
  for (int i = 0; i < mtx->r_size; i++) {
    for (int j = 0; j < mtx->c_size; j++) {
      printf("%d ", *(*(mtx->data + i) + j));
    }
    printf("\n");
  }
}

void setMtx(struct Matrix *mtx) {
  for (int i = 0; i < mtx->r_size; i++) {
    for (int j = 0; j < mtx->c_size; j++) {
      printf("[%d,%d] : ", i, j);
      scanf("%d", *(mtx->data + i) + j);
    }
  }
}

struct Vector *Vector(int size) {
  int *data = (int *)malloc(size * sizeof(int));
  struct Vector *vec = (struct Vector *)malloc(sizeof(struct Vector));
  vec->size = size;
  vec->data = data;
  return vec;
}

void getVec(struct Vector *vec) {
  printf("Vec Size : < %d >\n", vec->size);
  for (int i = 0; i < vec->size; i++) {
    printf("%d ", *(vec->data + i));
  }
  printf("\n");
}

void setVec(struct Vector *vec) {
  for (int i = 0; i < vec->size; i++) {
    printf("[%d] : ", i);
    scanf("%d", vec->data + i);
  }
  printf("\n");
}

struct Vector *pushVec(struct Vector *vec, int val) {
  int new_size = vec->size + 1;
  int *new_data = (int *)malloc(sizeof(int) * new_size);
  memcpy(new_data, vec->data, vec->size * sizeof(int));
  *(new_data + new_size) = val;
  // takes ownership and free old Vector
  free(vec);
  struct Vector *newVec = (struct Vector *)malloc(sizeof(struct Vector));
  return newVec;
}

int *arrMap(int *arr, int size, int (*fn)(int)) {
  int *newArr = (int *)malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    *(newArr + i) = fn(*(arr + i));
  }
  // takes ownership of array
  free(arr);
  return newArr;
}

int arrReduce(int *arr, int size, int acc, int (*fn)(int, int)) {
  for (int i = 0; i < size; i++) {
    acc = fn(acc, *(arr + i));
  }
  // takes ownership and frees array
  free(arr);
  return acc;
}

struct Vector *vecMap(struct Vector *vec, int (*fn)(int)) {
  int size = vec->size;
  int *new_data = arrMap(vec->data, vec->size, fn);
  free(vec);
  struct Vector *v = (struct Vector *)malloc(sizeof(struct Vector));
  v->size = size;
  v->data = new_data;
  return v;
}

int vecReduce(struct Vector *vec, int acc, int (*fn)(int, int)) {
  int res = arrReduce(vec->data, vec->size, acc, fn);
  free(vec);
  return res;
}

struct Vector *vecFilter(struct Vector *vec, bool (*fn)(int)) {
  int new_size = 0;
  for (int i = 0; i < vec->size; i++) {
    if (fn(*(vec->data + i))) {
      new_size++;
    }
  }
  int *resData = (int *)malloc(sizeof(int) * new_size);
  int count = 0;
  for (int i = 0; i < vec->size; i++) {
    if (fn(*(vec->data + i))) {
      *(resData + count) = *(vec->data + i);
      count++;
    }
  }
  free(vec);
  struct Vector *resVec = (struct Vector *)malloc(sizeof(struct Vector));
  resVec->size = new_size;
  resVec->data = resData;
  return resVec;
}
