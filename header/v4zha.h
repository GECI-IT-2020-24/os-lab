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
struct Matrix *mtxInit(int, int);
struct Vector *Vector(int);
void getVec(struct Vector *);
void setVec(struct Vector *);
void setVecVal(struct Vector *, int);
struct Vector *vecFillVal(int, int);
struct Vector *vecInit(int);
int *arrMap(int *, int, int (*fn)(int));
int *arrIndexMap(int *, int, int (*fn)(int, int));
int arrReduce(int *, int, int, int (*fn)(int, int));
void pushVec(struct Vector *, int);
struct Vector *vecMap(struct Vector *, int (*fn)(int));
struct Vector *vecIndexMap(struct Vector *, int (*fn)(int, int));
struct Vector *cloneVec(struct Vector *);
int vecReduce(struct Vector *, int, int (*fn)(int, int));
int vecFind(struct Vector *, bool (*fn)(int));
int vecFindIndex(struct Vector *, bool (*fn)(int));
struct Vector *vecFilter(struct Vector *, bool (*fn)(int));

// Reduce with default accumulator
#define arrReduceD(arr, size, fn) (arrReduce(arr, size, 0, fn))

#define vecReduceD(vec, fn) (vecReduce(vec, 0, fn))

#define new_vec(size) (vecInit(size))

// fill Vector will value
#define new_vecF(size, val) (vecFillVal(size, val))

#define zero_vec(size) (vecFillVal(size, 0))

#define vec_range(start, end) (range(start, end))

#define new_mtx(m, n) (mtxInit(m, n))

#define new_mtxF(m, n, val) (mtxFillVal(m, n, val))

#define zero_mtx(m, n) (mtxFillVal(m, n, 0))

#define mtx_val(mtx, i, j) (*(*(mtx->data + i) + j))

#define v_val(v, i) (*(v->data + i))

#define clone_vec(v) (cloneVec(v))

typedef struct Vector *Vec;
typedef struct Matrix *Mtx;

#endif

struct Matrix *Matrix(int m, int n) {
  int **data = (int **)malloc(m * sizeof(int *) + (sizeof(int) * n * m));
  for (int i = 0; i < m; i++) {
    // set row pointer : )
    *(data + i) = (int *)(data + m + n * i);
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
      scanf("%d", (*(mtx->data + i) + j));
    }
  }
}
void freeMtx(struct Matrix *mtx) {
  free(mtx->data);
  free(mtx);
}
struct Matrix *mtxInit(int m, int n) {
  struct Matrix *mtx = Matrix(m, n);
  setMtx(mtx);
  return mtx;
}

void setMtxVal(struct Matrix *mtx, int val) {
  for (int i = 0; i < mtx->r_size; i++) {
    for (int j = 0; j < mtx->c_size; j++) {
      // use memset as alternative : )
      *(*(mtx->data + i) + j) = val;
    }
  }
}

struct Matrix *mtxFillVal(int m, int n, int val) {
  struct Matrix *mtx = Matrix(m, n);
  setMtxVal(mtx, val);
  return mtx;
}
void mtxSum(Mtx res, Mtx a, Mtx b) {
  if (a->c_size != b->c_size || a->r_size != b->r_size) {
    printf("Error getting sum of Matrix \n");
    exit(0);
  } else {
    for (int i = 0; i < a->r_size; i++) {
      for (int j = 0; j < a->c_size; j++) {
        res->data[i][j] = a->data[i][j] + b->data[i][j];
      }
    }
  }
}
void mtxDiff(Mtx res, Mtx a, Mtx b) {
  if (a->c_size != b->c_size || a->r_size != b->r_size) {
    printf("Error getting sum of Matrix \n");
    exit(0);
  } else {
    for (int i = 0; i < a->r_size; i++) {
      for (int j = 0; j < a->c_size; j++) {
        res->data[i][j] = a->data[i][j] - b->data[i][j];
      }
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
// void unsafeSetVec(struct Vector *vec, char *desc) {
//   for (int i = 0; i < vec->size; i++) {
//     // Unsafe : )
//     // sanitize format string before execution
//     // Note : May result in formatString exploits : )
//     printf(desc, i);
//     scanf("%d", vec->data + i);
//   }
//   printf("\n");
// }

struct Vector *vecInit(int size) {
  struct Vector *v = Vector(size);
  setVec(v);
  return v;
}
void setVecVal(struct Vector *vec, int val) {
  for (int i = 0; i < vec->size; i++) {
    // use memset as alternative : )
    *(vec->data + i) = val;
  }
}

struct Vector *vecFillVal(int size, int val) {
  Vec v = Vector(size);
  setVecVal(v, val);
  return v;
}

void pushVec(struct Vector *vec, int val) {
  vec->data = (int *)realloc(vec->data, sizeof(int));
  vec->size += 1;
  *(vec->data + vec->size - 1) = val;
}

struct Vector *cloneVec(struct Vector *vec) {
  int size = vec->size;
  int *new_data = (int *)malloc(sizeof(int) * size);
  memcpy(new_data, vec->data, size * sizeof(int));
  struct Vector *new_vec = (struct Vector *)malloc(sizeof(struct Vector));
  new_vec->size = size;
  new_vec->data = new_data;
  return new_vec;
}
void freeVec(struct Vector *vec) {
  free(vec->data);
  free(vec);
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
int *arrIndexMap(int *arr, int size, int (*fn)(int, int)) {
  int *newArr = (int *)malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    *(newArr + i) = fn(*(arr + i), i);
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
  freeVec(vec);
  struct Vector *v = (struct Vector *)malloc(sizeof(struct Vector));
  v->size = size;
  v->data = new_data;
  return v;
}
struct Vector *vecIndexMap(struct Vector *vec, int (*fn)(int, int)) {
  int size = vec->size;
  int *new_data = arrIndexMap(vec->data, vec->size, fn);
  freeVec(vec);
  struct Vector *v = (struct Vector *)malloc(sizeof(struct Vector));
  v->size = size;
  v->data = new_data;
  return v;
}

int vecReduce(struct Vector *vec, int acc, int (*fn)(int, int)) {
  int res = arrReduce(vec->data, vec->size, acc, fn);
  freeVec(vec);
  return res;
}

int vecSum(struct Vector *vec) {
  // reduce not used bcoz reduce frees Vector after call [takes ownership] : )
  int sum = 0;
  for (int i = 0; i < vec->size; i++) {
    sum += vec->data[i];
  }
  return sum;
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
  freeVec(vec);
  struct Vector *resVec = (struct Vector *)malloc(sizeof(struct Vector));
  resVec->size = new_size;
  resVec->data = resData;
  return resVec;
}

int vecFind(struct Vector *vec, bool (*fn)(int)) {
  int val = -1;
  for (int i = 0; i < vec->size; i++) {
    if (fn(*(vec->data + i))) {
      val = *(vec->data + i);
      break;
    }
  }
  return val;
}
int vecFindIndex(struct Vector *vec, bool (*fn)(int)) {
  int index = -1;
  for (int i = 0; i < vec->size; i++) {
    if (fn(*(vec->data + i))) {
      index = i;
      break;
    }
  }
  return index;
}

struct Vector *range(int start, int end) {
  if (start >= end) {
    printf("Error! %d > %d , Cannot generate Range", start, end);
    exit(0);
  }
  int size = end - start;
  Vec res = Vector(size);
  for (int i = start; i < end; i++) {
    v_val(res, i) = i;
  }
  return res;
}
