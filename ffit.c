#include "./header/v4zha.h"

int main(int argc, char *argv[]) {
  int proc_no, block_no;
  printf("Enter the number of processes\n");
  scanf("%d", &proc_no);
  printf("Enter the number of Blocks\n");
  scanf("%d", &block_no);
  printf("Enter the Size of processes\n");
  Vec proc = new_vec(proc_no);
  printf("Enter the Size of Blocks\n");
  Vec block = new_vec(block_no);
  Vec flag = zero_vec(proc_no);
  Vec alloc = new_vecF(proc_no, -1);
  for (int i = 0; i < proc_no; i++) {
    for (int j = 0; j < block_no; j++) {
      printf("flag val : %d , block val : %d , proc val : %d \n",
             v_val(flag, i), v_val(block, j), v_val(proc, i));
      if (v_val(flag, i) == 0 && (v_val(block, j) >= v_val(proc, i))) {
        v_val(alloc, i) = j;
      }
    }
  }
  getVec(alloc);
  getVec(flag);
  return 0;
}
