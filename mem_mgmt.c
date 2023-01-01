#include "./header/v4zha.h"

#define alloc_print(x)                                                         \
  {                                                                            \
    if (x == -1) {                                                             \
      printf("None : ) \n");                                                   \
    } else {                                                                   \
      printf("%d\n", x);                                                       \
    }                                                                          \
  }
#define print_footer(chr, size)                                                \
  {                                                                            \
    for (int i = 0; i < size; i++) {                                           \
      printf("%s", chr);                                                       \
    }                                                                          \
    printf("\n");                                                              \
  }

Vec firstFit(Vec, Vec);
Vec bestFit(Vec, Vec);
Vec worstFit(Vec, Vec);
void displayAlloc(Vec, Vec, char *);

int main(int argc, char *argv[]) {
  int proc_no, block_no;
  printf("Enter the number of processes\n");
  scanf("%d", &proc_no);
  printf("Enter the Size of processes\n");
  Vec proc = new_vec(proc_no);
  printf("Enter the number of Blocks\n");
  scanf("%d", &block_no);
  printf("Enter the Size of Blocks\n");
  Vec ffit_block = new_vec(block_no);
  Vec bfit_block = clone_vec(ffit_block);
  Vec wfit_block = clone_vec(bfit_block);
  Vec ffit_alloc = firstFit(proc, ffit_block);
  print_footer("-", 40);
  displayAlloc(proc, ffit_alloc, "FirstFit");
  freeVec(ffit_alloc);
  freeVec(ffit_block);
  Vec bfit_alloc = bestFit(proc, bfit_block);
  displayAlloc(proc, bfit_alloc, "BestFit");
  freeVec(bfit_alloc);
  freeVec(bfit_block);
  Vec wfit_alloc = worstFit(proc, wfit_block);
  displayAlloc(proc, wfit_alloc, "WorstFit");
  freeVec(wfit_alloc);
  freeVec(wfit_block);
  return 0;
}

Vec firstFit(Vec proc, Vec block) {
  int proc_no = proc->size;
  int block_no = block->size;
  Vec alloc = new_vecF(proc_no, -1);
  for (int i = 0; i < proc_no; i++) {
    for (int j = 0; j < block_no; j++) {
      if ((v_val(block, j) >= v_val(proc, i))) {
        v_val(alloc, i) = j;
        v_val(block, j) -= v_val(proc, i);
        break;
      }
    }
  }
  return alloc;
}

Vec bestFit(Vec proc, Vec block) {
  int proc_no = proc->size;
  int block_no = block->size;
  Vec alloc = new_vecF(proc_no, -1);
  for (int i = 0; i < proc_no; i++) {
    int index = -1;
    for (int j = 0; j < block_no; j++) {
      if (v_val(block, j) >= v_val(proc, i)) {
        if (index == -1) {
          index = j;
        } else if (v_val(block, index) > v_val(block, j)) {
          index = j;
        }
      }
    }
    if (index != -1) {
      v_val(alloc, i) = index;
      v_val(block, index) -= v_val(proc, i);
    }
  }
  return alloc;
}

Vec worstFit(Vec proc, Vec block) {

  int proc_no = proc->size;
  int block_no = block->size;
  Vec alloc = new_vecF(proc_no, -1);
  for (int i = 0; i < proc_no; i++) {
    int index = -1;
    for (int j = 0; j < block_no; j++) {
      if (v_val(proc, i) <= v_val(block, j)) {
        if (index == -1) {
          index = j;
        } else if (v_val(block, j) > v_val(block, index)) {
          index = j;
        }
      }
    }
    if (index != -1) {
      v_val(alloc, i) = index;
      v_val(block, index) -= v_val(proc, i);
    }
  }
  return alloc;
}

void displayAlloc(Vec proc, Vec alloc, char *desc) {
  printf("\n\t\t%s\n", desc);
  int proc_no = proc->size;
  print_footer("=", 40);
  printf("Proc No.\tProc Size\tBlock No\n");
  for (int i = 0; i < proc_no; i++) {
    int val = v_val(alloc, i);
    printf("%d\t\t%d\t\t", i, v_val(proc, i));
    alloc_print(val);
  }
}
