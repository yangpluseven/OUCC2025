#include <iostream>
#include "ir/type.h"

int main() {
  auto *i32 = ir::BasicType::get(ir::BasicKind::I32);
  std::cout << i32->str() << std::endl;
  return 0;
}