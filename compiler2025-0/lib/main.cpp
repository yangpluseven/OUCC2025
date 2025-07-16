#include "ir/type.h"
#include "ir/instructions.h"
#include <iostream>
#include <memory>

int main() {
  auto i32 = std::make_unique<ir::BasicType>(ir::BasicKind::I32);
  std::cout << i32->str() << std::endl;
  return 0;
}