// phase_4函数中的func4函数的测试代码
// func4 是一个递归二分查找路径编码函数。
// 返回值是“从根到目标值”的路径编码（左0右1）。
// 在 phase_4 中，只有输入的第一个数字 local_10 使得 func4(local_10, 0, 0xe) 返回0，且第二个数字为0，才能通过。
#include <stdio.h>

int func4(int param_1, int param_2, int param_3) {
  int iVar1;
  int iVar2;

  iVar2 = (param_3 - param_2) / 2 + param_2;
  if (param_1 < iVar2) {
    iVar1 = func4(param_1, param_2, iVar2 - 1);
    iVar1 = iVar1 * 2;
  } else {
    iVar1 = 0;
    if (iVar2 < param_1) {
      iVar2 = func4(param_1, iVar2 + 1, param_3);
      iVar1 = iVar2 * 2 + 1;
    }
  }
  return iVar1;
}

int main() {
  int param_1 = 2;
  int param_2 = 0;
  int param_3 = 14;

  int result = func4(param_1, param_2, param_3);
  printf("Result: %d\n", result);

  return 0;
}