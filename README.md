# SysY Compiler - RISC-V Backend Implementation (2025 Compiler System Design Contest)

This project is the preliminary round submission by **OUC/Team水军出击** for the **2025 National College Student Computer System Ability Competition - Compiler System Design Contest - Compiler Implementation Contest**.

The compiler translates **SysY language** (a subset of C) into **RISC-V RV64GC** assembly code, covering the complete compilation workflow: from lexical and syntax analysis, AST construction, intermediate representation (IR) generation and optimization, to final target assembly code generation.

---

## 🛠 Build and Usage

This project uses `CMake` as the build system and supports automatically generating the lexer and parser from `.l` (Flex) and `.y` (Bison) files.

### Dependencies

* CMake ≥ 3.10
* Flex
* Bison
* C++17 compiler (`g++` or `clang++`)

### Example: Install Dependencies on Ubuntu

```bash
sudo apt update
sudo apt install cmake flex bison g++ -y
```

### Build the Project

```bash
git clone -b compile https://github.com/yangpluseven/OUCC2025.git
cd oucc2025
mkdir build && cd build
cmake ..
make -j
```

The generated executable will be located in the `build/` directory with the default name `compiler2025-0`.

### Usage

```bash
./build/compiler2025-0 path/to/source.sy -S -o output.s
```

This command compiles a SysY source file into RISC-V assembly code.

> **Note:** The project includes locally generated `parser` and `lexer` files. You may choose to regenerate them or use the provided ones.

To view all available command-line options, use the `-h` flag:

```bash
./build/compiler2025-0 -h
```

---

## 📁 Project Structure

```text
oucc2025/
├── CMakeLists.txt        # Build configuration
├── .clang-format         # Code formatting configuration
├── README.md             # This file
├── include/              # Public header files
├── src/                  # Source code implementation
│   ├── parser/           # AST traversal & IR generation
│   ├── ir/               # IR system implementation
│   ├── pass/             # Optimization passes
│   ├── riscv/            # IR to RISC-V assembly generation
│   ├── sysy/             # Flex/Bison lexer & parser
│   ├── main.cpp          # Program entry point
├── 3rd/                  # Third-party libraries (fmt, CLI11)
├── generated/            # Auto-generated Flex/Bison code
```

---

## 🧠 Compiler Architecture Overview

### Frontend

* Uses **Flex/Bison** to build the lexer and parser
* Constructs an Abstract Syntax Tree (AST)
* Implements the **Visitor Pattern** (`accept` + `visit` double dispatch) to traverse the AST and generate intermediate representation (IR)

### Intermediate Representation (IR)

* Core design follows **LLVM IR** but is a simplified subset
* Supports function-level, basic-block-level, and instruction-level optimizations
* All IR objects are managed using smart pointers (e.g., `std::unique_ptr`)
* Optimizations implemented for the preliminary round include:

  * Dead Code Elimination (DCE)
  * Branch Optimization
  * Constant Folding (CF)
  * Memory to Register Promotion (Mem2Reg)

* Optimizations added for the final round include:

  * Strength Reduction
  * Common Subexpression Elimination (CSE)
  * Move Instruction Reduction
  * Jump Optimization
  * Loop Invariant Code Motion (LICM)

### Backend

* Uses a separately designed backend IR (referred to as **MIR**), closer to RISC-V assembly
* Initially keeps backend IR in **Static Single Assignment (SSA) form**
* Provides **machine related** optimizations.
* Applies **graph coloring register allocation** for mapping virtual registers to physical registers
* After register allocation, SSA form is broken, and appropriate prologue/epilogue code is added to produce the final **RISC-V RV64GC** assembly

---

## 📦 Third-Party Open Source Tools Used

| Name      | Purpose                 | Link                                                                       |
| --------- | ----------------------- | -------------------------------------------------------------------------- |
| **Flex**  | Lexer generator         | [https://github.com/westes/flex](https://github.com/westes/flex)           |
| **Bison** | Parser generator        | [https://www.gnu.org/software/bison/](https://www.gnu.org/software/bison/) |
| **fmt**   | Fast C++ formatting lib | [https://github.com/fmtlib/fmt](https://github.com/fmtlib/fmt)             |
| **CLI11** | Command-line parsing    | [https://github.com/CLIUtils/CLI11](https://github.com/CLIUtils/CLI11)     |

All these libraries are open-source and have been validated for stability and compatibility on mainstream platforms. The respective copyright notices are marked in the source.