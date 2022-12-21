#include "./header/v4zha.h"

bool even(int x) { return x % 2 == 0; }
int main(int argc, char *argv[]) {
  Vec v = new_vec(5);
  printf("Enter Vector values\n");
  setVec(v);
  printf("Getting Vector values\n");
  getVec(v);
  printf("Getting Filtered Vector values\n");
  Vec res = vecFilter(v, even);
  getVec(res);
  return 0;
}
